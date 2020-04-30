#pragma once
#include <array>
#include <ctime>
#include "Card.h"

class Deck
{
private:
	std::array<Card, 52> m_deck;
	int m_cardIndex = 0;
public:
	Deck();
	void printDeck() const;
private:
	static void swapCard(Card& card1, Card& card2)
	{
		Card temp = card1;
		card1 = card2;
		card2 = temp;
	}
	// Генерируем случайное число между min и max(включительно)
	// Предполагается, что srand() уже был вызван
	static int64_t getRandomNumber(int64_t min, int64_t max)
	{
		srand(static_cast<unsigned int>(time(0))); // используем системные часы в качестве стартового значения
		rand(); // пользователям Visual Studio: делаем сброс первого случайного числа
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		// Равномерно распределяем генерацию случайного числа в диапазоне значений
		return static_cast<int64_t>(rand() * fraction * (max - min + 1) + min);
	}
public:
	void shuffleDeck();
	const Card& dealCard();
};
