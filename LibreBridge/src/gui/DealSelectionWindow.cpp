#include "Common.hpp"
#include "DealSelectionWindow.hpp"
#include "PlayWindow.hpp"
#include "WelcomeWindow.hpp"
#include "SeedValidator.hpp"
#include "../Game.hpp"
#include "../Misc.hpp"
#include <QPushButton>
#include <QResizeEvent>
#include <QLineEdit>
#include <QCloseEvent>
#include "Table1SockClient.hpp"
#include "Table2SockClient.hpp"
#include "Table3SockClient.hpp"
#include "Table4SockClient.hpp"

extern bool PositionNorth;
extern bool PracticePlay;
extern int sessionStartDeal;
extern bool Table1;
extern bool Table2;
extern bool Table3;
extern bool Table4;

DealSelectionWindow::DealSelectionWindow(QWidget *parent): QDialog (parent)
{
	this->parent = (PlayWindow*)parent;
	showWelcomeWindowWhenDone = true;
if (Table1){Table1SockClient *socket = Table1SockClient::instance();
      connect(socket,SIGNAL (minusDealRecd()), this, SLOT (minusDeal()));
      connect(socket,SIGNAL (plusDealRecd()), this, SLOT (plusDeal()));
      connect(socket,SIGNAL (startBiddingRecd()), this, SLOT (startBidding()));}
if (Table2){Table2SockClient *socket2 = Table2SockClient::instance();
      connect(socket2,SIGNAL (minusDealRecd()), this, SLOT (minusDeal()));
      connect(socket2,SIGNAL (plusDealRecd()), this, SLOT (plusDeal()));
      connect(socket2,SIGNAL (startBiddingRecd()), this, SLOT (startBidding()));}
if (Table3){Table3SockClient *socket3 = Table3SockClient::instance();
      connect(socket3,SIGNAL (minusDealRecd()), this, SLOT (minusDeal()));
      connect(socket3,SIGNAL (plusDealRecd()), this, SLOT (plusDeal()));
      connect(socket3,SIGNAL (startBiddingRecd()), this, SLOT (startBidding()));}
if (Table4){Table4SockClient *socket4 = Table4SockClient::instance();
      connect(socket4,SIGNAL (minusDealRecd()), this, SLOT (minusDeal()));
      connect(socket4,SIGNAL (plusDealRecd()), this, SLOT (plusDeal()));
      connect(socket4,SIGNAL (startBiddingRecd()), this, SLOT (startBidding()));}



    //setFixedSize(300, 100);
   // setGeometry(800,500,300,100);
    setGeometry(200,150,300,100);
	setTitle(this, "Deal selection");
    centerWindow(this);


	
	// Deal number
	seedTextBox = new QLineEdit(this);
    seedTextBox->setFixedSize(getSeedTextMaxWidth(), 30);
    seedTextBox->setFixedSize(200, 30);
    int x = (width()-seedTextBox->width()) / 2;
    seedTextBox->move(x, 10);
	seedTextBox->setMaxLength(getSeedTextMaxLength()+10);
	seedTextBox->setText(QString("%1").arg(getSeed()));
	seedTextBox->setAlignment(Qt::AlignCenter);
	seedValidator = new SeedValidator(this);
	seedTextBox->setValidator(seedValidator);
	connect(seedTextBox, SIGNAL (textChanged(QString)), this, SLOT (updateOnSeedChange(QString)));

	// Minus Button
	seedMinusButton = new QPushButton("-", this);
	seedMinusButton->setFixedSize(15, 15);
	seedMinusButton->move(seedTextBox->x() - 2*seedMinusButton->width(), seedTextBox->y() + (seedTextBox->height()-seedMinusButton->height())/2);
	seedMinusButton->setAutoDefault(false);
    seedMinusButton->setEnabled(false);
    connect(seedMinusButton, SIGNAL (clicked()), this, SLOT (sendminusDeal()));
	connect(seedMinusButton, SIGNAL (clicked()), this, SLOT (minusDeal()));


	// Plus Button
	seedPlusButton = new QPushButton("+", this);
	seedPlusButton->setFixedSize(15, 15);
	seedPlusButton->move(seedTextBox->x() + seedTextBox->width() + seedPlusButton->width(), seedTextBox->y() + (seedTextBox->height()-seedPlusButton->height())/2);
	seedPlusButton->setAutoDefault(false);
    seedPlusButton->setEnabled(false);
     connect(seedPlusButton, SIGNAL (clicked()), this, SLOT (sendplusDeal()));
	connect(seedPlusButton, SIGNAL (clicked()), this, SLOT (plusDeal()));


	// playButton
	playButton = new QPushButton("Play this deal", this);
	playButton->setFixedSize(150, 30);
	x = (width()-playButton->width()) / 2;
	playButton->move(x, seedTextBox->y() + seedTextBox->height() + 10);
    connect(playButton, SIGNAL (clicked()), this, SLOT (sendstartBidding()));
	connect(playButton, SIGNAL (clicked()), this, SLOT (startBidding()));
    playButton->setEnabled(false);
    if (PositionNorth) {playButton->setEnabled(true);}
    if (PositionNorth) {seedPlusButton->setEnabled(true);}
    if (PositionNorth) {seedMinusButton->setEnabled(true);}

}

void DealSelectionWindow::minusDeal()
{
	options.seedIncrementStep = -1; // So that if there are constraints, we don't just add back 1 to the seed
	incrementSeed();
	seedTextBox->setText(QString("%1").arg(getSeed())); // Should emit textChanged signal and run updateOnSeedChange()
	options.seedIncrementStep = 1;
    sessionStartDeal =sessionStartDeal+1;
}

void DealSelectionWindow::plusDeal()
{
	seedTextBox->setText(QString("%1").arg(getSeed()+1)); // Should emit textChanged signal and run updateOnSeedChange()
    sessionStartDeal =sessionStartDeal+1;
}

void DealSelectionWindow::updateOnSeedChange(const QString &text)
{
	QLocale defaultLocale;
	bool ok;
	RANDOMNESS_SIZE tmp = (RANDOMNESS_SIZE)(defaultLocale.RANDOMNESS_QT_SIZE(text, &ok));
	if(ok) // Should always be true, since the QLineEdit has a validator
	{
		options.seed = tmp;
		parent->destroyAllHandWidgets();
		parent->getGame()->findNextDeal();
		seedTextBox->setText(QString("%1").arg(getSeed())); // If constraints weren't met, the deal number may have changed
		parent->createAllHandWidgets();
		parent->updateDealInfoLabel();
	}
}

void DealSelectionWindow::closeEvent(QCloseEvent *)
{
	delete seedValidator;
	if(showWelcomeWindowWhenDone)
	{
        //WelcomeWindow *welcomeWindow = new WelcomeWindow;
        //copyWindowGeometry(parent, welcomeWindow);
        //parent->close();
        //welcomeWindow->show();
	}
}

void DealSelectionWindow::startBidding()
{
	showWelcomeWindowWhenDone = false;
	this->close();
	parent->startBidding();
}
void DealSelectionWindow::sendminusDeal()
{

  if (!PracticePlay) {
      if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QStringLiteral ("minusDeal"));}
      if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QStringLiteral ("minusDeal"));}
      if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QStringLiteral ("minusDeal"));}
      if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QStringLiteral ("minusDeal"));}
      }
}
void DealSelectionWindow::sendplusDeal()
{ if (!PracticePlay) {
        if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QStringLiteral ("plusDeal"));}
        if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QStringLiteral ("plusDeal"));}
        if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QStringLiteral ("plusDeal"));}
        if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QStringLiteral ("plusDeal"));}
        }
}
void DealSelectionWindow::sendstartBidding()
{  if (!PracticePlay) {
        if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QStringLiteral ("startBidding"));}
        if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QStringLiteral ("startBidding"));}
        if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QStringLiteral ("startBidding"));}
        if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QStringLiteral ("startBidding"));}
        }
}
