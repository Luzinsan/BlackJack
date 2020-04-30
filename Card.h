#pragma once
class Card
{
public:
	enum CardRank
	{
		RANK_NULL,
		RANK_2,
		RANK_3,
		RANK_4,
		RANK_5,
		RANK_6,
		RANK_7,
		RANK_8,
		RANK_9,
		RANK_10,
		RANK_JACK,
		RANK_QUEEN,
		RANK_KING,
		RANK_ACE,
		RANK_MAX,
		RANK_1_ACE
	};
	enum CardSuit
	{
		SUIT_CLUB,
		SUIT_DIAMOND,
		SUIT_HEART,
		SUIT_SPADE,
		SUIT_MAX
	};
private:
	CardRank m_rank;//ранг
	CardSuit m_suit;//достоинство
public:
	Card(CardRank rank = RANK_MAX, CardSuit suit = SUIT_MAX) : m_rank(rank), m_suit(suit) {}
	void printRank() const;
	void printSuit() const;
	void printCard() const;
	int getCardValue() const;
	friend int Summ(std::array<Card, 21>& cards);
};
