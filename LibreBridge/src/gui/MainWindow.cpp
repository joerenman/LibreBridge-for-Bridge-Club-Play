#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QResizeEvent>
#include <QGridLayout>
#include <QLabel>
#include <vector>
#include <iostream>
#include <QDockWidget>
#include "Common.hpp"
#include "MainWindow.hpp"
#include "ChatWindow.hpp"
#include "PlayWindow.hpp"
#include <QDebug>
#include <QStackedWidget>
#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>
#include "TableWindow.hpp"
#include "ChatSockClient.hpp"
#include "Table1SockClient.hpp"
#include "Table2SockClient.hpp"
#include "Table3SockClient.hpp"
#include "Table4SockClient.hpp"



#include <string>
#include <cstdint>


using namespace std;
extern bool PracticePlay;
extern bool PositionNorth;
extern bool PositionSouth;
extern bool iAmSeated;
extern bool Table1;
extern bool Table2;
extern bool Table3;
extern bool Table4;
extern int sessionStartDeal;
QString sessionDisplayMessage="Check who is Seated THEN take a seat, to change seat make current seat Vacant before choosing another";
QStringList userList={"Vacant","Player1","Player2","Player3","Player4","Player5","Player6","Player7","Player8",
             "Player9","Player10","Player11","Player12","Player13","Player14","Player15","Player16"};

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    ChatSockClient *socketchat = ChatSockClient::instance();
     connect(socketchat,&ChatSockClient::startDealRecd , this ,&MainWindow::setStartDeal);


    centerAndResize();
    playPageWidget=new PlayWindow(this);
    tablePageWidget = new TableWindow(this);

    connect(playPageWidget,SIGNAL (changeChatWindow()), this ,SLOT(hideShowChatWindow()));

    connect(playPageWidget,SIGNAL (backtoWelcome()), this ,SLOT(backToWelcomeWindow()));
    connect(playPageWidget,SIGNAL (backtoNewPlay()), this ,SLOT(showNewPlayWindow()));
    connect(tablePageWidget,SIGNAL (openPlayWindow()), this ,SLOT(showPlayWindow()));
    connect(tablePageWidget,SIGNAL (changeChatWindow()), this ,SLOT(hideShowChatWindow()));


    setObjectName("MainWindow"); // Otherwise all its children inherit the background color
    //setStyleSheet("#playWindow {background-color: green; }");
    setStyleSheet("#playWindow {color : white ; background-color: green; }");
    //setCentralWidget(centralWidget);

          stackedWidget = new QStackedWidget;
          stackedWidget->addWidget(playPageWidget);

          stackedWidget->addWidget(tablePageWidget);
          stackedWidget->setCurrentIndex(1);
          setCentralWidget(stackedWidget);


       chatWidget = new ChatWindow(this);
       QDockWidget *dockWidget = new QDockWidget(tr("Chat Window"), this);
         dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
         dockWidget->setWidget(chatWidget);
         addDockWidget(Qt::BottomDockWidgetArea, dockWidget);


	
	/*QPushButton* test = new QPushButton("test");
	test->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	gridLayout.addWidget(test, 1, 1);*/
		
  //  gridLayout.setColumnStretch(1, 1);
  //  gridLayout.setRowStretch(1, 1);
    //centralWidget->setLayout(&gridLayout);
	centerWindow(this);
	show();


           delete playPageWidget;
           playPageWidget=new PlayWindow(this);
           stackedWidget->insertWidget(0,playPageWidget);

}

MainWindow::~MainWindow()
{
	//destroyAllHandWidgets();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
}
void MainWindow::hideShowChatWindow()
{
     if (!chatWidget->isHidden()){    chatWidget->setHidden(true);}
     else {chatWidget->setHidden(false);}

}
void MainWindow::showPlayWindow()
{
           delete playPageWidget;
           playPageWidget=new PlayWindow(this);
           connect(playPageWidget,SIGNAL (changeChatWindow()), this ,SLOT(hideShowChatWindow()));
           connect(playPageWidget,SIGNAL (backtoWelcome()), this ,SLOT(backToWelcomeWindow()));
           connect(playPageWidget,SIGNAL (backtoNewPlay()), this ,SLOT(showNewPlayWindow()));
           stackedWidget->insertWidget(0,playPageWidget);
    stackedWidget->setCurrentIndex(0);

}
void MainWindow::showNewPlayWindow()
{
           delete playPageWidget;
           playPageWidget=new PlayWindow(this);
           connect(playPageWidget,SIGNAL (changeChatWindow()), this ,SLOT(hideShowChatWindow()));
           connect(playPageWidget,SIGNAL (backtoWelcome()), this ,SLOT(backToWelcomeWindow()));
           connect(playPageWidget,SIGNAL (backtoNewPlay()), this ,SLOT(showNewPlayWindow()));
           stackedWidget->insertWidget(0,playPageWidget);
           stackedWidget->setCurrentIndex(0);

}
void MainWindow::backToWelcomeWindow()
{
    if (!PracticePlay) {
        if (PositionNorth||PositionSouth){
        if (Table1) {ChatSockClient *socketchat = ChatSockClient::instance();
            socketchat->sendMesssage(QStringLiteral ("Seated:T1NVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T1EVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T1SVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T1WVacant"));}
        if (Table2) {ChatSockClient *socketchat = ChatSockClient::instance();
            socketchat->sendMesssage(QStringLiteral ("Seated:T2NVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T2EVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T2SVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T2WVacant"));}
        if (Table3) {ChatSockClient *socketchat = ChatSockClient::instance();
            socketchat->sendMesssage(QStringLiteral ("Seated:T3NVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T3EVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T3SVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T3WVacant"));}
        if (Table4) {ChatSockClient *socketchat = ChatSockClient::instance();
            socketchat->sendMesssage(QStringLiteral ("Seated:T4NVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T4EVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T4SVacant"));
            socketchat->sendMesssage(QStringLiteral ("Seated:T4WVacant"));}
        }
       }
    iAmSeated = false;
           stackedWidget->setCurrentIndex(1);

}
void MainWindow::closeEvent(QCloseEvent *event)
{
	QWidget::closeEvent(event);
}

void MainWindow::setStartDeal(QString message)
{
    int i = message.count("=");
    QString dealtext = message.section('=', 1, 1);
       sessionStartDeal =dealtext.toInt();
    sessionDisplayMessage = message.section('=',2,2);
    for (int idx = 3; idx<=i;idx++){
    QString Player =message.section("=",idx,idx);
    userList.replace((idx-3),  Player);
    }
        delete tablePageWidget;
        tablePageWidget=new TableWindow(this);
        connect(tablePageWidget,SIGNAL (openPlayWindow()), this ,SLOT(showPlayWindow()));
        connect(tablePageWidget,SIGNAL (changeChatWindow()), this ,SLOT(hideShowChatWindow()));
        stackedWidget->insertWidget(1,tablePageWidget);
        stackedWidget->setCurrentIndex(1);


}


void MainWindow::centerAndResize() {
    // get the dimension available on this screen
    QSize availableSize = qApp->desktop()->availableGeometry().size();
    int width = availableSize.width();
    int height = availableSize.height();
 //   qDebug() << "Available dimensions " << width << "x" << height;
    width *= 0.7; // 90% of the screen size
    height *= 0.7; // 90% of the screen size
 //   qDebug() << "Computed dimensions " << width << "x" << height;
    QSize newSize( width, height );

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            newSize,
            qApp->desktop()->availableGeometry()
        )
    );
}



