#ifndef BIDWINDOW_HPP
#define BIDWINDOW_HPP

#include <QDialog>
#include "../LibreBridge.hpp"
#include <QMessageBox>
class QLabel;
class QPushButton;
class QGridLayout;
class QHBoxLayout;
class WelcomeWindow;
class PlayWindow;
class BidButton;
class Game;
class ContractWindow;

class BidWindow : public QDialog 
{
	Q_OBJECT
	public:
		explicit BidWindow(QWidget *parent = Q_NULLPTR);
		void closeEvent(QCloseEvent *event);
		void disableAllButtons();
		void enableButtons();
		void bidClick(BetType betType, uint8_t level, Suit suit);
		PlayWindow* getPlayWindow() const;
		void reset();
	signals:
        void bidBackToPlay();
	public slots:
		void bidPass();
        void sendbidPass();
		void bidDouble();
        void sendbidDouble();
		void biddingProcess();
        void parseBidMessage(QString message);
	protected:
	private:
		PlayWindow *parent;
		bool showWelcomeWindowWhenDone;
       // QPushButton *evalButton;
       // QPushButton *hintButton;
       // QPushButton *interpretButton;
		QPushButton *passButton;
        QPushButton *doubleButton;
		QGridLayout *bidHistoryDisplayGrid;
		QHBoxLayout *bidHistoryPositionLabelsBox;
        QHBoxLayout *bidHistoryNextBidderBox;
		QLabel *bidHistoryPositionLabels[4];
		QLabel *bidHistoryLabels[28];
        QLabel *bidHistoryNextBidderLabel;
		int currentBidHistoryLabel;
		QWidget *bidHistoryPositionLabelsWidget;
        QWidget *bidHistoryNextBidderBoxWidget;
		QLabel *bidHistoryWidget;
		QWidget *bidButtonsWidget;
		QGridLayout *bidButtonsLayout;
		BidButton *bidButtons[35];
		QLabel *bidLevels[7];
		bool isDoubleLegal;
		bool isRedoubleLegal;
		uint8_t lastLevel;
		Suit lastSuit;
		Position playerWhoBetNormallyLast;
		Position playerPos;
		bool lastDoubled;
		bool lastRedoubled;
		Game* game;
		ContractWindow *contractWindow;
		bool waitForAI;
};

#endif
