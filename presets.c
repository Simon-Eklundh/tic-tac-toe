

#include <stdint.h>
#include <pic32mx.h>


//simon's
void preset_gameboard(void){
	display_string(0, "welcome to");
	display_string(1, "four in a row");
	display_string(2, "mate");
	display_update();
	delay(2000);
	
	display_string(0, "Instructions:");
	display_string(1, "swts fr left=row");
	display_string(2, "btns fr left=pos");
	display_update();
	delay(4000);
	
	display_string(0, "press reset");
	display_string(1, "button to");
	display_string(2, "reset wins etc");
	display_update();
	delay(2000);
	
// joel added a column :)
	display_string( 0 , "|_|_|_|_|");
	display_string( 1 , "|_|_|_|_|");
	display_string( 2 , "|_|_|_|_|");
	display_string(3 ,  "| | | | |");
	display_update();
	
}
