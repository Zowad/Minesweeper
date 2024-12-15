# include "iGraphics.h"
#include<iostream>
#include<windows.h>
#include<time.h>
//#include<unistd.h>
#include<math.h>
#include<string.h>

int x = 300, y = 300, r = 20;
int showmenu = 0;
int gbc = 0, music_on = 1, temp_music_on = 1, board_size = 1, bomb_num = 10, flag_count = 10, difficulty = 2, gamestate = 0, cont_mode = 1, temp_cont_mode = 1;
int menu_select = 0, temp_menu_select = 0, temp_board_size = 1, temp_difficulty = 2;
int click_count = 0, game_over = 0, uncover_cell_count = 0;
char diff_str[10], board_size_str[10], bomb_count_text[20], flag_count_text[20];
int ei_x = 288, ei_y = 55, e_x = 64, e_y = 64, g_x, g_y, g_r = 8, g_c = 10 ; // 8 10
int htp_ind = 0;
int timer_sec = 0, h,m,s;
char htp_page[4][30]={"image\\4_Mines_howtoplay_1.bmp","image\\4_Mines_howtoplay_2.bmp","image\\4_Mines_howtoplay_3.bmp","image\\4_Mines_howtoplay_4.bmp"};

struct cell
{
	int count;
	int stat;
};

cell grid_e[50][50];

struct timer
{
	int hour;
	int min;
	int sec;
};

timer  highscore = {0,1,21}, highscore_medium = {0,5,9}, highscore_large = {0,7,42};

int total_sec(int hr, int mn, int sc)
{
	return 3600*hr + 60*mn + sc;
}

void make_grid(int r_i, int c_i)
{
	int f = 1;
	if(c_i<0) 
	{
		c_i *= -1;
		f = 0;
	}
	int i,j,r,c=0;
	//int bomb = 15;
	//srand(time(NULL));
    r = rand() % 20;
	for(i=0;i<g_r;i++)
	for(j=0;j<g_c;j++) grid_e[i][j].count = 0;
	// placing bombs
	for(c = 0; c<bomb_num;)
	{
		i = rand() % g_r;
		j = rand() % g_c;
		if(grid_e[i][j].count == 0)
		if(abs(r_i - i) > 1 || abs(c_i - j) > 1) // ensuring the 1st move is safe
		{
			grid_e[i][j].count = -1;
			c++;
		} 
	}
	c = 0;
	int c2 = 0;
	for(i=0;i<g_r;i++) // numbering cells (count)
	for(j=0;j<g_c;j++)
	{
		if(grid_e[i][j].count == -1)continue;
		int x,y;
		for(x = i - 1; x <= i+1; x++)
		for(y = j - 1; y <= j+1; y++)
		{
			if(grid_e[x][y].count == -1) 
			if(0 <= x && x < g_r && 0 <= y && y < g_c) grid_e[i][j].count++;
		}
	}
	for(i=0;i<g_r;i++) // covering cells
	for(j=0;j<g_c;j++) 
	{
		if(f == 1) grid_e[i][j].stat = 1; 
		else if(grid_e[i][j].stat != 2) grid_e[i][j].stat = 1; 
	}
	
	
}
void print_grid(int b) // 1 for regular. 0 for uncovered
{
	int i,j,c=0;
	for(i=0;i<g_r;i++) // print grid
	{
		for(j=0;j<g_c;j++)
		{
			if(b == 1)
			{
				if(grid_e[i][j].stat == 1) printf("-  ");
				else if(grid_e[i][j].stat == 2) printf("F  ");
				else 
				{
					printf("%2d ",grid_e[i][j].count);
					if(grid_e[i][j].count == -1) c++;
				}
			}
			else
			{
				printf("%2d  ",grid_e[i][j].count);
				if(grid_e[i][j].count == -1) c++;
			}
			
		}
		printf("\n");
	}
	printf("Bomb count: %d\n",c);
}
void show_grid()
{
	int i,j,x,y;
	for(i=g_r-1;i>=0;i--)
	{
		
	}
	for(i=g_r-1;i>=0;i--)
	for(j=0; j<g_c; j++)
		{
			if(board_size == 1) //small
			{
				if(grid_e[i][j].stat == 1) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_blank_3.bmp");
				if(grid_e[i][j].stat == 2) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_flag_1.bmp");
				if(grid_e[i][j].stat == 0)
				{
					if(grid_e[i][j].count == -1) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_bomb_1.bmp");
					else if(grid_e[i][j].count == 0) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_blank_5.bmp");
					else if(grid_e[i][j].count == 1) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_num_1.bmp");
					else if(grid_e[i][j].count == 2) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_num_2.bmp");
					else if(grid_e[i][j].count == 3) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_num_3.bmp");
					else if(grid_e[i][j].count == 4) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_num_4.bmp");
					else if(grid_e[i][j].count == 5) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_num_5.bmp");
					else if(grid_e[i][j].count == 6) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_num_6.bmp");
					else if(grid_e[i][j].count == 7) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_num_7.bmp");
					else if(grid_e[i][j].count == 8) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\easy\\tile_num_8.bmp");
					
				}
			}
			if(board_size == 2) // medium
			{
				//iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_blank_3.bmp");
				if(grid_e[i][j].stat == 1) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_blank_3.bmp");
				if(grid_e[i][j].stat == 2) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_flag_1.bmp");
				if(grid_e[i][j].stat == 0)
				{
					if(grid_e[i][j].count == -1) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_bomb_1.bmp");
					else if(grid_e[i][j].count == 0) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_blank_5.bmp");
					else if(grid_e[i][j].count == 1) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_num_1.bmp");
					else if(grid_e[i][j].count == 2) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_num_2.bmp");
					else if(grid_e[i][j].count == 3) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_num_3.bmp");
					else if(grid_e[i][j].count == 4) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_num_4.bmp");
					else if(grid_e[i][j].count == 5) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_num_5.bmp");
					else if(grid_e[i][j].count == 6) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_num_6.bmp");
					else if(grid_e[i][j].count == 7) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_num_7.bmp");
					else if(grid_e[i][j].count == 8) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\medium\\tile_num_8.bmp");
					
				}
			}
			if(board_size == 3) // hard
			{
				//iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_blank_3.bmp");
				if(grid_e[i][j].stat == 1) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_blank_3.bmp");
				if(grid_e[i][j].stat == 2) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_flag_1.bmp");
				if(grid_e[i][j].stat == 0)
				{
					if(grid_e[i][j].count == -1) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_bomb_1.bmp");
					else if(grid_e[i][j].count == 0) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_blank_5.bmp");
					else if(grid_e[i][j].count == 1) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_num_1.bmp");
					else if(grid_e[i][j].count == 2) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_num_2.bmp");
					else if(grid_e[i][j].count == 3) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_num_3.bmp");
					else if(grid_e[i][j].count == 4) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_num_4.bmp");
					else if(grid_e[i][j].count == 5) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_num_5.bmp");
					else if(grid_e[i][j].count == 6) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_num_6.bmp");
					else if(grid_e[i][j].count == 7) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_num_7.bmp");
					else if(grid_e[i][j].count == 8) iShowBMP(ei_x+j*e_x, ei_y+(g_r-1-i)*e_y, "image\\large\\tile_num_8.bmp");
					
				}
			}
			
		}
}
void cell_uncover(int r, int c)
{
	grid_e[r][c].stat = 0;
	if(grid_e[r][c].count == 0)
	{
		int x,y;
		for(y = r-1; y<= r+1; y++)
		for(x = c-1; x<= c+1; x++)
			if(0 <= y && y < g_r && 0 <= x && x < g_c && grid_e[y][x].stat == 1)  cell_uncover(y,x);
	}
}
void show_timer()
{
	
	char timer_str[10];
	s = timer_sec%60;
	m = (timer_sec/60);
	h = (timer_sec/3600);
	sprintf(timer_str,"%d:%02d:%02d",h,m,s);
	iText(584,646,timer_str,GLUT_BITMAP_TIMES_ROMAN_24);
}
void update_timer()
{
	timer_sec++;
}

/*
	function iDraw() is called again and again by the system.

	*/

void iDraw() 
{
	//place your drawing codes here
	iClear();
	if(showmenu == 0) iShowBMP(0,0,"image\\Mines_homepage.bmp"); // homepage;

	if(showmenu == 1) // settings
	{
		iShowBMP(0,0,"image\\Mines_Settings.bmp"); 
		if(temp_music_on) iShowBMP2(576,425,"image\\musicon.bmp", 255);
		else iShowBMP2(576,425,"image\\music.bmp", 255);
		iSetColor(23, 92, 52);
		if(temp_cont_mode == 1) iRectangle(439,248,54,78);
		if(temp_cont_mode == 2) iRectangle(533,247,116,78);
		if(temp_cont_mode == 3) iRectangle(676,246,122,82);
		iSetColor(255,255,255);
		//iText(405,43,"Please click OK or press ENTER to save changes.",GLUT_BITMAP_9_BY_15); // GLUT_BITMAP_HELVETICA_18
	}
	if(showmenu == 2)  // LeaderBoard;
	{
		iShowBMP(0,0,"image\\Mines_LeaderBoard.bmp");
		iSetColor(0,0,0);
		char str_leaderboard_small[30], str_leaderboard_medium[30], str_leaderboard_large[30];
		sprintf(str_leaderboard_small, "%d:%02d:%02d",highscore.hour,highscore.min,highscore.sec);
		sprintf(str_leaderboard_medium,"%d:%02d:%02d",highscore_medium.hour,highscore_medium.min,highscore_medium.sec);
		sprintf(str_leaderboard_large, "%d:%02d:%02d",highscore_large.hour,highscore_large.min,highscore_large.sec);

		iText(470, 420, "Small:",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(470, 348, "Medium:",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(470, 262, "Large:",GLUT_BITMAP_TIMES_ROMAN_24);
		int del = 120;
		if(highscore.hour != 9) iText(470+del, 425, str_leaderboard_small,GLUT_BITMAP_TIMES_ROMAN_24);
		else iText(470+del, 425, "N/A",GLUT_BITMAP_TIMES_ROMAN_24);
		if(highscore_medium.hour != 9) iText(470+del, 348, str_leaderboard_medium,GLUT_BITMAP_TIMES_ROMAN_24);
		else iText(470+del, 348, "N/A",GLUT_BITMAP_TIMES_ROMAN_24);
		if(highscore_large.hour != 9) iText(470+del, 262, str_leaderboard_large,GLUT_BITMAP_TIMES_ROMAN_24);
		else iText(470+del, 262, "N/A",GLUT_BITMAP_TIMES_ROMAN_24);


	}
	if(showmenu == 3) iShowBMP(0,0,"image\\Mines_about_menu.bmp"); // about;
	if(showmenu == 4) iShowBMP(0,0,htp_page[htp_ind]); // how to play ;
	if(showmenu == 5) iShowBMP(0,0,"image\\Mines_exit_areyousure.bmp"); /*exit*/
	if(showmenu == 6) // game menu
	{
		iShowBMP(0,0,"image\\Mines_game_menu.bmp");
		iSetColor(21,93,117);
		iText(700 - (temp_board_size == 2)*10,440,board_size_str, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(700 - (temp_difficulty == 2)*10,312,diff_str, GLUT_BITMAP_TIMES_ROMAN_24);
		if(menu_select == 0) iRectangle(625,416,210,60);
		if(menu_select == 1) iRectangle(625,284,210,60);
		
	}
	
	if(showmenu == 7) // play;
	{
		iShowBMP(0,0,"image\\Mines_play_new.bmp");
		
		show_grid();
		iSetColor(255,255,255);
		sprintf(bomb_count_text,"Total Mines: %d", bomb_num);
		iText(222,636,bomb_count_text,GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(flag_count_text,"Flag remaining: %d", flag_count);
		iText(800,636,flag_count_text,GLUT_BITMAP_TIMES_ROMAN_24);

		if(cont_mode != 1)
		{
			if(board_size == 1) iShowBMP2(ei_x+g_x*e_x, ei_y+(g_r-1-g_y)*e_y, "image\\easy\\Mines_key_control_easy.bmp",255);
			if(board_size == 2) iShowBMP2(ei_x+g_x*e_x, ei_y+(g_r-1-g_y)*e_y, "image\\medium\\Mines_key_control_medium.bmp",255);
			if(board_size == 3) iShowBMP2(ei_x+g_x*e_x, ei_y+(g_r-1-g_y)*e_y, "image\\large\\Mines_key_control_large.bmp",255);
		}

		if(game_over == 1) // lost
		{
			iShowBMP2(0,0,"image\\Mines_gameover.bmp",255); 
			
			iPauseTimer(0);
		}
		if(game_over == 2)  // win
		{
			iShowBMP2(0,0,"image\\Mines_win.bmp",255);
			char win_time[30], highscore_time[30];
			int h_w = h, m_w = m, s_w = s;
			sprintf(win_time,"Time required: %d:%02d:%02d",h_w,m_w,s_w);
			

			if(board_size == 1 && total_sec(h_w, m_w, s_w) <= total_sec(highscore.hour, highscore.min, highscore.sec ))
			{
				highscore.hour = h_w;
				highscore.min = m_w;
				highscore.sec = s_w;
				sprintf(highscore_time,"High Score: %d:%02d:%02d",highscore.hour,highscore.min,highscore.sec);
			}
			else if(board_size == 2 && total_sec(h_w, m_w, s_w) <= total_sec(highscore_medium.hour, highscore_medium.min, highscore_medium.sec ))
			{
				highscore_medium.hour = h_w;
				highscore_medium.min = m_w;
				highscore_medium.sec = s_w;
				sprintf(highscore_time,"High Score: %d:%02d:%02d",highscore_medium.hour,highscore_medium.min,highscore_medium.sec);
			}
			else if(board_size == 3 && total_sec(h_w, m_w, s_w) <= total_sec(highscore_large.hour, highscore_large.min, highscore_large.sec ))
			{
				highscore_large.hour = h_w;
				highscore_large.min = m_w;
				highscore_large.sec = s_w;
				sprintf(highscore_time,"High Score: %d:%02d:%02d",highscore_large.hour,highscore_large.min,highscore_large.sec);
			}
			
			iSetColor(0,0,0);
			iText(350,270,win_time,GLUT_BITMAP_TIMES_ROMAN_24);
			iText(700,270,highscore_time,GLUT_BITMAP_TIMES_ROMAN_24);

			//timer_sec = 0;
			iPauseTimer(0);
		}
		show_timer();
	}
	
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	printf("x = %d, y = %d m\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	printf("x = %d, y= %d %s\n",mx,my, (button == GLUT_RIGHT_BUTTON)?"right":" ");
	if(showmenu == 0) //homepage
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) 
		{
			if(19 <= mx && mx <= 277 && 334 <= my && my <= 385 )
			{
				showmenu = 4; // how to play;
				htp_ind = 0;
			}
				
			
			if(170 <= mx && mx <= 380 && 620 <= my && my <= 670 )
				showmenu = 1; // settings;
			
			if(480 <= mx && mx <= 770 && 620 <= my && my <= 670 )
				showmenu = 2; // leaderboard;
			
			if(890 <= mx && mx <= 1060 && 620 <= my && my <= 670 )
				{showmenu = 3; // about;
				printf("ABOUT\n");}
			if(570 <= mx && mx <= 700 && 245 <= my && my <= 295 )
				{showmenu = 5;
				gbc++;
				} // exit;
			if(925 <= mx && mx <= 1200 && 434 <= my && my <= 477 )
			{
				showmenu = 6; // game menu;
				mx = 0;
				my = 0;
				click_count = 0;
			}
				
			if(572 <= mx && mx <= 695 && 354 <= my && my <= 406 )
			{
				//sleep(1);
				showmenu = 7; // play;
				make_grid(0,0);
				click_count = 0;
				flag_count = bomb_num;
				game_over = 0;
				uncover_cell_count = 0;
				mx = -1;
				my = -1;
				g_x = g_c/2;
				g_y = g_r/2;
				timer_sec = 0;
				iResumeTimer(0);
			}
		}	
	}
	if(showmenu == 1) // settings;
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if(790 <= mx && mx <= 840 && 510 <= my && my <= 560 ) // cross
			{
				showmenu = 0; // home
				temp_cont_mode = cont_mode;
				temp_music_on = music_on;
			}
			if(585 <= mx && mx <= 707 && 435 <= my && my <= 487 ){
				temp_music_on = 1 - temp_music_on;
				printf("music_on = %d\n",music_on);
				
			}
			if(441 <= mx && mx <= 491  && 248 <= my && my <= 326 )
				temp_cont_mode = 1;
			if(535 <= mx && mx <= 647  && 249 <= my && my <= 320 )
				temp_cont_mode = 2;
			if(677 <= mx && mx <= 795  && 249 <= my && my <= 322 )
				temp_cont_mode = 3;
			if(561 <= mx && mx <= 663  && 165 <= my && my <= 214 ) // ok
			{
				cont_mode = temp_cont_mode;
				music_on = temp_music_on;
				showmenu = 0;
			}
		}
	}
	if(showmenu == 2) // leaderboard
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		if(790 <= mx && mx <= 840 && 510 <= my && my <= 560 )
			showmenu = 0;
	}
	if(showmenu == 3) // about
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		if(805 <= mx && mx <= 855 && 590 <= my && my <= 650 )
			showmenu = 0;
	}
	if(showmenu == 4) // how to play
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if(1045 <= mx && mx <= 1103 && 568 <= my && my <= 628 )
			showmenu = 0;
			if(520 <= mx && mx <= 538 && 76 <= my && my <= 99 ) // left arrow
			{
				htp_ind--;
				if(htp_ind<0)htp_ind = 0;
			}
			
			if(658 <= mx && mx <= 677 && 76 <= my && my <= 99 ) // right arrow
			{
				htp_ind++;
				if(htp_ind>3)htp_ind = 3;
			}
			
		}
		
	}
	if(showmenu == 5) // exit ;
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if(520 <= mx && mx <= 700 && 350 <= my && my <= 430 )
				exit(0);
			if(470 <= mx && mx <= 750 && 240 <= my && my <= 315 )
			{
				gbc++;
				if(gbc >= 3){
					showmenu = 0;gbc = 0;
				}
			}
		}
	}
	if(showmenu == 6) // game menu ;
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if(790 <= mx && mx <= 840 && 510 <= my && my <= 560 ) // cross
			{
				showmenu = 0;
				temp_board_size = board_size;
				temp_difficulty = difficulty;
			}
			if(558 <= mx && mx <= 661 && 223 <= my && my <= 280 ) // ok
			{
				showmenu = 0;
				board_size = temp_board_size;
				difficulty = temp_difficulty;
				if(board_size == 1) 
				{
					g_r = 8;
					g_c = 10;
					e_x = 64;
					e_y = e_x;
					ei_x = 288;
					ei_y = 55;
					
					if(difficulty == 1) bomb_num = 5;
					if(difficulty == 2) bomb_num = 10;
					if(difficulty == 3) bomb_num = 15;
				}
				if(board_size == 2) 
				{
					g_r = 14;
					g_c = 18;
					e_x = 40;
					e_y = e_x;
					ei_x = 257;
					ei_y = 34;
					if(difficulty == 1) bomb_num = 30;
					if(difficulty == 2) bomb_num = 40;
					if(difficulty == 3) bomb_num = 50;
				}
				if(board_size == 3) 
				{
					g_r = 18;
					g_c = 24;
					e_x = 32;
					e_y = e_x;
					ei_x = 224;
					ei_y = 34;
					if(difficulty == 1) bomb_num = 80;
					if(difficulty == 2) bomb_num = 100;
					if(difficulty == 3) bomb_num = 120;
				}

				if(temp_difficulty == 1) strcpy(diff_str, "Easy");
				if(temp_difficulty == 2) strcpy(diff_str, "Medium");
				if(temp_difficulty == 3) strcpy(diff_str, "Hard");

				flag_count = bomb_num;
			}
			if(386 <= mx && mx <= 835 && 417 <= my && my <= 480 ) menu_select = 0;
			if(408 <= mx && mx <= 833 && 288 <= my && my <= 356 ) menu_select = 1;
			
			if(636 <= mx && mx <= 657 && 435 <= my && my <= 460 ) //board size left
			{
				temp_board_size--; 
				if(temp_board_size==0) temp_board_size = 3;
			}
			if(802 <= mx && mx <= 823 && 435 <= my && my <= 460 ) //board size right
			{
				temp_board_size++; 
				if(temp_board_size>=4) temp_board_size = 1;
			}
			if(636 <= mx && mx <= 657 && 309 <= my && my <= 333 ) //dificulty left
			{
				temp_difficulty--; 
				if(temp_difficulty==0) temp_difficulty = 3;
			}
			if(802 <= mx && mx <= 823 && 309 <= my && my <= 333 ) //dificulty right
			{
				temp_difficulty++; 
				if(temp_difficulty>=4) temp_difficulty = 1;
			}
			bomb_num = 10;

			if(temp_board_size == 1)strcpy(board_size_str, "Small");
			if(temp_board_size == 2)strcpy(board_size_str, "Medium");
			if(temp_board_size == 3)strcpy(board_size_str, "Large");


			if(board_size == 1) 
			{
				g_r = 8;
				g_c = 10;
				e_x = 64;
				e_y = e_x;
				ei_x = 288;
				ei_y = 55;
				
				if(difficulty == 1) bomb_num = 5;
				if(difficulty == 2) bomb_num = 10;
				if(difficulty == 3) bomb_num = 15;
			}
			if(board_size == 2) 
			{
				g_r = 14;
				g_c = 18;
				e_x = 40;
				e_y = e_x;
				ei_x = 257;
				ei_y = 34;
				if(difficulty == 1) bomb_num = 30;
				if(difficulty == 2) bomb_num = 40;
				if(difficulty == 3) bomb_num = 50;
			}
			if(board_size == 3) 
			{
				g_r = 18;
				g_c = 24;
				e_x = 32;
				e_y = e_x;
				ei_x = 224;
				ei_y = 34;
				if(difficulty == 1) bomb_num = 80;
				if(difficulty == 2) bomb_num = 100;
				if(difficulty == 3) bomb_num = 120;
			}

			if(temp_difficulty == 1) strcpy(diff_str, "Easy");
			if(temp_difficulty == 2) strcpy(diff_str, "Medium");
			if(temp_difficulty == 3) strcpy(diff_str, "Hard");

			flag_count = bomb_num;
			
		}
	}
	if(showmenu == 7) // play ;
	{
		
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if(18 <= mx && mx <= 105 && 600 <= my && my <= 687 ) // close
			{
				showmenu = 0;
				timer_sec = 0;
				iPauseTimer(0);
			}
				
			if(game_over != 0 && mx>0 && my>0) 
			{
				timer_sec = 0;
				showmenu = 0;
			}
		}
		
		if (state == GLUT_DOWN) // mouse control
		{
			if(cont_mode == 1)
			{
				if(ei_x <= mx && mx <= ei_x + g_c*e_x && ei_y <= my && my <= ei_y + g_r*e_y )
				{
					int g_x = ((mx-ei_x)/e_x);
					int g_y = g_r - 1 - ((my-ei_y)/e_y);
					if(button == GLUT_LEFT_BUTTON && grid_e[g_y][g_x].stat != 2) // uncover
					{
						if(grid_e[g_y][g_x].stat == 1 && music_on) PlaySound("music\\uncover_4.wav", NULL, SND_ASYNC);
						click_count++;
						if(click_count == 1) make_grid(g_y,-1*g_x);
						cell_uncover(g_y,g_x); 
						if(grid_e[g_y][g_x].count == -1) // lose
						{
							game_over = 1;
							if(music_on) PlaySound("music\\loss_1.wav", NULL, SND_ASYNC);
							
						}
						uncover_cell_count = 0;
						for(int i=0;i<g_r;i++)
						for(int j=0;j<g_c;j++)
						if(grid_e[i][j].stat == 0) uncover_cell_count++;
						if(game_over == 0 && uncover_cell_count == g_r*g_c - bomb_num)  // win
						{
							game_over = 2;
							if(music_on) PlaySound("music\\win_1.wav", NULL, SND_ASYNC);
						}
					}
					if(button == GLUT_RIGHT_BUTTON) 
					{
						if(grid_e[g_y][g_x].stat != 0 && music_on) PlaySound("music\\flag_1.wav", NULL, SND_ASYNC);
						if(grid_e[g_y][g_x].stat == 1 && flag_count > 0)  // flag
						{
							grid_e[g_y][g_x].stat = 2;
							flag_count--;
						}
						else if(grid_e[g_y][g_x].stat == 2)  //cover
						{
							grid_e[g_y][g_x].stat = 1;
							flag_count++;
						}
					}
				}
			}
				
		}
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 27) //esc
	{
		exit(0);
	}
	if (key == 13) {
		// exit(0);
	}
	if(game_over != 0) 
	{
		timer_sec = 0;
		showmenu = 0;
	}
	if(showmenu == 1) // settings
	{
		if(key == 13) // enter
		{
			cont_mode = temp_cont_mode;
			music_on = temp_music_on;
			showmenu = 0;
		}
	}

	if(showmenu == 6) // gamemenu
	{
		if(key == 13) // enter
		{
			board_size = temp_board_size;
			difficulty = temp_difficulty;
			showmenu = 0;
			if(board_size == 1) 
			{
				g_r = 8;
				g_c = 10;
				e_x = 64;
				e_y = e_x;
				ei_x = 288;
				ei_y = 55;
				
				if(difficulty == 1) bomb_num = 5;
				if(difficulty == 2) bomb_num = 10;
				if(difficulty == 3) bomb_num = 15;
			}
			if(board_size == 2) 
			{
				g_r = 14;
				g_c = 18;
				e_x = 40;
				e_y = e_x;
				ei_x = 257;
				ei_y = 34;
				if(difficulty == 1) bomb_num = 30;
				if(difficulty == 2) bomb_num = 40;
				if(difficulty == 3) bomb_num = 50;
			}
			if(board_size == 3) 
			{
				g_r = 18;
				g_c = 24;
				e_x = 32;
				e_y = e_x;
				ei_x = 224;
				ei_y = 34;
				if(difficulty == 1) bomb_num = 80;
				if(difficulty == 2) bomb_num = 100;
				if(difficulty == 3) bomb_num = 120;
			}

			if(temp_difficulty == 1) strcpy(diff_str, "Easy");
			if(temp_difficulty == 2) strcpy(diff_str, "Medium");
			if(temp_difficulty == 3) strcpy(diff_str, "Hard");

			flag_count = bomb_num;
		}
	}

	if(showmenu == 6) // gamemenu
	{
		if(key == 13) // enter
		{
			board_size = temp_board_size;
			//music_on = temp_music_on;
			showmenu = 0;
		}
	}
	if(showmenu == 7) //play
	{
		if(cont_mode == 3) // WASD control
		{
			if((key == 'W' || key == 'w') && g_y > 0) g_y--;
			if((key == 'S' || key == 's') && g_y < (g_r-1)) g_y++;
			if((key == 'A' || key == 'a') && g_x > 0) g_x--;
			if((key == 'D' || key == 'd') && g_x < (g_c-1)) g_x++;
			if(key == 'F' || key == 'f')
			{
				if(grid_e[g_y][g_x].stat == 1 && flag_count > 0)  // flag
				{
					grid_e[g_y][g_x].stat = 2;
					flag_count--;
				}
				else if(grid_e[g_y][g_x].stat == 2)  //cover
				{
					grid_e[g_y][g_x].stat = 1;
					flag_count++;
				}
			}
			if(key == 32 && grid_e[g_y][g_x].stat != 2) // uncover
			{
				click_count++;
				if(click_count == 1) make_grid(g_y,g_x*-1); 
				cell_uncover(g_y,g_x); 
				if(grid_e[g_y][g_x].count == -1)
				{
					game_over = 1;
				}
				uncover_cell_count = 0;
				for(int i=0;i<g_r;i++)
				for(int j=0;j<g_c;j++)
				{
					if(grid_e[i][j].stat == 0) uncover_cell_count++;
				}
				if(game_over == 0 && uncover_cell_count == g_r*g_c - bomb_num) game_over = 2; // win
			}
		}
		if(cont_mode == 2) // arrow control
		{
			if(key == 'F' || key == 'f')
			{
				if(grid_e[g_y][g_x].stat == 1 && flag_count > 0)  // flag
				{
					grid_e[g_y][g_x].stat = 2;
					flag_count--;
				}
				else if(grid_e[g_y][g_x].stat == 2)  //cover
				{
					grid_e[g_y][g_x].stat = 1;
					flag_count++;
				}
			}
			if(key == 32 && grid_e[g_y][g_x].stat != 2) // uncover
			{
				click_count++;
				if(click_count == 1) make_grid(g_y,g_x*-1); 
				cell_uncover(g_y,g_x); 
				if(grid_e[g_y][g_x].count == -1) game_over = 1; // game over
				uncover_cell_count = 0;
				for(int i=0;i<g_r;i++)
				for(int j=0;j<g_c;j++)
				{
					if(grid_e[i][j].stat == 0) uncover_cell_count++;
				}
				if(game_over == 0 && uncover_cell_count == g_r*g_c - bomb_num) game_over = 2; // win
			}
		}
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//if(game_over != 0) showmenu = 0;
	if(showmenu == 1) // settings ;
	{
		if(key == GLUT_KEY_LEFT ) 
		{
			temp_cont_mode--;
			if(temp_cont_mode<1) temp_cont_mode = 3;
		}
		if(key == GLUT_KEY_RIGHT ) 
		{
			temp_cont_mode++;
			if(temp_cont_mode>3) temp_cont_mode = 1;
		}
		

	}

	if(showmenu == 4) // how to play
	{
		if(key == GLUT_KEY_LEFT ) // left arrow
		{
			htp_ind--;
			if(htp_ind<0)htp_ind = 0;
		}
		
		if(key == GLUT_KEY_RIGHT ) // right arrow
		{
			htp_ind++;
			if(htp_ind>3)htp_ind = 3;
		}
	}

	if(showmenu == 6) // game menu ;
	{
		if(key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) menu_select = 1 - menu_select;

		if(menu_select == 0)
		{
			if(key == GLUT_KEY_LEFT) // board size left
			{
				temp_board_size--; 
				if(temp_board_size==0) temp_board_size = 3;
			}
			if(key == GLUT_KEY_RIGHT)
			{
				temp_board_size++; 
				if(temp_board_size>=4) temp_board_size = 1; // board size right
			}
		}
		if(menu_select == 1)
		{
			if(key == GLUT_KEY_LEFT) // difficulty left
			{
				temp_difficulty--; 
				if(temp_difficulty==0) temp_difficulty = 3;
			}
			if(key == GLUT_KEY_RIGHT)
			{
				temp_difficulty++; 
				if(temp_difficulty>=4) temp_difficulty = 1; // difficulty right
			}
		}
		if(temp_board_size == 1)strcpy(board_size_str, "Small");
		if(temp_board_size == 2)strcpy(board_size_str, "Medium");
		if(temp_board_size == 3)strcpy(board_size_str, "Large");

		if(board_size == 1) 
			{
				g_r = 8;
				g_c = 10;
				e_x = 64;
				e_y = e_x;
				ei_x = 288;
				ei_y = 55;
				if(difficulty == 1) bomb_num = 5;
				if(difficulty == 2) bomb_num = 10;
				if(difficulty == 3) bomb_num = 15;
			}
			if(board_size == 2) 
			{
				g_r = 14;
				g_c = 18;
				e_x = 40;
				e_y = e_x;
				ei_x = 257;
				ei_y = 34;
				if(difficulty == 1) bomb_num = 30;
				if(difficulty == 2) bomb_num = 40;
				if(difficulty == 3) bomb_num = 50;
			}
			if(board_size == 3) 
			{
				g_r = 18;
				g_c = 24;
				e_x = 32;
				e_y = e_x;
				ei_x = 224;
				ei_y = 34;
				if(difficulty == 1) bomb_num = 80;
				if(difficulty == 2) bomb_num = 100;
				if(difficulty == 3) bomb_num = 120;
			}

			if(temp_difficulty == 1) strcpy(diff_str, "Easy");
			if(temp_difficulty == 2) strcpy(diff_str, "Medium");
			if(temp_difficulty == 3) strcpy(diff_str, "Hard");

			flag_count = bomb_num;
	}

	if(showmenu == 7) // play ;
	{
		if(cont_mode == 2)
		{
			if((key == GLUT_KEY_UP ) && g_y > 0) g_y--;
			if((key == GLUT_KEY_DOWN ) && g_y < (g_r-1)) g_y++;
			if((key == GLUT_KEY_LEFT ) && g_x > 0) g_x--;
			if((key == GLUT_KEY_RIGHT ) && g_x < (g_c-1)) g_x++;
			//if(game_over != 0) key = 0;
			if(game_over != 0) showmenu = 0;
		}
	}

}


int main() {
	//place your own initialization codes here.
	iSetTimer(1000, update_timer);
	// if(music_on == 1) PlaySound("music\\calm_8bit_1.wav", NULL, SND_LOOP | SND_ASYNC);
	
	iInitialize(1225, 700, "Minesweeper");
	return 0;
}
