#pragma once
#include <graphics.h>
#include <vector>
#include "Animation.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Player
{
public:
	Player();
	~Player();
	void ProcessEvent(const ExMessage& msg);
	void Move();
	void Draw(int delta);
	const POINT GetPostion() const;
	const POINT GetBBox() const;
public:
	bool gethurt = false;

private:
	const int SPEED = 13;
	const int FRAME_WIDTH = 81;
	const int FRAME_HEIGHT = 71; 
	const int SHADOW_WIDTH = 32;
	const int FRAME_NUM = 4;
	const int HURT_FLICK = 15;

	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	Animation* anim_left_white;
	Animation* anim_right_white;
	Atlas* atlas_left;
	Atlas* atlas_right;
	Atlas* atlas_left_white;
	Atlas* atlas_right_white;
	POINT position = { WINDOW_WIDTH / 2 - FRAME_WIDTH / 2, WINDOW_HEIGHT / 2 - FRAME_HEIGHT / 2};
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;
};