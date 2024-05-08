#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Card.h"
#include "Deck.h"

using namespace std;

int main() {
	Deck decky{};
	int current_bet = 0, total_chips = 0, pair_plus = 0;
	string play = "";
	cout << "your moneys\n";
	cin >> total_chips;
	do {
		cout << "You have " << total_chips << " chips\n";
		cout << "enter your bet; enter 0 if you want to quit\n";
		cin >> current_bet;
		if (current_bet == 0) {
			current_bet = -1;
		}
		else {
			cout << "enter pair plus: enter 0 if you don't want to bet\n";
			cin >> pair_plus;
			total_chips -= current_bet + pair_plus;

			decky.shuffle();
			vector<Card> d_hand = decky.get_dealer_cards(), p_hand = decky.get_player_cards();
			int p_value = 0, d_value = 0;

			cout << "YOUR CARDS\n";
			for (Card element : p_hand) {
				cout << to_string(element) << "\n";
			}
			cout << "you have:\t";
			switch (decky.check_for_combo(p_hand)) {
			case 0: cout << "high card\n"; break;
			case 1: cout << "pair\n"; p_value = 1; break;
			case 2: cout << "flush\n"; p_value = 2; break;
			case 3: cout << "straight\n"; p_value = 3; break;
			case 4: cout << "triple\n"; p_value = 4; break;
			case 5: cout << "straight flush!\n"; p_value = 5; break;
			default: cout << "error!\n";
			}
			cout << "Play? enter yes or no\n";
			do {
				cin >> play;
				if (play == "yes") {
					total_chips -= current_bet;
					current_bet *= 2;
					break;
				}
				else if (play == "no") {
					current_bet = 0;
					break;
				}
			} while ((play != "yes") or (play != "no"));

			cout << "DEALER'S CARDS\n";
			for (Card element : d_hand) {
				cout << to_string(element) << "\n";
			}
			cout << "dealer has:\t";
			switch (decky.check_for_combo(d_hand)) {
			case 0: cout << "high card\n"; break;
			case 1: cout << "pair\n"; d_value = 1; break;
			case 2: cout << "flush\n"; d_value = 2; break;
			case 3: cout << "straight\n"; d_value = 3; break;
			case 4: cout << "triple\n"; d_value = 4; break;
			case 5: cout << "straight flush!\n"; d_value = 5; break;
			default: cout << "error!\n";
			}
			cout << "\n";
			if (p_value == d_value) {
				if (decky.anti_draw(p_value, p_hand) > decky.anti_draw(d_value, d_hand)) {
					cout << "PLAYER WINS " << decky.chips_won(current_bet, pair_plus, p_value) << " CHIPS\n";
					total_chips += decky.chips_won(current_bet, pair_plus, p_value);
				}
				else if (decky.anti_draw(p_value, p_hand) < decky.anti_draw(d_value, d_hand)) {
					cout << "DEALER WINS\n";
				}
				else {
					cout << "DRAW\n";
					total_chips += current_bet + pair_plus;
				}
			}
			else if (p_value > d_value) {
				total_chips += decky.chips_won(current_bet, pair_plus, p_value);
				cout << "PLAYER WINS " << decky.chips_won(current_bet, pair_plus, p_value) << " CHIPS\n";
			}
			else {
				cout << "DEALER WINS\n";
			}
		}
	} while (current_bet != -1);
}
