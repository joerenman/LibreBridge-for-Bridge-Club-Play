#include "TableWindow.hpp"
//#include "ui_tablewindow.hpp"
#include "Common.hpp"
#include "WelcomeWindow.hpp"
#include "PlayWindow.hpp"
#include <QPushButton>
#include <QApplication>
#include <QResizeEvent>
#include "Table1SockClient.hpp"
#include "Table2SockClient.hpp"
#include "Table3SockClient.hpp"
#include "Table4SockClient.hpp"
#include "ChatSockClient.hpp"
#include <QtWebSockets/QWebSocket>
#include <QComboBox>
#include <QGroupBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include "Common.hpp"


#include <QObject>
extern QString WebAddress;
extern bool PracticePlay;
extern bool PositionNorth;
extern bool PositionEast;
extern bool PositionSouth ;
extern bool PositionWest ;
extern bool NorthSeated ;
extern bool EastSeated ;
extern bool SouthSeated ;
extern bool WestSeated ;
extern bool iAmSeated;
extern bool Table1;
extern bool Table2;
extern bool Table3;
extern bool Table4;
extern bool Table5;
extern bool Table6;

extern QString sessionDisplayMessage;
extern QStringList userList;
bool statusResponder = true;
QString T1NPlayer;
QString T1SPlayer;
QString T1EPlayer;
QString T1WPlayer;
QString T2NPlayer;
QString T2SPlayer;
QString T2EPlayer;
QString T2WPlayer;
QString T3NPlayer;
QString T3SPlayer;
QString T3EPlayer;
QString T3WPlayer;
QString T4NPlayer;
QString T4SPlayer;
QString T4EPlayer;
QString T4WPlayer;




using namespace std;
  TableWindow::TableWindow(QWidget *parent): QDialog(parent)

{
     centralWidget = new QWidget(this);
     setTitle(this);
     setObjectName("tableWindow"); // Otherwise all its children inherit the background color
     setStyleSheet("#tableWindow {color : white ; background-color: green; }");
     styleSheet();

    table1 = new QGroupBox(this);
    table1->setGeometry(30,50,340,270);
    //table1->setTitle("Table 1");

    QTextEdit *sessionDisplay = new QTextEdit(this);
    sessionDisplay ->move(800,10);
    sessionDisplay->setFixedHeight(350);
    sessionDisplay->setFixedWidth(300);
    sessionDisplay->setFontPointSize(10);

    sessionDisplay->setText(sessionDisplayMessage);

    QGridLayout *TABLE1 = new QGridLayout(this);
    t1Label = new QLabel();
    t1Label->setText("  Table 1");
    QFont font("Courier");
    t1Label->setFont(font);
   // t1Label->setFixedSize(200,90);
    t1Label->setGeometry(100,110,96,29);
    T1NBox = new QComboBox(this);
    T1NBox->setGeometry(90,40,96,29);
     for (int index = 0; index < userList.size(); index++)
      {  T1NBox->addItem(userList.at(index));}
    connect(T1NBox, SIGNAL(activated(int)), this, SLOT(T1NChanged(int)));

    T1EBox = new QComboBox(this);
    for (int index = 0; index < userList.size(); index++)
      {  T1EBox->addItem(userList.at(index));};
    connect(T1EBox, SIGNAL(activated(int)), this, SLOT(T1EChanged(int)));

    T1WBox = new QComboBox(this);
    T1WBox->setGeometry(0,110,96,29);
    for (int index = 0; index < userList.size(); index++)
      {  T1WBox->addItem(userList.at(index));}
    connect(T1WBox, SIGNAL(activated(int)), this, SLOT(T1WChanged(int)));


    T1SBox = new QComboBox(this);
    T1SBox->setGeometry(90,200,96,29);
    for (int index = 0; index < userList.size(); index++)
      {  T1SBox->addItem(userList.at(index));}
    connect(T1SBox, SIGNAL(activated(int)), this, SLOT(T1SChanged(int)));


    TABLE1->addWidget(T1NBox,0,1);
    TABLE1->addWidget(T1EBox,1,2);
    TABLE1->addWidget(T1SBox,2,1);
    TABLE1->addWidget(T1WBox,1,0);
    TABLE1->addWidget(t1Label,1,1);


    table1->setLayout(TABLE1);
    table1->show();
////////////////////Table 2
////
    table2 = new QGroupBox(this);
    table2->setGeometry(420,50,340,270);
    //table2->setTitle("Table 1");

   QGridLayout *TABLE2 = new QGridLayout(this);
    t2Label = new QLabel();
    t2Label->setText("  Table 2");

    t2Label->setFont(font);
   // t2Label->setFixedSize(200,90);
    t2Label->setGeometry(100,110,96,29);
    T2NBox = new QComboBox(this);
    T2NBox->setGeometry(90,40,96,29);
    for (int index = 0; index < userList.size(); index++)
      {  T2NBox->addItem(userList.at(index));}
    connect(T2NBox, SIGNAL(activated(int)), this, SLOT(T2NChanged(int)));

    T2EBox = new QComboBox(this);
    T2EBox->setGeometry(220,110,96,29);
    for (int index = 0; index < userList.size(); index++)
      {  T2EBox->addItem(userList.at(index));}
    connect(T2EBox, SIGNAL(activated(int)), this, SLOT(T2EChanged(int)));

    T2WBox = new QComboBox(this);
    T2WBox->setGeometry(0,110,96,29);
    for (int index = 0; index < userList.size(); index++)
      {  T2WBox->addItem(userList.at(index));}
    connect(T2WBox, SIGNAL(activated(int)), this, SLOT(T2WChanged(int)));

    T2SBox = new QComboBox(this);
    T2SBox->setGeometry(90,200,96,29);
    for (int index = 0; index < userList.size(); index++)
      {  T2SBox->addItem(userList.at(index));}
    connect(T2SBox, SIGNAL(activated(int)), this, SLOT(T2SChanged(int)));


    TABLE2->addWidget(T2NBox,0,1);
    TABLE2->addWidget(T2EBox,1,2);
    TABLE2->addWidget(T2SBox,2,1);
    TABLE2->addWidget(T2WBox,1,0);
    TABLE2->addWidget(t2Label,1,1);
  //  T2NBox->show();
    table2->setLayout(TABLE2);
    table2->show();


    table3 = new QGroupBox(this);
       table3->setGeometry(30,300,340,270);
    QGridLayout *TABLE3 = new QGridLayout(this);
     t3Label = new QLabel();
     t3Label->setText("  Table 3");

     t3Label->setFont(font);
    // t3Label->setFixedSize(300,90);
  //   t3Label->setGeometry(100,110,96,39);
     T3NBox = new QComboBox(this);
     T3NBox->setGeometry(90,40,96,39);
     for (int index = 0; index < userList.size(); index++)
       {  T3NBox->addItem(userList.at(index));}
     connect(T3NBox, SIGNAL(activated(int)), this, SLOT(T3NChanged(int)));

     T3EBox = new QComboBox(this);
     T3EBox->setGeometry(330,110,96,39);
     for (int index = 0; index < userList.size(); index++)
       {  T3EBox->addItem(userList.at(index));}
     connect(T3EBox, SIGNAL(activated(int)), this, SLOT(T3EChanged(int)));

     T3WBox = new QComboBox(this);
     T3WBox->setGeometry(0,110,96,39);
     for (int index = 0; index < userList.size(); index++)
       {  T3WBox->addItem(userList.at(index));}
     connect(T3WBox, SIGNAL(activated(int)), this, SLOT(T3WChanged(int)));

     T3SBox = new QComboBox(this);
     T3SBox->setGeometry(90,300,96,39);
     for (int index = 0; index < userList.size(); index++)
       {  T3SBox->addItem(userList.at(index));}
     connect(T3SBox, SIGNAL(activated(int)), this, SLOT(T3SChanged(int)));

     TABLE3->addWidget(T3NBox,0,1);
     TABLE3->addWidget(T3EBox,1,3);
     TABLE3->addWidget(T3SBox,3,1);
     TABLE3->addWidget(T3WBox,1,0);
     TABLE3->addWidget(t3Label,1,1);

     table3->setLayout(TABLE3);
     table3->show();


     table4 = new QGroupBox(this);
        table4->setGeometry(420,300,340,270);
      QGridLayout *TABLE4 = new QGridLayout(this);
      t4Label = new QLabel();
      t4Label->setText("  Table 4");

      t4Label->setFont(font);
     // t4Label->setFixedSize(400,90);
      t4Label->setGeometry(100,110,96,49);
      T4NBox = new QComboBox(this);
      T4NBox->setGeometry(90,40,96,49);
      for (int index = 0; index < userList.size(); index++)
        {  T4NBox->addItem(userList.at(index));}
      connect(T4NBox, SIGNAL(activated(int)), this, SLOT(T4NChanged(int)));

      T4EBox = new QComboBox(this);
      T4EBox->setGeometry(440,110,96,49);
      for (int index = 0; index < userList.size(); index++)
        {  T4EBox->addItem(userList.at(index));}
      connect(T4EBox, SIGNAL(activated(int)), this, SLOT(T4EChanged(int)));

      T4WBox = new QComboBox(this);
      T4WBox->setGeometry(0,110,96,49);
      for (int index = 0; index < userList.size(); index++)
        {  T4WBox->addItem(userList.at(index));}
      connect(T4WBox, SIGNAL(activated(int)), this, SLOT(T4WChanged(int)));

      T4SBox = new QComboBox(this);
      T4SBox->setGeometry(90,400,96,49);
      for (int index = 0; index < userList.size(); index++)
        {  T4SBox->addItem(userList.at(index));}
      connect(T4SBox, SIGNAL(activated(int)), this, SLOT(T4SChanged(int)));


      TABLE4->addWidget(T4NBox,0,1);
      TABLE4->addWidget(T4EBox,1,4);
      TABLE4->addWidget(T4SBox,4,1);
      TABLE4->addWidget(T4WBox,1,0);
      TABLE4->addWidget(t4Label,1,1);

      table4->setLayout(TABLE4);
      table4->show();


      ChatSockClient *socketchat = ChatSockClient::instance();

       connect(socketchat,&ChatSockClient::seatStatusChangeRecd , this ,&TableWindow::seatingStatusChanged);
       connect(socketchat,&ChatSockClient::seatStatusRequestRecd , this ,&TableWindow::provideSeatingStatus);

       // playButton
       practiceButton = new QPushButton("Practice 4 hands", this);
       practiceButton->setGeometry(800, 500, 200, 40);
       practiceButton->setFocus();
       practiceButton->setDefault(true);
       connect(practiceButton, SIGNAL (clicked()), this, SLOT (startPracticeGame()));

       seatStatusButton = new QPushButton("Show Who is Seated", this);
       seatStatusButton->setGeometry(800, 450, 200, 40);
       seatStatusButton->setFocus();
       seatStatusButton->setDefault(true);
       connect(seatStatusButton, SIGNAL (clicked()), this, SLOT (requestSeatingStatus()));

       QPushButton *hideChatButton = new QPushButton("Hide/Show Chat", this);
       hideChatButton->setGeometry(800, 400, 200, 40);
       connect(hideChatButton, SIGNAL (clicked()), this, SLOT (hideChatWindow()));

       setTitle(this);
       show();
  }

void TableWindow::seatingStatusChanged(QString message)
{  // statusResponder=false;
    message.remove(0,7);
    QString positiontext = message.left(3);
    QString playertext = message.mid(3,9);

    if (positiontext=="T1N") {T1NBox->setCurrentText(playertext);T1NBox->setStyleSheet("QComboBox { background-color: red; }");
        T1NPlayer=playertext;NorthSeated=true;
        if (playertext=="Vacant"){NorthSeated =false;T1NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T1E") {T1EBox->setCurrentText(playertext);T1EBox->setStyleSheet("QComboBox { background-color: red; }");
        T1EPlayer=playertext;EastSeated=true;
        if (playertext=="Vacant"){EastSeated =false;T1EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T1S") {T1SBox->setCurrentText(playertext);T1SBox->setStyleSheet("QComboBox { background-color: red; }");
        T1SPlayer=playertext;SouthSeated=true;
        if (playertext=="Vacant"){SouthSeated =false;T1SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T1W") {T1WBox->setCurrentText(playertext);T1WBox->setStyleSheet("QComboBox { background-color: red; }");
        T1WPlayer=playertext;WestSeated=true;
        if (playertext=="Vacant"){WestSeated =false;T1WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T2N") {T2NBox->setCurrentText(playertext);T2NBox->setStyleSheet("QComboBox { background-color: red; }");
        T2NPlayer=playertext;NorthSeated=true;
        if (playertext=="Vacant"){NorthSeated =false;T2NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T2E") {T2EBox->setCurrentText(playertext);T2EBox->setStyleSheet("QComboBox { background-color: red; }");
        T2EPlayer=playertext;EastSeated=true;
        if (playertext=="Vacant"){EastSeated =false;T2EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T2S") {T2SBox->setCurrentText(playertext);T2SBox->setStyleSheet("QComboBox { background-color: red; }");
        T2SPlayer=playertext;SouthSeated=true;
        if (playertext=="Vacant"){SouthSeated =false;T2SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T2W") {T2WBox->setCurrentText(playertext);T2WBox->setStyleSheet("QComboBox { background-color: red; }");
        T2WPlayer=playertext;WestSeated=true;
        if (playertext=="Vacant"){WestSeated =false;T2WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T3N") {T3NBox->setCurrentText(playertext);T3NBox->setStyleSheet("QComboBox { background-color: red; }");
        T3NPlayer=playertext;NorthSeated=true;
        if (playertext=="Vacant"){NorthSeated =false;T3NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T3E") {T3EBox->setCurrentText(playertext);T2EBox->setStyleSheet("QComboBox { background-color: red; }");
        T3EPlayer=playertext;EastSeated=true;
        if (playertext=="Vacant"){EastSeated =false;T2EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T3S") {T3SBox->setCurrentText(playertext);T3SBox->setStyleSheet("QComboBox { background-color: red; }");
        T3SPlayer=playertext;SouthSeated=true;
        if (playertext=="Vacant"){SouthSeated =false;T3SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T3W") {T3WBox->setCurrentText(playertext);T3WBox->setStyleSheet("QComboBox { background-color: red; }");
        T3WPlayer=playertext;WestSeated=true;
        if (playertext=="Vacant"){WestSeated =false;T3WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T4N") {T4NBox->setCurrentText(playertext);T4NBox->setStyleSheet("QComboBox { background-color: red; }");
        T4NPlayer=playertext;NorthSeated=true;
        if (playertext=="Vacant"){NorthSeated =false;T4NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T4E") {T4EBox->setCurrentText(playertext);T4WBox->setStyleSheet("QComboBox { background-color: red; }");
        T4EPlayer=playertext;EastSeated=true;
        if (playertext=="Vacant"){EastSeated =false;T4EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T4S") {T4SBox->setCurrentText(playertext);T4SBox->setStyleSheet("QComboBox { background-color: red; }");
        T4SPlayer=playertext;SouthSeated=true;
        if (playertext=="Vacant"){SouthSeated =false;T4SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}
    if (positiontext=="T4W") {T4WBox->setCurrentText(playertext);T4WBox->setStyleSheet("QComboBox { background-color: red; }");
        T4WPlayer=playertext;WestSeated=true;
        if (playertext=="Vacant"){WestSeated =false;T4WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}}

    if (Table1&&(T1EBox->currentText()!="Vacant")&&(T1SBox->currentText()!="Vacant")&&(T1WBox->currentText()!="Vacant")&&(T1NBox->currentText()!="Vacant"))
    {emit openPlayWindow(); }
    if (Table2&&(T2EBox->currentText()!="Vacant")&&(T2SBox->currentText()!="Vacant")&&(T2WBox->currentText()!="Vacant")&&(T2NBox->currentText()!="Vacant"))
    {emit openPlayWindow(); }
    if (Table3&&(T3EBox->currentText()!="Vacant")&&(T3SBox->currentText()!="Vacant")&&(T3WBox->currentText()!="Vacant")&&(T3NBox->currentText()!="Vacant"))
    {emit openPlayWindow(); }
    if (Table4&&(T4EBox->currentText()!="Vacant")&&(T4SBox->currentText()!="Vacant")&&(T4WBox->currentText()!="Vacant")&&(T4NBox->currentText()!="Vacant"))
    {emit openPlayWindow(); }
}
void TableWindow::requestSeatingStatus()
{
    ChatSockClient *socketchat = ChatSockClient::instance();
    QString message =("SeatStatusRequest");
    socketchat->sendMesssage(QString (message));

}
void TableWindow::hideChatWindow()
{
   emit changeChatWindow();

}
void TableWindow::provideSeatingStatus()
{ // if (statusResponder)
    {
    ChatSockClient *socketchat = ChatSockClient::instance();
    QString message;QString Player;
    if (Table1){
 if (T1NBox->currentText()!="Vacant"){message = ("Seated:T1N");Player=T1NBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T1EBox->currentText()!="Vacant"){message = ("Seated:T1E");Player=T1EBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T1SBox->currentText()!="Vacant"){message = ("Seated:T1S");Player=T1SBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T1WBox->currentText()!="Vacant"){message = ("Seated:T1W");Player=T1WBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
     }
    if (Table2){
 if (T2NBox->currentText()!="Vacant"){message = ("Seated:T2N");Player=T2NBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T2EBox->currentText()!="Vacant"){message = ("Seated:T2E");Player=T2EBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T2SBox->currentText()!="Vacant"){message = ("Seated:T2S");Player=T2SBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T2WBox->currentText()!="Vacant"){message = ("Seated:T2W");Player=T2WBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
     }
    if (Table3){
 if (T3NBox->currentText()!="Vacant"){message = ("Seated:T3N");Player=T3NBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T3EBox->currentText()!="Vacant"){message = ("Seated:T3E");Player=T3EBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T3SBox->currentText()!="Vacant"){message = ("Seated:T3S");Player=T3SBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T3WBox->currentText()!="Vacant"){message = ("Seated:T3W");Player=T3WBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
    }
    if (Table4){
 if (T4NBox->currentText()!="Vacant"){message = ("Seated:T4N");Player=T4NBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T4EBox->currentText()!="Vacant"){message = ("Seated:T4E");Player=T4EBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T4SBox->currentText()!="Vacant"){message = ("Seated:T4S");Player=T4SBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
 if (T4WBox->currentText()!="Vacant"){message = ("Seated:T4W");Player=T4WBox->currentText();message.append(Player);socketchat->sendMesssage(QString (message));}
      }
    }
}
void TableWindow::startPracticeGame()
{
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

void TableWindow::PlayGame()
{
   if (iAmSeated) { emit openPlayWindow();}
}
void TableWindow::T1NChanged(int index)
{
    if (iAmSeated  && (index==0)) {PositionNorth=false;NorthSeated=false;Table1=false;iAmSeated = false;
        T1NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}

     if (iAmSeated && (index!=0)) { T1NBox ->setCurrentIndex(0);}
    if (!iAmSeated ){   T1NBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T1N");
    T1NPlayer=userList.at(index);
    message.append(T1NPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table1SockClient *socket = Table1SockClient::instance();
         connect(socket,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=true;Table2=false;Table3=false;Table4=false;
    PracticePlay=false;
    PositionNorth=true;PositionEast=false;PositionSouth=false;PositionWest=false;
    NorthSeated=true;EastSeated=false;SouthSeated=false;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T1NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table1 && (index!=0)&&(T1EBox->currentText()!="Vacant")&&(T1SBox->currentText()!="Vacant")&&(T1WBox->currentText()!="Vacant"))
    {   Table1SockClient *socket = Table1SockClient::instance();
        socket->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow(); }
     }
}
void TableWindow::T1EChanged(int index)
{     if (iAmSeated && (index==0)) {PositionEast=false;EastSeated=false;Table1=false;iAmSeated = false;
        T1EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (iAmSeated && (index!=0)) { T1EBox ->setCurrentIndex(0);}
    if (!iAmSeated ){
    T1EBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T1E");
    T1EPlayer=userList.at(index);
    message.append(T1EPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table1SockClient *socket = Table1SockClient::instance();
         connect(socket,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=true;Table2=false;Table3=false;Table4=false;
    PracticePlay=false;
    PositionNorth=false;PositionEast=true;PositionSouth=false;PositionWest=false;
    NorthSeated=false;EastSeated=true;SouthSeated=false;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T1EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table1 &&(index!=0)&&(T1NBox->currentText()!="Vacant")&&(T1SBox->currentText()!="Vacant")&&(T1WBox->currentText()!="Vacant"))
    {Table1SockClient *socket = Table1SockClient::instance();
        socket->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();}
      }
}
void TableWindow::T1SChanged(int index)
{
    if (iAmSeated && (index==0)) {PositionSouth=false;SouthSeated=false;Table1=false;iAmSeated = false;
        T1SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T1SBox ->setCurrentIndex(0);}
    if (!iAmSeated ){
    T1SBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T1S");
    T1SPlayer=userList.at(index);
    message.append(T1SPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table1SockClient *socket = Table1SockClient::instance();
         connect(socket,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=true;Table2=false;Table3=false;Table4=false;
    PracticePlay=false;
    PositionNorth=false;PositionEast=false;PositionSouth=true;PositionWest=false;
    NorthSeated=false;EastSeated=false;SouthSeated=true;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T1SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table1 &&(index!=0) &&(T1NBox->currentText()!="Vacant")&&(T1EBox->currentText()!="Vacant")&&(T1WBox->currentText()!="Vacant"))
    {Table1SockClient *socket = Table1SockClient::instance();
        socket->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();}
}
}
void TableWindow::T1WChanged(int index)
{
    if (iAmSeated && (index==0)) {PositionWest=false;WestSeated=false;Table1=false;iAmSeated = false;
        T1WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T1WBox ->setCurrentIndex(0);}
    if (!iAmSeated ){
    T1WBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T1W");
    T1WPlayer=userList.at(index);
    message.append(T1WPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table1SockClient *socket = Table1SockClient::instance();
         connect(socket,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=true;Table2=false;Table3=false;Table4=false;
    PracticePlay=false;
    PositionNorth=false;PositionEast=false;PositionSouth=false;PositionWest=true;
    NorthSeated=false;EastSeated=false;SouthSeated=false;WestSeated=true;iAmSeated =true;
    if (index==0){iAmSeated=false;T1WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table1 &&(index!=0)&&(T1NBox->currentText()!="Vacant")&&(T1EBox->currentText()!="Vacant")&&(T1SBox->currentText()!="Vacant"))
   { Table1SockClient *socket = Table1SockClient::instance();
    socket->sendMesssage(QStringLiteral ("Play"));
    emit openPlayWindow();}
}
}
void TableWindow::T2NChanged(int index)
{   if (iAmSeated && (index==0)) {PositionNorth=false;NorthSeated=false;Table2=false;iAmSeated = false;
        T2NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T2NBox ->setCurrentIndex(0);}
    if (!iAmSeated ){
    T2NBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T2N");
    T2NPlayer=userList.at(index);
    message.append(T2NPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table2SockClient *socket2 = Table2SockClient::instance();
         connect(socket2,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=true;Table3=false;Table4=false;
    PracticePlay=false;
    PositionNorth=true;PositionEast=false;PositionSouth=false;PositionWest=false;
    NorthSeated=true;EastSeated=false;SouthSeated=false;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T2NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table2 &&(index!=0)&&(T2EBox->currentText()!="Vacant")&&(T2SBox->currentText()!="Vacant")&&(T2WBox->currentText()!="Vacant"))
    {   Table2SockClient *socket2 = Table2SockClient::instance();
        socket2->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow(); }
     }
}
void TableWindow::T2EChanged(int index)
{  if (iAmSeated && (index==0)) {PositionEast=false;EastSeated=false;Table2=false;iAmSeated = false;
        T2EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T2EBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T2EBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T2E");
    T2EPlayer=userList.at(index);
    message.append(T2EPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table2SockClient *socket2 = Table2SockClient::instance();
         connect(socket2,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=true;Table3=false;Table4=false;
    PracticePlay=false;
    PositionNorth=false;PositionEast=true;PositionSouth=false;PositionWest=false;
    NorthSeated=false;EastSeated=true;SouthSeated=false;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T2EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table2 &&(index!=0)&&(T2NBox->currentText()!="Vacant")&&(T2SBox->currentText()!="Vacant")&&(T2WBox->currentText()!="Vacant"))
    {Table2SockClient *socket2 = Table2SockClient::instance();
        socket2->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();}
      }
}
void TableWindow::T2SChanged(int index)
{  if (iAmSeated && (index==0)) {PositionSouth=false;SouthSeated=false;Table2=false;iAmSeated = false;
        T2SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T2SBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T2SBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T2S");
    T2SPlayer=userList.at(index);
    message.append(T2SPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table2SockClient *socket2 = Table2SockClient::instance();
         connect(socket2,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=true;Table3=false;Table4=false;
    PracticePlay=false;
    PositionNorth=false;PositionEast=false;PositionSouth=true;PositionWest=false;
    NorthSeated=false;EastSeated=false;SouthSeated=true;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T2SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table2 &&(index!=0)&&(T2NBox->currentText()!="Vacant")&&(T2EBox->currentText()!="Vacant")&&(T2WBox->currentText()!="Vacant"))
    {Table2SockClient *socket2 = Table2SockClient::instance();
        socket2->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();}
   }
}
void TableWindow::T2WChanged(int index)
{   if (iAmSeated && (index==0)) {PositionWest=false;WestSeated=false;Table2=false;iAmSeated = false;
        T2WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T2WBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T2WBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T2W");
    T2WPlayer=userList.at(index);
    message.append(T2WPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table2SockClient *socket2 = Table2SockClient::instance();
         connect(socket2,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=true;Table3=false;Table4=false;
    PracticePlay=false;
    PositionNorth=false;PositionEast=false;PositionSouth=false;PositionWest=true;
    NorthSeated=false;EastSeated=false;SouthSeated=false;WestSeated=true;iAmSeated =true;
    if (index==0){iAmSeated=false;T2WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table2 &&(index!=0)&&(T2NBox->currentText()!="Vacant")&&(T2EBox->currentText()!="Vacant")&&(T2SBox->currentText()!="Vacant"))
   { Table2SockClient *socket2 = Table2SockClient::instance();
    socket2->sendMesssage(QStringLiteral ("Play"));
    emit openPlayWindow();}
}
}
void TableWindow::T3NChanged(int index)
{  if (iAmSeated && (index==0)) {PositionNorth=false;NorthSeated=false;Table3=false;iAmSeated = false;
        T3NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T3NBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T3NBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T3N");
    T3NPlayer=userList.at(index);
    message.append(T3NPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table3SockClient *socket3 = Table3SockClient::instance();
         connect(socket3,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=false;Table3=true;Table4=false;
    PracticePlay=false;
    PositionNorth=true;PositionEast=false;PositionSouth=false;PositionWest=false;
    NorthSeated=true;EastSeated=false;SouthSeated=false;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T3NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table3 &&(index!=0)&&(T3EBox->currentText()!="Vacant")&&(T3SBox->currentText()!="Vacant")&&(T3WBox->currentText()!="Vacant"))
    {   Table3SockClient *socket3 = Table3SockClient::instance();
        socket3->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow(); }
     }
}
void TableWindow::T3EChanged(int index)
{  if (iAmSeated && (index==0)) {PositionEast=false;EastSeated=false;Table3=false;iAmSeated = false;
        T3EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T3EBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T3EBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T3E");
    T3EPlayer=userList.at(index);
    message.append(T3EPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table3SockClient *socket3 = Table3SockClient::instance();
         connect(socket3,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=false;Table3=true;Table4=false;
    PracticePlay=false;
    PositionNorth=false;PositionEast=true;PositionSouth=false;PositionWest=false;
    NorthSeated=false;EastSeated=true;SouthSeated=false;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T3EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table3 &&(index!=0)&&(T3NBox->currentText()!="Vacant")&&(T3SBox->currentText()!="Vacant")&&(T3WBox->currentText()!="Vacant"))
    {Table3SockClient *socket3 = Table3SockClient::instance();
        socket3->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();}
      }
}
void TableWindow::T3SChanged(int index)
{  if (iAmSeated && (index==0)) {PositionSouth=false;SouthSeated=false;Table3=false;iAmSeated = false;
        T3SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T3SBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T3SBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T3S");
    T3SPlayer=userList.at(index);
    message.append(T3SPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table3SockClient *socket3 = Table3SockClient::instance();
         connect(socket3,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=false;Table3=true;Table4=false;
    PracticePlay=false;
    PositionNorth=false;PositionEast=false;PositionSouth=true;PositionWest=false;
    NorthSeated=false;EastSeated=false;SouthSeated=true;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T3SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table3 &&(index!=0)&&(T3NBox->currentText()!="Vacant")&&(T3EBox->currentText()!="Vacant")&&(T3WBox->currentText()!="Vacant"))
    {Table3SockClient *socket3 = Table3SockClient::instance();
        socket3->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();}
}
}
void TableWindow::T3WChanged(int index)
{  if (iAmSeated && (index==0)) {PositionWest=false;WestSeated=false;Table3=false;iAmSeated = false;
        T3WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T3WBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T3WBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T3W");
    T3WPlayer=userList.at(index);
    message.append(T3WPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table3SockClient *socket3 = Table3SockClient::instance();
         connect(socket3,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table3=false;Table2=false;Table3=true;Table4=false;
    PracticePlay=false;
    PositionNorth=false;PositionEast=false;PositionSouth=false;PositionWest=true;
    NorthSeated=false;EastSeated=false;SouthSeated=false;WestSeated=true;iAmSeated =true;
    if (index==0){iAmSeated=false;T3WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table1 &&(index!=0)&&(T3NBox->currentText()!="Vacant")&&(T3EBox->currentText()!="Vacant")&&(T3SBox->currentText()!="Vacant"))
   { Table3SockClient *socket3 = Table3SockClient::instance();
    socket3->sendMesssage(QStringLiteral ("Play"));
    emit openPlayWindow();}
}
}
void TableWindow::T4NChanged(int index)
{   if (iAmSeated && (index==0)) {PositionNorth=false;NorthSeated=false;iAmSeated = false;
        T4NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T4NBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T4NBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T4N");
    T4NPlayer=userList.at(index);
    message.append(T4NPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table4SockClient *socket4 = Table4SockClient::instance();
         connect(socket4,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=false;Table3=false;Table4=true;
    PracticePlay=false;
    PositionNorth=true;PositionEast=false;PositionSouth=false;PositionWest=false;
    NorthSeated=true;EastSeated=false;SouthSeated=false;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T4NBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table4 &&(index!=0)&&(T4EBox->currentText()!="Vacant")&&(T4SBox->currentText()!="Vacant")&&(T4WBox->currentText()!="Vacant"))
    {   Table4SockClient *socket4 = Table4SockClient::instance();
        socket4->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow(); }
     }
}
void TableWindow::T4EChanged(int index)
{   if (iAmSeated && (index==0)) {PositionEast=false;EastSeated=false;iAmSeated = false;
        T4EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T4EBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T4EBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T4E");
    T4EPlayer=userList.at(index);
    message.append(T4EPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table4SockClient *socket4 = Table4SockClient::instance();
         connect(socket4,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=false;Table3=false;Table4=true;
    PracticePlay=false;
    PositionNorth=false;PositionEast=true;PositionSouth=false;PositionWest=false;
    NorthSeated=false;EastSeated=true;SouthSeated=false;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T4EBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table4 &&(index!=0)&&(T4NBox->currentText()!="Vacant")&&(T4SBox->currentText()!="Vacant")&&(T4WBox->currentText()!="Vacant"))
    {Table4SockClient *socket4 = Table4SockClient::instance();
        socket4->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();}
      }
}
void TableWindow::T4SChanged(int index)
{   if (iAmSeated && (index==0)) {PositionSouth=false;SouthSeated=false;iAmSeated = false;
        T4SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T4SBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T4SBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T4S");
    T4SPlayer=userList.at(index);
    message.append(T4SPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table4SockClient *socket4 = Table4SockClient::instance();
         connect(socket4,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=false;Table3=false;Table4=true;
    PracticePlay=false;
    PositionNorth=false;PositionEast=false;PositionSouth=true;PositionWest=false;
    NorthSeated=false;EastSeated=false;SouthSeated=true;WestSeated=false;iAmSeated =true;
    if (index==0){iAmSeated=false;T4SBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table4 &&(index!=0)&&(T4NBox->currentText()!="Vacant")&&(T4EBox->currentText()!="Vacant")&&(T4WBox->currentText()!="Vacant"))
    {Table4SockClient *socket4 = Table4SockClient::instance();
        socket4->sendMesssage(QStringLiteral ("Play"));
        emit openPlayWindow();}
}
}
void TableWindow::T4WChanged(int index)
{   if (iAmSeated && (index==0)) {PositionWest=false;WestSeated=false;iAmSeated = false;
        T4WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
     if (iAmSeated && (index!=0)) { T4WBox ->setCurrentIndex(0);}
    if (!iAmSeated){
    T4WBox->setStyleSheet("QComboBox { background-color: red; }");
    QString message = ("Seated:T4W");
    T4WPlayer=userList.at(index);
    message.append(T4WPlayer);
    ChatSockClient *socketchat = ChatSockClient::instance();
    socketchat->sendMesssage(QString (message));
    Table4SockClient *socket4 = Table4SockClient::instance();
         connect(socket4,SIGNAL (PlayRecd()), this, SLOT (PlayGame()));
    Table1=false;Table2=false;Table3=false;Table4=true;
    PracticePlay=false;
    PositionNorth=false;PositionEast=false;PositionSouth=false;PositionWest=true;
    NorthSeated=false;EastSeated=false;SouthSeated=false;WestSeated=true;iAmSeated =true;
    if (index==0){iAmSeated=false;T4WBox->setStyleSheet("QComboBox { background-color: lightGray; }");}
    if (Table4 &&(index!=0)&&(T4NBox->currentText()!="Vacant")&&(T4EBox->currentText()!="Vacant")&&(T4SBox->currentText()!="Vacant"))
   { Table4SockClient *socket4 = Table4SockClient::instance();
    socket4->sendMesssage(QStringLiteral ("Play"));
    emit openPlayWindow();}
}
}
