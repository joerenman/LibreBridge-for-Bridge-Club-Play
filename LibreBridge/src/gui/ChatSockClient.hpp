#ifndef ChatSockClient_H
#define ChatSockClient_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QObject>
#include "WelcomeWindow.hpp"
#include "DealSelectionWindow.hpp"



class ChatSockClient : public QObject
{

    Q_OBJECT
public:
  
   static ChatSockClient *instance();
   void onConnect(const QUrl &url);
     void closed();
     void openSocket();
signals :
   void ChatRecd(QString message);
   void seatStatusChangeRecd(QString message);
   void seatStatusRequestRecd();
   void startDealRecd(QString message);
   
private slots:
  // void closed();
   void onConnected();
   void onTextMessageReceived(QString message);

public Q_SLOTS:
  void Checkmsg(QString messagein);
  void sendMesssage(QString message);



private:
    static ChatSockClient* m_instance;
    explicit ChatSockClient(QObject *parent = nullptr); 
    QWebSocket m_webSocket;
    QUrl m_url;
  

};





#endif // ChatSockClient_H

