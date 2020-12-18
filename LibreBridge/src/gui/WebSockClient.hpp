#ifndef WebSockClient_H
#define WebSockClient_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QObject>
#include "WelcomeWindow.hpp"
#include "DealSelectionWindow.hpp"



class WebSockClient : public QObject
{

    Q_OBJECT
public:
  //  explicit WebSockClient(const QString& name,const QUrl &url,  QObject *parent = nullptr);
   static WebSockClient *instance();
   QWebSocket m_webSocket;
   void onConnect(const QUrl &url);
   void sendMesssage(QString message);
   void closed();
   void showerror();
   void flushit();
signals :
   void PlayRecd();
   void minusDealRecd();
   void plusDealRecd();
   void startBiddingRecd();
   void clickBidRecd(QString message);
   void sendPassRecd();
   void sendDoubleRecd();
   void contractOKRecd();
   void clickCardWidgetRecd(QString message);
   void recdNorthSeated();
   void recdEastSeated();
   void recdSouthSeated();
   void recdWestSeated();
   void openDealWindowRecd();
    void tableChatReceived(QString message);
    void tableScoreReceived(QString message);
   void endOfGameNextDeal();
   void endOfGameBackToMenu();


private slots:
  // void closed();
   void onConnected();
   void onTextMessageReceived(QString message);

public Q_SLOTS:
  void Checkmsg(QString messagein);




private:
    static WebSockClient* m_instance;
    explicit WebSockClient(QObject *parent = nullptr); 
   // QWebSocket m_webSocket;
    QUrl m_url;
  

};





#endif // WebSockClient_H

