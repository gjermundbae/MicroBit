#include "uart.h"
#include <stdint.h>
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)


typedef struct {
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;
    volatile uint32_t RESERVED1[3];
	volatile uint32_t SUSPEND;
	volatile uint32_t RESERVED2[56];
    volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t TXDRDY;
    volatile uint32_t RESERVED3;
    volatile uint32_t ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t RXTO;
    volatile uint32_t RESERVED5[110];
    volatile uint32_t INTEN;
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED6[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED7[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED8;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED9;
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED10[17];
    volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init(){
    //GPIO->PIN_CNF[24] = GPIO->PIN_CNF[24] | 0x1); //Setter LSB til 1 dvs output
	//GPIO->PIN_CNF[25] = GPIO->PIN_CNF[25] & 0xFE); //Setter LSB til 0 dvs input

    GPIO->DIRSET = (1<<24);
    GPIO->DIRCLR = (1<<25);

    UART->PSELTXD = 24;
    UART->PSELTXD = 25;

    UART->BAUDRATE = 0x00275000;

    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;
    
    UART->ENABLE = 4;
    UART->STARTRX = 1;

    UART->TXDRDY = 1;

}
void uart_send(char letter){
    UART->STARTRX = 1;

    UART->TXD = letter;
    UART->TXDRDY = 0;
    
    while(!(UART->TXDRDY)){
        
    }
    UART->STOPTX = 1;
}
char uart_read(){
    if(UART->RXDRDY==0){
        return '\0';
    }
    UART->RXDRDY = 0;
    return UART->RXD;
}