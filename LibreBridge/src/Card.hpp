#ifndef CARD_HPP
#define CARD_HPP

#include <cstdint>
#include <string>
#include "LibreBridge.hpp"

class Card
{

public:
		Suit suit;
        uint8_t value;

	protected:
	public:
		Card(uint8_t v, Suit s);
        Card();
		static char valueToChar(uint8_t value);
		static uint8_t charToValue(char c);
		static char suitToChar(Suit suit);
		
		void printCard();

        bool operator == (const Card & card);
        bool operator < (const Card & card);
		uint8_t getValue() const;
		Suit getSuit() const;
		static Card stringToCard(std::string s);
		int getImageNumber() const; // Compatible with PokerTH sets
};

#endif
