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
void end(const Gamer& Jack, const int& start_bank);
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
		int index_Ace{21};
		for (int i = 0; i < 21; ++i)
		{
			if (cards[i].m_rank == Card::RANK_ACE)
				index_Ace = i;
		}

		if (summ > 21 && index_Ace != 21)
		{
			std::cout << "\n\tThe sum of your deck exceeds 21 points and it has an ACE, so the ACE now has the value '1'";
			cards[index_Ace].m_rank = Card::RANK_1_ACE;
			summ -= 10;
		}
		else if (rank == 0)
			break;
		else if (summ > 21) { return summ; }
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

	std::cout << "\n\t\tLet's start!";
	for (int i = 0; i < 2; ++i)
	{
		cardsOfGamer[i] = deck.dealCard();
		std::cout << "\n\t\t" << m_name << "'s card #" << i + 1 << '\n';
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
	std::cout << "\n\t" << m_name << "'s sum of ranks: " << summCardsOfGamer;
	std::cout << "\n\t";

	for (int i = 2; summCardsOfGamer < 21; ++i)
	{
		char answer{};
		std::cout << "\n\tDo you need another card?\tmore----->yes\tenough----->no\n\t\t\t\t\t\t     ";
		answer = question();
		if (answer)
		{
			cardsOfGamer[i] = deck.dealCard();
			std::cout << "\n\t\t" << m_name << "'s card #" << i + 1 << '\n';
			cardsOfGamer[i].printCard();
			summCardsOfGamer = Summ(cardsOfGamer);
			std::cout << "\n\t" << m_name << "'s sum of ranks: " << summCardsOfGamer << "\n\t";
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
			m_bank += m_bet;
			std::cout << "\n\n\t\tMachin's card #" << 2 << '\n';
			cardsOfMachine[1].printCard();
			std::cout << "\n\t" << m_name << ", we will refund your money -" << m_bet << "\n\t";

			std::cout << "\n\n\t\t\t"<< m_name <<"'s bank = " << m_bank << ".\n\n\n";

			system("pause");
			m_push++;
			menu();
		}
		else
		{
			std::cout << "\n\n\t\tMachin's card #" << 2 << '\n';
			cardsOfMachine[1].printCard();
			system("pause");
			for (int i = 2; summCardsOfMachine <= 26; ++i)
			{
				if (summCardsOfMachine == 21)
				{
					std::cout << "\n\t" << m_name << "'s sum of ranks: " << summCardsOfGamer
						<< "\n\tSumm of machine: " << summCardsOfMachine
						<< "\n\t\t\tPUSH!!!"
						<< "\n\tOkey. Take your loot back. - " << m_bet << ".\n\t";
					m_bank += m_bet;
					m_push++;

					std::cout << "\n\n\t\t\t" << m_name << "'s bank = " << m_bank << ".\n\n\n";

					system("pause");
					menu();
					break;
				}
				else if (summCardsOfMachine > 16)
				{

					std::cout << "\n\t" << m_name << "'s sum of ranks: " << summCardsOfGamer
							  << "\n\tSum of machine: " << summCardsOfMachine
							  << "\n\tThe machine can't take the card, so the sum of the values is greater than 16."
							  << "\n\tLucky! " << m_name << " win your tripled bet - "<< m_bet*3 <<". This is BLACKJACK!!!";
					picture();
					m_bank += (3 * m_bet) + m_bet;

					m_win++;

					std::cout << "\n\n\t\t\t" << m_name << "'s bank = " << m_bank << ".\n\n\n";

					std::cout << "\n\t";
					menu();
					break;
				}
				else
				{
					std::cout << "\n\tSumm of machine: " << summCardsOfMachine
							  << "\n\tThe machine takes another card."
							  << "\n\n\t\tMachin's card #" << i + 1 << '\n';
					cardsOfMachine[i] = deck.dealCard();
					cardsOfMachine[i].printCard();
					summCardsOfMachine = { Summ(cardsOfMachine) };
					system("pause");
				}
			}
		}
	}
	else if (summCardsOfGamer > 21)
	{
		std::cout << "\n\t\t\tDude! " << m_name << " lost!\n\t";
		m_losing_games++;

		std::cout << "\n\n\t\t\t" << m_name << "'s bank = " << m_bank << ".\n\n\n";

		system("pause");
		menu();
	}
	else
	{
		std::cout << "\n\n\t\tMachin's card #" << 2 << '\n';
		cardsOfMachine[1].printCard();
		system("pause");
		for (int i = 2; summCardsOfMachine <= 26; ++i)
		{
			std::cout << "\n\tSum of machine: " << summCardsOfMachine;
			if (summCardsOfMachine == summCardsOfGamer)
			{
				std::cout << "\n\t" << m_name << "'s sum of ranks: " << summCardsOfGamer
						  << "\n\t\t\tPUSH!!!"
						  << "\n\tOkey. Take your loot back - "<< m_bet <<".\n\t";
				m_bank += m_bet;

				std::cout << "\n\n\t\t\t" << m_name << "'s bank = " << m_bank << ".\n\n\n";
				
				m_push++;
				system("pause");
				menu();
				break;
			}
			else if (summCardsOfMachine > 16)
			{
				if (summCardsOfGamer > summCardsOfMachine || summCardsOfMachine > 21)
				{
					std::cout << "\n\t" << m_name << "'s sum of ranks: " << summCardsOfGamer
							  << "\n\tOkey. You win: " << 2.5 * m_bet <<".\n\t";
					m_bank += (2.5 * m_bet) + m_bet;
					m_win++;

					std::cout << "\n\n\t\t\t" << m_name << "'s bank = " << m_bank << ".\n\n\n";

					system("pause");
					menu();
					break;
				}
				else
				{
					std::cout << "\n\t" << m_name << "'s sum of ranks: " << summCardsOfGamer
							  << "\n\tDude! " << m_name << " lost!\n\t";
					m_losing_games++;

					std::cout << "\n\n\t\t\t" << m_name << "'s bank = " << m_bank << ".\n\n\n";

					system("pause");
					menu();
					break;
				}
			}
			else
			{
				cardsOfMachine[i] = deck.dealCard();
				std::cout << "\n\tThe machine takes another card."
						  << "\n\n\t\tMachin's card #" << i + 1 << '\n';
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
	const int start_bank(Jack.m_bank);
	Jack.menu();
	Owl_san();
	end(Jack, start_bank);
	return 0;
}


void end( const Gamer& Jack, const int& start_bank) 
{
	std::cout << "\n\t\t\tYour wins         - " << Jack.m_win
			  << "\n\t\t\t     losing games - " << Jack.m_losing_games
			  << "\n\t\t\t     start bank   - " << start_bank
			  << "\n\t\t\t     balance      - " << Jack.m_bank
			  << "\n\t\t\t     result         ";
	
	if (start_bank > Jack.m_bank)
	{
		std::cout << '-' << start_bank - Jack.m_bank;
	}
	else { std::cout << '+' << Jack.m_bank - start_bank; }
	exit(5);
}

void Owl_san()
{
	std::cout << "\n\n\t\t\t\t:)\\____/(:\n";
	std::cout << "\t\t\t\t  (@)v(@)\n";
	std::cout << "\t\t\t\t {|~- -~|}\n";
	std::cout << "\t\t\t\t {/^'^'^\\}\n";
	std::cout << "\t\t\t\t  ~~m-m~~\n\n\n";
}
