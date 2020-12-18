#ifndef DEALSELECTIONWINDOW_HPP
#define DEALSELECTIONWINDOW_HPP

#include <QDialog>
#include <QObject>
class QPushButton;
class QResizeEvent;
class QCloseEvent;
class QLineEdit;
class PlayWindow;
class SeedValidator;

class DealSelectionWindow : public QDialog 
{
	Q_OBJECT
	public:
		explicit DealSelectionWindow(QWidget *parent = Q_NULLPTR);
		QLineEdit *seedTextBox;
		QPushButton *seedMinusButton;
		QPushButton *seedPlusButton;
		void closeEvent(QCloseEvent *event);
//	signals:
	public slots:
		void minusDeal();
		void plusDeal();
		void updateOnSeedChange(const QString &text);
		void startBidding();
        void sendminusDeal();
        void sendplusDeal();
        void sendstartBidding();
	protected:
	private:
		PlayWindow *parent;
		SeedValidator *seedValidator;
		QPushButton *playButton;
		bool showWelcomeWindowWhenDone;
};

#endif
