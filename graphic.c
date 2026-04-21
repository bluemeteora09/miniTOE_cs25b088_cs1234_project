#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "miniTOE.h"

#define HEIGHT 23
#define WIDTH 80

char screen[HEIGHT][WIDTH];

void clear_screen(){
	for(int i=0; i<HEIGHT; i++){
		for(int j=0; j<WIDTH; j++){
			screen[i][j] = ' ';
		}
	}
}

void draw_box(int x, int y, int w, int h){
	if(y+h > HEIGHT){
		h = HEIGHT - y;
	}
	if(x+w > WIDTH){
		w = WIDTH - x;
	}
	for(int i=0; i<h; i++){
                if(i == 0 || i == h-1){
                        for(int j=0; j<w; j++){
				if(j==0 || j==w-1){
					screen[y+i][x+j] = '+';
				}
					else{
					screen[y+i][x+j] = '-'; 
				}
			}
		}
		
                else{
			for(int j=0; j<w; j++){
				if(j==0 || j==w-1){
					screen[y+i][x+j] = '|';
				}
				else{
					screen[y+i][x+j] = ' ';
				}
			}
                }
        }	
}

void write_text(int x, int y, char *str){
	int i=0;
	while(str[i] != '\0'){
		screen[y][x+i] = str[i];
		i++;
	}
}

void write_text_with_wrap(int x, int y, char *str, int box_w, int box_h){
	int px = 0;
	int py = 0;
	int i=0; 
	while(str[i] != '\0'){
		if(str[i] == '\n'){
			px = 0;
			py++;
			i++;
			continue;
		}
		if(str[i] == '\t'){
			for(int j=0; j<4; j++){
				if(px < box_w-2){
					screen[y+py][x+px] = ' ';
					px++;
				}
			}
			i++;
			continue;
		}
		if(px >= box_w-1){
			px = 0;
			py++;
		}
		if(py > box_h){
			break;
		}
		int screen_x = x + px;
		int screen_y = y + py;
		if(screen_x < WIDTH && screen_y < HEIGHT){
			screen[screen_y][screen_x] = str[i];
		}
		px++;
		i++;
	}
}

void draw_status_bar(){
	// for(int i=0; i<WIDTH; i++){
	// 	if(i==0 || i==WIDTH-1){
	// 		screen[20][i] = '+';
	// 	}
	int y;
	if(curr_st == LOGIN_PAGE){
		y = 17;
	}
	else{
		y = 20;
	}
	draw_box(0, y, 80, 3);

	if(strlen(msg_sys) > 0){
		write_text(1, y+1, "[SYS] : ");
		write_text(8, y+1, msg_sys);
	}
	else{
		write_text(1, y+1, "[SYS] : Waiting for Command");
	}
}