
/* mipslabwork.c
   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall
   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):
   This file modified 2017-04-31 by Ture Teknolog 
   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#include <stdbool.h>

#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

//global variables
int gamestate[9];
int row = 1;
int user = 1;
int mytime = 0x0;
void light(void) {
    static int counter = 1;
    volatile int *pointer = (volatile int *) 0xbf886110;
    *pointer = counter;
    counter++;
    return;
}

/* Interrupt Service Routine */
void user_isr(void) {
    static int timeoutcounter = 0;

	static int sum = 0;
    if (IFS(0) & 0x100) {

        IFSCLR(0) = 0x100;
        timeoutcounter++;
        if (timeoutcounter == 10) {
            timeoutcounter = 0;
			
            tick( &mytime );
            display_update();
			}
				
        }
    }
    
	
 
    



void timer(void) {
    T2CON = 0x0070;
    PR2 = 31250;
    TMR2 = 0;
    IECSET(0) = 0x100;
    IPCSET(2) = 0x5;
    T2CONSET = 0x8000;

    return;
}
/*
void set_temp(number, numstring){
	time = number;
	time = numstring;
}*/
/* Lab-specific initialization goes here */


void labinit(void) {
    volatile int *pointer = (volatile int *) 0xbf886110;
    int mask = 0xFF;
    mask = ~mask; //~ betyder 2:nd komplement 
    *pointer = *pointer & mask;
    TRISDSET = 0xFE0;
    timer();

	enable_interrupt();

   


    return;
}


void set_line(int gamestate[], int line){
	char row[3];
	int i;
	int j = (3*line);
	
	for(i = 0; i < 3; i++){
		
		switch (gamestate[j]){
		case 0 :
		row[i] = '_';
		break;
		case 1 :
		row[i] = 'x';
		break;
		case 2 :
		row[i] = 'o';
		break;
		
		}
		j++;
	}
	
	char theline[] = {row[0], '|', row[1], '|', row[2]};
	display_string(line, theline);
	
	return;

}
display_winner(int winner){
	if(winner == 1) display_string(3, "the winner was x");
	else if(winner == 2) display_string(3, "the winner was o");
	else display_string(3, "draw");
	delay(10000);

}

int colwin(int gamestate[]){
	int i;
	for( i = 0; i < 3; i++){
		if(gamestate[i] == 0) continue;
		else if(gamestate[i] == gamestate[i+3] && gamestate[i] == gamestate[i+6]){
			display_winner(gamestate[i]);
			return 1;

		
			
		}
	}
	return 0;
}
int rowwin(int gamestate[]){
	int i;
	for( i = 0; i < 7; i+=3){
		if(gamestate[i] == 0) continue;
		else if(gamestate[i] == gamestate[i+1] && gamestate[i] == gamestate[i+2]){
			display_winner(gamestate[i]);
			return 1;
			
			
		}
	}
	return 0;
}
int diagwin(int gamestate[]){
	
	
		if(gamestate[0] == 0 || gamestate[2] == 0) return 0;
		if(gamestate[0] == gamestate[4] && gamestate[0] == gamestate[8]){
			
			display_winner(gamestate[0]);
		return 1;}
		
		else if(gamestate[2] == gamestate[4] && gamestate[2] == gamestate[6])
			{
			display_winner(gamestate[2]);
		return 1;}
		
		
		return 0;
	
}

int is_game_won(int gamestate[]){
	int i;
	int count = 0;
	for (i=0;i<9; i++){
	if (!gamestate[i]) {
		count = 0;
		break;
	}
	else count = 1;
	}	
	
	if(colwin(gamestate))return 1;
	else if(rowwin(gamestate)) return 1;
	else if(diagwin(gamestate)) return 1;
	else if(count == 1) {display_winner(42); delay(10000);}
	
	
	else return 0;
	
	

	
	
}
void update_gamestate(int gamestate[]){
	int line = 0;
	set_line(gamestate, line);
	line++;
	set_line(gamestate, line);
	line++;
	set_line(gamestate, line);
	
	
}

/* This function is called repetitively from the main program */



void labwork(void) {
	int broken = 0;
	while(1){	
		if (getsw() == 8) {
			row == 1;
			if (getbtns() == 4){
				if (!gamestate[0]){
					gamestate[0] = user;
					broken++;
					break;
				}
			}
			else if (getbtns() == 2){
				if (!gamestate[1]){
					gamestate[1] = user;
					broken++;
					break;
				}
			}
			else if (getbtns() == 1) {
				if (!gamestate[2]) {
					gamestate[2] = user;
					broken++;
					break;
				}
			}
			
		display_string (3, "Row 1");	
		display_update();
		delay(100);
			
		}
		else if (getsw() == 4) {
			row = 2;
			
			if (getbtns() == 4){
				if (!gamestate[3]){
					gamestate[3] = user;
					broken++;
					break;
				}
			}
			else if (getbtns() == 2){
				if (!gamestate[4]){
					gamestate[4] = user;
					broken++;
					break;
				}
			}
			else if (getbtns() == 1) {
				if (!gamestate[5]){
					gamestate[5] = user;
					broken++;
					break;
				}
			}
			
			display_string (3, "Row 2");
			display_update();
			delay(100);
		}
	//	if(!gamestate[i]) gamestate[i] = user;
		else if (getsw() == 2) {
			row == 3;
			
			if (getbtns() == 4){
				if (!gamestate[6]){ gamestate[6] = user;
				broken++;
			
				break;
				}
			}
			else if (getbtns() == 2){
				if (!gamestate[7]) {gamestate[7] = user;
				broken++;
				break;
				}
			}
			else if (getbtns() == 1) {
				if (!gamestate[8]){ gamestate[8] = user;
				broken++;
				break;
				}
			}
			display_string (3, "Row 3");
			display_update();
			delay(100);
			
		}
		
		if(broken){
			broken = 0;
			
			//delay(1000);
			break;
		}
		//if(getbts){
			// array[row-1*3 + button] = user;
           	
	}
	if(user == 1) user = 2;
	else if(user == 2) user = 1;
	//display_debug(&user);
	delay(100);
	update_gamestate(gamestate);
	
	//delay(100);
	
	/* if(is_game_won(gamestate)){
		while(1){
	}} */
	is_game_won(gamestate);
	//if(rounds == 9 && !is_game_won(gamestate))
	//	display_winner(3);
    
    
	

   display_update();

	

    return;

}

//display_debug(&test);  used to print adress+ value of var on chipkit
  

