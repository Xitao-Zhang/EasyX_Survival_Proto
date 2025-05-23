#pragma once
#include <graphics.h>
#include "utils.hpp"
#include "Animation.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Enums.hpp"

class Enemy
{
public:
	Enemy();
	~Enemy();
	bool CheckBulletCollision(const Bullet& bullet);
	bool CheckPlayerCollision(const Player& player);
	void Move(const Player& player);
	void Draw(int delta);
	POINT GetCheckPoint();
	void Hurt();
	bool CheckAlive();

private:
	const int SPEED = 8;
	const int FRAME_WIDTH = 50;
	const int FRAME_HEIGHT = 50;
	const int SHADOW_WIDTH = 48;
	const int FRAME_NUM = 8;

	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	Atlas* atlas_left;
	Atlas* atlas_right;
	POINT position = { 0, 0 };
	bool facing_left = false;
	bool alive = true;
};