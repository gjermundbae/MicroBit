#include <stdint.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"


int main(){
    
    for(int i = 4; i <= 12; i++){
        GPIO->DIRSET = (1<<i);
		GPIO->OUTCLR = (1 << i);
    }
    for(int i = 13; i <= 15; i++){
        GPIO->DIRSET = (1<<i);
        GPIO->OUTCLR = (1 << i);

    }
    NRF_GPIOTE_REG* gpiote = GPIOTE;
    NRF_PPI_REG* ppi = PPI;

    //gpiote->CONFIG[0] = 100001000100000001;
    gpiote->CONFIG[0] = 0x21101;
    
    gpiote->CONFIG[1] = 0x130D03;
    //gpiote->CONFIG[1] = 100110000110100000011;
    gpiote->CONFIG[2]= 0x130E03;
    //gpiote->CONFIG[2] = 100110000111000000011;
    gpiote->CONFIG[3] = 0x130F03;
    //gpiote->CONFIG[3] = 100110000111100000011;
    gpiote->INTEN = 1;

    ppi->PPI_CH[0].EEP = (uint32_t) & (gpiote->IN[0]);
    ppi->PPI_CH[0].TEP = (uint32_t) & (gpiote->OUT[1]);
    ppi->PPI_CH[1].EEP = (uint32_t) & (gpiote->IN[0]);
    ppi->PPI_CH[1].TEP = (uint32_t) & (gpiote->OUT[2]);
    ppi->PPI_CH[2].EEP = (uint32_t) & (gpiote->IN[0]);
    ppi->PPI_CH[2].TEP = (uint32_t) & (gpiote->OUT[3]);
    

    PPI->CHENSET = 7;

    int sleep = 0 ;
    while(1){
        sleep = 10000;
        while(--sleep);
    }
    return 0;
}