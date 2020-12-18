#include "BidButton.hpp"
#include "BidWindow.hpp"
#include "../Bid.hpp"
#include "../Misc.hpp"
#include <iostream>
#include "Table1SockClient.hpp"
#include "Table2SockClient.hpp"
#include "Table3SockClient.hpp"
#include "Table4SockClient.hpp"
#include <QtWebSockets/QWebSocket>
#include <string>
#include <QString>
#include "../Contract.hpp"
#include "Common.hpp"

extern bool PracticePlay;
extern bool Table1;
extern bool Table2;
extern bool Table3;
extern bool Table4;

BidButton::BidButton(Suit suit, int level, QWidget *parent): QPushButton (parent)
{

	this->parent = (BidWindow*)parent;
	this->suit = suit;
	this->level = level;
	
	setImage();


      connect(this, SIGNAL (clicked()), this, SLOT (clickBidButton()));
      connect(this, SIGNAL (clicked()), this, SLOT (sendclickBidButton()));


}



void BidButton::clickBidButton()
{
	parent->bidClick(Normal, level, suit);
    std::string suittext = suitToString(suit);
    QString qstr = QString::fromStdString(suittext);

}

void BidButton::sendclickBidButton()
{
  QString message =  "clickBidButton," ;
          message.append(QString::number(level));
          message.append (",") ;
         std::string suittext = suitToString(suit);
         QString qstr = QString::fromStdString(suittext);
         message.append(qstr);
if (!PracticePlay) {
if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QString (message));}
if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QString (message));}
if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QString (message));}
if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QString (message));}
    }
}
void BidButton::setImage()
{
	setText(QString::fromStdString(suitToUnicodeString(suit)));
	if(suit == Diamonds || suit == Hearts) setStyleSheet("BidButton {color: red;}");
	QFont font = this->font();
	font.setPointSize(suit == NoTrump ? 10 : 14);
	setFont(font);
	
	setAutoDefault(false);
	setFixedSize(24, 24);
}
