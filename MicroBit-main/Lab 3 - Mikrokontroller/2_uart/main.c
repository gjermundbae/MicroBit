#include <stdint.h>
#include "uart.h"
#include "gpio.h"
#include <stdio.h>






ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
		/*if(i == count-2){
			uart_send(*letter)
		}*/
	}
	return count;
}

int main(){
   
    uart_init();

	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

    GPIO->PIN_CNF[24] = 0;
	GPIO->PIN_CNF[25] = 0;

	int lightsOn = 0;
	int sleep = 0;
	while(1){
        if(uart_read()) {
			if(lightsOn){
				for(int i = 4; i <= 12; i++){
				GPIO->OUTCLR = (1 << i);
				}
				for(int i = 13; i <= 15; i++){
					GPIO->OUTCLR = (1 << i);
				}
				lightsOn = 0;
			}
			else{
				for(int i = 4; i <= 12; i++){
					GPIO->OUTCLR = (1 << i);
				}
				for(int i = 13; i <= 15; i++){
					GPIO->OUTSET = (1 << i);
				}
				lightsOn = 1;
			}
		}


		/*
		if(!(GPIO->IN & 1<<17)){
            uart_send('A');
			for(int i = 4; i <= 12; i++){
				GPIO->OUTCLR = (1 << i);
			}
			for(int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1 << i);
			}
		}

		if(!(GPIO->IN & 1<<26)){
            uart_send('B');
			for(int i = 4; i <= 12; i++){
				GPIO->OUTCLR = (1 << i);
			}
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);
			}
		}*/

		iprintf("The average grade in TTK%d was in %d and %d: %c\n\r",4235,2019,2018,'C');
        

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
