#include <stdint.h>
#include "uart.h"
#include "gpio.h"


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


	int sleep = 0;
	while(1){
        
		if(!(GPIO->IN & 1<<17)){
            uart_send('A');
		}

		if(!(GPIO->IN & 1<<26)){
            uart_send('B');
		}
        

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
