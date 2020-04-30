#pragma once
#include "Deck.h"

class Gamer
{
private:
	int m_win{ 0 };
	int m_push{ 0 };
	int m_losing_games{ 0 };
	int m_bank;
	int m_age{ 0 };
	int m_bet;
	std::string m_name = "Jack";
public:
	Gamer();
	void value_f(int* parameter);
	bool question();
	void menu();
	void playBlackjack(Deck& deck);
	
	friend void end(const Gamer& Jack, const int& start_bank);
	friend int main();
};
