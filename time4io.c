#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"




int getsw (void){
	int switchstatus = PORTD >> 8;
	int mask = 0xF;
    switchstatus = switchstatus & mask;
	return switchstatus;
}

	int getbtns(void){
	int buttonstatus = PORTD >> 5;
	int mask = 0x7;
	buttonstatus = buttonstatus & mask;
	buttonstatus = (buttonstatus << 1) && ((PORTF >> 1)& 1);
	return buttonstatus;
}

