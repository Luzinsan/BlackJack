//	 Логика работы с картами.
//   Логика работы с колодами карт.
//   Логика раздачи карт из колоды.
//   Логика игры.

#include <iostream>
#include <array>
#include "Card.h"
#include "Deck.h"
#include "Gamer.h"

void Owl_san();
void picture()
{
	std::cout << "\n\t\t------------------------------------------------------------"
		<< "\n\t\t\t╔══╗─╔╗───╔═══╗╔═══╗╔╗╔═╗     ──╔╗╔═══╗╔═══╗╔╗╔═╗"
		<< "\n\t\t\t║╔╗║─║║───║╔═╗║║╔═╗║║║║╔╝     ──║║║╔═╗║║╔═╗║║║║╔╝"
		<< "\n\t\t\t║╚╝╚╗║║───║║─║║║║─╚╝║╚╝╝─     ──║║║║─║║║║─╚╝║╚╝╝─"
		<< "\n\t\t\t║╔═╗║║║─╔╗║╚═╝║║║─╔╗║╔╗║─     ╔╗║║║╚═╝║║║─╔╗║╔╗║─"
		<< "\n\t\t\t║╚═╝║║╚═╝║║╔═╗║║╚═╝║║║║╚╗     ║╚╝║║╔═╗║║╚═╝║║║║╚╗"
		<< "\n\t\t\t╚═══╝╚═══╝╚╝─╚╝╚═══╝╚╝╚═╝     ╚══╝╚╝─╚╝╚═══╝╚╝╚═╝"
		<< "\n\t\t-------------------------------------------------------------\n";
	system("pause");
}

int Summ(std::array<Card, 21>& cards)
{
	int summ{ 0 };

	for (auto& element : cards)
	{
		int rank = element.Card::getCardValue();
		summ += rank;

		//Если на руках есть туз И ---> сумма всех карт превышает 21 - то мы заменяем ПЕРВЫЙ ВСТРЕЧНЫЙ туз на модифицированный туз со значением 1
				//1,11,11 = 23--->1,1,11 = 13 (варианта 11,1,11 просто не может существовать)
		int index_Ace;
		for (int i = 0; i < 21; ++i)
		{
			if (cards[i].m_rank == Card::RANK_ACE)
				index_Ace = i;
		}

		if (summ > 21 && index_Ace != 21)
		{
			cards[index_Ace].m_rank = Card::RANK_1_ACE;
			summ -= 10;
		}
		else if (rank == 0)
			break;
	}
	return summ;

}

void Gamer::playBlackjack(Deck& deck)
{
	m_bank -= m_bet;
	std::array<Card, 21> cardsOfGamer = {};
	std::array<Card, 21> cardsOfMachine = {};

	int summCardsOfGamer{ 0 };
	int summCardsOfMachine{ 0 };

	for (int i = 0; i < 2; ++i)
	{
		cardsOfGamer[i] = deck.dealCard();
		std::cout << "\n\t\tYour card #" << i + 1 << '\n';
		cardsOfGamer[i].printCard();
		system("pause");

		cardsOfMachine[i] = deck.dealCard();
		if (i == 0)
		{
			std::cout << "\n\t\tMachin's card #" << i + 1 << '\n';
			cardsOfMachine[i].printCard();
			system("pause");
		}
	}
	summCardsOfGamer = { Summ(cardsOfGamer) };
	summCardsOfMachine = { Summ(cardsOfMachine) };
	std::cout << "\n\tYour summ of ranks: " << summCardsOfGamer;

	for (int i = 2; summCardsOfGamer < 21; ++i)
	{
		char answer{};
		std::cout << "\n\tDo you need another card?\tmore----->yes\tenough----->no\n\t\t\t\t\t\t     ";
		answer = question();
		if (answer)
		{
			cardsOfGamer[i] = deck.dealCard();
			std::cout << "\n\t\tYour card #" << i + 1 << '\n';
			cardsOfGamer[i].printCard();
			summCardsOfGamer = Summ(cardsOfGamer);
			std::cout << "\n\tYour summ of ranks: " << summCardsOfGamer;
			system("pause");
		}
		else
			break;
	}


	if ((summCardsOfGamer == 21) && (cardsOfMachine[0].getCardValue() > Card::RANK_10))
	{
		std::cout << "\n\t\tHit or Stand?\n\t\thit---->yes\tstand---->no\n\t\t\t\t   ";
		char answer{};
		question();
		if (answer)
		{
			m_bank += (2 * m_bet);
			cardsOfMachine[0].printCard();
			std::cout << "\n\tYour winnings are " << m_bet << " from the original bet";
			system("pause");
			m_win++;
			menu();
		}
		else
		{
			std::cout << "\n\t\tMachin's card #" << 2 << '\n';
			cardsOfMachine[1].printCard();
			system("pause");
			for (int i = 2; summCardsOfMachine <= 26; ++i)
			{
				if (summCardsOfMachine == 21)
				{
					std::cout << "\n\tYour summ of ranks: " << summCardsOfGamer;
					std::cout << "\n\tSumm of machine: " << summCardsOfMachine;
					std::cout << "\n\t\t\tPUSH!!!";
					m_bank += m_bet;
					m_push++;
					std::cout << "\n\tOkey. Take your loot back.";
					system("pause");
					menu();
				}
				else if (summCardsOfMachine > 16)
				{
					std::cout << "\n\tYour summ of ranks: " << summCardsOfGamer;
					std::cout << "\n\tSumm of machine: " << summCardsOfMachine;
					std::cout << "\n\tLucky! you win your tripled bet. This is BLACKJACK!!!";
					picture();
					m_bank += (3 * m_bank) + m_bet;
					m_push++;
					system("pause");
					menu();
				}
				else
				{
					std::cout << "\n\tSumm of machine: " << summCardsOfMachine;
					std::cout << "\n\tThe machine takes another card.";
					cardsOfMachine[i] = deck.dealCard();
					std::cout << "\n\t\tMachin's card #" << i + 1 << '\n';
					cardsOfMachine[i].printCard();
					summCardsOfMachine = { Summ(cardsOfMachine) };
					system("pause");
				}
			}
		}
	}
	else if (summCardsOfGamer > 21)
	{
		std::cout << "\n\t\t\tDude! You lost!";
		m_losing_games++;
		system("pause");
		menu();
	}
	else
	{
		std::cout << "\n\t\tMachin's card #" << 2 << '\n';
		cardsOfMachine[1].printCard();
		system("pause");
		for (int i = 2; summCardsOfMachine <= 26; ++i)
		{
			std::cout << "\n\tSumm of machine: " << summCardsOfMachine;
			if (summCardsOfMachine == summCardsOfGamer)
			{
				std::cout << "\n\tYour summ of ranks: " << summCardsOfGamer;
				std::cout << "\n\t\t\tPUSH!!!";
				m_bank -= m_bet;
				std::cout << "\n\tOkey. Take your loot back.";
				m_push++;
				system("pause");
				menu();
			}
			else if (summCardsOfMachine > 16)
			{
				if (summCardsOfGamer > summCardsOfMachine || summCardsOfMachine > 21)
				{
					std::cout << "\n\tYour summ of ranks: " << summCardsOfGamer;
					m_bank += (2.5 * m_bet) + m_bet;
					std::cout << "\n\tOkey. You win: " << 2.5 * m_bet;
					m_win++;
					system("pause");
					menu();
				}
				else
				{
					std::cout << "\n\tYour summ of ranks: " << summCardsOfGamer;
					std::cout << "\n\tDude! you lost!";
					m_losing_games++;
					system("pause");
					menu();
				}
			}
			else
			{
				cardsOfMachine[i] = deck.dealCard();
				std::cout << "\n\tThe machine takes another card.";
				std::cout << "\n\t\tMachin's card #" << i + 1 << '\n';
				cardsOfMachine[i].printCard();
				summCardsOfMachine = { Summ(cardsOfMachine) };
				system("pause");
			}
		}
	}
}

int main() 
{
	{ Owl_san(); picture(); std::cout << "\t\t\t\t\t\t\tby OwlSan - 2020\n\t\t";}
	Gamer Jack;
	Jack.menu();
	
	return 0;
}

void Owl_san()
{
	std::cout << "\n\n\t\t\t\t:)\\____/(:\n";
	std::cout << "\t\t\t\t  (@)v(@)\n";
	std::cout << "\t\t\t\t {|~- -~|}\n";
	std::cout << "\t\t\t\t {/^'^'^\\}\n";
	std::cout << "\t\t\t\t  ~~m-m~~\n\n\n";
}
