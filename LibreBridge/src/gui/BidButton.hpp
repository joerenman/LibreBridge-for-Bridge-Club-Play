#ifndef BIDBUTTON_HPP
#define BIDBUTTON_HPP

#include <QPushButton>
#include "../LibreBridge.hpp"


class BidWindow;

class BidButton : public QPushButton 
{
	Q_OBJECT
	public:
		explicit BidButton(Suit suit, int level, QWidget *parent = Q_NULLPTR);
		void setImage();

	public slots:
		void clickBidButton();
        void sendclickBidButton();

public:
		Suit suit;
		int level;
        QString message;
		BidWindow *parent;
};

#endif
