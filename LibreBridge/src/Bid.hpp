#ifndef BID_HPP
#define BID_HPP

#include <cstdint>
#include <string>
#include "LibreBridge.hpp"

class Bid {
    //private:
public:
		Position player;
		BetType betType;
		uint8_t	suit : 3,
				level : 3,
				:2;
	protected:
	public:
		void setBid(std::string stringBid, Position pla, uint8_t lastLevel, Suit lastSuit, bool lastDoubled, bool lastRedoubled, Position playerWhoBetNormallyLast);
		void setBid(BetType& betType, Suit& suit, uint8_t& level, Position pla, uint8_t lastLevel, Suit lastSuit, bool lastDoubled, bool lastRedoubled, Position playerWhoBetNormallyLast);
		std::string toString();
		BetType getBetType();
		Suit getSuit();
		uint8_t getLevel();
};

#endif
