#define _CRT_SECURE_NO_WARNINGS
#define WINDOW_LEN 456
#define WINDOW_LINE 100
#define MID_LINE 13
#define WINDOW_ALLLINE 213
#define DOWNSIDE_Y 113
#define CHARA_LEN 26
#define CHARA_LINE 16
#define PET_LEN 24
#define PET_LINE 9
#define CHARA_ORANGE_LEN 35
#define CHARA_ORANGE_LINE 23
#define CHARA_MOTION 9
#define CHARA_ORANGE_MOTION 5
#define PET_MOTION 3
#define ORANGE_LEN 35
#define ORANGE_LINE 18
#define TOTAL_ROOM_TYPE 3
#define SCORE_LEN 8
#define SCORE_LINE 5
#define HP_LEN 11
#define HP_LINE 6
#define LETTER_LEN 6
#define LETTER_LINE 7
#define MES_LEN 47
#define MES_LINE 7
#define TITLE_LINE 56
#define PRESS_LEN 92
#define PRESS_LINE 7
#define DIALOG_LINE 12
#define RULES_LINE 64
#define RESULT_LINE 45
#define REPLAY_LEN 194
#define REPLAY_LINE 34

/*コントロールのタイプ*/
enum ControlType
{
	KEYBOARD,
	JOYSTICK
};
enum CharacterSpeedType
{
	NORMAL,
	SLOW
};
/*キャラの状態*/
enum CharacterAction
{
	DEAD,
	MOVE,
	STAND,
	CLIMB,
	JUMP,
};
#include"conioex.h"
#include<time.h>

typedef struct 
{
	int x;
	int y;
	int old_x;
	int old_y;
	bool dir;
	int anim;
	int room;
}Bullet_Data;

typedef struct
{
	int x;
	int y;
	int old_x;
	int old_y;
	float dx;
	float dy;
	float spd;
	float jumpforce;
	float dx_limit;
	int dy_limit;
	int hp;
	int old_hp;
	int hp_max;
	int st;
	int old_st;
	int st_old;
	int score;
	int old_score;
	bool win;
	bool faceright;
	bool jump;
	bool climb;
	bool down;
	bool getfruit;
	bool fall;
	bool rdyfire;
	bool usedtobeorange;
	bool usedtofire;
	bool switchroom;
	bool cc;
	int room;
	int old_room;
	int controltype;
	bool hitwall;
	Bullet_Data atk;
}Character_Data;
Character_Data player[2] = { 0 };

int psc_map[3][WINDOW_LINE][WINDOW_LEN] = { 0 };
int map[3][WINDOW_LINE][WINDOW_LEN] = { 0 };
int chara[2][CHARA_MOTION][CHARA_LINE][CHARA_LEN] = { 0 };
int midmap[MID_LINE][WINDOW_LEN] = { 0 };
int bigmap[WINDOW_ALLLINE][WINDOW_LEN] = { 0 };
int chara_orange[2][CHARA_ORANGE_MOTION][CHARA_ORANGE_LINE][CHARA_ORANGE_LEN] = { 0 };
int pet_data[2][PET_MOTION][PET_LINE][PET_LEN] = { 0 };
int score_data[2][SCORE_LINE][SCORE_LEN] = { 0 };
int hp_data[2][HP_LINE][HP_LEN] = { 0 };
int letter_data[10][LETTER_LINE][LETTER_LEN] = { 0 };
int mes_data[3][MES_LINE][MES_LEN] = { 0 };
int title_data[TITLE_LINE][WINDOW_LEN] = { 0 };
int press_data[PRESS_LINE][PRESS_LEN] = { 0 };
int dialog_data[5][DIALOG_LINE][WINDOW_LEN] = { 0 };
int rules_data[3][RULES_LINE][WINDOW_LEN] = { 0 };
int result_data[3][RESULT_LINE][WINDOW_LEN] = { 0 };
int replay_data[REPLAY_LINE][REPLAY_LEN] = { 0 };

char midpic[MID_LINE*WINDOW_LEN * 22] = { 0 };
char pic[3][WINDOW_LINE*WINDOW_LEN * 22] = { 0 };
char bigpic[WINDOW_ALLLINE*WINDOW_LEN*22] = { 0 };
char display[2][WINDOW_LINE*WINDOW_LEN * 22] = { 0 };
char man[2][CHARA_MOTION][CHARA_LINE*CHARA_LEN * 22] = { 0 };
char pet[4][PET_MOTION][PET_LINE*PET_LEN*22] = { 0 };
char score_pic[2][SCORE_LINE*SCORE_LEN*22] = { 0 };
char hp_pic[2][HP_LINE*HP_LEN*22] = { 0 };
char letter_pic[10][LETTER_LINE*LETTER_LEN*22] = { 0 };
char mes_pic[3][MES_LINE*MES_LEN*22] = { 0 };
char title_pic[TITLE_LINE*WINDOW_LEN*22] = { 0 };
char press_pic[PRESS_LINE*PRESS_LEN*22] = { 0 };
char press_cover[PRESS_LINE*PRESS_LEN * 22] = { 0 };
char dialog_pic[5][DIALOG_LINE*WINDOW_LEN*22] = { 0 };
char rules_pic[3][RULES_LINE*WINDOW_LEN*22] = { 0 };
char result_pic[3][RESULT_LINE*WINDOW_LEN*22] = { 0 };
char replay_pic[REPLAY_LINE*REPLAY_LEN*22] = { 0 };

char cover[2][PET_LINE*PET_LEN * 22] = { 0 };
char coverman[2][CHARA_LINE*CHARA_LEN * 22] = { 0 };
char man_orange[2][CHARA_ORANGE_MOTION][CHARA_ORANGE_LINE*CHARA_ORANGE_LEN*22] = { 0 };
char coverman_orange[2][CHARA_ORANGE_LINE*CHARA_ORANGE_LEN * 22] = { 0 };
char select_pic[2 * 60 * 2] = { 0 };
char select_pic_cover[2 * 60 * 2] = { 0 };

char c[1];

float gravity = 1.2f;
float friction = 2.2f;
int time_st;
int time_ed;
int count_st;
int b_spd = 10;
int ct_max = 546;
//int ct_max = 3;//test用
int old_ct;
int countdown;
int min_ten, min_one, sec_ten, sec_one;
int old_mten, old_mone, old_sten, old_sone;
void title();
void rules();
void setgame();
int game();
int ending();
void setscene();
void updatecontrol();
void updatescene();
void result();
void setFontSize(int nX, int nY);
void loadtitle();
void loadgame();
void loadmusic();
void effect(int id,int type);

int bgm0;
int cat_SE0;
int dog_SE0;
int confirm_SE;
int jump_SE;
int music[4] = {0};

int main(void)
{
	setFontSize(3,3);
	//system("mode con cols=456 lines=213");							//プログラムの画面サイズを設定
	system("mode con cols=456 lines=213");							//プログラムの画面サイズを設定
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	char titlename[] = "オレンジ！！！";									//プログラムの名前
	setcaption(titlename); 
	setcursortype(NOCURSOR);
	GetConsoleMode(hIn, &mode);
	mode = mode & ~ENABLE_QUICK_EDIT_MODE;
	mode = mode & ~ENABLE_INSERT_MODE;
	SetConsoleMode(hIn, mode);
	loadtitle();
	loadmusic();
	setvolume(bgm0, 100);
	int cc;
	while (1)
	{
		srand((int)time(NULL));
		title();
		rules();
		while (1)
		{
			cc = game();
			if (cc)
			{
				break;
			}
			for (int i = 0; i < 2; i++)
			{
				cover[i][0] = NULL;
				coverman[i][0] = NULL;
				coverman_orange[i][0] = NULL;
			}
		}
		if (cc)
		{
			break;
		}
		clrscr();
	}
	
	closesound(bgm0);
	closesound(cat_SE0);
	closesound(dog_SE0);
	closesound(confirm_SE);
	closesound(jump_SE);
	CloseHandle(hIn);
	for (int i = 0; i < 4; i++)
	{
		closesound(music[i]);
	}
	return 0;
}
/*タイトル画面*/
void title()
{
	gotoxy(1, 1);
	printf("%s", bigpic);
	gotoxy(1,70);
	printf("%s", title_pic);
	gotoxy(181, 164);
	printf("%s", press_pic);
	playsound(bgm0, 1);
	playsound(music[0], 1);
	time_st = clock();
	while (1)
	{
		time_ed = clock();
		updatesound(bgm0);
		updatesound(music[0]);
		if (time_ed-time_st>500)
		{
			time_st = clock();
		}
		if (getch())
		{
			reinport();
			break;
		}
	}
	int count=0;
	bool cc=TRUE;
	playsound(confirm_SE, 0);
	time_st = clock();
	while (1)
	{
		time_ed = clock();
		updatesound(bgm0);
		if (time_ed - time_st>100)
		{
			if (cc)
			{
				gotoxy(181, 164);
				printf("%s", press_pic);
				cc = FALSE;
			}
			else
			{
				gotoxy(181, 164);
				printf("%s", press_cover);
				count++;
				cc = TRUE;
			}
			time_st = clock();
		}
		if (count>7)
		{
			break;
		}
	}
	clrscr();
}
/*ルール説明画面*/
void rules()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD mouseRec;
	COORD crPos;
	DWORD	res;
	gotoxy(1, 1);
	printf("%s", bigpic);
	time_st = clock();
	int count = 0;
	while (1)
	{
		updatesound(music[0]);
		time_ed = clock();
		updatesound(bgm0);

		if (time_ed-time_st>3000)
		{
			switch (count)
			{
			case 0:
				gotoxy(1, 49);
				printf("%s", dialog_pic[0]);
				break;
			case 1:
				gotoxy(1, 63);
				printf("%s", dialog_pic[1]);
				break;
			case 2:
				gotoxy(1, 77);
				printf("%s", dialog_pic[2]);
				break;
			case 3:
				gotoxy(1, 91);
				printf("%s", dialog_pic[3]);
				break;
			case 4:
				gotoxy(1, 105);
				printf("%s", dialog_pic[4]);
				break;
			default:
				break;
			}
			count++;
			time_st = clock();
		}
		if (count>5)
		{
			break;
		}
	}

	int page = 0;
	int old_page=-1;
	int mouse_x, mouse_y;
	while (1)
	{
		updatesound(music[0]);
		updatesound(bgm0);
		if (old_page!=page)
		{
			gotoxy(1, 136);
			printf("%s", rules_pic[page]);
		}
		old_page = page;
		fflush(stdin);
		SetConsoleMode(hIn, 16);
		ReadConsoleInput(hIn, &mouseRec, 1, &res);
		crPos = mouseRec.Event.MouseEvent.dwMousePosition;
		mouse_x = crPos.X;
		mouse_y = crPos.Y;
		if (page == 2)
		{
			if (mouseRec.Event.MouseEvent.dwButtonState == 1 && mouse_y>169 && mouse_y<182 && mouse_x>361 && mouse_x<439)
			{
				playsound(confirm_SE, 0);
				break;
			}
		}
		if (mouseRec.Event.MouseEvent.dwButtonState==1 && mouse_y>185 && mouse_y<196 && mouse_x>361 && mouse_x<384)
		{
			page--;
		}
		else if (mouseRec.Event.MouseEvent.dwButtonState == 1 && mouse_y>185 && mouse_y<196 && mouse_x>416 && mouse_x<439)
		{
			page++;
		}
		if (page<0)
		{
			page = 0;
		}
		else if (page>2)
		{
			page = 2;
		}
		
	}
	loadgame();
	clrscr();
}
/*ゲームデータを設定する*/
void setgame()
{
	stopsound(music[0]);
	min_ten = -1, min_one = -1, sec_ten = -1, sec_one = -1;
	player[0].x = 1;
	player[0].y = 81;
	player[1].x = WINDOW_LEN - CHARA_LEN;
	player[1].y = 81;
	player[0].faceright = TRUE;
	player[1].faceright = FALSE;
	player[0].win = FALSE;
	player[1].win = FALSE;
	player[0].rdyfire = TRUE;
	player[1].rdyfire = TRUE;
	player[0].dy_limit = 0;
	player[1].dy_limit = 0;
	effect(0,NORMAL);
	effect(1,NORMAL);
	player[0].rdyfire = TRUE;
	player[1].rdyfire = TRUE;
	player[0].hp_max = 3;
	player[1].hp_max = 3;
	player[0].hp = player[0].hp_max;
	player[1].hp = player[1].hp_max;
	player[0].score = 0;
	player[1].score = 0;
	player[0].st = STAND;
	player[1].st = STAND;
	player[0].old_st = STAND;
	player[1].old_st = STAND;
	player[0].room = 0;
	player[1].room = 2;
	player[0].old_room = 0;
	player[1].old_room = 2;
	player[0].controltype = KEYBOARD;
	player[1].controltype = JOYSTICK;
}
/*ゲーム本体*/
int game()
{
	setgame();
	int count_ed;
	countdown = ct_max;
	if (countdown==546)
	{
		playsound(music[1], 0);
	}
	setscene();
	time_st= clock();
	count_st = time(NULL);
	while (1)
	{
		updatesound(bgm0);
		time_ed = clock();
		count_ed = time(NULL);
		if (time_ed-time_st>30)
		{
			updatecontrol();
			updatescene();
			time_st = clock();
		}
		old_ct = countdown;
		countdown=ct_max-(count_ed - count_st);
		
		if (countdown==288)
		{
			playsound(music[2], 0);
		}
		if (countdown==107)
		{
			playsound(music[3], 0);
		}
		if (player[0].win||player[1].win||countdown<0)
		{
			break;
		}
	}
	result();
	return ending();
}
/*初期画面*/
void setscene()
{
	int count = 0;
	gotoxy(1, 1);
	printf("%s", pic[player[0].room]);
	gotoxy(1, 1 + WINDOW_LINE);
	printf("%s", midpic);
	gotoxy(1, 1 + DOWNSIDE_Y);
	printf("%s", pic[player[1].room]);
	for (int i = 0; i < 2; i++)
	{
		int x_hp;
		switch (i)
		{
		case 0:
			x_hp = 89;
			break;
		case 1:
			x_hp = 380;
			break;
		default:
			break;
		}
		gotoxy(x_hp, 102);
		printf("%s", hp_pic[1]);
		gotoxy(x_hp + 16, 102);
		printf("%s", hp_pic[1]);
		gotoxy(x_hp + 32, 102);
		printf("%s", hp_pic[1]);
		int x_score;
		switch (i)
		{
		case 0:
			x_score = 78;
			break;
		case 1:
			x_score = 369;
			break;
		default:
			break;
		}
		gotoxy(x_score, 109);
		printf("%s", score_pic[0]);
		gotoxy(x_score + 16, 109);
		printf("%s", score_pic[0]);
		gotoxy(x_score + 32, 109);
		printf("%s", score_pic[0]);
	}
	time_st = clock();
	while (1)
	{
		updatesound(bgm0);
		time_ed = clock();
		if (time_ed-time_st>1000)
		{
			switch (count)
			{
			case 0:
				gotoxy(228, 102);
				printf("%s", letter_pic[3]);
				break;
			case 1:
				gotoxy(228, 102);
				printf("%s", letter_pic[2]);
				break;
			case 2:
				gotoxy(228, 102);
				printf("%s", letter_pic[1]);
				break;
			case 3:
				gotoxy(208, 102);
				printf("%s", mes_pic[1]);
				break;
			case 4:
				gotoxy(208, 102);
				printf("%s", mes_pic[2]);
				break;
			default:
				break;
			}
			count++;
			time_st = clock();
		}
		if (count>5)
		{
			gotoxy(208, 102);
			printf("%s", mes_pic[0]);
			break;
		}
	}
}
/*データ更新*/
void updatecontrol() 
{
	int oldnum;
	int newnum;
	int ky;
	int kx;
	int count;
	for (int k = 0; k < 2; k++)
	{
		player[k].old_x = player[k].x;
		player[k].old_y = player[k].y;
		player[k].old_hp = player[k].hp;
		player[k].old_st = player[k].st;
		kx = player[k].x;
		ky = player[k].y;
		oldnum = -1;
	
		if (player[k].getfruit==TRUE)
		{
			coverman_orange[k][0] = '\0';
			for (int i = 0; i < CHARA_ORANGE_LINE; i++)
			{
				strcat(coverman_orange[k], "\033[s");
				for (int j = 0; j < CHARA_ORANGE_LEN; j++)
				{
					newnum = map[player[k].room][player[k].y - 7 + i][player[k].x - 2 + j];
					if (oldnum == newnum)
					{
						strcat(coverman_orange[k], " ");
					}
					else
					{
						int rgb[9];
						strcat(coverman_orange[k], "\033[48;2;");
						for (int count = 0; count < 9; count++)
						{
							int ten = 1;
							for (int kk = 0; kk < count; kk++)
							{
								ten *= 10;
							}
							rgb[count] = (newnum / (100000000 / ten)) % 10;
							itoa(rgb[count], c, 10);
							strcat(coverman_orange[k], c);
							if (count == 2 || count == 5)
							{
								strcat(coverman_orange[k], ";");
							}
							else if (count == 8)
							{
								strcat(coverman_orange[k], "m");
							}
						}
						strcat(coverman_orange[k], " ");
					}
					oldnum = newnum;
				}
				strcat(coverman_orange[k], "\033[u");
				strcat(coverman_orange[k], "\033[1B");
			}
		}
		else
		{
			coverman[k][0] = '\0';
			for (int i = 0; i < CHARA_LINE; i++)
			{
				strcat(coverman[k], "\033[s");
				for (int j = 0; j < CHARA_LEN; j++)
				{
					newnum = map[player[k].room][player[k].y + i][player[k].x + j];
					if (oldnum == newnum)
					{
						strcat(coverman[k], " ");
					}
					else
					{
						int rgb[9];
						strcat(coverman[k], "\033[48;2;");
						for (int count = 0; count < 9; count++)
						{
							int ten = 1;
							for (int kk = 0; kk < count; kk++)
							{
								ten *= 10;
							}
							rgb[count] = (newnum / (100000000 / ten)) % 10;
							itoa(rgb[count], c, 10);
							strcat(coverman[k], c);
							if (count == 2 || count == 5)
							{
								strcat(coverman[k], ";");
							}
							else if (count == 8)
							{
								strcat(coverman[k], "m");
							}
						}
						strcat(coverman[k], " ");
					}
					oldnum = newnum;
				}
				strcat(coverman[k], "\033[u");
				strcat(coverman[k], "\033[1B");
			}
		} 
		
		for (int i = 0; i < CHARA_LINE; i++)
		{
			for (int j = 0; j < 14; j++)
			{
				if (psc_map[player[k].room][ky + i][kx + 6 + j] == 2)
				{
					player[k].climb = 1;
					break;
				}
				else
				{
					player[k].climb = 0;
				}
			}
			if (player[k].climb == 1)
			{
				break;
			}
		}
		for (int j = 0; j < 14; j++)
		{
			if (psc_map[player[k].room][ky + CHARA_LINE][kx + 6 + j]==2)
			{
				player[k].down = 1;
				break;
			}
			else
			{
				player[k].down = 0;
			}
		}
		for (int j = 0; j < 6; j++)
		{
			if (psc_map[player[k].room][ky + CHARA_LINE][kx + 10 + j] == 1)
			{
				player[k].fall = FALSE;
				break;
			}
			else
			{
				player[k].fall = TRUE;
			}
		}
		if (player[k].getfruit==FALSE)
		{
			if (k==0)
			{
				if (player[0].room == 2)
				{
					if (psc_map[2][ky + 10][kx] == 3)
					{
						effect(0, SLOW);
					}
				}
			}
			else
			{
				if (player[1].room == 0)
				{
					if (psc_map[0][ky + 10][kx + CHARA_LEN - 1] == 3)
					{
						effect(1, SLOW);
					}
				}
			}
		}
		if (player[k].old_score!=player[k].score)
		{
			player[k].old_score = player[k].score;
		}
		if (player[k].getfruit == TRUE)
		{
			if (k == 0)
			{
				if (player[0].room == 0)
				{
					if (psc_map[0][ky + 10][kx + CHARA_LEN-1] == 3)
					{
						effect(0, NORMAL);
						player[0].score++;
					}
				}
			}
			else
			{
				if (player[1].room == 2)
				{
					if (psc_map[2][ky + 10][kx] == 3)
					{
						effect(1,NORMAL);
						player[1].score++;
					}
				}
			}
		}

		if (psc_map[player[k].room][ky + 10][kx + CHARA_LEN - 1] == 5 || psc_map[player[k].room][ky + 10][kx] == 5)
		{
			player[k].switchroom = TRUE;
		}
		else
		{
			player[k].switchroom = FALSE;
		}

		if (player[k].climb && player[k].down)
		{
			player[k].st = CLIMB;
			player[k].dx = 0;
			player[k].fall = FALSE;
		}
		else
		{
			if (player[k].fall)
			{
				player[k].st = JUMP;
			
				player[k].jump = TRUE;
				player[k].dy_limit = 6;
			}
			else
			{
				player[k].st = STAND;
			}
		}
	}

	for (int k = 0; k < 2; k++)
	{
		if (player[k].rdyfire==FALSE)
		{
			switch (k)
			{
			case 0:
				if (player[0].atk.room == player[1].room)
				{
					if ((player[0].atk.x > player[1].x && player[0].atk.x<player[1].x + CHARA_LEN - 1 && player[0].atk.y>player[1].y && player[0].atk.y < player[1].y + CHARA_LINE - 1) || (player[0].atk.x + PET_LEN - 1 > player[1].x && player[0].atk.x + PET_LEN - 1 < player[1].x + CHARA_LEN - 1 && player[0].atk.y + PET_LINE - 1 > player[1].y && player[0].atk.y + PET_LINE - 1 < player[1].y + CHARA_LINE - 1))
					{
						player[1].hp--;
						player[0].rdyfire = TRUE;
					}
				}
				break;
			case 1:
				if (player[1].atk.room == player[0].room)
				{
					if ((player[1].atk.x > player[0].x && player[1].atk.x<player[0].x + CHARA_LEN - 1 && player[1].atk.y>player[0].y && player[1].atk.y < player[0].y + CHARA_LINE - 1) || (player[1].atk.x + PET_LEN - 1 > player[0].x && player[1].atk.x + PET_LEN - 1 < player[0].x + CHARA_LEN - 1 && player[1].atk.y + PET_LINE - 1 > player[0].y && player[1].atk.y + PET_LINE - 1 < player[0].y + CHARA_LINE - 1))
					{
						player[0].hp--;
						player[1].rdyfire = TRUE;
					}
				}
				break;
			default:
				break;
			}
		}
		
		if (player[k].usedtofire)
		{
			oldnum = -1;
			cover[k][0] = '\0';
			player[k].atk.old_x = player[k].atk.x;
			player[k].atk.old_y = player[k].atk.y;
			for (int i = 0; i < PET_LINE; i++)
			{
				strcat(cover[k], "\033[s");
				for (int j = 0; j < PET_LEN; j++)
				{
					newnum = map[player[k].room][player[k].atk.old_y + i][player[k].atk.old_x + j];
					if (oldnum == newnum)
					{
						strcat(cover[k], " ");
					}
					else
					{
						int rgb[9];
						strcat(cover[k], "\033[48;2;");
						for (int count = 0; count < 9; count++)
						{
							int ten = 1;
							for (int kk = 0; kk < count; kk++)
							{
								ten *= 10;
							}
							rgb[count] = (newnum / (100000000 / ten)) % 10;
							itoa(rgb[count], c, 10);
							strcat(cover[k], c);
							if (count == 2 || count == 5)
							{
								strcat(cover[k], ";");
							}
							else if (count == 8)
							{
								strcat(cover[k], "m");
							}
						}
						strcat(cover[k], " ");
					}
					oldnum = newnum;
				}
				strcat(cover[k], "\033[u");
				strcat(cover[k], "\033[1B");
			}
			
			if (player[k].atk.anim < PET_MOTION-1)
			{
				player[k].atk.anim++;
			}
			else
			{
				player[k].atk.anim = 0;
			}
			if (player[k].atk.dir)
			{
				player[k].atk.x += b_spd;
			}
			else
			{
				player[k].atk.x -= b_spd;
			}
			if (player[k].atk.x > WINDOW_LEN-PET_LEN+1 || player[k].atk.x < 1)
			{
				player[k].rdyfire = TRUE;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		player[i].st_old = player[i].st;
	
		if (player[i].controltype == JOYSTICK)
			{
			int jc_x;
			jc_x = inport(PJ_XPOS);

			/*switch (i)
			{
			case 0:
				jc_x = inport(PJ_XPOS);
				break;
			case 1:
				jc_x = inport(PJ2_XPOS);	
				break;
			default:
				break;
			}*/
			if (jc_x >= 0)
			{
				int key;
				int key_old = -1;
				int jc_y;
				key = inport(PJ_BTNS);
				jc_y = inport(PJ_YPOS);
				/*switch (i)
				{
				case 0:
					key = inport(PJ_BTNS);
					jc_y = inport(PJ_YPOS);
					break;
				case 1:
					key = inport(PJ2_BTNS);
					jc_y = inport(PJ2_YPOS);
					break;
				default:
					break;
				}*/
				
				if (jc_x > 45535 || jc_x < 20000)
				{
					if (player[i].st != CLIMB)
					{
						if (jc_x > 45535)
						{
							if (player[i].faceright == FALSE)
							{
								player[i].dx = 0.0f;
								player[i].faceright = TRUE;
								player[i].switchroom = FALSE;
							}
							if (player[i].switchroom == TRUE && player[i].x > WINDOW_LEN / 2)
							{
								player[i].old_room = player[i].room;
								player[i].room++;
								player[i].x = 1;
							}
							else
							{
								if (player[i].dx < player[i].dx_limit)
								{
									player[i].dx += player[i].spd;
								}
								player[i].dx -= friction;
								if (player[i].dx < 0)
								{
									player[i].dx = 0;
								}
								count = 0;
								for (int g = 0; g < player[i].dx; g++)
								{
									if (psc_map[player[i].room][player[i].y + 12][player[i].x + CHARA_LEN + g] == 4)
									{
										player[i].x += count;
										player[i].hitwall = TRUE;

										break;
									}
									else
									{
										player[i].hitwall = FALSE;
										count++;
									}
								}

								if (player[i].hitwall == FALSE)
								{
									player[i].x += player[i].dx;
								}
							}
							player[i].st = MOVE;
						}
						else
						{
							if (player[i].faceright == TRUE)
							{
								player[i].dx = 0.0f;
								player[i].faceright = FALSE;
								player[i].switchroom = FALSE;
							}
							if (player[i].switchroom == TRUE && player[i].x < WINDOW_LEN / 2)
							{
								player[i].old_room = player[i].room;
								player[i].room--;
								player[i].x = WINDOW_LEN - CHARA_LEN - 1;
							}
							else
							{

								if (player[i].dx < player[i].dx_limit)
								{
									player[i].dx += player[i].spd;
								}
								player[i].dx -= friction;
								if (player[i].dx < 0)
								{
									player[i].dx = 0;
								}
								count = 0;
								for (int g = 0; g < player[i].dx; g++)
								{
									if (psc_map[player[i].room][player[i].y + 12][player[i].x - 1 - g] == 4)
									{
										player[i].x -= count;
										player[i].hitwall = TRUE;

										break;
									}
									else
									{
										player[i].hitwall = FALSE;
										count++;
									}
								}

								if (player[i].hitwall == FALSE)
								{
									player[i].x -= player[i].dx;
								}
							}
							player[i].st = MOVE;
						}
					}
				}
				if (jc_y > 45535 || jc_y < 20000)
				{
					if (jc_y > 45535)
					{
						if (player[i].down)
						{
							player[i].y++;
							if (player[i].cc)
							{
								player[i].cc = 0;
							}
							else
							{
								player[i].cc = 1;
							}
						}
					}
					else
					{
						if (player[i].climb)
						{
							player[i].y--;
							if (player[i].cc)
							{
								player[i].cc = 0;
							}
							else
							{
								player[i].cc = 1;
							}
						}
					}
				}
				if (key_old != key)
				{
					if (key & 1)
					{
						//1
					}
					if (key & 2)
					{
						//jump
						if (player[i].dy_limit < 4)
						{
							player[i].dy_limit += 2;
							if (player[i].jump == FALSE)
							{
								player[i].jump = TRUE;
								playsound(jump_SE, 0);
							}
							player[i].dy -= player[i].jumpforce;
						}
					}
					if (player[i].jump == FALSE && player[i].getfruit == FALSE && player[i].st != CLIMB)
					{
						if (key & 4)
						{
							//attack
							if (player[i].rdyfire)
							{
								if (i)
								{
									playsound(cat_SE0, 0);
								}
								else
								{
									playsound(dog_SE0, 0);
								}
								player[i].rdyfire = FALSE;
								player[i].atk.anim = 0;
								player[i].atk.dir = player[i].faceright;
								if (player[i].atk.dir)
								{
									player[i].atk.x = player[i].x + CHARA_LEN - 1;
								}
								else
								{
									player[i].atk.x = player[i].x;
								}
								player[i].atk.y = player[i].y + 7;
								player[i].atk.room = player[i].room;
							}
						}
					}
					if (key & 8)
					{
						//release fruit
						if (player[i].getfruit == TRUE)
						{
							effect(i, NORMAL);
						}
					}
				}
				key_old = key;
				}
		}
		else if (player[i].controltype == KEYBOARD)
		{
			if (inport(PK_W))
			{
				if (player[i].climb)
				{
					player[i].y--;
					if (player[i].cc)
					{
						player[i].cc = 0;
					}
					else
					{
						player[i].cc = 1;
					}
				}
			}
			else if (inport(PK_S))
			{
				if (player[i].down)
				{
					player[i].y++;
					if (player[i].cc)
					{
						player[i].cc = 0;
					}
					else
					{
						player[i].cc = 1;
					}
				}
			}

			if (player[i].st != CLIMB)
			{
				if (inport(PK_A))
				{
					if (player[i].faceright == TRUE)
					{
						player[i].dx = 0.0f;
						player[i].faceright = FALSE;
						player[i].switchroom = FALSE;
					}
					if (player[i].switchroom == TRUE && player[i].x < WINDOW_LEN / 2)
					{
						player[i].old_room = player[i].room;
						player[i].room--;
						player[i].x = WINDOW_LEN - CHARA_LEN - 1;
					}
					else
					{

						if (player[i].dx < player[i].dx_limit)
						{
							player[i].dx += player[i].spd;
						}
						player[i].dx -= friction;
						if (player[i].dx < 0)
						{
							player[i].dx = 0;
						}
						count = 0;
						for (int g = 0; g < player[i].dx; g++)
						{
							if (psc_map[player[i].room][player[i].y + 12][player[i].x - 1 - g] == 4)
							{
								player[i].x -= count;
								player[i].hitwall = TRUE;

								break;
							}
							else
							{
								player[i].hitwall = FALSE;
								count++;
							}
						}

						if (player[i].hitwall == FALSE)
						{
							player[i].x -= player[i].dx;
						}
					}
					player[i].st = MOVE;
				}
				else if (inport(PK_D))
				{
					if (player[i].faceright == FALSE)
					{
						player[i].dx = 0.0f;
						player[i].faceright = TRUE;
						player[i].switchroom = FALSE;
					}
					if (player[i].switchroom == TRUE && player[i].x > WINDOW_LEN / 2)
					{
						player[i].old_room = player[i].room;
						player[i].room++;
						player[i].x = 1;
					}
					else
					{
						if (player[i].dx < player[i].dx_limit)
						{
							player[i].dx += player[i].spd;
						}
						player[i].dx -= friction;
						if (player[i].dx < 0)
						{
							player[i].dx = 0;
						}
						count = 0;
						for (int g = 0; g < player[i].dx; g++)
						{
							if (psc_map[player[i].room][player[i].y + 12][player[i].x + CHARA_LEN + g] == 4)
							{
								player[i].x += count;
								player[i].hitwall = TRUE;

								break;
							}
							else
							{
								player[i].hitwall = FALSE;
								count++;
							}
						}

						if (player[i].hitwall == FALSE)
						{
							player[i].x += player[i].dx;
						}
					}
					player[i].st = MOVE;
				}
				if (player[i].jump==FALSE && player[i].getfruit == FALSE)
				{
					if (inport(PK_K))
					{
						if (player[i].rdyfire)
						{
							if (i)
							{
								playsound(cat_SE0, 0);
							}
							else
							{
								playsound(dog_SE0, 0);
							}
							player[i].rdyfire = FALSE;
							player[i].atk.anim = 0;
							player[i].atk.dir = player[i].faceright;
							if (player[i].atk.dir)
							{
								player[i].atk.x = player[i].x + CHARA_LEN - 1;
							}
							else
							{
								player[i].atk.x = player[i].x;
							}
							player[i].atk.y = player[i].y + 7;
							player[i].atk.room = player[i].room;
						}
					}
				}
			}
			if (inport(PK_J))
			{
				if (player[i].dy_limit < 4)
				{
					player[i].dy_limit += 2;
					if (player[i].jump == FALSE)
					{
						player[i].jump = TRUE;
						playsound(jump_SE,0);
					}
					player[i].dy -= player[i].jumpforce;
				}
			}
			if (player[i].getfruit==TRUE)
			{
				if (inport(PK_L))
				{
					effect(i,NORMAL);
				}
			}
		}
	}

	for (int p = 0; p < 2; p++)
	{

		kx = player[p].x;
		ky = player[p].y + CHARA_LINE;

		switch (player[p].room)
		{
		case 0:
			for (int i = 0; i < CHARA_LEN; i++)
			{
				count = 0;
				if (player[p].jump == TRUE)
				{
					if (player[p].dy >= 0)
					{
						player[p].cc = 1;
						for (int g = 0; g < player[p].dy; g++)
						{
							if (psc_map[0][ky + g][kx + i])
							{
								player[p].jump = FALSE;
								for (int up = 1; up <= CHARA_LEN; up++)
								{
									if (psc_map[0][ky + g - up][kx + i] == 0)
									{
										break;
									}
									else if (psc_map[2][ky + g - up][kx + i] == 1)
									{
										count--;
									}
								}
								break;
							}
							else
							{
								count++;
							}
							
						}
						break;
					}
					else
					{
						player[p].cc = 0;
					}
				}
				else
				{
					break;
				}
			}
			break;
		case 1:
			for (int i = 0; i < CHARA_LEN; i++)
			{
				count = 0;
				if (player[p].jump == TRUE)
				{
					if (player[p].dy >= 0)
					{
						player[p].cc = 1;
						for (int g = 0; g < player[p].dy; g++)
						{
							if (psc_map[1][ky + g][kx + i])
							{
								player[p].jump = FALSE;
								for (int up = 1; up <= CHARA_LEN; up++)
								{
									if (psc_map[1][ky + g - up][kx + i]==0)
									{
										break;
									}
									else if (psc_map[2][ky + g - up][kx + i] == 1)
									{
										count--;
									}
								}
								break;
							}
							else
							{
								count++;
							}
						}
						break;
					}
					else
					{
						player[p].cc = 0;
					}
				}
				else
				{
					break;
				}
			}
			break;
		case 2:
			for (int i = 0; i < CHARA_LEN; i++)
			{
				count = 0;
				if (player[p].jump == TRUE)
				{
					if (player[p].dy >= 0)
					{
						player[p].cc = 1;
						for (int g = 0; g < player[p].dy; g++)
						{
							if (psc_map[2][ky + g][kx + i])
							{
								player[p].jump = FALSE;
								for (int up = 1; up <= CHARA_LEN; up++)
								{
									if (psc_map[2][ky + g - up][kx + i] == 0)
									{
										break;
									}
									else if (psc_map[2][ky + g - up][kx + i] == 1)
									{
										count--;
									}
								}
								break;
							}
							else
							{
								count++;
							}
						}
						break;
					}
					else
					{
						player[p].cc = 0;
					}
				}
				else
				{
					break;
				}
			}
			break;
		default:
			break;
		}

		if (player[p].jump == TRUE)
		{
			player[p].dy += gravity;
			player[p].y += player[p].dy;
			player[p].st = JUMP;
		}
		else
		{
			player[p].y += count;
			player[p].dy = 0.0f;
			count = 0;
			player[p].dy_limit = 0;
		}

		for (int i = 0; i < 2; i++)
		{
			if (player[i].y<0)
			{
				player[i].y = 0;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			if (player[i].hp<=0)
			{
				player[i].st = DEAD;
			}
			if (player[i].score>=3)
			{
				player[i].win = TRUE;
			}
			if (player[i].st == DEAD)
			{
				switch (i)
				{
				case 0:
					player[i].room = 0;
					player[i].x = 1;
					break;
				case 1:
					player[i].room = 2;
					player[i].x = WINDOW_LEN - 1 - CHARA_LEN;
					break;
				default:
					break;
				}
				player[i].y = 81;
				effect(i, NORMAL);
				player[i].st = STAND;
				player[i].hp = player[i].hp_max;
			}
		}
		
	}
}
/*画面更新*/
void updatescene()
{
	int pos0;
	int pos1;
	char *p0;
	char *p1;
	char *p0_cover;
	char *p1_cover;
	int x0, y0;
	int x1, y1;
	int x0_old, y0_old;
	int x1_old, y1_old;
	
	if (player[0].getfruit)
	{
		switch (player[0].st)
		{
		case MOVE:
			if (player[0].cc)
			{
				pos0 = 1;
				player[0].cc = 0;
			}
			else
			{
				pos0 = 2;
				player[0].cc = 1;
			}
			break;
		case STAND:
			pos0 = 0;
			break;
		case JUMP:
			if (player[0].cc)
			{
				pos0 = 1;
			}
			else
			{
				pos0 = 0;
			}
			break;
		case CLIMB:
			if (player[0].cc)
			{
				pos0 = 3;
			}
			else
			{
				pos0 = 4;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (player[0].st)
		{
		case MOVE:
			if (player[0].cc)
			{
				pos0 = 1;
				player[0].cc = 0;
			}
			else
			{
				pos0 = 2;
				player[0].cc = 1;
			}
			break;
		case STAND:
			pos0 = 0;
			break;
		case JUMP:
			if (player[0].cc)
			{
				pos0 = 6;
			}
			else
			{
				pos0 = 5;
			}
			break;
		case CLIMB:
			if (player[0].cc)
			{
				pos0 = 7;
			}
			else
			{
				pos0 = 8;
			}
			break;
		default:
			break;
		}
	}
	if (player[1].getfruit)
	{
		switch (player[1].st)
		{
		case MOVE:
			if (player[1].cc)
			{
				pos1 = 1;
				player[1].cc = 0;
			}
			else
			{
				pos1 = 2;
				player[1].cc = 1;
			}
			break;
		case STAND:
			pos1 = 0;
			break;
		case JUMP:
			if (player[1].cc)
			{
				pos1 = 1;
			}
			else
			{
				pos1 = 0;
			}
			break;
		case CLIMB:
			if (player[1].cc)
			{
				pos1 = 3;
			}
			else
			{
				pos1 = 4;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (player[1].st)
		{
		case MOVE:
			if (player[1].cc)
			{
				pos1 = 1;
				player[1].cc = 0;
			}
			else
			{
				pos1 = 2;
				player[1].cc = 1;
			}
			break;
		case STAND:
			pos1 = 0;
			break;
		case JUMP:
			if (player[1].cc)
			{
				pos1 = 6;
			}
			else
			{
				pos1 = 5;
			}
			break;
		case CLIMB:
			if (player[1].cc)
			{
				pos1 = 7;
			}
			else
			{
				pos1 = 8;
			}
			break;
		default:
			break;
		}
	}

	if (player[0].getfruit)
	{
		p0 = man_orange[0][pos0];
		x0 = player[0].x - 1;
		if (x0<1)
		{
			x0 = 1;
		}
		y0 = player[0].y - 6;
		if (y0<1)
		{
			y0 = 1;
		}
	}
	else
	{
		p0 = man[0][pos0];
		x0 = player[0].x + 1;
		y0 = player[0].y + 1;
	}
	if (player[1].getfruit)
	{
		p1 = man_orange[1][pos1];
		x1 = player[1].x - 1;
		if (x1<1)
		{
			x1 = 1;
		}
		y1 = player[1].y - 6;
		if (y1<1)
		{
			y1 = 1;
		}
	}
	else
	{
		p1 = man[1][pos1];
		x1 = player[1].x + 1;
		y1 = player[1].y + 1;
	}
	if (player[0].usedtobeorange)
	{
		p0_cover = coverman_orange[0];
		x0_old = player[0].old_x-1;
		if (x0_old<1)
		{
			x0_old = 1;
		}
		y0_old = player[0].old_y-6;
		if (y0_old<1)
		{
			y0_old = 1;
		}
	}
	else
	{
		p0_cover = coverman[0];
		x0_old = player[0].old_x+1;
		y0_old = player[0].old_y+1;
	}
	if (player[1].usedtobeorange)
	{
		p1_cover = coverman_orange[1];
		x1_old = player[1].old_x-1;
		if (x1_old<1)
		{
			x1_old = 1;
		}
		y1_old = player[1].old_y-6;
		if (y1_old<1)
		{
			y1_old = 1;
		}
	}
	else
	{
		p1_cover = coverman[1];
		x1_old = player[1].old_x+1;
		y1_old = player[1].old_y+1;
	}

	if (player[0].old_room != player[0].room)
	{
		gotoxy(1, 1);
		printf("%s", pic[player[0].room]);
	}
	if (player[1].old_room != player[1].room)
	{
		gotoxy(1, 1 + DOWNSIDE_Y);
		printf("%s", pic[player[1].room]);
	}
	/*上の動物たち*/
	if (player[0].usedtofire)
	{
		if (player[0].atk.room == player[0].room)
		{
			gotoxy(player[0].atk.old_x + 1, player[0].atk.old_y + 1);
			printf("%s", cover[0]);
		}
	}
	if (player[1].usedtofire)
	{
		if (player[1].atk.room == player[0].room)
		{
			gotoxy(player[1].atk.old_x + 1, player[1].atk.old_y + 1);
			printf("%s", cover[1]);
		}
	}
	if (!player[0].rdyfire)
	{
		if (player[0].atk.room == player[0].room)
		{
			gotoxy(player[0].atk.x + 1, player[0].atk.y + 1);
			if (player[0].atk.dir)
			{
				printf("%s", pet[0][player[0].atk.anim]);
			}
			else
			{
				printf("%s", pet[2][player[0].atk.anim]);
			}
		}
	}
	if (!player[1].rdyfire)
	{
		if (player[1].atk.room == player[0].room)
		{
			gotoxy(player[1].atk.x + 1, player[1].atk.y + 1);
			if (player[1].atk.dir)
			{
				printf("%s", pet[1][player[1].atk.anim]);
			}
			else
			{
				printf("%s", pet[3][player[1].atk.anim]);
			}
		}
	}
	/*上のプレイヤー１*/
	if (player[1].room==player[0].room)
	{
		if (player[1].old_room==player[1].room)
		{
			if (player[1].old_x != player[1].x || player[1].old_y != player[1].y || player[1].old_st != player[1].st || (player[1].usedtobeorange == TRUE && player[1].getfruit == FALSE))
			{
				gotoxy(x1_old, y1_old);
				printf("%s", p1_cover);
			}
		}
		gotoxy(x1, y1);
		printf("%s", p1);
	}
	else if (player[1].old_room == player[0].room)
	{
		gotoxy(x1_old, y1_old);
		printf("%s", p1_cover);
	}
	/*上のプレイヤー0*/
	if (player[0].old_x != player[0].x || player[0].old_y != player[0].y || player[0].old_st != player[0].st || (player[0].usedtobeorange == TRUE && player[0].getfruit == FALSE))
	{
		if (player[0].old_room == player[0].room)
		{
			gotoxy(x0_old, y0_old);
			printf("%s", p0_cover);
		}
	}
	gotoxy(x0, y0);
	printf("%s", p0);

	/*下の動物たち*/
	if (player[0].usedtofire)
	{
		if (player[0].atk.room == player[1].room)
		{
			gotoxy(player[0].atk.old_x + 1, player[0].atk.old_y + 1 + DOWNSIDE_Y);
			printf("%s", cover[0]);
		}
	}
	if (player[1].usedtofire)
	{
		if (player[1].atk.room == player[1].room)
		{
			gotoxy(player[1].atk.old_x + 1, player[1].atk.old_y + 1 + DOWNSIDE_Y);
			printf("%s", cover[1]);
		}
	}
	if (!player[0].rdyfire)
	{
		if (player[0].atk.room == player[1].room)
		{
			gotoxy(player[0].atk.x + 1, player[0].atk.y + 1 + DOWNSIDE_Y);
			if (player[0].atk.dir)
			{
				printf("%s", pet[0][player[0].atk.anim]);
			}
			else
			{
				printf("%s", pet[2][player[0].atk.anim]);
			}
		}
	}
	if (!player[1].rdyfire)
	{
		if (player[1].atk.room == player[1].room)
		{
			gotoxy(player[1].atk.x + 1, player[1].atk.y + 1 + DOWNSIDE_Y);
			if (player[1].atk.dir)
			{
				printf("%s", pet[1][player[1].atk.anim]);
			}
			else
			{
				printf("%s", pet[3][player[1].atk.anim]);
			}
		}
	}
	/*下のプレイヤー0*/
	if (player[0].room == player[1].room)
	{
		if (player[0].old_room == player[0].room)
		{
			if (player[0].old_x != player[0].x || player[0].old_y != player[0].y || player[0].old_st != player[0].st || (player[0].usedtobeorange == TRUE && player[0].getfruit == FALSE))
			{
				gotoxy(x0_old, y0_old+DOWNSIDE_Y);
				printf("%s", p0_cover);
			}
		}
		gotoxy(x0, y0+DOWNSIDE_Y);
		printf("%s", p0);
	}
	else if (player[0].old_room == player[1].room)
	{
		gotoxy(x0_old, y0_old+DOWNSIDE_Y);
		printf("%s", p0_cover);
	}
	/*下のプレイヤー1*/
	if (player[1].old_x != player[1].x || player[1].old_y != player[1].y || player[1].old_st != player[1].st || (player[1].usedtobeorange == TRUE && player[1].getfruit == FALSE))
	{
		if (player[1].old_room == player[1].room)
		{
			gotoxy(x1_old, y1_old+DOWNSIDE_Y);
			printf("%s", p1_cover);
		}
	}
	gotoxy(x1, y1+DOWNSIDE_Y);
	printf("%s", p1);

	/*check usedtobeorange & update oldroom to room & check usedtofire*/
	for (int i = 0; i < 2; i++)
	{
		if (player[i].old_hp!=player[i].hp)
		{
			int x_hp;
			switch (i)
			{
			case 0:
				x_hp = 89;
				break;
			case 1:
				x_hp = 380;
				break;
			default:
				break;
			}

			switch (player[i].hp)
			{
			case 0:
				gotoxy(x_hp, 102);
				printf("%s", hp_pic[0]);
				gotoxy(x_hp+16, 102);
				printf("%s", hp_pic[0]);
				gotoxy(x_hp+32, 102);
				printf("%s", hp_pic[0]);
				break;
			case 1:
				gotoxy(x_hp, 102);
				printf("%s", hp_pic[1]);
				gotoxy(x_hp + 16, 102);
				printf("%s", hp_pic[0]);
				gotoxy(x_hp + 32, 102);
				printf("%s", hp_pic[0]);
				break;
			case 2:
				gotoxy(x_hp, 102);
				printf("%s", hp_pic[1]);
				gotoxy(x_hp + 16, 102);
				printf("%s", hp_pic[1]);
				gotoxy(x_hp + 32, 102);
				printf("%s", hp_pic[0]);
				break;
			case 3:
				gotoxy(x_hp, 102);
				printf("%s", hp_pic[1]);
				gotoxy(x_hp + 16, 102);
				printf("%s", hp_pic[1]);
				gotoxy(x_hp + 32, 102);
				printf("%s", hp_pic[1]);
				break;
			default:
				break;
			}
		}
		if (player[i].old_score!=player[i].score)
		{
			int x_score;
			switch (i)
			{
			case 0:
				x_score = 78;
				break;
			case 1:
				x_score = 369;
				break;
			default:
				break;
			}
			switch (player[i].score)
			{
			case 0:
				gotoxy(x_score, 109);
				printf("%s", score_pic[0]);
				gotoxy(x_score + 16, 109);
				printf("%s", score_pic[0]);
				gotoxy(x_score + 32, 109);
				printf("%s", score_pic[0]);
				break;
			case 1:
				gotoxy(x_score, 109);
				printf("%s", score_pic[1]);
				gotoxy(x_score + 16, 109);
				printf("%s", score_pic[0]);
				gotoxy(x_score + 32, 109);
				printf("%s", score_pic[0]);
				break;
			case 2:
				gotoxy(x_score, 109);
				printf("%s", score_pic[1]);
				gotoxy(x_score + 16, 109);
				printf("%s", score_pic[1]);
				gotoxy(x_score + 32, 109);
				printf("%s", score_pic[0]);
				break;
			case 3:
				gotoxy(x_score, 109);
				printf("%s", score_pic[1]);
				gotoxy(x_score + 16, 109);
				printf("%s", score_pic[1]);
				gotoxy(x_score + 32, 109);
				printf("%s", score_pic[1]);
				break;
			default:
				break;
			}
		}
		
		old_mten = min_ten;
		old_mone = min_one;
		old_sten = sec_ten;
		old_sone = sec_one;
		min_ten = countdown / 600;
		min_one = (countdown / 60) % 10;
		sec_ten = countdown % 60 / 10;
		sec_one = (countdown % 60) % 10;
		if (old_mten != min_ten)
		{
			gotoxy(208, 102);
			printf("%s", letter_pic[min_ten]);
		}
		if (old_mone != min_one)
		{
			gotoxy(218, 102);
			printf("%s", letter_pic[min_one]);
		}
		if (old_sten != sec_ten)
		{
			gotoxy(239, 102);
			printf("%s", letter_pic[sec_ten]);
		}
		if (old_sone != sec_one)
		{
			gotoxy(249, 102);
			printf("%s", letter_pic[sec_one]);
		}
		if (player[i].getfruit)
		{
			player[i].usedtobeorange = 1;
		}
		else
		{
			player[i].usedtobeorange = 0;
		}
		player[i].old_room = player[i].room;
		 
		if (player[i].rdyfire==FALSE)
		{
			player[i].usedtofire = TRUE;
		}
		else
		{
			player[i].usedtofire = FALSE;
		}
	}
}
/*結果を表示する画面*/
void result()
{
	for (int i = 1; i < 4; i++)
	{
		stopsound(music[i]);
	}
	playsound(music[0],1);
	if (player[0].score==player[1].score)
	{
		gotoxy(1, 27);
		printf("%s", result_pic[2]);
		gotoxy(1, 140);
		printf("%s", result_pic[2]);
	}
	else if (player[0].score>player[1].score)
	{
		gotoxy(1, 27);
		printf("%s", result_pic[0]);
		gotoxy(1, 140);
		printf("%s", result_pic[1]);
	}
	else
	{
		gotoxy(1, 27);
		printf("%s", result_pic[1]);
		gotoxy(1, 140);
		printf("%s", result_pic[0]);
	}
}
/*ゲームを続くか*/
int ending()
{
	bool cc=0;
	bool old_cc=1;

	gotoxy(132, 90);
	printf("%s", replay_pic);
	while (1)
	{
		updatesound(music[0]);
		if (old_cc!=cc)
		{
			switch (cc)
			{
			case 0:
				gotoxy(168, 120);
				printf("%s", select_pic);
				gotoxy(232, 120);
				printf("%s", select_pic_cover);
				break;
			case 1:
				gotoxy(168, 120);
				printf("%s", select_pic_cover);
				gotoxy(232, 120);
				printf("%s", select_pic);
				break;
			default:
				break;
			}
		}
		old_cc = cc;
		if (inport(PK_ENTER))
		{
			playsound(confirm_SE, 0);
			reinport();
			break;
		}
		if (inport(PK_A)|| inport(PK_D)||inport(PK_LEFT)||inport(PK_RIGHT))
		{
			cc = !cc;
			reinport();
		}
	}
	return cc;
}
/*タイトル用のデータをロードする*/
void loadtitle()
{
	FILE *fp;
	int old_num;
	int new_num;
	/*bigmapの画像のデータ格納*/
	{
		char picaddr[20] = ".\\pic\\bigbg";
		if ((fp = fopen(picaddr, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < WINDOW_ALLLINE; i++)
		{
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				fscanf(fp, "%d", &bigmap[i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	/*bigmapの画像のデータを画像データに変換*/
	old_num = -1;
	for (int i = 0; i < WINDOW_ALLLINE; i++)
	{
		for (int j = 0; j < WINDOW_LEN; j++)
		{
			new_num = bigmap[i][j];
			if (old_num == new_num)
			{
				strcat(bigpic, " ");
			}
			else
			{
				int rgb[9];
				strcat(bigpic, "\033[48;2;");
				for (int count = 0; count < 9; count++)
				{
					int ten = 1;
					for (int kk = 0; kk < count; kk++)
					{
						ten *= 10;
					}
					rgb[count] = (new_num / (100000000 / ten)) % 10;
					itoa(rgb[count], c, 10);
					strcat(bigpic, c);
					if (count == 2 || count == 5)
					{
						strcat(bigpic, ";");
					}
					else if (count == 8)
					{
						strcat(bigpic, "m");
					}
				}
				strcat(bigpic, " ");
			}
			old_num = new_num;
		}
	}
	strcat(bigpic, "\033[0m");
	/*titleのデータを読み取る*/
	{
		char picaddr2[30] = ".\\pic\\title";

		if ((fp = fopen(picaddr2, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < TITLE_LINE; i++)
		{
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				fscanf(fp, "%d", &title_data[i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	/*titleのデータを画像データに変換する*/
	old_num = -1;
	for (int i = 0; i < TITLE_LINE; i++)
	{
		strcat(title_pic, "\033[s");
		for (int j = 0; j < WINDOW_LEN; j++)
		{
			new_num = title_data[i][j];

			if (new_num != 255255255)
			{
				if (old_num == new_num)
				{
					strcat(title_pic, " ");
				}
				else
				{
					int rgb[9];
					strcat(title_pic, "\033[48;2;");
					for (int count = 0; count < 9; count++)
					{
						int ten = 1;
						for (int kk = 0; kk < count; kk++)
						{
							ten *= 10;
						}
						rgb[count] = (new_num / (100000000 / ten)) % 10;
						itoa(rgb[count], c, 10);
						strcat(title_pic, c);
						if (count == 2 || count == 5)
						{
							strcat(title_pic, ";");
						}
						else if (count == 8)
						{
							strcat(title_pic, "m");
						}
					}
					strcat(title_pic, " ");
				}
			}
			else
			{
				strcat(title_pic, "\033[1C");
			}
			old_num = new_num;
		}
		strcat(title_pic, "\033[u");
		strcat(title_pic, "\033[1B");
	}

	/*pressのデータを読み取る*/
	{
		char picaddr2[30] = ".\\pic\\pressany";

		if ((fp = fopen(picaddr2, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < PRESS_LINE; i++)
		{
			for (int j = 0; j < PRESS_LEN; j++)
			{
				fscanf(fp, "%d", &press_data[i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	/*pressのデータを画像データに変換する*/
	old_num = -1;
	for (int i = 0; i < PRESS_LINE; i++)
	{
		strcat(press_pic, "\033[s");
		for (int j = 0; j < PRESS_LEN; j++)
		{
			new_num = press_data[i][j];

			if (new_num != 255255255)
			{
				if (old_num == new_num)
				{
					strcat(press_pic, " ");
				}
				else
				{
					int rgb[9];
					strcat(press_pic, "\033[48;2;");
					for (int count = 0; count < 9; count++)
					{
						int ten = 1;
						for (int kk = 0; kk < count; kk++)
						{
							ten *= 10;
						}
						rgb[count] = (new_num / (100000000 / ten)) % 10;
						itoa(rgb[count], c, 10);
						strcat(press_pic, c);
						if (count == 2 || count == 5)
						{
							strcat(press_pic, ";");
						}
						else if (count == 8)
						{
							strcat(press_pic, "m");
						}
					}
					strcat(press_pic, " ");
				}
			}
			else
			{
				strcat(press_pic, "\033[1C");
			}
			old_num = new_num;
		}
		strcat(press_pic, "\033[u");
		strcat(press_pic, "\033[1B");
	}

	/*pressのcoverを画像データに変換する*/
	old_num = -1;
	for (int i = 0; i < PRESS_LINE; i++)
	{
		strcat(press_cover, "\033[s");
		for (int j = 0; j < PRESS_LEN; j++)
		{
			new_num = 255230153;

			if (old_num == new_num)
			{
				strcat(press_cover, " ");
			}
			else
			{
				int rgb[9];
				strcat(press_cover, "\033[48;2;");
				for (int count = 0; count < 9; count++)
				{
					int ten = 1;
					for (int kk = 0; kk < count; kk++)
					{
						ten *= 10;
					}
					rgb[count] = (new_num / (100000000 / ten)) % 10;
					itoa(rgb[count], c, 10);
					strcat(press_cover, c);
					if (count == 2 || count == 5)
					{
						strcat(press_cover, ";");
					}
					else if (count == 8)
					{
						strcat(press_cover, "m");
					}
				}
				strcat(press_cover, " ");
			}
			old_num = new_num;
		}
		strcat(press_cover, "\033[u");
		strcat(press_cover, "\033[1B");
	}

	/*dialogのデータを読み取る*/
	for (int k = 0; k < 5; k++)
	{
		char picaddr2[30] = ".\\pic\\dialog";
		itoa(k, c, 10);
		strcat(picaddr2, c);
		if ((fp = fopen(picaddr2, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < DIALOG_LINE; i++)
		{
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				fscanf(fp, "%d", &dialog_data[k][i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	/*dialogのデータを画像データに変換する*/
	for (int k = 0; k < 5; k++)
	{
		old_num = -1;
		for (int i = 0; i < DIALOG_LINE; i++)
		{
			strcat(dialog_pic[k], "\033[s");
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				new_num = dialog_data[k][i][j];

					if (old_num == new_num)
					{
						strcat(dialog_pic[k], " ");
					}
					else
					{
						int rgb[9];
						strcat(dialog_pic[k], "\033[48;2;");
						for (int count = 0; count < 9; count++)
						{
							int ten = 1;
							for (int kk = 0; kk < count; kk++)
							{
								ten *= 10;
							}
							rgb[count] = (new_num / (100000000 / ten)) % 10;
							itoa(rgb[count], c, 10);
							strcat(dialog_pic[k], c);
							if (count == 2 || count == 5)
							{
								strcat(dialog_pic[k], ";");
							}
							else if (count == 8)
							{
								strcat(dialog_pic[k], "m");
							}
						}
						strcat(dialog_pic[k], " ");
					}
				old_num = new_num;
			}
			strcat(dialog_pic[k], "\033[u");
			strcat(dialog_pic[k], "\033[1B");
		}
	}
	/*rulesのデータを読み取る*/
	for (int k = 0; k < 3; k++)
	{
		char picaddr2[30] = ".\\pic\\rules";
		itoa(k, c, 10);
		strcat(picaddr2, c);
		if ((fp = fopen(picaddr2, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < RULES_LINE; i++)
		{
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				fscanf(fp, "%d", &rules_data[k][i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	/*rulesのデータを画像データに変換する*/
	for (int k = 0; k < 3; k++)
	{
		old_num = -1;
		for (int i = 0; i < RULES_LINE; i++)
		{
			strcat(rules_pic[k], "\033[s");
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				new_num = rules_data[k][i][j];
					if (old_num == new_num)
					{
						strcat(rules_pic[k], " ");
					}
					else
					{
						int rgb[9];
						strcat(rules_pic[k], "\033[48;2;");
						for (int count = 0; count < 9; count++)
						{
							int ten = 1;
							for (int kk = 0; kk < count; kk++)
							{
								ten *= 10;
							}
							rgb[count] = (new_num / (100000000 / ten)) % 10;
							itoa(rgb[count], c, 10);
							strcat(rules_pic[k], c);
							if (count == 2 || count == 5)
							{
								strcat(rules_pic[k], ";");
							}
							else if (count == 8)
							{
								strcat(rules_pic[k], "m");
							}
						}
						strcat(rules_pic[k], " ");
					}
				old_num = new_num;
			}
			strcat(rules_pic[k], "\033[u");
			strcat(rules_pic[k], "\033[1B");
		}
	}
}
/*ゲーム用のデータをロードする*/
void loadgame()
{
	FILE *fp;
	int old_num;
	int new_num;
	
	/*三つのルームサイズの画像のデータ格納*/
	for (int k = 0; k < TOTAL_ROOM_TYPE; k++)
	{
		char picaddr[20] = ".\\pic\\bg";
		itoa(k, c, 10);
		strcat(picaddr, c);
		if ((fp = fopen(picaddr, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < WINDOW_LINE; i++)
		{
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				fscanf(fp, "%d", &map[k][i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}

	/*三つのルームサイズの画像のデータを画像データに変換*/
	for (int k = 0; k < TOTAL_ROOM_TYPE; k++)
	{
		old_num = -1;
		for (int i = 0; i < WINDOW_LINE; i++)
		{
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				new_num = map[k][i][j];
				if (old_num == new_num)
				{
					strcat(pic[k], " ");
				}
				else
				{
					int rgb[9];
					strcat(pic[k], "\033[48;2;");
					for (int count = 0; count < 9; count++)
					{
						int ten = 1;
						for (int kk = 0; kk < count; kk++)
						{
							ten *= 10;
						}
						rgb[count] = (new_num / (100000000 / ten)) % 10;
						itoa(rgb[count], c, 10);
						strcat(pic[k], c);
						if (count == 2 || count == 5)
						{
							strcat(pic[k], ";");
						}
						else if (count == 8)
						{
							strcat(pic[k], "m");
						}
					}
					strcat(pic[k], " ");
				}
				old_num = new_num;
			}
		}
		strcat(pic[k], "\033[0m");
	}
	
	/*三つのルームサイズの画像の物理データ格納*/
	for (int k = 0; k < TOTAL_ROOM_TYPE; k++)
	{
		char picaddr[20] = ".\\pic\\psc_bg";
		itoa(k, c, 10);
		strcat(picaddr, c);
		if ((fp = fopen(picaddr, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < WINDOW_LINE; i++)
		{
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				fscanf(fp, "%d", &psc_map[k][i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	/*真中のバーのデータを読み取り、画像データに変換する*/
	if ((fp = fopen(".\\pic\\midbar", "r")) == NULL)
	{
		exit(1);
	}
	for (int i = 0; i < MID_LINE; i++)
	{
		for (int j = 0; j < WINDOW_LEN; j++)
		{
			fscanf(fp, "%d", &midmap[i][j]);
		}
		fscanf(fp, "\n");
	}
	fclose(fp);
	old_num = -1;
	for (int i = 0; i < MID_LINE; i++)
	{
		for (int j = 0; j < WINDOW_LEN; j++)
		{
			new_num = midmap[i][j];
			if (old_num == new_num)
			{
				strcat(midpic, " ");
			}
			else
			{
				int rgb[9];
				strcat(midpic, "\033[48;2;");
				for (int count = 0; count < 9; count++)
				{
					int ten = 1;
					for (int kk = 0; kk < count; kk++)
					{
						ten *= 10;
					}
					rgb[count] = (midmap[i][j] / (100000000 / ten)) % 10;
					itoa(rgb[count], c, 10);
					strcat(midpic, c);
					if (count == 2 || count == 5)
					{
						strcat(midpic, ";");
					}
					else if (count == 8)
					{
						strcat(midpic, "m");
					}
				}
				strcat(midpic, " ");
			}
			old_num = new_num;
		}
	}
	strcat(midpic, "\033[0m");

	/*動物のデータ*/
	for (int k = 0; k < 2; k++)
	{
		for (int n = 0; n < PET_MOTION; n++)
		{
			char picaddr2[30] = ".\\pic\\pet";
			itoa(k, c, 10);
			strcat(picaddr2, c);
			itoa(n, c, 10);
			strcat(picaddr2, c);
			if ((fp = fopen(picaddr2, "r")) == NULL)
			{
				exit(1);
			}
			for (int i = 0; i < PET_LINE; i++)
			{
				for (int j = 0; j < PET_LEN; j++)
				{
					fscanf(fp, "%d", &pet_data[k][n][i][j]);
				}
				fscanf(fp, "\n");
			}
			fclose(fp);
		}
	}
	for (int k = 0; k < 2; k++)
	{
		for (int n = 0; n < PET_MOTION; n++)
		{
			old_num = -1;
			for (int i = 0; i < PET_LINE; i++)
			{
				strcat(pet[k][n], "\033[s");
				for (int j = 0; j < PET_LEN; j++)
				{
					new_num = pet_data[k][n][i][j];

					if (new_num != 255255255)
					{
						if (old_num == new_num)
						{
							strcat(pet[k][n], " ");
						}
						else
						{
							int rgb[9];
							strcat(pet[k][n], "\033[48;2;");
							for (int count = 0; count < 9; count++)
							{
								int ten = 1;
								for (int kk = 0; kk < count; kk++)
								{
									ten *= 10;
								}
								rgb[count] = (new_num / (100000000 / ten)) % 10;
								itoa(rgb[count], c, 10);
								strcat(pet[k][n], c);
								if (count == 2 || count == 5)
								{
									strcat(pet[k][n], ";");
								}
								else if (count == 8)
								{
									strcat(pet[k][n], "m");
								}
							}
							strcat(pet[k][n], " ");
						}
					}
					else
					{
						strcat(pet[k][n], "\033[1C");
					}
					old_num = new_num;
				}
				strcat(pet[k][n], "\033[u");
				strcat(pet[k][n], "\033[1B");
			}
		}
	}
	for (int k = 2; k < 4; k++)
	{
		for (int n = 0; n < PET_MOTION; n++)
		{
			old_num = -1;
			for (int i = 0; i < PET_LINE; i++)
			{
				strcat(pet[k][n], "\033[s");

				for (int j = 23; j > 0; j--)
				{
					new_num = pet_data[k-2][n][i][j];

					if (new_num != 255255255)
					{
						if (old_num == new_num)
						{
							strcat(pet[k][n], " ");
						}
						else
						{
							int rgb[9];
							strcat(pet[k][n], "\033[48;2;");
							for (int count = 0; count < 9; count++)
							{
								int ten = 1;
								for (int kk = 0; kk < count; kk++)
								{
									ten *= 10;
								}
								rgb[count] = (new_num / (100000000 / ten)) % 10;
								itoa(rgb[count], c, 10);
								strcat(pet[k][n], c);
								if (count == 2 || count == 5)
								{
									strcat(pet[k][n], ";");
								}
								else if (count == 8)
								{
									strcat(pet[k][n], "m");
								}
							}
							strcat(pet[k][n], " ");
						}
					}
					else
					{
						strcat(pet[k][n], "\033[1C");
					}
					old_num = new_num;
				}
				strcat(pet[k][n], "\033[u");
				strcat(pet[k][n], "\033[1B");
			}
		}
	}

	/*キャラがオレンジを背負うのデータを読み取る*/
	for (int k = 0; k < 2; k++)
	{
		for (int n = 0; n < CHARA_ORANGE_MOTION; n++)
		{
			char picaddr2[30] = ".\\pic\\chara_orange";
			itoa(k, c, 10);
			strcat(picaddr2, c);
			itoa(n, c, 10);
			strcat(picaddr2, c);
			if ((fp = fopen(picaddr2, "r")) == NULL)
			{
				exit(1);
			}
			for (int i = 0; i < CHARA_ORANGE_LINE; i++)
			{
				for (int j = 0; j < CHARA_ORANGE_LEN; j++)
				{
					fscanf(fp, "%d", &chara_orange[k][n][i][j]);
				}
				fscanf(fp, "\n");
			}
			fclose(fp);
		}
	}
	/*キャラがオレンジを背負うのデータを画像データに変換する*/
	for (int k = 0; k < 2; k++)
	{
		for (int n = 0; n < CHARA_ORANGE_MOTION; n++)
		{
			old_num = -1;
			for (int i = 0; i < CHARA_ORANGE_LINE; i++)
			{
				strcat(man_orange[k][n], "\033[s");
				for (int j = 0; j < CHARA_ORANGE_LEN; j++)
				{
					new_num = chara_orange[k][n][i][j];

					if (new_num != 255255255)
					{
						if (old_num == new_num)
						{
							strcat(man_orange[k][n], " ");
						}
						else
						{
							int rgb[9];
							strcat(man_orange[k][n], "\033[48;2;");
							for (int count = 0; count < 9; count++)
							{
								int ten = 1;
								for (int kk = 0; kk < count; kk++)
								{
									ten *= 10;
								}
								rgb[count] = (new_num / (100000000 / ten)) % 10;
								itoa(rgb[count], c, 10);
								strcat(man_orange[k][n], c);
								if (count == 2 || count == 5)
								{
									strcat(man_orange[k][n], ";");
								}
								else if (count == 8)
								{
									strcat(man_orange[k][n], "m");
								}
							}
							strcat(man_orange[k][n], " ");
						}
					}
					else
					{
						strcat(man_orange[k][n], "\033[1C");
					}
					old_num = new_num;
				}
				strcat(man_orange[k][n], "\033[u");
				strcat(man_orange[k][n], "\033[1B");
			}
		}
	}
	/*キャラのデータを読み取る*/
	for (int k = 0; k < 2; k++)
	{
		for (int n = 0; n < CHARA_MOTION; n++)
		{
			char picaddr[20] = ".\\pic\\chara";
			itoa(k, c, 10);
			strcat(picaddr, c);
			itoa(n, c, 10);
			strcat(picaddr, c);
			if ((fp = fopen(picaddr, "r")) == NULL)
			{
				exit(1);
			}
			for (int i = 0; i < CHARA_LINE; i++)
			{
				for (int j = 0; j < CHARA_LEN; j++)
				{
					fscanf(fp, "%d", &chara[k][n][i][j]);
				}
				fscanf(fp, "\n");
			}
			fclose(fp);
		}
	}
	/*キャラのデータを画像データに変換する*/
	for (int k = 0; k < 2; k++)
	{
		for (int n = 0; n < CHARA_MOTION; n++)
		{
			old_num = -1;
			for (int i = 0; i < CHARA_LINE; i++)
			{
				strcat(man[k][n], "\033[s");
				for (int j = 0; j < CHARA_LEN; j++)
				{
					new_num = chara[k][n][i][j];
					
					if (new_num!=255255255)
					{
						if (old_num == new_num)
						{
							strcat(man[k][n], " ");
						}
						else
						{
							int rgb[9];
							strcat(man[k][n], "\033[48;2;");
							for (int count = 0; count < 9; count++)
							{
								int ten = 1;
								for (int kk = 0; kk < count; kk++)
								{
									ten *= 10;
								}
								rgb[count] = (new_num / (100000000 / ten)) % 10;
								itoa(rgb[count], c, 10);
								strcat(man[k][n], c);
								if (count == 2 || count == 5)
								{
									strcat(man[k][n], ";");
								}
								else if (count == 8)
								{
									strcat(man[k][n], "m");
								}
							}
							strcat(man[k][n], " ");
						}
					}
					else
					{
						strcat(man[k][n], "\033[1C");
					}
					old_num = new_num;
				}
				strcat(man[k][n], "\033[u");
				strcat(man[k][n], "\033[1B");
			}
		}
	}

	/*スコア図のデータを読み取る*/
	for (int k = 0; k < 2; k++)
	{
		char picaddr2[30] = ".\\pic\\score";
		itoa(k, c, 10);
		strcat(picaddr2, c);
		
		if ((fp = fopen(picaddr2, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < SCORE_LINE; i++)
		{
			for (int j = 0; j < SCORE_LEN; j++)
			{
				fscanf(fp, "%d", &score_data[k][i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
		
	}
	/*スコア図のデータを画像データに変換する*/
	for (int k = 0; k < 2; k++)
	{
		old_num = -1;
		for (int i = 0; i < SCORE_LINE; i++)
		{
			strcat(score_pic[k], "\033[s");
			for (int j = 0; j < SCORE_LEN; j++)
			{
				new_num = score_data[k][i][j];

				if (new_num != 255255255)
				{
					if (old_num == new_num)
					{
						strcat(score_pic[k], " ");
					}
					else
					{
						int rgb[9];
						strcat(score_pic[k], "\033[48;2;");
						for (int count = 0; count < 9; count++)
						{
							int ten = 1;
							for (int kk = 0; kk < count; kk++)
							{
								ten *= 10;
							}
							rgb[count] = (new_num / (100000000 / ten)) % 10;
							itoa(rgb[count], c, 10);
							strcat(score_pic[k], c);
							if (count == 2 || count == 5)
							{
								strcat(score_pic[k], ";");
							}
							else if (count == 8)
							{
								strcat(score_pic[k], "m");
							}
						}
						strcat(score_pic[k], " ");
					}
				}
				else
				{
					strcat(score_pic[k], "\033[1C");
				}
				old_num = new_num;
			}
			strcat(score_pic[k], "\033[u");
			strcat(score_pic[k], "\033[1B");
		}
	}

	/*HP図のデータを読み取る*/
	for (int k = 0; k < 2; k++)
	{
		char picaddr2[30] = ".\\pic\\heart";
		itoa(k, c, 10);
		strcat(picaddr2, c);

		if ((fp = fopen(picaddr2, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < HP_LINE; i++)
		{
			for (int j = 0; j < HP_LEN; j++)
			{
				fscanf(fp, "%d", &hp_data[k][i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);

	}
	/*HP図のデータを画像データに変換する*/
	for (int k = 0; k < 2; k++)
	{
		old_num = -1;
		for (int i = 0; i < HP_LINE; i++)
		{
			strcat(hp_pic[k], "\033[s");
			for (int j = 0; j < HP_LEN; j++)
			{
				new_num = hp_data[k][i][j];

				if (new_num != 255255255)
				{
					if (old_num == new_num)
					{
						strcat(hp_pic[k], " ");
					}
					else
					{
						int rgb[9];
						strcat(hp_pic[k], "\033[48;2;");
						for (int count = 0; count < 9; count++)
						{
							int ten = 1;
							for (int kk = 0; kk < count; kk++)
							{
								ten *= 10;
							}
							rgb[count] = (new_num / (100000000 / ten)) % 10;
							itoa(rgb[count], c, 10);
							strcat(hp_pic[k], c);
							if (count == 2 || count == 5)
							{
								strcat(hp_pic[k], ";");
							}
							else if (count == 8)
							{
								strcat(hp_pic[k], "m");
							}
						}
						strcat(hp_pic[k], " ");
					}
				}
				else
				{
					strcat(hp_pic[k], "\033[1C");
				}
				old_num = new_num;
			}
			strcat(hp_pic[k], "\033[u");
			strcat(hp_pic[k], "\033[1B");
		}
	}

	/*LETTER図のデータを読み取る*/
	for (int k = 0; k < 10; k++)
	{
		char picaddr2[30] = ".\\pic\\letter";
		itoa(k, c, 10);
		strcat(picaddr2, c);

		if ((fp = fopen(picaddr2, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < LETTER_LINE; i++)
		{
			for (int j = 0; j < LETTER_LEN; j++)
			{
				fscanf(fp, "%d", &letter_data[k][i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);

	}
	/*LETTER図のデータを画像データに変換する*/
	for (int k = 0; k < 10; k++)
	{
		old_num = -1;
		for (int i = 0; i < LETTER_LINE; i++)
		{
			strcat(letter_pic[k], "\033[s");
			for (int j = 0; j < LETTER_LEN; j++)
			{
				new_num = letter_data[k][i][j];

				if (new_num != 255255255)
				{
					if (old_num == new_num)
					{
						strcat(letter_pic[k], " ");
					}
					else
					{
						int rgb[9];
						strcat(letter_pic[k], "\033[48;2;");
						for (int count = 0; count < 9; count++)
						{
							int ten = 1;
							for (int kk = 0; kk < count; kk++)
							{
								ten *= 10;
							}
							rgb[count] = (new_num / (100000000 / ten)) % 10;
							itoa(rgb[count], c, 10);
							strcat(letter_pic[k], c);
							if (count == 2 || count == 5)
							{
								strcat(letter_pic[k], ";");
							}
							else if (count == 8)
							{
								strcat(letter_pic[k], "m");
							}
						}
						strcat(letter_pic[k], " ");
					}
				}
				else
				{
					strcat(letter_pic[k], "\033[1C");
				}
				old_num = new_num;
			}
			strcat(letter_pic[k], "\033[u");
			strcat(letter_pic[k], "\033[1B");
		}
	}

	/*MES図のデータを読み取る*/
	for (int k = 0; k < 3; k++)
	{
		char picaddr2[30] = ".\\pic\\message";
		itoa(k, c, 10);
		strcat(picaddr2, c);

		if ((fp = fopen(picaddr2, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < MES_LINE; i++)
		{
			for (int j = 0; j < MES_LEN; j++)
			{
				fscanf(fp, "%d", &mes_data[k][i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);

	}
	/*MES図のデータを画像データに変換する*/
	for (int k = 0; k < 3; k++)
	{
		old_num = -1;
		for (int i = 0; i < MES_LINE; i++)
		{
			strcat(mes_pic[k], "\033[s");
			for (int j = 0; j < MES_LEN; j++)
			{
				new_num = mes_data[k][i][j];

				if (new_num != 255255255)
				{
					if (old_num == new_num)
					{
						strcat(mes_pic[k], " ");
					}
					else
					{
						int rgb[9];
						strcat(mes_pic[k], "\033[48;2;");
						for (int count = 0; count < 9; count++)
						{
							int ten = 1;
							for (int kk = 0; kk < count; kk++)
							{
								ten *= 10;
							}
							rgb[count] = (new_num / (100000000 / ten)) % 10;
							itoa(rgb[count], c, 10);
							strcat(mes_pic[k], c);
							if (count == 2 || count == 5)
							{
								strcat(mes_pic[k], ";");
							}
							else if (count == 8)
							{
								strcat(mes_pic[k], "m");
							}
						}
						strcat(mes_pic[k], " ");
					}
				}
				else
				{
					strcat(mes_pic[k], "\033[1C");
				}
				old_num = new_num;
			}
			strcat(mes_pic[k], "\033[u");
			strcat(mes_pic[k], "\033[1B");
		}
	}

	/*resultのデータを読み取る*/
	for (int k = 0; k < 3; k++)
	{
		char picaddr2[30] = ".\\pic\\result";
		itoa(k, c, 10);
		strcat(picaddr2, c);
		if ((fp = fopen(picaddr2, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < RESULT_LINE; i++)
		{
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				fscanf(fp, "%d", &result_data[k][i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	/*resultのデータを画像データに変換する*/
	for (int k = 0; k < 3; k++)
	{
		old_num = -1;
		for (int i = 0; i < RESULT_LINE; i++)
		{
			strcat(result_pic[k], "\033[s");
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				new_num = result_data[k][i][j];
				if (old_num == new_num)
				{
					strcat(result_pic[k], " ");
				}
				else
				{
					int rgb[9];
					strcat(result_pic[k], "\033[48;2;");
					for (int count = 0; count < 9; count++)
					{
						int ten = 1;
						for (int kk = 0; kk < count; kk++)
						{
							ten *= 10;
						}
						rgb[count] = (new_num / (100000000 / ten)) % 10;
						itoa(rgb[count], c, 10);
						strcat(result_pic[k], c);
						if (count == 2 || count == 5)
						{
							strcat(result_pic[k], ";");
						}
						else if (count == 8)
						{
							strcat(result_pic[k], "m");
						}
					}
					strcat(result_pic[k], " ");
				}
				old_num = new_num;
			}
			strcat(result_pic[k], "\033[u");
			strcat(result_pic[k], "\033[1B");
		}
	}

	/*replayの画像のデータ格納*/
	{
		char picaddr[20] = ".\\pic\\replay";
		if ((fp = fopen(picaddr, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < REPLAY_LINE; i++)
		{
			for (int j = 0; j < REPLAY_LEN; j++)
			{
				fscanf(fp, "%d", &replay_data[i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	/*replayの画像のデータを画像データに変換*/
	old_num = -1;
	for (int i = 0; i < REPLAY_LINE; i++)
	{
		strcat(replay_pic, "\033[s");
		for (int j = 0; j < REPLAY_LEN; j++)
		{
			new_num = replay_data[i][j];
			if (old_num == new_num)
			{
				strcat(replay_pic, " ");
			}
			else
			{
				int rgb[9];
				strcat(replay_pic, "\033[48;2;");
				for (int count = 0; count < 9; count++)
				{
					int ten = 1;
					for (int kk = 0; kk < count; kk++)
					{
						ten *= 10;
					}
					rgb[count] = (new_num / (100000000 / ten)) % 10;
					itoa(rgb[count], c, 10);
					strcat(replay_pic, c);
					if (count == 2 || count == 5)
					{
						strcat(replay_pic, ";");
					}
					else if (count == 8)
					{
						strcat(replay_pic, "m");
					}
				}
				strcat(replay_pic, " ");
			}
			old_num = new_num;
		}
		strcat(replay_pic, "\033[u");
		strcat(replay_pic, "\033[1B");
	}
	strcat(replay_pic, "\033[0m");

	/*selectを画像データに変換*/
	old_num = -1;
	for (int i = 0; i < 2; i++)
	{
		strcat(select_pic, "\033[s");
		for (int j = 0; j < 60; j++)
		{
			new_num = 235110025;
			if (old_num == new_num)
			{
				strcat(select_pic, " ");
			}
			else
			{
				int rgb[9];
				strcat(select_pic, "\033[48;2;");
				for (int count = 0; count < 9; count++)
				{
					int ten = 1;
					for (int kk = 0; kk < count; kk++)
					{
						ten *= 10;
					}
					rgb[count] = (new_num / (100000000 / ten)) % 10;
					itoa(rgb[count], c, 10);
					strcat(select_pic, c);
					if (count == 2 || count == 5)
					{
						strcat(select_pic, ";");
					}
					else if (count == 8)
					{
						strcat(select_pic, "m");
					}
				}
				strcat(select_pic, " ");
			}
			old_num = new_num;
		}
		strcat(select_pic, "\033[u");
		strcat(select_pic, "\033[1B");
	}
	strcat(select_pic, "\033[0m");

	/*select_coverを画像データに変換*/
	old_num = -1;
	for (int i = 0; i < 2; i++)
	{
		strcat(select_pic_cover, "\033[s");
		for (int j = 0; j < 60; j++)
		{
			new_num = 89089089;
			if (old_num == new_num)
			{
				strcat(select_pic_cover, " ");
			}
			else
			{
				int rgb[9];
				strcat(select_pic_cover, "\033[48;2;");
				for (int count = 0; count < 9; count++)
				{
					int ten = 1;
					for (int kk = 0; kk < count; kk++)
					{
						ten *= 10;
					}
					rgb[count] = (new_num / (100000000 / ten)) % 10;
					itoa(rgb[count], c, 10);
					strcat(select_pic_cover, c);
					if (count == 2 || count == 5)
					{
						strcat(select_pic_cover, ";");
					}
					else if (count == 8)
					{
						strcat(select_pic_cover, "m");
					}
				}
				strcat(select_pic_cover, " ");
			}
			old_num = new_num;
		}
		strcat(select_pic_cover, "\033[u");
		strcat(select_pic_cover, "\033[1B");
	}
	strcat(select_pic_cover, "\033[0m");
}
/*ゲーム用のMUSICをロードする*/
void loadmusic()
{
	char bg_s[] = ".\\music\\bgm.wav";
	char cat_0[] = ".\\music\\mew.wav";
	char dog_0[] = ".\\music\\wang.wav";
	char confirm_s[] = ".\\music\\confirm.wav";
	char jump_s[] = ".\\music\\jump.mp3";
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
		{
			char music_s[] = ".\\music\\music0.mp3";
			music[i] = opensound(music_s);
		}
			break;
		case 1:
		{
			char music_s[] = ".\\music\\music1.mp3";
			music[i] = opensound(music_s);
		}
			break;
		case 2:
		{
			char music_s[] = ".\\music\\music2.mp3";
			music[i] = opensound(music_s);
		}
			break;
		case 3:
		{
			char music_s[] = ".\\music\\music3.mp3";
			music[i] = opensound(music_s);
		}
			break;
		default:
			break;
		}
	}
	bgm0 = opensound(bg_s);
	cat_SE0 = opensound(cat_0);
	dog_SE0 = opensound(dog_0);
	confirm_SE = opensound(confirm_s);
	jump_SE = opensound(jump_s);
}

/*キャラのスビート変換、Also can be used as skill effect system*/
void effect(int id, int type)
{
	switch (type)
	{
	case 0:
		player[id].spd = 3.7f;
		player[id].dx_limit = 6.0f;
		player[id].jumpforce = 4.8f;
		player[id].getfruit = FALSE;
		break;
	case 1:
		player[id].spd = 3.7f;
		player[id].dx_limit = 6.0f;
		player[id].jumpforce = 2.8f;
		player[id].getfruit = TRUE;
		break;
	default:
		break;
	}
}

/*文字サイズ変更*/
void setFontSize(int nX, int nY)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hConsole, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = nX;
	lpConsoleCurrentFontEx->dwFontSize.Y = nY;
	SetCurrentConsoleFontEx(hConsole, 0, lpConsoleCurrentFontEx);
}