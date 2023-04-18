#ifndef __CARD_H_
#define __CARD_H_

#define CARDX 4
#define CARDY 4
#define CARDN (CARDX * CARDY)
#define GAPX 0.2
#define GAPY 0.2

typedef enum
{
	STATE_HIDE,
	STATE_SHOW,
	STATE_MATCHED,
	STATE_HINT
} State;

typedef struct
{
	State state;
	double x, y;
	double width, height;
	char *colorName;
	void (*drawFunc)(struct Card *pCard);
} Card;

void DrawCardBoundary(Card *pCard, string color);
void DrawBlindCard(Card *pCard);

void DrawSquare(Card *pCard);
void DrawRect(Card *pCard);
void DrawTriangle(Card *pCard);
void DrawCircle(Card *pCard);
void DrawTrapezoid(Card *pCard);
void DrawParallellogram(Card *pCard);
void DrawClip(Card *pCard);
void DrawTree(Card *pCard);
void DrawFace(Card *pCard);
void DrawArcheryTarget(Card *pCard); // ??????? 
void DrawDiagram(Card *pCard);		 // ??????? 
void DrawDice(Card *pCard);			 // ???????? 

#endif
