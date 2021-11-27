#define _CRT_SECURE_NO_WARNINGS
#define WINDOW_LEN 400
#define WINDOW_LINE 200
#define SCORE_LEN 8
#define SCORE_LINE 5
#define LETTER_LEN 6
#define LETTER_LINE 7
#define PRESS_LEN 92
#define PRESS_LINE 7
#define STONE_WIDTH 40
#define STONE_HEIGHT 20

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
	int anim;
	float force;
}Stone_Data;

typedef struct
{
	int score_x;
	int score_y;
	int score;
	int old_score;

	int stone_start_pos_x;
	int stone_start_pos_y;

	bool cc;
	int controltype;
	bool readyToFire;

	Stone_Data atk;
}Character_Data;
Character_Data player[4] = { 0 };

int backgroundImg[WINDOW_LINE][WINDOW_LEN] = { 0 };
int letter_data[10][LETTER_LINE][LETTER_LEN] = { 0 };
int score_data[SCORE_LINE][SCORE_LEN] = { 0 };
int press_data[PRESS_LINE][PRESS_LEN] = { 0 };
int stone_data[STONE_HEIGHT][STONE_WIDTH] = { 0 };

char backgroundImg_pic[WINDOW_LINE * WINDOW_LEN * 22] = { 0 };
char letter_pic[10][LETTER_LINE * LETTER_LEN * 22] = { 0 };
char score_pic[SCORE_LINE * SCORE_LEN * 22] = { 0 };			// Don't need cover
char press_pic[PRESS_LINE * PRESS_LEN * 22] = { 0 };
char press_cover[PRESS_LINE * PRESS_LEN * 22] = { 0 };
char stone_pic[STONE_HEIGHT * STONE_WIDTH * 22] = { 0 };
char stone_cover[STONE_HEIGHT * STONE_WIDTH * 22] = { 0 };
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
void Title();
void Rules();
void SetDefaultData();
int Game();
int Ending();
void SetDefaultScene();
void UpdateLogic();
void UpdateScreen();
void Result();
void SetFontSize(int nX, int nY);
void LoadTitle();
void LoadGame();
void LoadMusic();

int bgm0;
int cat_SE0;
int dog_SE0;
int confirm_SE;
int jump_SE;
int music[4] = { 0 };

int main(void)
{
	SetFontSize(2, 4);
	system("mode con cols=400 lines=200");							//プログラムの画面サイズを設定
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	char titlename[] = "カーリング";									//プログラムの名前
	setcaption(titlename);
	setcursortype(NOCURSOR);
	GetConsoleMode(hIn, &mode);
	mode = mode & ~ENABLE_QUICK_EDIT_MODE;
	mode = mode & ~ENABLE_INSERT_MODE;
	SetConsoleMode(hIn, mode);
	LoadTitle();
	LoadMusic();
	setvolume(bgm0, 100);
	int cc;
	while (1)
	{
		srand((int)time(NULL));
		Title();
		Rules();
		LoadGame();
		while (1)
		{
			cc = Game();
			if (cc)
			{
				break;
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
void Title()
{
	gotoxy(1, 1);
	printf("%s", backgroundImg_pic);

	gotoxy(151, 164);
	printf("%s", press_pic);

	playsound(bgm0, 1);
	playsound(music[0], 1);
	time_st = clock();
	while (1)
	{
		time_ed = clock();
		updatesound(bgm0);
		updatesound(music[0]);
		if (time_ed - time_st > 500)
		{
			time_st = clock();
		}
		if (getch())
		{
			reinport();
			break;
		}
	}
	int count = 0;
	bool cc = TRUE;
	playsound(confirm_SE, 0);
	time_st = clock();
	while (1)
	{
		time_ed = clock();
		updatesound(bgm0);
		if (time_ed - time_st > 100)
		{
			if (cc)
			{
				gotoxy(151, 164);
				printf("%s", press_pic);
				cc = FALSE;
			}
			else
			{
				gotoxy(151, 164);
				printf("%s", press_cover);
				count++;
				cc = TRUE;
			}
			time_st = clock();
		}
		if (count > 7)
		{
			break;
		}
	}
	clrscr();
}
/*ルール説明画面*/
void Rules()
{}
/*ゲームデータを設定する*/
void SetDefaultData()
{
	stopsound(music[0]);
	min_ten = -1, min_one = -1, sec_ten = -1, sec_one = -1;
	player[0].score_x = 3;
	player[0].score_y = 2;
	player[1].score_x = 377;
	player[1].score_y = 2;
	player[2].score_x = 3;
	player[2].score_y = 193;
	player[3].score_x = 377;
	player[3].score_y = 193;

	player[0].stone_start_pos_x = 3;
	player[0].stone_start_pos_y = 3;

	for (int i = 0; i < 4; i++)
	{
		player[i].score = 0;
		player[i].old_score = -1;
	}

	player[0].controltype = KEYBOARD;
	player[1].controltype = JOYSTICK;
}
/*ゲーム本体*/
int Game()
{
	SetDefaultData();
	int count_ed;
	countdown = ct_max;
	if (countdown == 546)
	{
		playsound(music[1], 0);
	}
	SetDefaultScene();
	time_st = clock();
	count_st = time(NULL);
	while (1)
	{
		updatesound(bgm0);
		time_ed = clock();
		count_ed = time(NULL);
		if (time_ed - time_st > 30)
		{
			UpdateLogic();
			UpdateScreen();
			time_st = clock();
		}
		old_ct = countdown;
		countdown = ct_max - (count_ed - count_st);

		if (countdown == 288)
		{
			playsound(music[2], 0);
		}
		if (countdown == 107)
		{
			playsound(music[3], 0);
		}
		if (countdown < 0)
		{
			break;
		}
	}
	Result();
	return Ending();
}
/*初期画面*/
void SetDefaultScene()
{
	gotoxy(17, 4);
	printf("%s", score_pic);

	gotoxy(391, 4);
	printf("%s", score_pic);

	gotoxy(17, 195);
	printf("%s", score_pic);

	gotoxy(391, 195);
	printf("%s", score_pic);

	int ten = 0;
	int one = 0;

	for (int i = 0; i < 4; i++)
	{
		if (player[i].old_score != player[i].score)
		{
			ten = player[i].score / 10;
			one = player[i].score % 10;
			gotoxy(player[i].score_x, player[i].score_y);
			printf("%s", letter_pic[ten]);
			gotoxy(player[i].score_x + LETTER_LEN + 1, player[i].score_y);
			printf("%s", letter_pic[one]);

			player[i].old_score = player[i].score;
		}


	}
}
/*データ更新*/
void UpdateLogic()
{
	int oldnum;
	int newnum;
	int ky;
	int kx;
	int count;

}
/*画面更新*/
void UpdateScreen()
{
	int pos0;
	int pos1;
	char* p0;
	char* p1;
	char* p0_cover;
	char* p1_cover;
	int x0, y0;
	int x1, y1;
	int x0_old, y0_old;
	int x1_old, y1_old;


	int ten = 0;
	int one = 0;

	for (int i = 0; i < 4; i++)
	{
		if (player[i].old_score != player[i].score)
		{
			ten = player[i].score / 10;
			one = player[i].score % 10;
			gotoxy(player[i].score_x, player[i].score_y);
			printf("%s", letter_pic[ten]);
			gotoxy(player[i].score_x + LETTER_LEN + 1, player[i].score_y);
			printf("%s", letter_pic[one]);

			player[i].old_score = player[i].score;
		}
	}
}
/*結果を表示する画面*/
void Result()
{

}
/*ゲームを続くか*/
int Ending()
{
	bool cc = 0;
	bool old_cc = 1;


	while (1)
	{
		updatesound(music[0]);
		if (old_cc != cc)
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
		if (inport(PK_A) || inport(PK_D) || inport(PK_LEFT) || inport(PK_RIGHT))
		{
			cc = !cc;
			reinport();
		}
	}
	return cc;
}
/*タイトル用のデータをロードする*/
void LoadTitle()
{
	FILE* fp;
	int old_num;
	int new_num;
	/*BackgroundIMGの画像のデータ格納*/
	{
		char picaddr[20] = ".\\pic\\EL\\Title";
		if ((fp = fopen(picaddr, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < WINDOW_LINE; i++)
		{
			for (int j = 0; j < WINDOW_LEN; j++)
			{
				fscanf(fp, "%d", &backgroundImg[i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	/*BackgroundIMGの画像のデータを画像データに変換*/
	old_num = -1;
	for (int i = 0; i < WINDOW_LINE; i++)
	{
		for (int j = 0; j < WINDOW_LEN; j++)
		{
			new_num = backgroundImg[i][j];
			if (old_num == new_num)
			{
				strcat(backgroundImg_pic, " ");
			}
			else
			{
				int rgb[9];
				strcat(backgroundImg_pic, "\033[48;2;");
				for (int count = 0; count < 9; count++)
				{
					int ten = 1;
					for (int kk = 0; kk < count; kk++)
					{
						ten *= 10;
					}
					rgb[count] = (new_num / (100000000 / ten)) % 10;
					itoa(rgb[count], c, 10);
					strcat(backgroundImg_pic, c);
					if (count == 2 || count == 5)
					{
						strcat(backgroundImg_pic, ";");
					}
					else if (count == 8)
					{
						strcat(backgroundImg_pic, "m");
					}
				}
				strcat(backgroundImg_pic, " ");
			}
			old_num = new_num;
		}
	}
	strcat(backgroundImg_pic, "\033[0m");


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
			new_num = 255255255;

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


}
/*ゲーム用のデータをロードする*/
void LoadGame()
{
	FILE* fp;
	int old_num;
	int new_num;

	/*スコア図のデータを読み取る*/

	char picaddr2[30] = ".\\pic\\EL\\Pt";

	if ((fp = fopen(picaddr2, "r")) == NULL)
	{
		exit(1);
	}
	for (int i = 0; i < SCORE_LINE; i++)
	{
		for (int j = 0; j < SCORE_LEN; j++)
		{
			fscanf(fp, "%d", &score_data[i][j]);
		}
		fscanf(fp, "\n");
	}
	fclose(fp);


	/*スコア図のデータを画像データに変換する*/

	old_num = -1;
	for (int i = 0; i < SCORE_LINE; i++)
	{
		strcat(score_pic, "\033[s");
		for (int j = 0; j < SCORE_LEN; j++)
		{
			new_num = score_data[i][j];

			if (new_num != 255255255)
			{
				if (old_num == new_num)
				{
					strcat(score_pic, " ");
				}
				else
				{
					int rgb[9];
					strcat(score_pic, "\033[48;2;");
					for (int count = 0; count < 9; count++)
					{
						int ten = 1;
						for (int kk = 0; kk < count; kk++)
						{
							ten *= 10;
						}
						rgb[count] = (new_num / (100000000 / ten)) % 10;
						itoa(rgb[count], c, 10);
						strcat(score_pic, c);
						if (count == 2 || count == 5)
						{
							strcat(score_pic, ";");
						}
						else if (count == 8)
						{
							strcat(score_pic, "m");
						}
					}
					strcat(score_pic, " ");
				}
			}
			else
			{
				strcat(score_pic, "\033[1C");
			}
			old_num = new_num;
		}
		strcat(score_pic, "\033[u");
		strcat(score_pic, "\033[1B");
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

	/*stoneのデータを読み取る*/
	{
		char picaddr2[30] = ".\\pic\\EL\\Stone";

		if ((fp = fopen(picaddr2, "r")) == NULL)
		{
			exit(1);
		}
		for (int i = 0; i < STONE_HEIGHT; i++)
		{
			for (int j = 0; j < STONE_WIDTH; j++)
			{
				fscanf(fp, "%d", &stone_data[i][j]);
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	/*stoneのデータを画像データに変換する*/
	old_num = -1;
	for (int i = 0; i < STONE_HEIGHT; i++)
	{
		strcat(press_pic, "\033[s");
		for (int j = 0; j < STONE_WIDTH; j++)
		{
			new_num = stone_data[i][j];

			if (new_num != 255255255)
			{
				if (old_num == new_num)
				{
					strcat(stone_pic, " ");
				}
				else
				{
					int rgb[9];
					strcat(stone_pic, "\033[48;2;");
					for (int count = 0; count < 9; count++)
					{
						int ten = 1;
						for (int kk = 0; kk < count; kk++)
						{
							ten *= 10;
						}
						rgb[count] = (new_num / (100000000 / ten)) % 10;
						itoa(rgb[count], c, 10);
						strcat(stone_pic, c);
						if (count == 2 || count == 5)
						{
							strcat(stone_pic, ";");
						}
						else if (count == 8)
						{
							strcat(stone_pic, "m");
						}
					}
					strcat(stone_pic, " ");
				}
			}
			else
			{
				strcat(stone_pic, "\033[1C");
			}
			old_num = new_num;
		}
		strcat(stone_pic, "\033[u");
		strcat(stone_pic, "\033[1B");
	}

	/*stoneのcoverを画像データに変換する*/
	old_num = -1;
	for (int i = 0; i < STONE_HEIGHT; i++)
	{
		strcat(stone_cover, "\033[s");
		for (int j = 0; j < STONE_WIDTH; j++)
		{
			new_num = 255255255;

			if (old_num == new_num)
			{
				strcat(stone_cover, " ");
			}
			else
			{
				int rgb[9];
				strcat(stone_cover, "\033[48;2;");
				for (int count = 0; count < 9; count++)
				{
					int ten = 1;
					for (int kk = 0; kk < count; kk++)
					{
						ten *= 10;
					}
					rgb[count] = (new_num / (100000000 / ten)) % 10;
					itoa(rgb[count], c, 10);
					strcat(stone_cover, c);
					if (count == 2 || count == 5)
					{
						strcat(stone_cover, ";");
					}
					else if (count == 8)
					{
						strcat(stone_cover, "m");
					}
				}
				strcat(stone_cover, " ");
			}
			old_num = new_num;
		}
		strcat(stone_cover, "\033[u");
		strcat(stone_cover, "\033[1B");
	}


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
void LoadMusic()
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


/*文字サイズ変更*/
void SetFontSize(int nX, int nY)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hConsole, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = nX;
	lpConsoleCurrentFontEx->dwFontSize.Y = nY;
	SetCurrentConsoleFontEx(hConsole, 0, lpConsoleCurrentFontEx);
}