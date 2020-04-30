#include "Gamer.h"
#include <iostream>
#include <cstring>

Gamer::Gamer()
{
	int value(0);
	std::cout << "\t\tHow old are you?\t";
	value_f(&m_age);
	std::cout << "\n\t\tHow much money are you willing to spend on gambling?\n\t\tMinimum - 100\t";
	value_f(&m_bank);
	std::cout << "\t\tWhat is yout name?\t";
	std::cin >> m_name;
	std::cin.clear();
	std::cin.ignore(32676, '\n');
}

void Gamer::value_f(int* parameter)
{
	int value(0);
	do {
		std::cin >> value;
		std::cin.ignore(32676, '\n');
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32676, '\n');
			std::cout << "\t\tIncorrect data. Try again.\t";
			continue;
		}

		if ((value < 18) && (parameter == &m_age ))
		{
			std::cerr << "\t\tYou're too small...\t";
			exit(1);
		}
		else if (parameter == &m_age) { m_age = value; }

		else if ((parameter == &m_bank) && (value < 100))
		{
			std::cerr << "\t\tInsufficient funds. Minimum - 100.\t";
			exit(2);
		}
		else if (parameter == &m_bank) { m_bank = value; }

		else if (parameter == &m_bet)
		{
			if (m_bank < 100)
			{
				std::cout << "\t\tInsufficient funds. Your bank: " << m_bank;
				exit(3);
			}
			else if (m_bank < value)
			{
				std::cout << "\t\tInsufficient funds. Minimum - 100. Your bank: " << m_bank << ". Try again.";
				continue;
			}
			else if (value < 100)
			{
				std::cout << "\t\tToo little. Minimum - 100. Your bank: " << m_bank;
				continue;
			}
			else { m_bet = value; };
		}
		else { std::cerr << "\t\t\tSomething went wrong"; }
	} while (m_bank == 0 || m_age == 0 || m_bet == 0);
}

bool Gamer::question()
{
	std::string answer;
	while (answer != "yes" && answer != "no")
	{
		std::cin.ignore(32676, '\n');
		std::cin >> answer;
	}
	return (answer == "yes") ? true : false;
}

void Gamer::menu()
{
	const int start_bank = m_bank;
	std::cout << "\n\tDo you want to play?\t'yes' or 'no'\n\t\t\t\t\t   ";
	if (question())
	{
		Deck deck;
		deck.shuffleDeck();
		std::cout << "\n\tYour bet - ";
		value_f(&m_bet);
		playBlackjack(deck);
	}
	else
	{
		std::cout << "\n\t\t\tYour balance      - " << m_bank
			<< "\n\t\t\t     wins         - " << m_win
			<< "\n\t\t\t     losing games - " << m_losing_games
			<< "\n\t\t\t     result       - " << start_bank - m_bank;

		exit(5);
	}
}
