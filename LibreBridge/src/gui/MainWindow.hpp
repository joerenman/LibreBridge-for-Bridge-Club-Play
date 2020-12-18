#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <vector>
#include <QMainWindow>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QStackedWidget>
#include "../LibreBridge.hpp"

class QMenuBar;
class QPushButton;
class QLabel;


class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = Q_NULLPTR);
		~MainWindow();
        void closeEvent(QCloseEvent *event) override;

public    slots:    void setStartDeal(QString);
private	slots:
        void showPlayWindow();
        void showNewPlayWindow();
        void backToWelcomeWindow();
        void hideShowChatWindow();

	protected:
		void resizeEvent(QResizeEvent *event) override;
        void centerAndResize();
	private:
		
		QMenuBar *menuBar;
		QMenu *fileMenu;
        QWidget *welcomePageWidget;
        QWidget *playPageWidget;
        QWidget *tablePageWidget;
        QWidget *centralWidget1;
        QWidget *centralWidget2;
        QStackedWidget *stackedWidget;
        QWidget *chatWidget;
        QWidget *tableChatWidget;
		QGridLayout gridLayout;

        QPlainTextEdit *textEdit2;

};

#endif
