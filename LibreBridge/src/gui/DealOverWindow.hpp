#ifndef DEALOVERWINDOW_HPP
#define DEALOVERWINDOW_HPP

#include <QDialog>
class QPushButton;
class QCloseEvent;
class PlayWindow;
class QTextEdit;
class QLabel;
class QDialogButtonBox;

class DealOverWindow : public QDialog 
{
	Q_OBJECT
	public:
		explicit DealOverWindow(QWidget *parent = Q_NULLPTR);
		void closeEvent(QCloseEvent *event);
	signals:
       void dealOverBackToMenu();
       void dealOverNextDeal();
	public slots:
        void score();
		void playAgain();
		void reviewBidding();
		void replay();
		void save();
		void print();
		void nextDeal();
		void backToMenu();
        void updateScoreReceived(QString message);
	protected:
	private:
		PlayWindow *playWindow;
		bool showWelcomeWindowWhenDone;
		QPushButton *scoreButton;
		QPushButton *playAgainButton;
		QPushButton *reviewBiddingButton;
		QPushButton *replayButton;
		QPushButton *saveButton;
		QPushButton *printButton;
		QPushButton *nextDealButton;
		QPushButton *backToMenuButton;
        QLabel *scoreLabel;
        QLabel *pointsLabel;
        QTextEdit *pointsDisplay;
        QDialogButtonBox *buttonBox;

};

#endif
