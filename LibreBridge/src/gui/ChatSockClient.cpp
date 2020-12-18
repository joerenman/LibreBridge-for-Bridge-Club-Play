#include "ChatSockClient.hpp"
#include <QtCore/QDebug>
#include <QObject>

QT_USE_NAMESPACE
using namespace std;
extern QString WebAddress;



ChatSockClient* ChatSockClient::m_instance = nullptr;
ChatSockClient::ChatSockClient(QObject *parent) : QObject(parent)
{
}

ChatSockClient *ChatSockClient::instance()
{
if (m_instance == nullptr)
        m_instance = new ChatSockClient;
    return m_instance;
}

void ChatSockClient::onConnect(const QUrl &url)
{
    m_url =url;

    connect(&m_webSocket, &QWebSocket::connected, this, &ChatSockClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &ChatSockClient::closed);

    m_webSocket.open(QUrl(url));

}

void ChatSockClient::onConnected()
{

   //  qDebug() << "ChatSocket connected";
      connect(&m_webSocket, &QWebSocket::textMessageReceived,
 
       this, &ChatSockClient::Checkmsg);
    
    m_webSocket.sendTextMessage(QStringLiteral("SeatStatusRequest"));
    // qDebug() << "Hello World sent";
}

void ChatSockClient::onTextMessageReceived(QString message)
{
         m_webSocket.sendTextMessage(message);
  //   m_webSocket.close();
}
void ChatSockClient::closed()
{
    m_webSocket.close();
    m_webSocket.open(QUrl(QString(WebAddress+":8010")));
}
void ChatSockClient::openSocket()
{
   // m_url = url;
    m_webSocket.open(QUrl(QString(WebAddress+":8010")));
}
void ChatSockClient::Checkmsg(QString message)

{
    QString str1="Seated:";
    QString str2="SeatStatusRequest";
    QString str3="Chat";
    QString str4="StartDeal=";
     if (message.startsWith(str1)) { emit seatStatusChangeRecd(message); }
     if (message.startsWith(str2)) { emit seatStatusRequestRecd(); }
     if (message.startsWith(str3)) {emit ChatRecd(message);}
     if (message.startsWith(str4)) {emit startDealRecd(message);}

}


void ChatSockClient::sendMesssage(QString message)
{


        m_webSocket.sendTextMessage(message);
        m_webSocket.flush();
   
}


