#include "Deck.h"
#include <iostream>
#include <cassert>

Deck::Deck()
{
	int card(0);
	for (int suit = 0; suit < Card::SUIT_MAX; ++suit)
		for (int rank = 1; rank < Card::RANK_MAX; ++rank)
			//Присваиваем облик одной карты
			m_deck[card++] = Card(static_cast<Card::CardRank>(rank), static_cast<Card::CardSuit>(suit));

}

void Deck::printDeck() const
{
	for (const Card& card : m_deck)
	{
		card.printCard();
		std::cout << '\n';
	}
}

void Deck::shuffleDeck()
{
	m_cardIndex = 0;//Начинаем новую раздачу карт
	for (Card& card : m_deck)
		swapCard(card, m_deck[getRandomNumber(0, 51)]);
}

const Card& Deck::dealCard()
{
	assert(m_cardIndex < 52);
	return m_deck[m_cardIndex++];
}

