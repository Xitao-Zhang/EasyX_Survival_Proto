#include <graphics.h>
#include <string>
#include "../includes/utils.hpp"
#include "../includes/Player.hpp"
#include "../includes/Enemy.hpp"
#include "../includes/StartButton.hpp"
#include "../includes/QuitButton.hpp"

#pragma comment(lib, "Winmm.lib") 

#define PI 3.1415926

#define FPS 60
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define BUTTON_WIDTH 192
#define BUTTON_HEIGHT 75
#define ENEMY_GEN_FREQ 4
#define PLAYER_HEART 10
#define BULLET_NUM 5

#define DEBUG
#undef DEBUG

IMAGE img_background;
IMAGE img_menu;

Player* player = new Player();

void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	const int INTERVAL = 100 / ENEMY_GEN_FREQ;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}

void UpdateBullets(std::vector<Bullet>& bullet_list, const Player& player)
{
	const double RADIAL_SPEED = 0.0045;                   // �����ٶ�
	const double TANGENT_SPEED = 0.0055;                  // �����ٶ�
	double radian_interval = 2 * PI / bullet_list.size(); // �ӵ����
	POINT player_position = player.GetPostion();
	double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
	for (size_t i = 0; i < bullet_list.size(); i++)
	{
		double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i; // ��ǰ�ӵ��Ļ���ֵ
		bullet_list[i].postion.x = player_position.x + player.GetBBox().x / 2 + (int)(radius * sin(radian));
		bullet_list[i].postion.y = player_position.y + player.GetBBox().y / 2 + (int)(radius * cos(radian));
	}
}

int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	// ������Ƶ��Դ
	//mciSendString(_T("open assets/audio/bgm1.mp3 alias bgm wait"), NULL, 0, NULL);
	//mciSendString(_T("open assets/audio/hit.wav alias hit"), NULL, 0, NULL); 

	//mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);

	// ����ͼƬ��Դ
	loadimage(&img_menu, _T("assets/imgs/ui/menu.png"));
	loadimage(&img_background, _T("assets/imgs/background.png"));
	
	bool running = true;
	bool is_game_started = false;

	ExMessage msg;
	std::vector<Enemy*> enemy_list;
	std::vector<Bullet> bullet_list(BULLET_NUM);

	RECT region_btn_start, region_btn_quit;
	region_btn_start.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region_btn_start.right = region_btn_start.left + BUTTON_WIDTH;
	region_btn_start.top = 430;
	region_btn_start.bottom = region_btn_start.top + BUTTON_HEIGHT;

	region_btn_quit.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region_btn_quit.right = region_btn_quit.left + BUTTON_WIDTH;
	region_btn_quit.top = 550;
	region_btn_quit.bottom = region_btn_quit.top + BUTTON_HEIGHT;

	StartButton start_btn = StartButton(region_btn_start, _T("assets/imgs/ui/ui_start_idle.png"),
		_T("assets/imgs/ui/ui_start_hovered.png"), _T("assets/imgs/ui/ui_start_pushed.png"));
	QuitButton quit_btn = QuitButton(region_btn_quit, _T("assets/imgs/ui/ui_quit_idle.png"),
		_T("assets/imgs/ui/ui_quit_hovered.png"), _T("assets/imgs/ui/ui_quit_pushed.png"));

	BeginBatchDraw();

	while (running)
	{
		static int heart = PLAYER_HEART;
		if (start_btn.clicked)
			is_game_started = true;
		else if (quit_btn.clicked)
			running = false;

		if (!is_game_started)
		{
			cleardevice();
			putimage(0, 0, &img_menu);
			start_btn.Draw();
			quit_btn.Draw();
			FlushBatchDraw();

			while (peekmessage(&msg))
			{
				start_btn.ProcessEvent(msg);
				quit_btn.ProcessEvent(msg);
			}
			
			continue;
		}


		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			// �����û�����
			player->ProcessEvent(msg);
		}

		// �ƶ�
		player->Move();
		UpdateBullets(bullet_list, *player);
		TryGenerateEnemy(enemy_list);
		for (Enemy* enemy : enemy_list)
			enemy->Move(*player);

		// ��ײ���
		// ��������ҵ���ײ���
		for (Enemy* enemy : enemy_list)
		{
			if (enemy->CheckPlayerCollision(*player))
			{
				if (heart > 0)
				{
					heart--;
					player->gethurt = true;
					enemy->Hurt();
					if (heart == 0)
					{
						MessageBox(GetHWnd(), _T("ʧ��"), _T("��Ϸ����"), MB_OK);
						running = false;
					}
				}
				break;
			}
		}

		// �������ӵ�����ײ���
		for (Enemy* enemy : enemy_list)
		{
			for (const Bullet& bullet : bullet_list)
			{
				if (enemy->CheckBulletCollision(bullet))
					//mciSendString(_T("play hit from 0"), NULL, 0, NULL);
					enemy->Hurt();
			}
		}

		// �Ƴ�����ֵΪ0�ĵ���
		for (size_t i = 0; i < enemy_list.size(); i++)
		{
			Enemy* enemy = enemy_list[i];
			if (!enemy->CheckAlive())
			{
				std::swap(enemy_list[i], enemy_list.back());
				enemy_list.pop_back();
				delete enemy;
			}
		}

		// ��Ⱦ
		cleardevice();

		putimage(0, 0, &img_background);
		player->Draw(20);
		DrawTipText(heart);
		for (Enemy* enemy : enemy_list)
			enemy->Draw(20);
		for (const Bullet& bullet : bullet_list)
			bullet.Draw();

#ifdef DEBUG
		DrawBBox(player->GetPostion().x, player->GetPostion().y, player->GetBBox().x, player->GetBBox().y);
		for (Enemy* enemy : enemy_list)
		{
			solidcircle(enemy->GetCheckPoint().x, enemy->GetCheckPoint().y, 2);
		}
		//solidcircle(player_pos.x, player_pos.y, 2); // ��ʾλ��

		DrawTipText(enemy_list.size());
#endif // DEBUG

		FlushBatchDraw();

		// �Ż�
		// whileִ�нϿ죬ռ��CPU�ϸ�
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / FPS) // �趨ˢ����ΪFPS
		{
			Sleep(1000 / FPS - delta_time);
		}
	}

	EndBatchDraw();

	return 0;
}