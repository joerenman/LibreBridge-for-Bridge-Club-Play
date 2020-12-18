#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QIcon>
#include <QSize>
#include <QString>
#include <QTimer>
#include <iostream>
#include "CardWidget.hpp"
#include "PlayWindow.hpp"
#include <QtCore/QDebug>
#include <string>
#include <cstdint>
#include "../Misc.hpp"
#include "Table1SockClient.hpp"
#include "Table2SockClient.hpp"
#include "Table3SockClient.hpp"
#include "Table4SockClient.hpp"
#include "Common.hpp"

extern QString lastMessageParsed ;
extern QString lastCardPlayedMessage ;
extern bool PracticePlay;
extern bool Table1;
extern bool Table2;
extern bool Table3;
extern bool Table4;

QString clickCardWidgetMessage=" ";
CardWidget::CardWidget(Card c, QWidget *parent) : QPushButton("", parent)
{
	this->parent = (PlayWindow*)parent;
	card = c;
	isFlashing = false;
	isEmphasized = false;
	isFaceUp = false;
	
	setCardImageFaceUp();
    setStyleSheet("QPushButton {background-color: black;}");
	QSize size = cardImage.rect().size();
    setIconSize(size);
    resize(size);
    setMinimumSize(size);
	setFlat(true);


    connect(this, SIGNAL (clicked()), this, SLOT (sendclickCardWidget()));
	connect(this, SIGNAL (clicked()), this, SLOT (clickCardWidget()));
}

Card CardWidget::getCard()
{
	return card;
}

void CardWidget::sendclickCardWidget()
{
    QString message1 =  "clickCardWidget," ;
    std::string cardtext1;
    cardtext1 = std::to_string(card.value);
    QString qstr1 = QString::fromStdString(cardtext1);
    std::string suittext1 = suitToString(card.suit);
    QString qstr2 = QString::fromStdString(suittext1);
    message1.append(qstr1);
      message1.append (",");
    message1.append(qstr2);
    clickCardWidgetMessage =message1;



}


void CardWidget::clickCardWidget()
{
	if(parent->getIsPaused())
	{
		parent->resumeFromPause();
		return; // We just wanted to unpause, not play the card
	}
	if(!parent->getCardsAreClickable()) return;
	stopFlashing();
	resetColor();
	parent->playCard(this);



}

void CardWidget::setEmphasisColor()
{
	QPixmap emphasisedImage = cardImage;
	QPixmap emphasisedColorFilledImage = cardImage;
	QPixmap maskedImage = cardImage;
	emphasisedColorFilledImage.fill("#ffff80");
	QPainter painter(&emphasisedImage);
	painter.drawPixmap(0, 0, emphasisedColorFilledImage);
	QBitmap mask = maskedImage.createMaskFromColor("#F0F0F0", Qt::MaskInColor);
	maskedImage.setMask(mask);
	painter.drawPixmap(0, 0, maskedImage);
	setIcon(QIcon(emphasisedImage));
	isEmphasized = true;
}

void CardWidget::startFlashing()
{
	isFlashing = true;
	keepFlashing();
}

void CardWidget::keepFlashing()
{
	if(!options.theme_flashingDelay || !isFlashing)
	{
		resetColor();
		isFlashing = false;
	}
	else
	{
		if(isEmphasized) resetColor();
		else setEmphasisColor();
		QTimer::singleShot(options.theme_flashingDelay, this, SLOT(keepFlashing()));
	}
}

void CardWidget::resetColor()
{
	setIcon(cardImage);
	isEmphasized = false;
}

void CardWidget::stopFlashing()
{
	isFlashing = false;
	resetColor();
}

void CardWidget::setCardImageFaceUp(bool faceUp)
{
	if(isFaceUp != faceUp)
	{
		cardImage = QPixmap(QString::fromStdString(getImagePath(faceUp)));
		setIcon(QIcon(cardImage));
		isFaceUp = faceUp;
	}
}

std::string CardWidget::getImagePath(bool faceUp) const
{
	if(faceUp) return "./images/cards/" + options.theme_cards + "/" + std::to_string(card.getImageNumber()) + ".png";
	else return "./images/cards/" + options.theme_cards + "/flipside.png";
}
