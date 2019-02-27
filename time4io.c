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
	int buttonstatus = PORTD >> 4;
	int mask = 0xF;
	buttonstatus = buttonstatus & mask;
	return buttonstatus;
}

