

#include <stdint.h>
#include <pic32mx.h>



void preset_gameboard(void){
	display_string(0, "welcome to");
	display_string(1, "tic tac toe");
	display_string(2, "mate");
	display_update();
	delay(2000);
	
	display_string( 0 , "_|_|_");
	display_string( 1 , "_|_|_");
	display_string( 2 , " | | ");
	display_string(3 , "row: 1 player: X");
	display_update();
	
}
