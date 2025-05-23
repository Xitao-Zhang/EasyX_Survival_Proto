#include "Enemy.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

Enemy::Enemy()
{
	loadimage(&img_shadow, _T("assets/imgs/shadow_player.png"));
	atlas_left = new Atlas(_T("assets/imgs/FlyingEye/FlyingEye_IDLE_Left_%d.png"), FRAME_NUM);
	atlas_right = new Atlas(atlas_left,processtype::flip);
	anim_left = new Animation(atlas_left, 45);
	anim_right = new Animation(atlas_right, 45);
	
	enum class SpawnEdge
	{
		Up = 0,
		Down,
		Left,
		Right
	};

	SpawnEdge edge = (SpawnEdge)(rand() % 4);
	switch (edge)
	{
	case SpawnEdge::Up:
		position.x = rand() % WINDOW_WIDTH; 
		position.y = -FRAME_HEIGHT;
		break;
	case SpawnEdge::Down:
		position.x = rand() % WINDOW_WIDTH;
		position.y = -FRAME_HEIGHT;
		break;
	case SpawnEdge::Left:
		position.x = -FRAME_WIDTH;
		position.y = rand() % WINDOW_HEIGHT;
		break;
	case SpawnEdge::Right:
		position.x = -FRAME_WIDTH;
		position.y = rand() % WINDOW_HEIGHT;
		break;
	default:
		break;
	}
}

Enemy::~Enemy()
{
	delete anim_left;
	delete anim_right;
}

bool Enemy::CheckBulletCollision(const Bullet& bullet)
{
	bool is_overlap_x = (bullet.postion.x >= position.x && bullet.postion.x <= position.x + FRAME_WIDTH);
	bool is_overlap_y = (bullet.postion.y >= position.y && bullet.postion.y <= position.y + FRAME_HEIGHT);
	return is_overlap_x && is_overlap_y;
}

bool Enemy::CheckPlayerCollision(const Player& player)
{
	// µÐÈËµÄÅö×²¼ì²âµã
	POINT check_point = { position.x + FRAME_WIDTH / 2, position.y + FRAME_HEIGHT / 2 };
	int tolerance = 5;
	bool is_overlap_x = check_point.x > player.GetPostion().x + tolerance && check_point.x <= player.GetPostion().x + player.GetBBox().x - tolerance;
	bool is_overlap_y = check_point.y > player.GetPostion().y + tolerance && check_point.y <= player.GetPostion().y + player.GetBBox().y - tolerance;
	return is_overlap_x && is_overlap_y;
}

void Enemy::Move(const Player& player)
{
	const POINT& player_position = player.GetPostion();
	int dir_x = player_position.x - position.x;
	int dir_y = player_position.y - position.y;
	double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (len_dir != 0)
	{
		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_y / len_dir;
		position.x += (int)(SPEED * normalized_x);
		position.y += (int)(SPEED * normalized_y);
	}

	if (dir_x < 0)
		facing_left = true;
	else if (dir_x > 0)
		facing_left = false;
}

void Enemy::Draw(int delta)
{
	int shadow_x = 0;
	int shadow_y = 0;
	/*int position_x = position.x + (FRAME_WIDTH / 2 - SHADOW_WIDTH / 2);
	int position_y = position.y + FRAME_HEIGHT - 5;
	putimage_alpha(position_x, position_y, &img_shadow);*/

	if (facing_left)
	{
		shadow_x = position.x + 3;
		shadow_y = position.y + FRAME_HEIGHT - 6;
		putimage_alpha(shadow_x, shadow_y, &img_shadow);
		anim_left->Play(position.x, position.y, delta);
	}
	else
	{
		shadow_x = position.x + (FRAME_WIDTH - SHADOW_WIDTH) + 8;
		shadow_y = position.y + FRAME_HEIGHT - 6;
		putimage_alpha(shadow_x, shadow_y, &img_shadow);
		anim_right->Play(position.x, position.y, delta);
	}

}

POINT Enemy::GetCheckPoint()
{
	POINT check_point = { position.x + FRAME_WIDTH / 2, position.y + FRAME_HEIGHT / 2 };
	return check_point;
}

void Enemy::Hurt()
{
	alive = false;
}

bool Enemy::CheckAlive()
{
	return alive;
}