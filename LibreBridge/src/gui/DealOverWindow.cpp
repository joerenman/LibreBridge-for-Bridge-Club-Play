#include "Common.hpp"
#include "DealOverWindow.hpp"
#include "PlayWindow.hpp"
#include "../Game.hpp"
#include "../Misc.hpp"
#include <QPushButton>
#include <QCloseEvent>
#include <iostream>
#include "../Contract.hpp"
#include <QDebug>
#include <QLabel>
#include <QTextEdit>
#include "Table1SockClient.hpp"
#include "Table2SockClient.hpp"
#include "Table3SockClient.hpp"
#include "Table4SockClient.hpp"
#include <QtWebSockets/QWebSocket>
#include "TableWindow.hpp"

extern int sessionStartDeal;
extern int cumPointsNS;
extern int cumPointsEW;
extern bool PositionNorth;
extern bool PracticePlay;
extern bool Table1;
extern bool Table2;
extern bool Table3;
extern bool Table4;

extern QString T1NPlayer;
extern QString T1SPlayer;
extern QString T1EPlayer;
extern QString T1WPlayer;
extern QString T2NPlayer;
extern QString T2SPlayer;
extern QString T2EPlayer;
extern QString T2WPlayer;
extern QString T3NPlayer;
extern QString T3SPlayer;
extern QString T3EPlayer;
extern QString T3WPlayer;
extern QString T4NPlayer;
extern QString T4SPlayer;
extern QString T4EPlayer;
extern QString T4WPlayer;
extern QString lastCardPlayedMessage;
extern QString lastMessageParsed ;

QString ContractSuit = "NoTrump";
QString ContractDeclarer = "North";
uint8_t ContractLevel=1;
int TricksNS=1;
int TricksEW = 1;
int PointsNS=0;
int PointsEW=0;
int DeclarerTricks=0;
int DefenderTricks=0;
int DeclarerPoints=0;
int DefenderPoints=0;
int DealNumber =0;


bool ContractVulnerable= false;
bool ContractDoubled= false;
bool ContractRedoubled= false;
bool ContractNS = false;
bool ContractEW= false;


DealOverWindow::DealOverWindow(QWidget *parent): QDialog (parent)
{
	this->playWindow = (PlayWindow*)parent;
	showWelcomeWindowWhenDone = true;
if (Table1){Table1SockClient *socket = Table1SockClient::instance();
    connect(socket,&Table1SockClient::tableScoreReceived , this ,&DealOverWindow::updateScoreReceived);
    connect(socket,&Table1SockClient::endOfGameNextDeal , this ,&DealOverWindow::nextDeal);
    connect(socket,&Table1SockClient::endOfGameBackToMenu , this ,&DealOverWindow::backToMenu);}
if (Table2){Table2SockClient *socket2 = Table2SockClient::instance();
    connect(socket2,&Table2SockClient::tableScoreReceived , this ,&DealOverWindow::updateScoreReceived);
    connect(socket2,&Table2SockClient::endOfGameNextDeal , this ,&DealOverWindow::nextDeal);
    connect(socket2,&Table2SockClient::endOfGameBackToMenu , this ,&DealOverWindow::backToMenu);}
if (Table3){Table3SockClient *socket3 = Table3SockClient::instance();
    connect(socket3,&Table3SockClient::tableScoreReceived , this ,&DealOverWindow::updateScoreReceived);
    connect(socket3,&Table3SockClient::endOfGameNextDeal , this ,&DealOverWindow::nextDeal);
    connect(socket3,&Table3SockClient::endOfGameBackToMenu , this ,&DealOverWindow::backToMenu);}
if (Table4){Table4SockClient *socket4 = Table4SockClient::instance();
    connect(socket4,&Table4SockClient::tableScoreReceived , this ,&DealOverWindow::updateScoreReceived);
    connect(socket4,&Table4SockClient::endOfGameNextDeal , this ,&DealOverWindow::nextDeal);
    connect(socket4,&Table4SockClient::endOfGameBackToMenu , this ,&DealOverWindow::backToMenu);}

    lastCardPlayedMessage="  ";
    lastMessageParsed ="  ";
	// This window
    //setFixedSize(550, 237);
    setGeometry(200,200,550,237);
	setTitle(this, "Deal over");
	centerWindow(this);
    setModal(true);


	// score button
	scoreButton = new QPushButton("Score this deal", this);
    scoreButton->setFixedSize(135, 24);
    scoreButton->move(10, 10);
    scoreButton->setEnabled(false);
    if (PositionNorth) {scoreButton->setEnabled(true);}
    connect(scoreButton, SIGNAL (clicked()), this, SLOT (score()));
	
	// playAgain button
    playAgainButton = new QPushButton("Play deal again", this);
    playAgainButton->setFixedSize(135, 24);
    playAgainButton->move(10, 40);
    playAgainButton->setAutoDefault(false);
    playAgainButton->setEnabled(false);
    //if (PositionNorth) {playAgainButton->setEnabled(true);}
	connect(playAgainButton, SIGNAL (clicked()), this, SLOT (playAgain()));
	
	// reviewBidding button
/*	reviewBiddingButton = new QPushButton("Review bidding", this);
	reviewBiddingButton->setFixedSize(130, 24);
	reviewBiddingButton->move(10, 63);
	reviewBiddingButton->setEnabled(false);
	reviewBiddingButton->setAutoDefault(false);
	connect(reviewBiddingButton, SIGNAL (clicked()), this, SLOT (reviewBidding()));
	
	// replay button
	replayButton = new QPushButton("View hand replay", this);
	replayButton->setFixedSize(130, 24);
    replayButton->move(10, 92);
    connect(socket,&Table1SockClient::tableScoreReceived , this ,&DealOverWindow::updateScoreReceived);
	replayButton->setEnabled(false);
	replayButton->setAutoDefault(false);
	connect(replayButton, SIGNAL (clicked()), this, SLOT (replay()));
	
	// save button
	saveButton = new QPushButton("Save deal number", this);
	saveButton->setFixedSize(130, 24);
	saveButton->move(10, 121);
	saveButton->setEnabled(false);
	saveButton->setAutoDefault(false);
    connect(savvoid playRemoteCard(QString message);eButton, SIGNAL (clicked()), this, SLOT (save()));
	
	// print button
	printButton = new QPushButton("Print deal", this);
	printButton->setFixedSize(130, 24);
	printButton->move(10, 150);
	printButton->setEnabled(false);
	printButton->setAutoDefault(false);
	connect(printButton, SIGNAL (clicked()), this, SLOT (print()));
	*/

	// nextDeal button
    nextDealButton = new QPushButton("Next Game", this);
    nextDealButton->setFixedSize(135, 24);
    nextDealButton->move(10, 70);
	nextDealButton->setEnabled(false);
	nextDealButton->setAutoDefault(false);
    nextDealButton->setEnabled(false);
    if (PositionNorth) {nextDealButton->setEnabled(true);}
	connect(nextDealButton, SIGNAL (clicked()), this, SLOT (nextDeal()));
	
	// backToMenu button
    backToMenuButton = new QPushButton("Back Seat Select", this);
    backToMenuButton->setFixedSize(150, 24);
    backToMenuButton->move(10, 100);
	backToMenuButton->setAutoDefault(false);
    backToMenuButton->setEnabled(false);
    if (PositionNorth) {backToMenuButton->setEnabled(true);}
	connect(backToMenuButton, SIGNAL (clicked()), this, SLOT (backToMenu()));

    pointsDisplay = new QTextEdit(this);
    pointsDisplay ->move(150,10);
    pointsDisplay->setFixedWidth(400);


}

void DealOverWindow::score()
{
    Contract contract = playWindow->getGame()->getContract();
    Position player =(contract.getDeclarer());
    ContractDeclarer =QString::fromStdString( positionToString(player));
    Suit suit = (contract.getSuit());
    ContractSuit =QString::fromStdString( suitToString(suit));
    ContractLevel = (contract.getLevel());
    ContractVulnerable =contract.isTeamVulnerable(player);
    ContractDoubled= (contract.doubled);
    ContractRedoubled= (contract.redoubled);


    TricksNS=(playWindow->tricksMade[0]);
    TricksEW=(playWindow->tricksMade[1]);

    if (ContractDeclarer=="North" || ContractDeclarer=="South")
         {
             ContractNS=true;
             ContractEW=false;
             DeclarerTricks=TricksNS;
             DefenderTricks=TricksEW;
         }
         if (ContractDeclarer=="East" || ContractDeclarer=="West")
        {
            ContractEW=true;
             ContractNS=false;
             DeclarerTricks=TricksEW;
             DefenderTricks=TricksNS;
        }

         {
             if ((ContractLevel+6) > DeclarerTricks)
               {  DeclarerPoints =0;
                 if (ContractVulnerable ==false)
                 {
                   DefenderPoints = ((ContractLevel+6)-DeclarerTricks)*50;
                   if (ContractDoubled)
                   {
                       DefenderPoints = ((ContractLevel+6)-DeclarerTricks)*100;
                       if (((ContractLevel+6)-DeclarerTricks)>1){DefenderPoints= DefenderPoints+ (((ContractLevel+6)-(DeclarerTricks+1))*100);}
                      if (((ContractLevel+6)-DeclarerTricks)>3){DefenderPoints = DefenderPoints+ (((ContractLevel+6)-(DeclarerTricks+3))*100);}
                   }
                   if(ContractRedoubled) { DefenderPoints = DefenderPoints *2;}
                  }
                 if (ContractVulnerable)
                 {
                   DefenderPoints = ((ContractLevel+6)-DeclarerTricks)*100;
                   if (ContractDoubled)
                   {
                       DefenderPoints = ((ContractLevel+6)-DeclarerTricks)*200;
                       if (((ContractLevel+6)-DeclarerTricks)>1){DefenderPoints = DefenderPoints + (((ContractLevel+6)-(DeclarerTricks+1))*100);}

                   }
                   if(ContractRedoubled) { DefenderPoints = DefenderPoints *2;}
                  }
                }
             if ((ContractLevel+6) <= DeclarerTricks)
               {  DefenderPoints =0;
                  if (ContractSuit =="NoTrump" or ContractSuit=="No Trump")
                  {
                   if (!ContractDoubled) DeclarerPoints=10+((DeclarerTricks-6)*30);
                   if ((ContractDoubled) and (!ContractRedoubled)) DeclarerPoints=(20+((DeclarerTricks-6)*60));
                   if (ContractRedoubled) DeclarerPoints=(40+((DeclarerTricks-6)*120));

                  }
                  if (ContractSuit =="Clubs" or ContractSuit=="Diamonds")
                  {
                      if (!ContractDoubled) DeclarerPoints=((DeclarerTricks-6)*20);
                      if ((ContractDoubled) and (!ContractRedoubled)) DeclarerPoints=((DeclarerTricks-6)*40);
                      if (ContractRedoubled) DeclarerPoints=((DeclarerTricks-6)*80);
                  }

                  if (ContractSuit =="Hearts" or ContractSuit=="Spades")
                  {
                   if (!ContractDoubled) DeclarerPoints=((DeclarerTricks-6)*30);
                   if ((ContractDoubled) and (!ContractRedoubled)) DeclarerPoints=((DeclarerTricks-6)*60);
                   if (ContractRedoubled) DeclarerPoints=((DeclarerTricks-6)*120);
                  }

                  if (ContractSuit =="NoTrump" or ContractSuit=="No Trump")
                  {   if ((ContractLevel+6)<9) DeclarerPoints = DeclarerPoints +50;
                      if ((DeclarerTricks >= 9) and ((ContractLevel+6)>=9) and (!ContractVulnerable)) DeclarerPoints = DeclarerPoints +300;
                      if ((DeclarerTricks >= 9) and ((ContractLevel+6)>=9) and (ContractVulnerable)) DeclarerPoints = DeclarerPoints +500;
                      if ((ContractDoubled) and(!ContractRedoubled)and(!ContractVulnerable)) DeclarerPoints =DeclarerPoints+50+(((DeclarerTricks-(ContractLevel+6))*40));
                      if ((ContractDoubled) and(!ContractRedoubled)and(ContractVulnerable)) DeclarerPoints =DeclarerPoints+50+(((DeclarerTricks-(ContractLevel+6))*140));
                      if ((ContractDoubled) and(ContractRedoubled)and(!ContractVulnerable)) DeclarerPoints =DeclarerPoints+100+(((DeclarerTricks-(ContractLevel+6))*80));
                      if ((ContractDoubled) and(ContractRedoubled)and(ContractVulnerable)) DeclarerPoints =DeclarerPoints+100+(((DeclarerTricks-(ContractLevel+6))*280));
                  }

                  if (ContractSuit =="Clubs" or ContractSuit=="Diamonds")
                  {
                      if ((ContractLevel+6)< 11) DeclarerPoints = DeclarerPoints +50;
                  if ((DeclarerTricks >= 11) and ((ContractLevel+6)>=11) and (!ContractVulnerable)) DeclarerPoints = DeclarerPoints +300;
                  if ((DeclarerTricks >= 11) and ((ContractLevel+6)>=11) and (ContractVulnerable)) DeclarerPoints = DeclarerPoints +500;
                  if ((ContractDoubled) and(!ContractRedoubled)and(!ContractVulnerable)) DeclarerPoints =DeclarerPoints+50+(((DeclarerTricks-(ContractLevel+6))*60));
                  if ((ContractDoubled) and(!ContractRedoubled)and(ContractVulnerable)) DeclarerPoints =DeclarerPoints+50+(((DeclarerTricks-(ContractLevel+6))*160));
                  if ((ContractDoubled) and(ContractRedoubled)and(!ContractVulnerable)) DeclarerPoints =DeclarerPoints+100+(((DeclarerTricks-(ContractLevel+6))*120));
                  if ((ContractDoubled) and(ContractRedoubled)and(ContractVulnerable)) DeclarerPoints =DeclarerPoints+100+(((DeclarerTricks-(ContractLevel+6))*320));
                    }
                  if (ContractSuit =="Hearts" or ContractSuit=="Spades")
                  {
                   if ((ContractLevel+6)<10) DeclarerPoints = DeclarerPoints +50;
                   if ((DeclarerTricks >= 10) and ((ContractLevel+6)>=10) and (!ContractVulnerable)) DeclarerPoints = DeclarerPoints +300;
                   if ((DeclarerTricks >= 10) and ((ContractLevel+6)>=10) and (ContractVulnerable)) DeclarerPoints = DeclarerPoints +500;
                   if ((ContractDoubled) and(!ContractRedoubled)and(!ContractVulnerable)) DeclarerPoints =DeclarerPoints+50+(((DeclarerTricks-(ContractLevel+6))*40));
                   if ((ContractDoubled) and(!ContractRedoubled)and(ContractVulnerable)) DeclarerPoints =DeclarerPoints+50+(((DeclarerTricks-(ContractLevel+6))*140));
                   if ((ContractDoubled) and(ContractRedoubled)and(!ContractVulnerable)) DeclarerPoints =DeclarerPoints+100+(((DeclarerTricks-(ContractLevel+6))*80));
                   if ((ContractDoubled) and(ContractRedoubled)and(ContractVulnerable)) DeclarerPoints =DeclarerPoints+100+(((DeclarerTricks-(ContractLevel+6))*280));
                  }
                }
             if ((DeclarerTricks >= 12) and ((ContractLevel+6)==12) and (!ContractVulnerable)) DeclarerPoints = DeclarerPoints +500;
             if ((DeclarerTricks >= 12) and ((ContractLevel+6)==12) and (ContractVulnerable)) DeclarerPoints = DeclarerPoints +750;
             if ((DeclarerTricks == 13) and ((ContractLevel+6)==13) and (!ContractVulnerable)) DeclarerPoints= DeclarerPoints +1000;
             if ((DeclarerTricks == 13) and ((ContractLevel+6)==13) and (ContractVulnerable)) DeclarerPoints = DeclarerPoints +1500;
            }

         if(ContractNS) {PointsNS=DeclarerPoints;
                         PointsEW=DefenderPoints;  }

         if(ContractEW) {PointsNS=DefenderPoints;
                         PointsEW=DeclarerPoints;  }




    DealNumber=getSeed();
    QString messagec=("Deal ");
    messagec.append (QString::number(DealNumber));
    messagec.append (", Contract was ");
    messagec.append(QString::number(ContractLevel));
    messagec.append(" , ");
    messagec.append (ContractSuit);
    pointsDisplay -> setText(messagec);
    messagec.append(", by,  ");
    messagec.append (ContractDeclarer);
    messagec.append("\n");

    if (ContractVulnerable) {messagec.append(" Vulnerable\n ");}
    if (ContractDoubled) {messagec.append(" Doubled ");}
    if (ContractRedoubled) {messagec.append(",Re-Doubled ");}
    messagec.append("\n ");

    QString message =("NS Tricks = ");
    message.append(QString::number(TricksNS));
    message.append("\n EW Tricks = ");
    pointsDisplay -> setText(messagec);
    message.append(QString::number(TricksEW));
    message.append("\n NS Points = ");
    message.append(QString::number(PointsNS));
    message.append("\n EW Points = ");
    message.append(QString::number(PointsEW));
    cumPointsNS = cumPointsNS + PointsNS;
    cumPointsEW = cumPointsEW + PointsEW;
    message.append("\n Session NS Points = ");
    message.append(QString::number(cumPointsNS));
    message.append("\n Session EW Points = ");
    message.append(QString::number(cumPointsEW));

    pointsDisplay -> setText(messagec);
    pointsDisplay ->append(message);
    QString messageWS =  "Score," ;
            messageWS.append(messagec);
            messageWS.append (message) ;

            if (!PracticePlay) {
            if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QString (messageWS));}
            if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QString (messageWS));}
            if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QString (messageWS));}
            if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QString (messageWS));}
                }


    //Now construct version for saving in Score file
   messagec=("Deal");
    messagec.append (QString::number(DealNumber));
    messagec.append (",Contract was");
    messagec.append(QString::number(ContractLevel));
    messagec.append(",");
    messagec.append (ContractSuit);
    messagec.append(",by,");
    messagec.append (ContractDeclarer);
    messagec.append(",");

    if (ContractVulnerable) {messagec.append("Vulnerable,");}else {messagec.append(",");}
    if (ContractDoubled) {messagec.append("Doubled,");}else {messagec.append(",");}
    if (ContractRedoubled) {messagec.append("Re-Doubled,");}else {messagec.append(",");}

    message =("NS Tricks,");
    message.append(QString::number(TricksNS));
    message.append(",EW Tricks,");
    message.append(QString::number(TricksEW));
    message.append(",NS Points,");
    message.append(QString::number(PointsNS));
    message.append(",EW Points,");
    message.append(QString::number(PointsEW));

            messageWS =  "Score:" ;
            messageWS.append(messagec);
            messageWS.append (message) ;
            messageWS.append(",NSEW,");
if (Table1){messageWS.append(T1NPlayer+",");messageWS.append(T1SPlayer+",");messageWS.append(T1EPlayer+",");messageWS.append(T1WPlayer);}
if (Table2){messageWS.append(T2NPlayer+",");messageWS.append(T2SPlayer+",");messageWS.append(T2EPlayer+",");messageWS.append(T2WPlayer);}
if (Table3){messageWS.append(T3NPlayer+",");messageWS.append(T3SPlayer+",");messageWS.append(T3EPlayer+",");messageWS.append(T3WPlayer);}
if (Table4){messageWS.append(T4NPlayer+",");messageWS.append(T4SPlayer+",");messageWS.append(T4EPlayer+",");messageWS.append(T4WPlayer);}

            if (!PracticePlay) {
            if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QString (messageWS));}
            if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QString (messageWS));}
            if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QString (messageWS));}
            if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QString (messageWS));}
                }

}
void DealOverWindow::updateScoreReceived(QString message)
{pointsDisplay -> setText(message);
}
void DealOverWindow::playAgain()
{
	showWelcomeWindowWhenDone = false;
	close();
	playWindow->startNewGame(getSeed()-1);
}

void DealOverWindow::reviewBidding()
{
	
}

void DealOverWindow::replay()
{
	
}

void DealOverWindow::save()
{
	
}

void DealOverWindow::print()
{
	
}

void DealOverWindow::nextDeal()
{   if (PositionNorth) {
     if (!PracticePlay) {
     if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QStringLiteral ("EndOfGameNextDeal"));}
     if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QStringLiteral ("EndOfGameNextDeal"));}
     if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QStringLiteral ("EndOfGameNextDeal"));}
     if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QStringLiteral ("EndOfGameNextDeal"));}
            }
    }
    sessionStartDeal = sessionStartDeal + 1;
    emit  dealOverNextDeal();
   //this->close();
  //  playWindow->startNewGame(getSeed());
}

void DealOverWindow::backToMenu()
{ if (PositionNorth) {
   if (!PracticePlay) {
   if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
   if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
   if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
   if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
            }
    }
    emit dealOverBackToMenu();
    this->close();

}

void DealOverWindow::closeEvent(QCloseEvent *)
{

    if (PositionNorth) {
            if (!PracticePlay) {
            if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
            if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
            if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
            if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
            }
        }
       this->close();
}
