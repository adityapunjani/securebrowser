 #include <QtGui>

 class QWebView;
 class QLineEdit;

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow(const QUrl& url);


 protected slots:

     void adjustLocation();
     void changeLocation();
     void adjustTitle();
     void setProgress(int p);
     void finishLoading(bool);
     void handleButton();
     void slotSourceDownloaded();
     void handleShortcut();

 private:
     QWebView *view;
     QLineEdit *locationEdit;
     QToolBar *toolBar;
     QPushButton *closebutton;
     QShortcut *endapp;
     QProcess *taskmanager;
     QLabel *plabel;

     int progress;
 };
