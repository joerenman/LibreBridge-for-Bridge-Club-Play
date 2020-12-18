#include "WebSockClient.hpp"
#include <QtCore/QDebug>
#include <QObject>

QT_USE_NAMESPACE
using namespace std;


//! [constructor]

WebSockClient* WebSockClient::m_instance = nullptr;
WebSockClient::WebSockClient(QObject *parent) : QObject(parent)
{
}

WebSockClient *WebSockClient::instance()
{
if (m_instance == nullptr)
        m_instance = new WebSockClient;
    return m_instance;
}

void WebSockClient::onConnect(const QUrl &url)
{
    m_url =url;
    //qDebug() << "WebSocket server:" << url;

    connect(&m_webSocket, &QWebSocket::connected, this, &WebSockClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSockClient::closed);
    connect(&m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
           this,&WebSockClient::showerror);

    //connect(this, &WebSockClient::PlayRecd, &welcomeWindow,&WelcomeWindow::startLocalGame);
   //  connect(this, &WebSockClient::plusDealRecd, &dealSelectionWindow,&DealSelectionWindow::plusDeal);
     m_webSocket.open(QUrl(url));

  //  qDebug() << "WebSocket opened";

}
//! [constructor]

//! [onConnected]
void WebSockClient::onConnected()
{
      connect(&m_webSocket, &QWebSocket::textMessageReceived,
       this, &WebSockClient::Checkmsg);  
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}
//! [onConnected]

//! [onTextMessageReceived]
void WebSockClient::onTextMessageReceived(QString message)
{ qDebug() << " sendtextmessage" << message;

    m_webSocket.sendTextMessage(message);

 //   m_webSocket.close();
}
void WebSockClient::closed()
{
    m_webSocket.close();
     qDebug() << "WebSocket closed";
}
void WebSockClient::showerror()
{   qDebug() << "Websocket error";
    qDebug() << m_webSocket.error();

}
void WebSockClient::flushit()
{
    m_webSocket.flush();

}
//! [onTextMessageReceived]
void WebSockClient::Checkmsg(QString message)

{ //qDebug() << " Check Message" << message;
    // messageout = messagein;
    QString str1="Play";
     QString str2="minusDeal";
     QString str3="plusDeal";
     QString str4="startBidding";
     QString str5="clickBidButton";
     QString str6="Pass,0,NoTrump";
     QString str7="Double,0,NoTrump";
     QString str8="ContractOK";
     QString str9="clickCardWidget";
     QString str10="NorthSeated";
     QString str11="EastSeated";
     QString str12="SouthSeated";
     QString str13="WestSeated";
     QString str14="Chat";
     QString str15="OpenDealWindow";
     QString str16="Score,";
     QString str17="EndOfGameNextDeal";
     QString str18="EndOfGameBackToMenu";

      if (message==str1) { emit PlayRecd(); }
      if (message==str2) { emit minusDealRecd();}
      if (message==str3) { emit plusDealRecd();}
      if (message==str4) { emit startBiddingRecd(); }
      if (message.startsWith(str5)){ emit clickBidRecd(message);}
      if (message==str6) { emit sendPassRecd(); }
      if (message==str7) { emit sendDoubleRecd();}
      if (message==str8) { emit contractOKRecd();}
      if (message.startsWith(str9)){ emit clickCardWidgetRecd(message);}
      if (message==str10){emit recdNorthSeated();}
      if (message==str11){ emit recdEastSeated();}
      if (message==str12){ emit recdSouthSeated();}
      if (message==str13){ emit recdWestSeated();}
      if (message.startsWith(str14)){emit tableChatReceived(message);}
      if (message==str15){ emit openDealWindowRecd();}
      if (message.startsWith(str16)){emit tableScoreReceived(message);}
      if (message==str17){ emit endOfGameNextDeal();}
      if (message==str18){ emit endOfGameBackToMenu();}
      //connect(this, &WebSockClient::PlayRecd, &welcomeWindow,&WelcomeWindow::startLocalGame);
     //  connect(this, &WebSockClient::plusDealRecd, &dealSelectionWindow,&DealSelectionWindow::plusDeal);
}


//! [sendMessage]
void WebSockClient::sendMesssage(QString message)
{  qDebug() << " sendMessage" << message;
        m_webSocket.sendTextMessage(message);
        qDebug() << " sendMessage now flush" << message;
        m_webSocket.flush();

}
//! [sendMessage]

