#include "Common.hpp"
#include "ChatWindow.hpp"
#include "PlayWindow.hpp"
#include "WelcomeWindow.hpp"
#include "../Game.hpp"
#include "../Misc.hpp"
#include <QPushButton>
#include <QCloseEvent>
#include <iostream>
#include "../Contract.hpp"
#include <QDebug>
#include <QLabel>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QLineEdit>
#include "ChatSockClient.hpp"
#include "Table1SockClient.hpp"
#include "Table2SockClient.hpp"
#include "Table3SockClient.hpp"
#include "Table4SockClient.hpp"
#include <QtWebSockets/QWebSocket>



extern bool PracticePlay;
extern bool Table1;
extern bool Table2;
extern bool Table3;
extern bool Table4;

ChatWindow::ChatWindow(QWidget *parent): QDialog (parent)
{
    ChatSockClient *socketchat = ChatSockClient::instance();

       connect(socketchat,&ChatSockClient:: ChatRecd, this, &ChatWindow::updateGeneralChat);

//if (Table1)
{Table1SockClient *socket = Table1SockClient::instance();
       connect(socket,&Table1SockClient::tableChatReceived , this ,&ChatWindow::updateTableChat);}
//if (Table2)
{Table2SockClient *socket2 = Table2SockClient::instance();
       connect(socket2,&Table2SockClient::tableChatReceived , this ,&ChatWindow::updateTableChat);}
//if (Table3)
{Table3SockClient *socket3 = Table3SockClient::instance();
       connect(socket3,&Table3SockClient::tableChatReceived , this ,&ChatWindow::updateTableChat);}
//if (Table4)
{Table4SockClient *socket4 = Table4SockClient::instance();
       connect(socket4,&Table4SockClient::tableChatReceived , this ,&ChatWindow::updateTableChat);}


	// This window
     //  setMaximumSize(1280,150);
       setMinimumSize(MIN_WIDTH,120);

       tableChatDisplay = new QPlainTextEdit(this);
       tableChatDisplay->setMinimumWidth(640);
      // tableChatDisplay->setMinimumHeight(70);
       tableChatDisplay->ensureCursorVisible();
        tableChatDisplay->setCenterOnScroll(true);
       //tableChatDisplay->setFontPointSize(8);
       tableChatDisplay->setMaximumHeight(120);
       tableChatDisplay->setPlainText("Table Chat");

       tableText =new QLineEdit(this);
       tableText->setMinimumWidth(640);
       tableText->setMaximumHeight(20);
       tableText->move(0,100);

       generalChatDisplay = new QPlainTextEdit(this);
       generalChatDisplay->setMinimumWidth(640);
     //  generalChatDisplay->setFontPointSize(8);
       generalChatDisplay->setMaximumHeight(120);
       generalChatDisplay->setCenterOnScroll(true);
       generalChatDisplay->setPlainText("General Chat");
       generalChatDisplay->ensureCursorVisible();
       generalChatDisplay->move(650,0);
       generalText =new QLineEdit(this);
       generalText->setMinimumWidth(640);
       generalText->setMaximumHeight(20);
       generalText->move(650,100);

       sendTableChatButton = new QPushButton("Table Send", this);
       sendTableChatButton->setFixedSize(100, 15);
       sendTableChatButton->move((640-100), 100);
       connect(sendTableChatButton, SIGNAL (clicked()), this, SLOT (sendTableChat()));
       sendTableChatButton->setEnabled(true);

       sendGeneralChatButton = new QPushButton("All Send", this);
       sendGeneralChatButton->setFixedSize(100, 15);
       sendGeneralChatButton->move((650+640-100), 100);
       connect(sendGeneralChatButton, SIGNAL (clicked()), this, SLOT (sendGeneralChat()));
       sendGeneralChatButton->setEnabled(true);

	setTitle(this, "Chat");
    show();
    setModal(true);

}
void ChatWindow::sendGeneralChat()
{
    ChatSockClient *socketchat = ChatSockClient::instance();

    QString message = generalText->text().trimmed();
        if(!message.isEmpty())
        {
           socketchat->sendMesssage("Chat"+QString (message + "\n"));
        }
        generalText->clear();
        generalText->setFocus();
    }
void ChatWindow::updateGeneralChat(QString message)
{
      generalChatDisplay->appendPlainText(message);

    }

void ChatWindow::sendTableChat()
{

    QString message = "Chat ";
    message.append (tableText->text().trimmed());
    if (!PracticePlay) {
    if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QString (message));}
    if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QString (message));}
    if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QString (message));}
    if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QString (message));}
        }
        tableText->clear();
        tableText->setFocus();

    }
void ChatWindow::updateTableChat(QString message)
{
   message.remove(0,5);
    tableChatDisplay->appendPlainText(message);

    }






