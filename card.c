#include "extgraph.h"
#include "card.h"

void DrawCardBoundary(Card *pCard, string color)
{
	MovePen(pCard->x, pCard->y);
	SetPenColor(color);
	DrawLine(0, pCard->height);
	DrawLine(pCard->width, 0);
	DrawLine(0, -pCard->height);
	DrawLine(-pCard->width, 0);
}

void DrawBlindCard(Card *pCard)
{
	MovePen(pCard->x, pCard->y);
	SetPenColor("Light Gray");
	StartFilledRegion(1);
	DrawLine(0, pCard->height);
	DrawLine(pCard->width, 0);
	DrawLine(0, -pCard->height);
	DrawLine(-pCard->width, 0);
	EndFilledRegion();
}

void DrawSquare(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;

	double len = pCard->width * 0.6;
	MovePen(cx - len / 2, cy - len / 2);
	SetPenColor(pCard->colorName);
	StartFilledRegion(1);
	DrawLine(0, len);
	DrawLine(len, 0);
	DrawLine(0, -len);
	DrawLine(-len, 0);
	EndFilledRegion();

	char *str = "ÄãºÃ£¬CÓïÑÔ£¡";
	double fontAscent = GetFontAscent();
	double tw = TextStringWidth(str);
	MovePen(cx - tw / 2, cy - fontAscent / 2);
	SetPenColor("Black");
	DrawTextString(str);
}

void DrawRect(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;

	double w = pCard->width * 0.7;
	double h = pCard->width * 0.5;
	MovePen(cx - w / 2, cy - h / 2);
	SetPenColor(pCard->colorName);
	StartFilledRegion(1);
	DrawLine(0, h);
	DrawLine(w, 0);
	DrawLine(0, -h);
	DrawLine(-w, 0);
	EndFilledRegion();
}

void DrawTriangle(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;

	double len = pCard->width * 0.7;
	MovePen(cx, cy + len * sqrt(3) / 4);
	SetPenColor(pCard->colorName);
	StartFilledRegion(1);
	DrawLine(-len / 2, -len * sqrt(3) / 2);
	DrawLine(len, 0);
	DrawLine(-len / 2, len * sqrt(3) / 2);
	EndFilledRegion();
}

void DrawCircle(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;

	double r = pCard->width * 0.35;
	MovePen(cx + r, cy);
	SetPenColor(pCard->colorName);
	StartFilledRegion(1);
	DrawArc(r, 0, 360);
	EndFilledRegion();
}

void DrawTrapezoid(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;

	double w = pCard->width * 0.4;
	double h = pCard->height * 0.5;
	MovePen(cx - w / 2, cy + h / 2);
	SetPenColor(pCard->colorName);
	StartFilledRegion(1);
	DrawLine(-w / 2, -h);
	DrawLine(w * 2, 0);
	DrawLine(-w / 2, h);
	DrawLine(-w, 0);
	EndFilledRegion();
}

void DrawParallellogram(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;

	double w = pCard->width * 0.6;
	double h = pCard->height * 0.5;
	double s = pCard->width * 0.1;
	MovePen(cx - w / 2, cy + h / 2);
	SetPenColor(pCard->colorName);
	StartFilledRegion(1);
	DrawLine(-s, -h);
	DrawLine(w + s, 0);
	DrawLine(s, h);
	DrawLine(-w - s, 0);
	EndFilledRegion();
}

void DrawClip(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;
	double l = pCard->width * 0.4;
	double r = pCard->width / 8;

	int penSize = GetPenSize();
	SetPenSize(2);
	SetPenColor(pCard->colorName);
	MovePen(cx - l / 5 * 2, cy - r);
	DrawLine(l, 0);
	DrawArc(r, -90, 180);
	DrawLine(-l / 5 * 6, 0);
	DrawArc(r * 0.94, 90, 180);
	DrawLine(l, 0);
	DrawArc(r * 0.88, -90, 180);
	DrawLine(-l / 5 * 4, 0);
	SetPenSize(penSize);
}

void DrawTree(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;
	double w = pCard->width;
	double h = pCard->height;

	pCard->colorName = "Brown";
	SetPenColor(pCard->colorName);
	MovePen(cx - 0.02, cy);
	StartFilledRegion(1);
	DrawLine(0.04, 0);
	DrawLine(0.01, -h * 0.4);
	DrawLine(-0.06, 0);
	DrawLine(0.01, h * 0.4);
	EndFilledRegion();

	SetPenColor("Green");
	MovePen(cx, cy + h * 0.35);
	StartFilledRegion(1);
	DrawLine(w * 0.3, -h * 0.25);
	DrawLine(-w * 0.6, 0);
	DrawLine(w * 0.3, h * 0.25);
	EndFilledRegion();

	MovePen(cx, cy + h * 0.25);
	StartFilledRegion(1);
	DrawLine(w * 0.35, -h * 0.25);
	DrawLine(-w * 0.7, 0);
	DrawLine(w * 0.35, h * 0.25);
	EndFilledRegion();

	MovePen(cx, cy + h * 0.15);
	StartFilledRegion(1);
	DrawLine(w * 0.4, -h * 0.25);
	DrawLine(-w * 0.8, 0);
	DrawLine(w * 0.4, h * 0.25);
	EndFilledRegion();
}

void DrawFace(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;
	double headWidth = pCard->width * 0.8;
	double headHeight = pCard->height * 0.8;

	SetPenColor("Gray");
	StartFilledRegion(1);
	MovePen(cx - headWidth / 2, cy - headHeight / 2);
	DrawLine(headWidth, 0);
	DrawLine(0, headHeight);
	DrawLine(-headWidth, 0);
	DrawLine(0, -headHeight);
	EndFilledRegion();

	double eyeRadius = pCard->width * 0.06;
	double x = cx - headWidth / 5 + eyeRadius;
	double y = cy + headHeight / 4;

	SetPenColor(pCard->colorName);
	StartFilledRegion(1);
	MovePen(x, y);
	DrawArc(eyeRadius, 0, 360);
	EndFilledRegion();

	x = cx + headWidth / 5 + eyeRadius;
	y = cy + headHeight / 4;
	StartFilledRegion(1);
	MovePen(x, y);
	DrawArc(eyeRadius, 0, 360);
	EndFilledRegion();

	double mouseWidth = pCard->width * 0.36;
	double mouseHeight = pCard->width * 0.12;
	x = cx - mouseWidth / 2;
	y = cy - headHeight / 4 - mouseHeight / 2;

	SetPenColor("White");
	StartFilledRegion(1);
	MovePen(x, y);
	DrawLine(mouseWidth, 0);
	DrawLine(0, mouseHeight);
	DrawLine(-mouseWidth, 0);
	DrawLine(0, -mouseHeight);
	EndFilledRegion();
}
// Draw a target
void DrawArcheryTarget(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;
	double r = pCard->width / 2;

	SetPenColor("White");
	StartFilledRegion(1);
	MovePen(cx + r, cy);
	DrawArc(r, 0, 360);
	EndFilledRegion();

	SetPenColor("Black");
	StartFilledRegion(1);
	MovePen(cx + r * 0.8, cy);
	DrawArc(r * 0.8, 0, 360);
	EndFilledRegion();

	SetPenColor("Red");
	StartFilledRegion(1);
	MovePen(cx + r * 0.6, cy);
	DrawArc(r * 0.6, 0, 360);
	EndFilledRegion();

	SetPenColor("Black");
	StartFilledRegion(1);
	MovePen(cx + r * 0.4, cy);
	DrawArc(r * 0.4, 0, 360);
	EndFilledRegion();

	SetPenColor("Yellow");
	StartFilledRegion(1);
	MovePen(cx + r * 0.2, cy);
	DrawArc(r * 0.2, 0, 360);
	EndFilledRegion();
}
// Drawdiagram
void DrawDiagram(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;
	double w = pCard->width * 0.8;
	double h = pCard->height * 0.15;
	double r = pCard->height * 0.2;

	MovePen(cx + r, cy + r);
	SetPenColor("Cyan");
	StartFilledRegion(1);
	DrawArc(r, 0, 360);
	EndFilledRegion();

	MovePen(cx, cy);
	SetPenColor("Black");
	DrawLine(0, -r * 1.25);

	MovePen(cx - w / 2, cy - r * 1.25);
	SetPenColor("River Blue");
	StartFilledRegion(1);
	DrawLine(w, 0);
	DrawLine(0, -h);
	DrawLine(-w, 0);
	DrawLine(0, h);
	EndFilledRegion();

	char *str1 = "Program";
	char *str2 = "GraphicsProgram";
	double frontAscent = GetFontAscent();
	double tw1 = TextStringWidth(str1);
	double tw2 = TextStringWidth(str2);
	MovePen(cx - tw1 / 2, cy + r - frontAscent / 2);
	SetPenColor("Black");
	DrawTextString(str1);
	MovePen(cx - tw2 / 2, cy - r * 1.25 - frontAscent / 2 - h / 2);
	DrawTextString(str2);
}
// DrawDice
void DrawDice(Card *pCard)
{
	double cx = pCard->x + pCard->width / 2;
	double cy = pCard->y + pCard->height / 2;
	double w = pCard->width * 0.5;
	double b = pCard->width * 0.02;
	double r = w * 0.1;

	MovePen(cx - w / 2, cy - w / 2);
	SetPenColor("Black");
	StartFilledRegion(1);
	DrawLine(0, w);
	DrawLine(w, 0);
	DrawLine(0, -w);
	DrawLine(-w, 0);
	EndFilledRegion();

	MovePen(cx - w / 2 + b, cy - w / 2 + b);
	SetPenColor(pCard->colorName);
	StartFilledRegion(1);
	DrawLine(0, w - 2 * b);
	DrawLine(w - 2 * b, 0);
	DrawLine(0, -w + 2 * b);
	DrawLine(-w + 2 * b, 0);
	EndFilledRegion();

	MovePen(cx - w * 0.25 + r, cy + w * 0.25);
	SetPenColor("Black");
	StartFilledRegion(1);
	DrawArc(r, 0, 360);
	EndFilledRegion();

	MovePen(cx + w * 0.25 + r, cy + w * 0.25);
	SetPenColor("Black");
	StartFilledRegion(1);
	DrawArc(r, 0, 360);
	EndFilledRegion();

	MovePen(cx - w * 0.25 + r, cy - w * 0.25);
	SetPenColor("Black");
	StartFilledRegion(1);
	DrawArc(r, 0, 360);
	EndFilledRegion();

	MovePen(cx + w * 0.25 + r, cy - w * 0.25);
	SetPenColor("Black");
	StartFilledRegion(1);
	DrawArc(r, 0, 360);
	EndFilledRegion();
}
