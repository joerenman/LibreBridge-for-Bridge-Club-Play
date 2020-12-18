#ifndef PLAYWINDOW_HPP
#define PLAYWINDOW_HPP

#include <vector>
#include <QMainWindow>
#include <QDialog>
#include <QGridLayout>
#include "../LibreBridge.hpp"
#include "../Card.hpp"
class CardLayout;
class QMenuBar;
class QPushButton;
class QLabel;
class CardWidget;
class DealSelectionWindow;
class BidWindow;
class DealOverWindow;
class Game;
class PlayedCardsLayout;


class PlayWindow : public QDialog
{
	Q_OBJECT
	public:
		explicit PlayWindow(QWidget *parent = Q_NULLPTR);
        ~PlayWindow();
        void closeEvent(QCloseEvent *event) override;
		void createAllHandWidgets();
		void createHandWidgets(Position p);
		void destroyAllHandWidgets();
		void destroyHandWidgets(Position p);
		Game* getGame() const;
		void startBidding();
		bool getCardsAreClickable() const;
		void setCardsAreClickable(bool c);
		void updateDealInfoLabel();
		void updateContractInfoLabel();
		void playCard(CardWidget* c);
		void updateCurrentPlayerArrow();
		bool getIsPaused() const;
        void startNewGame(RANDOMNESS_SIZE currentDeal);

	signals:
        void backtoWelcome();
        void backtoNewPlay();
        void changeChatWindow();

	public slots:
		void playingProcess();
		void resumeFromPause();
        void playRemoteCard(QString message);
        void hideChatWindow();
        void DEALSelection();
        void backToWelcome();
        void backToNewPlay();
        void openDealSelectionWindow();
	protected:
        void resizeEvent(QResizeEvent *event) override;
	private:
		DealSelectionWindow *dealSelectionWindow;
		BidWindow *bidWindow;
		DealOverWindow *dealOverWindow;
		QMenuBar *menuBar;
		QMenu *fileMenu;
		QWidget *centralWidget;
		Game *game;
        QGridLayout gridLayout;
		CardLayout *cardLayouts[4];
		std::vector<CardWidget*> handsWidgets[4];
		bool cardsAreClickable;
		QLabel *dealInfoLabel;
		QLabel *contractInfoLabel;
		QLabel *tricksInfoLabel;
        QLabel *northInfoLabel;
		PlayedCardsLayout *playedCardsLayout;
		std::vector<CardWidget*> playedCardsWidgets;
		Suit firstSuit;
		QLabel *arrows[4];
        //int tricksMade[2]; // %2 for team
		bool waitForAI;
		bool waitForAutoplaySingles;
		bool isPaused; // between hands
		CardWidget* getCardWidgetFromCard(Card c) const;
		void updateTricksInfoLabel() const;
    public:
        int tricksMade[2]; // %2 for team

};

#endif
