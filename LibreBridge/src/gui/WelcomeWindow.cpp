#include "Common.hpp"
#include "WelcomeWindow.hpp"
#include "PlayWindow.hpp"
#include <QPushButton>
#include <QApplication>
#include <QResizeEvent>
#include "Table1SockClient.hpp"
#include "Table2SockClient.hpp"
#include "ChatSockClient.hpp"
#include <QtWebSockets/QWebSocket>

#include <QObject>
extern bool PracticePlay;
extern bool PositionNorth;
extern bool PositionEast;
extern bool PositionSouth ;
extern bool PositionWest ;
extern bool NorthSeated ;
extern bool EastSeated ;
extern bool SouthSeated ;
extern bool WestSeated ;
extern bool Table1;
extern bool Table2;
extern bool Table3;
extern bool Table4;
extern bool Table5;
extern bool Table6;

using namespace std;
//WelcomeWindow::WelcomeWindow(QWidget *parent): QWidget(parent)
  WelcomeWindow::WelcomeWindow(QWidget *parent): QDialog(parent)

{  PracticePlay=false;
if (Table1){Table1SockClient *socket = Table1SockClient::instance();
    connect(socket,SIGNAL (PlayRecd()), this, SLOT (startLocalGame()));
      connect(socket,SIGNAL (recdNorthSeated()), this, SLOT (northSeated()));
        connect(socket,SIGNAL (recdEastSeated()), this, SLOT (eastSeated()));
          connect(socket,SIGNAL (recdSouthSeated()), this, SLOT (southSeated()));
            connect(socket,SIGNAL (recdWestSeated()), this, SLOT (westSeated()));}
if (Table2){Table2SockClient *socket = Table2SockClient::instance();
    connect(socket,SIGNAL (PlayRecd()), this, SLOT (startLocalGame()));
      connect(socket,SIGNAL (recdNorthSeated()), this, SLOT (northSeated()));
        connect(socket,SIGNAL (recdEastSeated()), this, SLOT (eastSeated()));
          connect(socket,SIGNAL (recdSouthSeated()), this, SLOT (southSeated()));
            connect(socket,SIGNAL (recdWestSeated()), this, SLOT (westSeated()));}
         // This window
            centralWidget = new QWidget(this);
            setTitle(this);
            setObjectName("welcomeWindow"); // Otherwise all its children inherit the background color
            setStyleSheet("#welcomeWindow {color : white ; background-color: green; }");
            styleSheet(); //JB
    // Background
    setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
    //QPixmap tmpBackground("./images/LibreBridge.png");
  // background = tmpBackground.scaled(MIN_WIDTH, MIN_HEIGHT, Qt::KeepAspectRatio);
    QPixmap tmpBackground("./images/LibreBridge.png");
       background = tmpBackground.scaled(this->size(), Qt::IgnoreAspectRatio);
       // QPixmap background("./images/LibreBridge.png");
        QPalette palette;
        palette.setBrush(QPalette::Background, tmpBackground);
        this->setPalette(palette);

	// quitButton
    //quitButton = new QPushButton("Quit", this);
    //quitButton->setGeometry(10, 110, 100, 30);
	/*quitButton->setFixedSize(100, 30);
	quitButton->setToolTip("Panus");
	QFont font("Courier");
	quitButton->setFont(font);
	QIcon icon("./images/LibreBridge.ico");
	quitButton->setIcon(icon);*/
    //connect(quitButton, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));

      // play as North Button
      playAsNorthButton = new QPushButton("Play as North", this);
      playAsNorthButton->setGeometry(300, 300, 120, 40);
      connect(playAsNorthButton, SIGNAL (clicked()), this, SLOT (playAsNorth()));

        // play as South Button
        playAsSouthButton = new QPushButton("Play as South", this);
        playAsSouthButton->setGeometry(300, 500, 120, 40);
        connect(playAsSouthButton, SIGNAL (clicked()), this, SLOT (playAsSouth()));

          // play as East Button
          playAsEastButton = new QPushButton("Play as East", this);
          playAsEastButton->setGeometry(500, 400, 120, 40);
          connect(playAsEastButton, SIGNAL (clicked()), this, SLOT (playAsEast()));

            // play as West Button
            playAsWestButton = new QPushButton("Play as West", this);
            playAsWestButton->setGeometry(100, 400, 120, 40);
            connect(playAsWestButton, SIGNAL (clicked()), this, SLOT (playAsWest()));

	// playButton
    playButton = new QPushButton("Practice 4 hands", this);
    playButton->setGeometry(10, 50, 140, 30);
	playButton->setFocus();
    playButton->setDefault(true);
   // connect(playButton, SIGNAL (clicked()), this, SLOT (sendPlay()));
    connect(playButton, SIGNAL (clicked()), this, SLOT (startPracticeGame()));



	setTitle(this);
	show();
    //centerWindow(this);
   // qDebug() << "Setup Welcome Window Complete";


}

void WelcomeWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
	
    //Resize background image
    QSize size = event->size();
    QPixmap tmpBackground("./images/LibreBridge.png");
    background = tmpBackground.scaled(size.width(), size.height(), Qt::IgnoreAspectRatio);
    //background =tmpBackground;
	QPalette palette;
	palette.setBrush(QPalette::Background, background);
	this->setPalette(palette);


}

void WelcomeWindow::sendPlay()
{

Table1SockClient *socket = Table1SockClient::instance();
   if (!PracticePlay) { socket->sendMesssage(QStringLiteral ("Play"));}
    PositionNorth=true;
    NorthSeated =true;
    PositionSouth=true;
    SouthSeated =true;
    PositionEast=true;
    EastSeated =true;
    PositionWest=true;
    WestSeated =true;

}
void WelcomeWindow::startPracticeGame()
{

    PracticePlay=true;
    PositionNorth=true;
    NorthSeated =true;
    PositionSouth=true;
    SouthSeated =true;
    PositionEast=true;
    EastSeated =true;
    PositionWest=true;
    WestSeated =true;
       emit openPlayWindow();
}
void WelcomeWindow::startLocalGame()
{

    PracticePlay=false;

       emit openPlayWindow();
}
void WelcomeWindow::playAsNorth()
{
  //  qDebug() << "Play as North";
    Table1SockClient *socket = Table1SockClient::instance();
        socket->sendMesssage(QStringLiteral ("Chat NorthSeated"));
        socket->sendMesssage(QStringLiteral ("NorthSeated"));
        PracticePlay=false;
    PositionNorth=true;
    NorthSeated =true;
    playAsNorthButton->setEnabled(false);
    if (EastSeated && SouthSeated && WestSeated){
      socket->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();
    //playWindow = new PlayWindow();
   // copyWindowGeometry(this, playWindow);
    //this->close();
    }
}
void WelcomeWindow::playAsSouth()
{
    qDebug() << "Play as South";
   Table1SockClient *socket = Table1SockClient::instance();
   socket->sendMesssage(QStringLiteral ("Chat SouthSeated"));
        socket->sendMesssage(QStringLiteral ("SouthSeated"));
        PracticePlay=false;
    PositionSouth=true;
    SouthSeated =true;
    playAsSouthButton->setEnabled(false);
    if (EastSeated && NorthSeated && WestSeated){
      socket->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();
   // playWindow = new PlayWindow();
   // copyWindowGeometry(this, playWindow);
   // this->close();
  }
}
void WelcomeWindow::playAsEast()
{
    qDebug() << "Play as East";
    Table1SockClient *socket = Table1SockClient::instance();
    socket->sendMesssage(QStringLiteral ("Chat EastSeated"));
        socket->sendMesssage(QStringLiteral ("EastSeated"));
        PracticePlay=false;
    PositionEast=true;
    EastSeated =true;
    playAsEastButton->setEnabled(false);
    if (NorthSeated && SouthSeated && WestSeated){
    socket->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();
  //  playWindow = new PlayWindow();
   // copyWindowGeometry(this, playWindow);
   // this->close();
    }
}
void WelcomeWindow::playAsWest()
{
    qDebug() << "Play as West";
    Table1SockClient *socket = Table1SockClient::instance();
   socket->sendMesssage(QStringLiteral ("Chat WestSeated"));
       socket->sendMesssage(QStringLiteral ("WestSeated"));
       PracticePlay=false;
    PositionWest=true;NorthSeated=true;
    WestSeated =true;
    playAsWestButton->setEnabled(false);
    if (EastSeated && SouthSeated && NorthSeated){
     socket->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();
   // playWindow = new PlayWindow();
  //  copyWindowGeometry(this, playWindow);
  //  this->close();
    }
}
void WelcomeWindow::northSeated()
{
    NorthSeated =true;
    playAsNorthButton->setEnabled(false);
}
void WelcomeWindow::eastSeated()
{
    EastSeated =true;
    playAsEastButton->setEnabled(false);
}
void WelcomeWindow::southSeated()
{
    SouthSeated =true;
    playAsSouthButton->setEnabled(false);
}
void WelcomeWindow::westSeated()
{
    WestSeated =true;
    playAsWestButton->setEnabled(false);

}
