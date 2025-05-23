#pragma once
#include <graphics.h>

class Bullet
{
public:
	POINT postion = { 0, 0 };
	Bullet() = default;
	~Bullet() = default;

	void Draw() const
	{
		setlinecolor(RGB(255, 155, 50));
		setfillcolor(RGB(200, 75, 10));
		fillcircle(postion.x, postion.y, RADIUS);
	}
private:
	const int RADIUS = 10;
};