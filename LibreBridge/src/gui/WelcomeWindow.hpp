#ifndef WELCOMEWINDOW_HPP
#define WELCOMEWINDOW_HPP

#include <QWidget>
#include <QObject>
#include <QDialog>
class QPushButton;
class QPixmap;
class QResizeEvent;
class PlayWindow;

class WelcomeWindow : public QDialog
{
	Q_OBJECT
	public:
		explicit WelcomeWindow(QWidget *parent = Q_NULLPTR);
		QPushButton *quitButton;
		QPushButton *playButton;
        QPushButton *playAsNorthButton;
        QPushButton *playAsSouthButton;
        QPushButton *playAsEastButton;
        QPushButton *playAsWestButton;

	public slots:
        void startLocalGame();
        void startPracticeGame();
        void sendPlay();
        void playAsNorth();
        void playAsSouth();
        void playAsEast();
        void playAsWest();
        void northSeated();
        void eastSeated();
        void southSeated();
        void westSeated();
     signals:
        void openPlayWindow();
	protected:
		void resizeEvent(QResizeEvent *event) override;
	private:
        QWidget *centralWidget;
		QPixmap background;
        PlayWindow *playWindow;
};

#endif
