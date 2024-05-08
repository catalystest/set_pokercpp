#ifndef DECK_H_
#define DECK_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include "Card.h"
#include "Sort.h"

using namespace std;

class Deck {
private:
	bool is_flush(vector<Card> hand)const {
		return (hand[0].suit == hand[1].suit) and (hand[0].suit == hand[2].suit);
	}
	bool is_straight(vector<Card> hand)const {
		vector<int> sorted(hand.size());
		for (int i = 0; i < 3; ++i) {
			sorted[i] = hand[i].value;
		}
		bubble_sort(sorted);
		return (sorted[0] == sorted[1] - 1) and (sorted[0] == sorted[2] - 2);
	}
	bool is_triple(vector<Card> hand)const {
		return (hand[0].value == hand[1].value) and (hand[0].value == hand[2].value);
	}
	bool is_double(vector<Card> hand)const {
		return (hand[0].value == hand[1].value) or (hand[0].value == hand[2].value) or (hand[1].value == hand[2].value);
	}
public:
	vector<Card> cards{};
	Deck() {
		for (int suit = 0; suit < 4; ++suit)
			for (int value = 2; value < 15; ++value)
				cards.push_back(Card{ suit, value });
	}
	void shuffle() {
		int size = cards.size();
		mt19937 gen{ random_device{}() };
		uniform_int_distribution<int> dist{ 0, size - 1 };
		for (int i = 0; i < 1000; ++i) {
			int from{ dist(gen) }, to;
			do {
				to = dist(gen);
			} while (to == from);
			swap(cards[from], cards[to]);
		}
	}
	vector<Card> get_player_cards()const {
		vector<Card> p_cards(3);
		for (int i = 0; i < 3; ++i) {
			p_cards[i] = cards[i];
		}
		return p_cards;
	}
	vector<Card> get_dealer_cards()const {
		vector<Card> d_cards(3);
		for (int i = 3; i < 6; ++i) {
			d_cards[i - 3] = cards[i];
		}
		return d_cards;
	}
	int check_for_combo(vector<Card> hand)const {
		if (is_flush(hand) and is_straight(hand)) {
			return 5;
		}
		else if (is_triple(hand)) {
			return 4;
		}
		else if (is_straight(hand)) {
			return 3;
		}
		else if (is_flush(hand)) {
			return 2;
		}
		else if (is_double(hand)) {
			return 1;
		}
		else {
			return 0;
		}

	}
	int anti_draw(int num, vector<Card> hand)const {
		switch (num) {
		case 0: {
			int max = 0;
			for (int i = 0; i < 3; ++i)
			{
				if (hand[i].value > max)
				{
					max = hand[i].value;
				}
			}
			return max;
		}
		case 1: {
			if (hand[0].value == hand[1].value) {
				return (hand[0].value + hand[1].value) * 2;
			}
			else if (hand[0].value == hand[2].value) {
				return (hand[0].value + hand[2].value) * 2;
			}
			else if (hand[1].value == hand[2].value) {
				return (hand[1].value + hand[2].value) * 2;
			}
		}
		case 2: {
			return (hand[0].value + hand[1].value + hand[2].value) * 4;
		}
		case 3: {
			return (hand[0].value + hand[1].value + hand[2].value) * 5;
		}
		case 4: {
			return (hand[0].value + hand[1].value + hand[2].value) * 20;
		}
		case 5: {
			return (hand[0].value + hand[1].value + hand[2].value) * 40;
		}
		default: return 0;
		}
	}
	int chips_won(int bet, int pair_p, int num)const {
		switch (num) {
		case 0: {
			return bet * 2;
		}
		case 1: {
			return bet * 2 + pair_p * 2;
		}
		case 2: {
			return bet * 2 + pair_p * 4;
		}
		case 3: {
			return bet * 3 + pair_p * 5;
		}
		case 4: {
			return bet * 5 + pair_p * 20;
		}
		case 5: {
			return bet * 6 + pair_p * 40;
		}
		default: return 0;
		}
	}
};

#endif /* DECK_H_ */