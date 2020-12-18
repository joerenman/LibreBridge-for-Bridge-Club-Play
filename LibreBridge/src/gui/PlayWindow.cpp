
#include <QMenuBar>
#include <QMenu>
#include <QResizeEvent>
#include <QGridLayout>
#include <QLabel>
#include <vector>
#include <iostream>
#include "CardWidget.hpp"
#include "Common.hpp"
#include "PlayWindow.hpp"
#include "DealSelectionWindow.hpp"
#include "BidWindow.hpp"
#include "DealOverWindow.hpp"
#include "CardLayout.hpp"
#include "PlayedCardsLayout.hpp"
#include "PauseClickGrabber.hpp"
#include "../Card.hpp"
#include "../Game.hpp"
#include "../Misc.hpp"
#include "Table1SockClient.hpp"
#include "Table2SockClient.hpp"
#include "Table3SockClient.hpp"
#include "Table4SockClient.hpp"
#include <string>
#include <cstdint>
#include "CardWidget.hpp"
#include <QPushButton>

using namespace std;
extern QString lastMessageParsed ;
extern bool PositionNorth;
extern bool PracticePlay;
extern bool Table1;
extern bool Table2;
extern bool Table3;
extern bool Table4;

extern QString clickCardWidgetMessage;
extern QString lastCardPlayedMessage;
int remotePlayDelay =1000;

PlayWindow::PlayWindow(QWidget *parent): QDialog(parent)
{

if (Table1){Table1SockClient *socket = Table1SockClient::instance();
    connect(socket,&Table1SockClient::clickCardWidgetRecd , this ,&PlayWindow::playRemoteCard);
    connect(socket,&Table1SockClient::openDealWindowRecd , this ,&PlayWindow::openDealSelectionWindow);
    connect(socket,&Table1SockClient::showNewPlayRecd , this ,&PlayWindow::backToNewPlay);}
if (Table2){Table2SockClient *socket2 = Table2SockClient::instance();
    connect(socket2,&Table2SockClient::clickCardWidgetRecd , this ,&PlayWindow::playRemoteCard);
    connect(socket2,&Table2SockClient::openDealWindowRecd , this ,&PlayWindow::openDealSelectionWindow);
    connect(socket2,&Table2SockClient::showNewPlayRecd , this ,&PlayWindow::backToNewPlay);}
if (Table3){Table3SockClient *socket3 = Table3SockClient::instance();
    connect(socket3,&Table3SockClient::clickCardWidgetRecd , this ,&PlayWindow::playRemoteCard);
    connect(socket3,&Table3SockClient::openDealWindowRecd , this ,&PlayWindow::openDealSelectionWindow);
    connect(socket3,&Table3SockClient::showNewPlayRecd , this ,&PlayWindow::backToNewPlay);}
if (Table4){Table4SockClient *socket4 = Table4SockClient::instance();
    connect(socket4,&Table4SockClient::clickCardWidgetRecd , this ,&PlayWindow::playRemoteCard);
    connect(socket4,&Table4SockClient::openDealWindowRecd , this ,&PlayWindow::openDealSelectionWindow);
    connect(socket4,&Table4SockClient::showNewPlayRecd , this ,&PlayWindow::backToNewPlay);}


	randomizeSeed();
	game = new Game();
	game->findNextDeal();
	
	// This window
    centralWidget = new QWidget(this);
	setTitle(this);
    setMinimumSize(MIN_WIDTH,MIN_HEIGHT);
	setObjectName("playWindow"); // Otherwise all its children inherit the background color
    //setStyleSheet("#playWindow {background-color: green; }");
    setStyleSheet("#playWindow {color : white ; background-color: green; }");
    //setCentralWidget(centralWidget);
	cardsAreClickable = false;
	firstSuit = NoTrump;
	tricksMade[0] = 0;
	tricksMade[1] = 0;
	waitForAI = true;
	waitForAutoplaySingles = true;
	isPaused = false;
	
	// Menu
	/*menuBar = new QMenuBar(centralWidget);
	QMenu *fileMenu = new QMenu("File");
	fileMenu->addMenu(new QMenu("menu1_SubMenu"));
	menuBar->addMenu(fileMenu);*/
	
    createAllHandWidgets();


	dealInfoLabel = new QLabel("", this);
    dealInfoLabel->setStyleSheet("QLabel { color : white; background-color : green;  }");
    gridLayout.addWidget(dealInfoLabel, 0, 2);
    gridLayout.setAlignment(dealInfoLabel, Qt::AlignRight);
    updateDealInfoLabel();
	
	contractInfoLabel = new QLabel("", this);
    contractInfoLabel->setStyleSheet("QLabel { color : white; background-color : green;  }");
    gridLayout.addWidget(contractInfoLabel, 2, 2);
	gridLayout.setAlignment(dealInfoLabel, Qt::AlignRight);
	
	tricksInfoLabel = new QLabel("", this);
    tricksInfoLabel->setStyleSheet("QLabel { color : white; background-color : green;  }");
	gridLayout.addWidget(tricksInfoLabel, 0, 0);
    gridLayout.setAlignment(tricksInfoLabel, Qt::AlignLeft);

    QVBoxLayout *buttonLayout = new QVBoxLayout;

    QPushButton *hideChatButton = new QPushButton("Hide/Show Chat", this);
    hideChatButton->setGeometry(100, 100, 60, 25);
    connect(hideChatButton, SIGNAL (clicked()), this, SLOT (hideChatWindow()));
    QPushButton *dealButton = new QPushButton("Deal / Bid", this);
    dealButton->setGeometry(100, 100, 60, 25);
    connect(dealButton, SIGNAL (clicked()), this, SLOT (DEALSelection()));
    QPushButton *quitButton = new QPushButton("Back to Seat Select", this);
    quitButton->setGeometry(100, 100, 60, 25);
    connect(quitButton, SIGNAL (clicked()), this, SLOT (backToWelcome()));
    QPushButton *restartButton = new QPushButton("Restart Game", this);
    restartButton->setGeometry(100, 100, 60, 25);
    connect(restartButton, SIGNAL (clicked()), this, SLOT (backToNewPlay()));


        buttonLayout->addWidget(hideChatButton);
        hideChatButton->setMaximumSize(140,25);
        buttonLayout->addWidget(dealButton);
        dealButton->setMaximumSize(140,25);
        buttonLayout->addWidget(quitButton);
        quitButton->setMaximumSize(160,25);
        buttonLayout->addWidget(restartButton);
        restartButton->setMaximumSize(140,25);

      gridLayout.addLayout(buttonLayout, 2, 0);
      hideChatButton->setEnabled(true);
      dealButton->setEnabled(false);
      quitButton->setEnabled(false);
      restartButton->setEnabled(false);
     if (PositionNorth) {dealButton->setEnabled(true);}
     if (PositionNorth) {quitButton->setEnabled(true);}
     if (PositionNorth) {restartButton->setEnabled(true);}
	
	playedCardsLayout = new PlayedCardsLayout(&playedCardsWidgets, game, Q_NULLPTR);
    gridLayout.addLayout(playedCardsLayout, 1, 1);
	
	QPixmap arrowImage("./images/arrow.png");
	for(int i=0; i<4; i++)
	{
		QTransform transformArrow;
        transformArrow.scale(0.5, 0.5);
		arrows[i] = new QLabel;
		QFlags<Qt::AlignmentFlag> flag;
		switch(Position(i))
		{
			case North:
				flag = Qt::AlignHCenter | Qt::AlignTop;
				break;
			case South:
				transformArrow.rotate(180);
				flag = Qt::AlignHCenter | Qt::AlignBottom;
				break;
			case East:
				transformArrow.rotate(90);
				flag = Qt::AlignVCenter | Qt::AlignRight;
				break;
			case West:
				transformArrow.rotate(270);
				flag = Qt::AlignVCenter | Qt::AlignLeft;
				break;
		}
        gridLayout.addWidget(arrows[i], 1, 1, flag);
		arrows[i]->setPixmap(arrowImage.transformed(transformArrow));
		arrows[i]->setVisible(false);
	}
	
	/*QPushButton* test = new QPushButton("test");
	test->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	gridLayout.addWidget(test, 1, 1);*/
		
    gridLayout.setColumnStretch(1, 1);
    gridLayout.setRowStretch(1, 1);
	centralWidget->setLayout(&gridLayout);
    //centerWindow(this);
	show();


    //dealSelectionWindow = new DealSelectionWindow(this);
    //dealSelectionWindow->show();

	PauseClickGrabber *g = new PauseClickGrabber(this);
	installEventFilter(g);
	
	dealOverWindow = new DealOverWindow(this);
    connect(dealOverWindow,&DealOverWindow::dealOverBackToMenu , this ,&PlayWindow::backToWelcome);
    connect(dealOverWindow,&DealOverWindow::dealOverNextDeal , this ,&PlayWindow::backToNewPlay);


}

PlayWindow::~PlayWindow()
{
	destroyAllHandWidgets();
}
void PlayWindow::DEALSelection()
{
    if (!PracticePlay) {
        if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QStringLiteral ("OpenDealWindow"));}
        if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QStringLiteral ("OpenDealWindow"));}
        if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QStringLiteral ("OpenDealWindow"));}
        if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QStringLiteral ("OpenDealWindow"));}
        }
    dealSelectionWindow = new DealSelectionWindow(this);
    dealSelectionWindow->show();

}
void PlayWindow::openDealSelectionWindow()
{

    dealSelectionWindow = new DealSelectionWindow(this);
    dealSelectionWindow->show();

}
void PlayWindow::hideChatWindow()
{
   emit changeChatWindow();
 }
void PlayWindow::backToWelcome()
{
    PracticePlay=false;
    if (PositionNorth){
    if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
    if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
    if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
    if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QStringLiteral ("EndOfGameBackToMenu"));}
    }
    //  close();
   emit backtoWelcome();

}
void PlayWindow::backToNewPlay()
{
    if (PositionNorth){
    if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QStringLiteral ("ShowNewPlayWindow"));}
    if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QStringLiteral ("ShowNewPlayWindow"));}
    if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QStringLiteral ("ShowNewPlayWindow"));}
    if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QStringLiteral ("ShowNewPlayWindow"));}
    }
   emit backtoNewPlay();
   // close();
}
void PlayWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
}

void PlayWindow::closeEvent(QCloseEvent *event)
{
	QWidget::closeEvent(event);
    close();
}

void PlayWindow::createAllHandWidgets()
{
	for(int i=0; i<4; i++) createHandWidgets((Position)i);
}

void PlayWindow::createHandWidgets(Position p)
{
	Player *player = game->getPlayers()[p];
	cardLayouts[p] = new CardLayout(player, &handsWidgets[p], this);
	for (auto &card : player->getHand())
	{
		CardWidget* cardWidget = new CardWidget(card, this);
		handsWidgets[p].push_back(cardWidget);
		cardLayouts[p]->addWidget(cardWidget);
	}
    if(p == North)	gridLayout.addLayout(cardLayouts[p], 0, 1);
    if(p == East)	gridLayout.addLayout(cardLayouts[p], 1, 2);
    if(p == South)	gridLayout.addLayout(cardLayouts[p], 2, 1);
	if(p == West)	gridLayout.addLayout(cardLayouts[p], 1, 0);
}

void PlayWindow::destroyAllHandWidgets()
{
	for(int i=0; i<4; i++) destroyHandWidgets((Position)i);
}

void PlayWindow::destroyHandWidgets(Position p)
{
	for (auto &cardWidget : handsWidgets[p])
	{
		delete cardWidget;
	}
	handsWidgets[p].clear();
	if(cardLayouts[p])
	{
		delete cardLayouts[p];
		cardLayouts[p] = NULL;
	}
}

void PlayWindow::startBidding()
{
	bidWindow = new BidWindow(this);
    connect(bidWindow,SIGNAL(bidBackToPlay()),this,SLOT(backToNewPlay()));

	bidWindow->show();
	//delete dealSelectionWindow;
}

Game* PlayWindow::getGame() const
{
	return game;
}

bool PlayWindow::getCardsAreClickable() const
{
	return cardsAreClickable;
}

void PlayWindow::setCardsAreClickable(bool c)
{
	cardsAreClickable = c;
}

void PlayWindow::updateDealInfoLabel()
{
	QString dealNumber = QString("Deal: ") + QString::number(getSeed());
	QString dealer = QString("Dealer: ") + QString::fromStdString(positionToString(game->getDealer()));
	QString vulnerability = QString("Vulnerable: ") + QString::fromStdString(vulnerabilityToString(game->getVulnerability()));
	dealInfoLabel->setText(dealNumber + "\n" + dealer + "\n" + vulnerability);
}

void PlayWindow::updateContractInfoLabel()
{
	contractInfoLabel->setText(QString::fromStdString(game->getContract().toString()));
}

void PlayWindow::playCard(CardWidget *c)
{
	Card card = c->getCard();
	Position p = game->getPositionFromCard(card);
	Player *player = game->getPlayers()[p];
	if(game->getPlayedCardsHistory().size() % 4 == 0) firstSuit = NoTrump; // So player can choose card of any suit
	if(game->whoseTurnIsItToPlay() != p) return;
	if(!player->hasCard(card)) return;
	if(!player->isValidPlay(card, firstSuit)) return;
	
	if(game->getPlayedCardsHistory().size() % 4 == 0) firstSuit = card.getSuit();
	cardLayouts[p]->removeCardWidget(c);
	playedCardsWidgets.push_back(c);
	c->setCardImageFaceUp();
	playedCardsLayout->addWidget(c);
	player->clearCard(card);
	game->addCardToPlayHistory(card);
	updateCurrentPlayerArrow();
    if (lastCardPlayedMessage != clickCardWidgetMessage ) {
                lastCardPlayedMessage = clickCardWidgetMessage ;
        if (!PracticePlay) {

        if (Table1) {Table1SockClient *socket = Table1SockClient::instance();socket->sendMesssage(QString (clickCardWidgetMessage));}
        if (Table2) {Table2SockClient *socket2 = Table2SockClient::instance();socket2->sendMesssage(QString (clickCardWidgetMessage));}
        if (Table3) {Table3SockClient *socket3 = Table3SockClient::instance();socket3->sendMesssage(QString (clickCardWidgetMessage));}
        if (Table4) {Table4SockClient *socket4 = Table4SockClient::instance();socket4->sendMesssage(QString (clickCardWidgetMessage));}
            }
          }
	if(game->getPlayedCardsHistory().size() % 4 == 0)
	{
		tricksMade[game->whoseTurnIsItToPlay() % 2]++; // The one whose turn it is is necessarily the one who one the trick
		updateTricksInfoLabel();
        isPaused = true;
		if(!options.waitAfterTrick) QTimer::singleShot(options.minimalWait, this, SLOT(resumeFromPause()));
	}
	else playingProcess();
}
void PlayWindow::playRemoteCard(QString message)
{     Card cardr ;
      qDebug()<< message;
    if (lastMessageParsed != message ) {
            lastMessageParsed = message ;
    //    qDebug() << "Parse Card Message " << message;
        QString leveltext = message.section(',', 1, 1);
        QString suittext = message.section(',', 2, 2);
        cardr.value = leveltext.toInt();
        std::string suitstr = suittext.toStdString();
       // suit = charToSuit(suitstr[1]);
        if (suittext == "Clubs"){cardr.suit =Clubs; }
        if (suittext == "Diamonds"){cardr.suit =Diamonds; }
        if (suittext == "Hearts"){cardr.suit =Hearts; }
        if (suittext == "Spades"){cardr.suit =Spades; }
        if (suittext == "No Trump"){cardr.suit =NoTrump; }

         QString message1 =  "parsed from message " ;
                message1.append(QString::number(cardr.value));
                message1.append (",") ;
               std::string suittext1 = suitToString(cardr.suit);
               QString qstr1 = QString::fromStdString(suittext1);
               message1.append(qstr1);

    }
       //this_thread::sleep_for(chrono::milliseconds(remotePlayDelay));
       CardWidget *c=getCardWidgetFromCard(cardr) ;

    //Card card = c->getCard();
    Position p = game->getPositionFromCard(cardr);
    Player *player = game->getPlayers()[p];
    if(game->getPlayedCardsHistory().size() % 4 == 0) firstSuit = NoTrump; // So player can choose card of any suit
    if(game->whoseTurnIsItToPlay() != p) return;
    if(!player->hasCard(cardr)) return;
    if(!player->isValidPlay(cardr, firstSuit)) return;

    if(game->getPlayedCardsHistory().size() % 4 == 0) firstSuit = cardr.getSuit();
    cardLayouts[p]->removeCardWidget(c);
    playedCardsWidgets.push_back(c);
    c->setCardImageFaceUp();
    playedCardsLayout->addWidget(c);
    player->clearCard(cardr);
    game->addCardToPlayHistory(cardr);
    updateCurrentPlayerArrow();
    if(game->getPlayedCardsHistory().size() % 4 == 0)
    {
        tricksMade[game->whoseTurnIsItToPlay() % 2]++; // The one whose turn it is is necessarily the one who one the trick
        updateTricksInfoLabel();
        isPaused = true;
        if(!options.waitAfterTrick) QTimer::singleShot(options.minimalWait, this, SLOT(resumeFromPause()));
    }
    else playingProcess();
}

void PlayWindow::updateCurrentPlayerArrow()
{
	Position p = game->whoseTurnIsItToPlay();
	int numberOfPlayedCards = game->getPlayedCardsHistory().size();
	for(int i=0; i<4; i++) arrows[i]->setVisible(Position(i) == p && numberOfPlayedCards != 52);
}

void PlayWindow::playingProcess()
{
	updateTricksInfoLabel();
	int numberOfPlayedCards = game->getPlayedCardsHistory().size();
	Position player = game->whoseTurnIsItToPlay();
	Position dummyPosition = nextTeammate(game->getContract().getDeclarer());
	bool isDummy = (player == dummyPosition);
	Suit firstSuit = (numberOfPlayedCards%4 == 0 ? NoTrump : game->getPlayedCardsHistory().at((numberOfPlayedCards-1) - (numberOfPlayedCards-1)%4).getSuit());
	Position actualPlayer = (isDummy ? game->getContract().getDeclarer() : player);
	
	if(numberOfPlayedCards == 52)
	{
		Player **players = game->getPlayers();
		destroyAllHandWidgets();
		for(int i=0; i<4; i++)
		{
			for(auto &card : recreateHand(Position(i), game->getPlayedCardsHistory(), game->getContract())) players[i]->addCardToHand(card);
            players[i]->sortHand(game->getContract().getSuit());
		}
		createAllHandWidgets();
		dealOverWindow->show();
		return;
	}
	
	if(game->getPlayers()[actualPlayer]->getIsHuman())
	{
		if(options.autoplaySingles && game->getPlayers()[player]->getPlayableCards(firstSuit).size() == 1)
		{
			// Autoplay single
			if(options.minimalWait && waitForAutoplaySingles && numberOfPlayedCards)
			{
				waitForAutoplaySingles = false;
				QTimer::singleShot(options.minimalWait, this, SLOT(playingProcess()));
				return;
			}
			waitForAutoplaySingles = true;
			Card card = game->getPlayers()[player]->getPlayableCards(firstSuit).front();
			playCard(getCardWidgetFromCard(card)); // Validity has already been checked since it's the only playable card
			cardsAreClickable = false;
			return;
		}
		else
		{
			cardsAreClickable = true;
			return;
		}
	}
	else cardsAreClickable = false;
	
	if(options.AI_playDelay && waitForAI && numberOfPlayedCards)
	{
		waitForAI = false;
		QTimer::singleShot(options.AI_playDelay, this, SLOT(playingProcess()));
		return;
	}
	waitForAI = true;
	
	Card playedCard;
	do
	{
		playedCard = (isDummy ? game->getPlayers()[actualPlayer]->playCard(firstSuit, game->getPlayers()[dummyPosition]->getHand()) : game->getPlayers()[actualPlayer]->playCard(firstSuit));
	} while(!game->getPlayers()[player]->hasCard(playedCard) || !game->getPlayers()[player]->isValidPlay(playedCard, firstSuit));
	playCard(getCardWidgetFromCard(playedCard));
}

CardWidget* PlayWindow::getCardWidgetFromCard(Card c) const
{
	Position p = game->getPositionFromCard(c);
	for (auto &o : handsWidgets[p]) if(o->getCard() == c) return o;
    if(DEBUG_COUT) std:: cout << std::flush << "PlayWindow::getCardWidgetFromCard ERROR" << endl << std::flush;
	return Q_NULLPTR;
}

void PlayWindow::resumeFromPause()
{
	if(isPaused)
	{
		playedCardsLayout->clearPlayedCardsWidgets();
        isPaused = false;
		updateCurrentPlayerArrow();

		playingProcess();
	}
}

bool PlayWindow::getIsPaused() const
{
	return isPaused;
}

void PlayWindow::updateTricksInfoLabel() const
{
	tricksInfoLabel->setText(QString::fromStdString("NS tricks: " + to_string(tricksMade[0]) + "\nEW tricks: " + to_string(tricksMade[1])));
}

void PlayWindow::startNewGame(RANDOMNESS_SIZE currentDeal)
{
	destroyAllHandWidgets();
	setSeed(currentDeal);
	game->prepareForNextGame();
	game->findNextDeal();
	
	cardsAreClickable = false;
	firstSuit = NoTrump;
	tricksMade[0] = 0;
	tricksMade[1] = 0;
	waitForAI = true;
	waitForAutoplaySingles = true;
    isPaused = false;
	
	createAllHandWidgets();
	updateDealInfoLabel();
	contractInfoLabel->setText("");
	updateTricksInfoLabel();
	for(int i=0; i<4; i++) arrows[i]->setVisible(false);
	
    //bidWindow->reset();
    bidWindow->show();
	
}

