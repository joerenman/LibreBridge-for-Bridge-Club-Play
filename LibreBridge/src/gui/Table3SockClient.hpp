#ifndef Table3SockClient_H
#define Table3SockClient_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QObject>
#include "WelcomeWindow.hpp"
#include "DealSelectionWindow.hpp"



class Table3SockClient : public QObject
{

    Q_OBJECT
public:
   static Table3SockClient *instance();
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
   void showNewPlayRecd();


private slots:
  // void closed();
   void onConnected();
   void onTextMessageReceived(QString message);

public Q_SLOTS:
  void Checkmsg(QString messagein);




private:
    static Table3SockClient* m_instance;
    explicit Table3SockClient(QObject *parent = nullptr); 
   // QWebSocket m_webSocket;
    QUrl m_url;
  

};





#endif // Table3SockClient_H

