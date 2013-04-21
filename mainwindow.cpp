
 #include <QtGui>
 #include <QtWebKit>
 #include "mainwindow.h"
 #include <QNetworkProxyFactory>
 #include <QNetworkReply>


 MainWindow::MainWindow(const QUrl& url)
 {
     progress = 0;

     QNetworkProxyFactory::setUseSystemConfiguration(true);

     endapp = new QShortcut(this);
     endapp->setKey(Qt::CTRL + Qt::SHIFT + Qt::Key_P);
     connect(endapp, SIGNAL(activated()), SLOT(handleShortcut()));
     view = new QWebView(this);
     view->load(url);

     connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
     connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
     connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
     connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

     locationEdit = new QLineEdit(this);
     locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
     connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

     toolBar = addToolBar(tr("Navigation"));
     toolBar->addAction(view->pageAction(QWebPage::Back));
     toolBar->addAction(view->pageAction(QWebPage::Forward));
     toolBar->addAction(view->pageAction(QWebPage::Reload));
     toolBar->addAction(view->pageAction(QWebPage::Stop));
     toolBar->addWidget(locationEdit);
     plabel= new QLabel(this);
     plabel->setMargin(3);
     toolBar->addWidget(plabel);
     plabel->setText("Loaded 100%");
     closebutton = new QPushButton(tr("Close"), this);
     closebutton->setDisabled(1);
     toolBar->addWidget(closebutton);
     connect(closebutton, SIGNAL(clicked()), SLOT(handleButton()));
     setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint );
     setCentralWidget(view);
     setUnifiedTitleAndToolBarOnMac(true);
     locationEdit->setDisabled(1);

 }

 void MainWindow::slotSourceDownloaded()
 {
     QNetworkReply* reply = qobject_cast<QNetworkReply*>(const_cast<QObject*>(sender()));
     QTextEdit* textEdit = new QTextEdit(NULL);
     reply->ignoreSslErrors();
     textEdit->setAttribute(Qt::WA_DeleteOnClose);
     textEdit->show();
     textEdit->setPlainText(reply->readAll());
     reply->deleteLater();
 }

 void MainWindow::adjustLocation()
 {
     locationEdit->setText(view->url().toString());
 }

 void MainWindow::changeLocation()
 {

     QUrl url = QUrl(locationEdit->text());
     view->load(url);
     view->setFocus();

 }

 void MainWindow::adjustTitle()
 {
     if (progress <= 0 || progress >= 100)
         plabel->setText("Loaded 100%");
     else
          plabel->setText(QString("Loading %1%").arg(progress));
 }

 void MainWindow::setProgress(int p)
 {
     progress = p;
     adjustTitle();
 }

 void MainWindow::finishLoading(bool)
 {
     closebutton->setDisabled(1);
     progress = 100;
     adjustTitle();
     QString link = locationEdit->text();
     if(link.contains("="))
     closebutton->setDisabled(0);

 }

 void MainWindow::handleButton()
 {
          QMessageBox* msgBox = new QMessageBox(this);
          msgBox->setIcon(QMessageBox::Warning);
          msgBox->setText("Are you sure you want to quit the application?");
          msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
          msgBox->setDefaultButton(QMessageBox::Cancel);
          int ret = msgBox->exec();
          if (ret==QMessageBox::Ok)
          qApp->quit();

 }

 void MainWindow::handleShortcut()
 {
     qApp->quit();
 }
