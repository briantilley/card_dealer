#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_DECK 52
#define SIZE_HAND 5
#define NUM_SUITS 4
#define NUM_VALUES 13

const char* const suitNames[NUM_SUITS]  = {"Hearts", "Diamonds", "Clubs", "Spades"};
const char* const valueNames[NUM_VALUES] = {"Ace", "Two", "Three", "Four", "Five", "Six",
								  "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a < b) ? a : b; }

// fill deck with 0 to size-1 sequence (0 to 51, in practice)
void populateDeck(int deck[], size_t size)
{
	for(int i = 0; i < size; i++)
	{
		deck[i] = i;
	}
}

// put number values in random order
void shuffleDeck(int deck[], size_t size, size_t shuffleIterations)
{
	size_t swapIdx = 0;
	int tempInt = 0;

	// shuffle at least once
	shuffleIterations = max(shuffleIterations, 1);

	for(int iter = 0; iter < shuffleIterations; iter++)
		for(int i = 0; i < size; i++)
		{
			// swap values between current location and other randomly chosen location
			swapIdx = rand() % size;

			tempInt = deck[swapIdx];
			deck[swapIdx] = deck[i];
			deck[i] = tempInt;
		}
}

// reset hand to empty values (-1)
void clearHand(int hand[], size_t sizeHand)
{
	for(int i = 0; i < sizeHand; ++i)
	{
		hand[i] = -1;
	}
}

// copy sizeHand cards from the top of the deck into hand,
// ignoring the cards already dealt, and update the number of cards dealt
void deal(int hand[], size_t sizeHand, int deck[], size_t sizeDeck, size_t* pCardsDealt)
{
	int i;
	for(i = *pCardsDealt; i < min(sizeHand + *pCardsDealt, sizeDeck); i++)
	{
		hand[i - *pCardsDealt] = deck[i];
	}

	*pCardsDealt = i;
}

// print the numerical values of the deck array
void printDeck(int deck[], size_t size)
{
	for(int i = 0; i < size; i++)
	{
		printf("%2d ", deck[i]);
		if((i + 1) % (size / 4) == 0) printf("\n");
	}
}

// print the plain English name of the card
void printCard(int card)
{
	printf("%8s of %s", valueNames[card % 13], suitNames[card / 13]);
}

// find each pair of cards and print the common trait
void printPairs(int hand[], size_t sizeHand)
{
	// check every card against every other card in the hand
	// performs sizeHand - 1 linear searches
	for(int i = 0; i < sizeHand - 1; ++i)
	{
		// break upon encountering an empty slot in the hand
		if(hand[i] == -1) break;

		for(int j = i + 1; j < sizeHand; ++j)
		{
			if(hand[j] == -1) break;

			if(hand[i] / 13 == hand[j] / 13)
			{
				printf("You have a pair of %s!\n", suitNames[hand[i] / 13]);
			}
			else if(hand[i] % 13 == hand[j] % 13)
			{
				// print an 'e' after value name "Six"
				printf("You have a pair of %s%cs!\n", valueNames[hand[i] % 13], (hand[i] % 13 == 5) ? 'e' : '\0');
			}
		}
	}
}

int main(int argc, char* argv[])
{
	int deck[SIZE_DECK];
	int hand[SIZE_HAND];
	size_t cardsDealt = 0;

	srand(time(NULL));

	populateDeck(deck, SIZE_DECK);
	shuffleDeck(deck, SIZE_DECK, 20);

	// print the entire deck in 2 columns
	printf("deck:\n\n");
	for(int i = 0; i < SIZE_DECK / 2; i++)
	{
		printCard(deck[i]);
		printf("\t");
		printCard(deck[i + SIZE_DECK / 2]);
		printf("\n");
	}

	// deal i hands, print the cards' names, and print pairs
	printf("\nhands dealt:\n\n");
	for(int i = 0; i < 5; i++)
	{
		deal(hand, SIZE_HAND, deck, SIZE_DECK, &cardsDealt);
		for(int j = 0; j < SIZE_HAND; j++)
		{
			// break upon encountering an empty slot in the hand
			if(hand[j] == -1) break;

			printCard(hand[j]);
			printf("\n");
		}
		printPairs(hand, SIZE_HAND);
		clearHand(hand, SIZE_HAND);
		printf("\n");
	}

	return 0;
}
