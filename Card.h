#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Card {
public:
	int suit, value;


	Card(const int& suit = 0, const int& value = 14) :suit{ suit }, value{ value } {}
	Card(const string& name) {
		int size = name.size();
		suit = to_int_suit(name[size - 1]);
		value = to_int_value(name[size - 2]);
		if (value < 0)
			value = stoi(name.substr(0, size - 1));
	}

	int points()const {
		if (value <= 10)
			return value;
		switch (value) {
		case 11:
		case 12:
		case 13:
			return 10;
		case 14:
			return 11;
		default:
			return -1;
		}
	}

	static bool is_red(const Card& card) {
		return card.suit > 1;
	}
	static bool is_black(const Card& card) {
		return card.suit < 2;
	}



	string print()const {
		stringstream ss;
		ss << to_suit(suit);
		if (value <= 10) {
			ss << value;
		}
		else {
			ss << to_char_value(value);
		}
		return ss.str();
	}
	friend string to_string(const Card& card) {
		stringstream ss;
		if (card.value <= 10) {
			ss << card.value;
		}
		else {
			ss << to_char_value(card.value);
		}
		ss << to_char_suit(card.suit);
		return ss.str();
	}


	static char to_char_suit(const int& suit) {
		switch (suit) {
		case 0: return 'S';
		case 1: return 'C';
		case 2: return 'D';
		case 3: return 'H';
		default: return ' ';
		}
	}
	static char to_char_value(const int& value) {
		switch (value) {
		case 11: return 'J';
		case 12: return 'Q';
		case 13: return 'K';
		case 14: return 'A';
		default: return ' ';
		}
	}
	static int to_int_suit(const char& suit) {
		switch (suit) {
		case 'S': return 0;
		case 'C': return 1;
		case 'D': return 2;
		case 'H': return 3;
		default: return -1;
		}
	}
	static int to_int_value(const char& value) {
		switch (value) {
		case 'J': return 11;
		case 'Q': return 12;
		case 'K': return 13;
		case 'A': return 14;
		default: return -1;
		}
	}
	static char to_suit(const int& suit) {
		switch (suit) {
		case 0: return 6;
		case 1: return 5;
		case 2: return 4;
		case 3: return 3;
		default: return ' ';
		}
	}
	/*static string to_suit(const int &suit){
		switch(suit){
		case 0: return "♤";
		case 1: return "♧";
		case 2: return "♦";
		case 3: return "♥";
		default: return "";
		}
	}*/


};

#endif /* CARD_H_ */