#include "Gamer.h"
#include <iostream>
#include <cstring>

Gamer::Gamer()
{

	std::cout << "\n\n\t\t\tHow old are you?\t";
	value_f(&m_age);
	std::cout << "\n\t\tHow much money are you willing to spend on gambling?\n\t\tMinimum - 100\t\t\t\t";
	value_f(&m_bank);
	std::cout << "\n\t\tWhat is yout name?\t";
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
			std::cout << "\n\t\tIncorrect data. Try again.\t\t";
			continue;
		}

		if ((value < 18) && (parameter == &m_age ))
		{
			std::cerr << "\n\t\t\tYou're too small...\t";
			exit(1);
		}
		else if (parameter == &m_age) { m_age = value; }

		else if ((parameter == &m_bank) && (value < 100))
		{
			std::cout << "\n\t\tInsufficient funds. Minimum - 100.\t";
			continue;
		}
		else if (parameter == &m_bank) { m_bank = value; }

		else if (parameter == &m_bet)
		{
			if (m_bank < 100)
			{
				std::cout << "\n\t\t\tInsufficient funds. Your bank: " << m_bank;
				exit(3);
			}
			else if (m_bank < value)
			{
				std::cout << "\n\t\t\tInsufficient funds. Minimum - 100. Your bank: " << m_bank << ". Try again.\t";
				continue;
			}
			else if (value < 100)
			{
				std::cout << "\n\t\t\tToo little. Minimum - 100. Your bank: " << m_bank<<"\t";
				continue;
			}
			else { m_bet = value; };
		}
		else { std::cerr << "\n\t\t\tSomething went wrong"; break; }
		break;
	} while (m_bank == 0 || m_age == 0 || m_bet == 0);
}

bool Gamer::question()
{
	std::string answer{"Answer"};
	std::cin >> answer;
	while (answer != "yes" && answer != "no")
	{
		std::cout << "\n\t\tInvalid response. Try again. \t";
		std::cin >> answer;
	}
	return (answer == "yes") ? true : false;
}

void Gamer::menu()
{
	std::cout << "\n\t\tDo you want to play?\t'yes' or 'no'\n\t\t\t\t\t   ";
	if (question())
	{
		srand(static_cast<unsigned int>(time(0))); // используем системные часы в качестве стартового значения
		rand(); // пользователям Visual Studio: делаем сброс первого случайного числа

		Deck deck;
		deck.shuffleDeck();
		std::cout << "\n\t\tYour bet? Minimum - 100\t\t";
		value_f(&m_bet);

		playBlackjack(deck);
	}
}
