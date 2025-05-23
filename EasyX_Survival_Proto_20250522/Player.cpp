#include "Player.hpp"

Player::Player()
{
	loadimage(&img_shadow, _T("assets/imgs/shadow_player.png"));
	atlas_left = new Atlas(_T("assets/imgs/Demon/Demon_IDLE_Left_%d.png"), FRAME_NUM);
	atlas_right = new Atlas(atlas_left,processtype::flip);
	atlas_left_white = new Atlas(atlas_left, processtype::white);
	atlas_right_white = new Atlas(atlas_right, processtype::white);
	anim_left = new Animation(atlas_left, 45);
	anim_right = new Animation(atlas_right, 45);
	anim_left_white = new Animation(atlas_left_white, 45);
	anim_right_white = new Animation(atlas_right_white, 45);
}

Player::~Player()
{
	delete anim_left;
	delete anim_right;
}

void Player::ProcessEvent(const ExMessage& msg)
{
	// 处理用户输入
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case VK_UP:
			is_move_up = true;
			break;
		case VK_DOWN:
			is_move_down = true;
			break;
		case VK_LEFT:
			is_move_left = true;
			break;
		case VK_RIGHT:
			is_move_right = true;
			break;
		}
	}
	else if (msg.message == WM_KEYUP)
	{
		switch (msg.vkcode)
		{
		case VK_UP:
			is_move_up = false;
			break;
		case VK_DOWN:
			is_move_down = false;
			break;
		case VK_LEFT:
			is_move_left = false;
			break;
		case VK_RIGHT:
			is_move_right = false;
			break;
		}
	}
}

void Player::Move()
{
	int dir_x = is_move_right - is_move_left;
	int dir_y = is_move_down - is_move_up;
	double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (len_dir != 0)
	{
		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_y / len_dir;
		position.x += (int)(SPEED * normalized_x);
		position.y += (int)(SPEED * normalized_y);
	}

	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x + FRAME_WIDTH > WINDOW_WIDTH) position.x = WINDOW_WIDTH - FRAME_WIDTH;
	if (position.y + FRAME_HEIGHT > WINDOW_HEIGHT) position.y = WINDOW_HEIGHT - FRAME_HEIGHT;
}

void Player::Draw(int delta)
{
	int shadow_x = 0;
	int shadow_y = 0;

	static bool facing_left = true;
	int dir_x = is_move_right - is_move_left;
	if (dir_x < 0)
		facing_left = true;
	else if (dir_x > 0)
		facing_left = false;

	if (facing_left)
	{
		shadow_x = position.x + 16;
		shadow_y = position.y + FRAME_HEIGHT;
		putimage_alpha(shadow_x, shadow_y, &img_shadow);
		if(gethurt)
		{
			static int countdown_left = HURT_FLICK;
			if ((countdown_left % 2) && (countdown_left != 0))
			{
				anim_left_white->Play(position.x, position.y, delta);
			}
			else if (!(countdown_left % 2) && (countdown_left != 0))
			{
				anim_left->Play(position.x, position.y, delta);
			}
			countdown_left--;

			if(countdown_left == 0)
			{
				countdown_left = HURT_FLICK;
				gethurt = false;
			}
		}
		if (!gethurt)
			anim_left->Play(position.x, position.y, delta);
	}
	else
	{
		shadow_x = position.x + (FRAME_WIDTH - SHADOW_WIDTH) - 16;
		shadow_y = position.y + FRAME_HEIGHT;
		putimage_alpha(shadow_x, shadow_y, &img_shadow);
		if (gethurt)
		{
			static int countdown_right = HURT_FLICK;
			if ((countdown_right % 2) && (countdown_right != 0))
			{
				anim_right_white->Play(position.x, position.y, delta);
			}
			else if (!(countdown_right % 2) && (countdown_right != 0))
			{
				anim_right->Play(position.x, position.y, delta);
			}
			countdown_right--;

			if (countdown_right == 0)
			{
				countdown_right = HURT_FLICK;
				gethurt = false;
			}
		}
		if(!gethurt)
			anim_right->Play(position.x, position.y, delta);
	}
}

const POINT Player::GetPostion() const
{
	return position;
}

const POINT Player::GetBBox() const
{
	POINT bbox = { FRAME_WIDTH, FRAME_HEIGHT };
	return bbox;
}