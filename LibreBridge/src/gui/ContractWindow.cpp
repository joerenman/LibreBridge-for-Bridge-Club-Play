#include "Common.hpp"
#include "BidWindow.hpp"
#include "ContractWindow.hpp"
#include "PlayWindow.hpp"
#include "../Game.hpp"
#include "../Misc.hpp"
#include <QPushButton>
#include <QLabel>
#include <QCloseEvent>
#include "Table1SockClient.hpp"
#include "Table2SockClient.hpp"
#include "Table3SockClient.hpp"
#include "Table4SockClient.hpp"
#include "../Contract.hpp"


extern bool PositionNorth;
extern bool PracticePlay;
extern bool Table1;
extern bool Table2;
extern bool Table3;
extern bool Table4;


ContractWindow::ContractWindow(Contract c, QWidget *parent): QDialog (parent)
{
	contract = c;
	this->parent = (BidWindow*)parent;
	
	// This window
	setFixedSize(300, 200);
	setTitle(this, "Contract");
	centerWindow(this);
	setModal(true);


if (Table1){Table1SockClient *socket = Table1SockClient::instance(); connect(socket, SIGNAL (contractOKRecd()), this ,SLOT (OK()));}
if (Table2){Table2SockClient *socket2 = Table2SockClient::instance(); connect(socket2, SIGNAL (contractOKRecd()), this ,SLOT (OK()));}
if (Table3){Table3SockClient *socket3 = Table3SockClient::instance(); connect(socket3, SIGNAL (contractOKRecd()), this ,SLOT (OK()));}
if (Table4){Table4SockClient *socket4 = Table4SockClient::instance(); connect(socket4, SIGNAL (contractOKRecd()), this ,SLOT (OK()));}
	OKButton = new QPushButton("OK", this);
	OKButton->setFixedSize(40, 30);
	OKButton->move(130, 140);
    OKButton->setEnabled(false);
    if (PositionNorth) {OKButton->setEnabled(true);}
    connect(OKButton, SIGNAL (clicked()), this, SLOT (sendOK()));
    connect(OKButton, SIGNAL (clicked()), this, SLOT (OK()));
	
	// playAsDeclarer button
	playAsDeclarerButton = new QPushButton("Play as declarer", this);
	playAsDeclarerButton->setFixedSize(100, 30);
	playAsDeclarerButton->move(15, 85);
	playAsDeclarerButton->setEnabled(false);
	playAsDeclarerButton->setAutoDefault(false);
	connect(playAsDeclarerButton, SIGNAL (clicked()), this, SLOT (playAsDeclarer()));

	changeBidButton = new QPushButton("Change bid", this);
	changeBidButton->setFixedSize(80, 30);
	changeBidButton->move(15, 140);
	changeBidButton->setEnabled(false);
	changeBidButton->setAutoDefault(false);
	connect(changeBidButton, SIGNAL (clicked()), this, SLOT (changeBid()));
	
	// restartBidding button
    restartBiddingButton = new QPushButton("Abandon bidding", this);
    restartBiddingButton->setFixedSize(140, 30);
	restartBiddingButton->move(130, 85);
    restartBiddingButton->setEnabled(false);
	restartBiddingButton->setAutoDefault(false);
	connect(restartBiddingButton, SIGNAL (clicked()), this, SLOT (restartBidding()));

	// contract label
	contractLabel = new QLabel(QString::fromStdString(contract.toString()), this);
	contractLabel->move(15, 15);


}

void ContractWindow::playAsDeclarer()
{/*
	options.seedIncrementStep = -1; // So that if there are constraints, we don't just add back 1 to the seed
	incrementSeed();
	seedTextBox->setText(QString("%1").arg(getSeed())); // Should emit textChanged signal and run updateOnSeedChange()
	options.seedIncrementStep = 1;*/
}

void ContractWindow::changeBid()
{
	//seedTextBox->setText(QString("%1").arg(getSeed()+1)); // Should emit textChanged signal and run updateOnSeedChange()
}

void ContractWindow::restartBidding()
{
    //showWelcomeWindowWhenDone = false;
    emit contractBackToWelcome();
    this->close();
    parent->close();
    //parent->startBidding();
}
void ContractWindow::sendOK()
{   QString message = "ContractOK";
    if (!PracticePlay) {
    if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QString (message));}
    if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QString (message));}
    if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QString (message));}
    if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QString (message));}
        }
}

void ContractWindow::OK()
{
    PlayWindow *playWindow = parent->getPlayWindow();
    playWindow->setCardsAreClickable(true);
    playWindow->getGame()->setContract(contract);
    playWindow->updateContractInfoLabel();
    playWindow->updateCurrentPlayerArrow();

    this->close();
    parent->close();

    playWindow->activateWindow();
    playWindow->playingProcess();
}

void ContractWindow::closeEvent(QCloseEvent *)
{
    //delete seedValidator;
    //if(showWelcomeWindowWhenDone)
	{
      //  WelcomeWindow *welcomeWindow = new WelcomeWindow;
      //  copyWindowGeometry(parent, welcomeWindow);
     //parent-> close();
     //   welcomeWindow->show();
    }
}
