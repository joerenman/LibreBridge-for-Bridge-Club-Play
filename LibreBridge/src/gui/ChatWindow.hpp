#ifndef CHATWINDOW_HPP
#define CHATWINDOW_HPP

#include <QDialog>
class QPushButton;
class QCloseEvent;
class PlayWindow;
class QTextEdit;
class QLabel;
class QDialogButtonBox;
class QLineEdit;
class QPlainTextEdit;

class ChatWindow : public QDialog 
{
	Q_OBJECT
	public:
		explicit ChatWindow(QWidget *parent = Q_NULLPTR);

	signals:
	public slots:
        void sendTableChat();
        void updateTableChat(QString message);
        void sendGeneralChat();
        void updateGeneralChat(QString message);

	protected:
	private:
		PlayWindow *playWindow;
		bool showWelcomeWindowWhenDone;
        QPushButton *sendTableChatButton;
        QPushButton *sendGeneralChatButton;
        
        QPlainTextEdit *tableChatDisplay;
        QPlainTextEdit *generalChatDisplay;
        QLineEdit *tableText;
        QLineEdit *generalText;
        QDialogButtonBox *buttonBox;

};

#endif
