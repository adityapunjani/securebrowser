 #include <QtGui>
 #include "mainwindow.h"

 int main(int argc, char * argv[])
 {
     QApplication app(argc, argv);
     QUrl url;
     if (argc > 1)
         url = QUrl(argv[1]);
     else
         url = QUrl("https://www.google.com/");
     MainWindow *browser = new MainWindow(url);
     browser->showFullScreen();
     return app.exec();

 }
