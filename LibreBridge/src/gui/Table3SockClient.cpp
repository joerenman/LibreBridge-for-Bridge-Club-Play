#include "Table3SockClient.hpp"
#include <QtCore/QDebug>
#include <QObject>

QT_USE_NAMESPACE
using namespace std;
extern QString WebAddress;
Table3SockClient* Table3SockClient::m_instance = nullptr;
Table3SockClient::Table3SockClient(QObject *parent) : QObject(parent)
{
}

Table3SockClient *Table3SockClient::instance()
{
if (m_instance == nullptr)
        m_instance = new Table3SockClient;
    return m_instance;
}

void Table3SockClient::onConnect(const QUrl &url)
{
    m_url =url;
    connect(&m_webSocket, &QWebSocket::connected, this, &Table3SockClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Table3SockClient::closed);
    connect(&m_webSocket, &QWebSocket::aboutToClose, this, &Table3SockClient::closed);
     m_webSocket.open(QUrl(url));
}

void Table3SockClient::onConnected()
{
      connect(&m_webSocket, &QWebSocket::textMessageReceived,
       this, &Table3SockClient::Checkmsg);  
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}


void Table3SockClient::onTextMessageReceived(QString message)
{     m_webSocket.sendTextMessage(message);
}
void Table3SockClient::closed()
{
    m_webSocket.close();

}

void Table3SockClient::flushit()
{
    m_webSocket.flush();
}

void Table3SockClient::Checkmsg(QString message)

{
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
     QString str19="ShowNewPlayWindow";

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
       if (message==str19){ emit showNewPlayRecd();}

}



void Table3SockClient::sendMesssage(QString message)
{
        m_webSocket.sendTextMessage(message);

        m_webSocket.flush();

}


