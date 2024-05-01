#include"TM4C123.h"
#include <string.h>
#include <stdint.h>
#include "hi.h"
#define CR 0x0D



//*****************************************************************************
//
// UART0
//
//*****************************************************************************
void UART0_Init(void){
    
    SYSCTL_RCGCUART_R |= 0x0001;
  SYSCTL_RCGCGPIO_R |= 0X0001;
    while((SYSCTL_PRGPIO_R & 0x01) == 0){}
    UART0_CTL_R =~UART_CTL_UARTEN;
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    UART0_LCRH_R |= 0x70;
    UART0_CTL_R |= 0x301;
    GPIO_PORTA_DEN_R |= 0x03;
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_AMSEL_R &= ~0x03;
    GPIO_PORTA_PCTL_R |= 0x00000011;
    
}
void UART0_WriteChar(unsigned char ch)   //function to write char
{
    while((UART0_FR_R&0X20)!=0){}
        UART0_DR_R = ch;    
}

unsigned char UART0_ReadChar(void){                                //function that Read Char
    while((UART0_FR_R&0X10) != 0){}
    return (UART0_DR_R&0xFF);
}
void UART1_ReadString(char *str , int len){
char c = UART1_ReadChar();{        //Read String
	for(int i=0;i<len;i++){
		if(c!=CR){
		*str = c;
		str++;
		c = UART1_ReadChar();
		}
		else if(c==CR || i==len) break;
	}	
}
*str=0x00;
}
	
    void printStr(char *str){     //Print String
        while(*str){
            UART0_WriteChar(*str);
            str++;
        }
    }
//*****************************************************************************
//
// UART1
//
//*****************************************************************************


void UART1_Init(void){
SYSCTL_RCGCUART_R |= 0x0002;
SYSCTL_RCGCGPIO_R |= 0X0002;
while((SYSCTL_PRGPIO_R & 0x02) == 0){}
UART1_CTL_R =~UART_CTL_UARTEN;
UART1_IBRD_R=104;
UART1_FBRD_R=11;
UART1_LCRH_R |= 0x70;
UART1_CTL_R |= 0x301;
GPIO_PORTB_DEN_R |= 0x03;
GPIO_PORTB_AFSEL_R |= 0x03;
GPIO_PORTB_AMSEL_R &= ~0x03;
GPIO_PORTB_PCTL_R |= 0x00000011;
}


void UART1_WriteChar(unsigned char ch)   //function to write char
{
	while((UART1_FR_R&0x20)!=0){}
		UART1_DR_R = ch;	
}

unsigned char UART1_ReadChar(void){								//function that Read Char
	while((UART1_FR_R&0x10) != 0){}
	return (UART1_DR_R&0xFF);
}


void UART1_ReadString(char *str , int len)	      	//Read String
{	
 char c = UART1_ReadChar();
	for(int i=0;i<len;i++){
		if(c!=CR){
		*str = c;
		str++;
		c = UART1_ReadChar();
		}
		else if(c==CR || i==len) break;
	}
	*str=0x00;
}
 void printStr(char *str){       //Print String
        while(*str){
            UART1_WriteChar(*str);
            str++;
        }
    }
//*****************************************************************************
//
// UART5
//
//*****************************************************************************

void UART5_Init(){
	SET(SYSCTL_RCGCUART_R,5);
	SET(SYSCTL_RCGCGPIO_R,4);
	while((SYSCTL_PRGPIO_R & (0x01<<4)) == 0){}
	CLEAR(UART5_CTL_R,0);
	UART5_IBRD_R = 104;
	UART5_FBRD_R = 11;
	UART5_LCRH_R |= 0x70;
	UART5_CTL_R |= 0x301;
	GPIO_PORTE_DEN_R |= 0x30;
	GPIO_PORTE_AFSEL_R |= 0x30;
	GPIO_PORTE_AMSEL_R &= ~0x30;
	GPIO_PORTE_PCTL_R |= 0x00110000;
	
}
void UART5_WriteChar(unsigned char ch){						//Write Char
	while((UART5_FR_R&0x20) != 0){}
	UART5_DR_R = ch;
}

unsigned char UART5_ReadChar(void){								//Read Char
	while((UART5_FR_R&0x10) != 0){}
	return UART5_DR_R&0xFF;
}

void UART5_ReadString(char *str , int len)	      	//Read String
{	
 char c = UART5_ReadChar();
	for(int i=0;i<len;i++){
		if(c!=CR){
		*str = c;
		str++;
		c = UART5_ReadChar();
		}
		else if(c==CR || i==len) break;
	}
	*str=0x00;
}
 void printStr(char *str){       //Print String
        while(*str){
            UART5_WriteChar(*str);
            str++;
        }
    }

//*****************************************************************************
//
// UART7
//
//*****************************************************************************

void UART7_Init(){
	
	SET(SYSCTL_RCGCUART_R,7);
	SET(SYSCTL_RCGCGPIO_R,4);
	while((SYSCTL_PRGPIO_R & (0x01<<4)) == 0){}
	CLEAR(UART7_CTL_R,0);
	UART7_IBRD_R = 104;
	UART7_FBRD_R = 11;
	UART7_LCRH_R |= 0x70;
	UART7_CTL_R |= 0x301;
	GPIO_PORTE_DEN_R |= 0x03;
	GPIO_PORTE_AFSEL_R |= 0x03;
	GPIO_PORTE_AMSEL_R &= ~0x03;
	GPIO_PORTE_PCTL_R |= 0x00000011;
	
}
void UART7_WriteChar(unsigned char ch){						//Write Char
	while((UART7_FR_R&0x02) != 0){}
	UART7_DR_R = ch;
}

unsigned char UART7_ReadChar(void){								//Read Char
	while((UART7_FR_R&0x01) != 0){}
	return UART7_DR_R&0xFF;
}

void UART7_ReadString(char *str , int len)	      	//Read String
{	
 char c = UART7_ReadChar();
	for(int i=0;i<len;i++){
		if(c!=CR){
		*str = c;
		str++;
		c = UART7_ReadChar();
		}
		else if(c==CR || i==len) break;
	}
	*str=0x00;
}
//*****************************************************************************
//
// UART5
//
//*****************************************************************************

void UART5_Init(unsigned long baudRate){
	unsigned long uartIBRD, uartFBRD;
	double CLDIV = (16000000.0 / (16.0 * baudRate));
	
	uartIBRD = (int)(CLDIV);
	uartFBRD = (int)((CLDIV - uartIBRD) * 64 + 0.5);
	
	SET(SYSCTL_RCGCUART_R,5);
	SET(SYSCTL_RCGCGPIO_R,4);
	while((SYSCTL_PRGPIO_R & (0x01<<4)) == 0){}
	CLEAR(UART5_CTL_R,0);
	UART5_IBRD_R = uartIBRD;
	UART5_FBRD_R = uartFBRD;
	UART5_LCRH_R |= 0x70;
	UART5_CTL_R |= 0x301;
	GPIO_PORTE_DEN_R |= 0x30;
	GPIO_PORTE_AFSEL_R |= 0x30;
	GPIO_PORTE_AMSEL_R &= ~0x30;
	GPIO_PORTE_PCTL_R |= 0x00110000;
	
}
void UART5_WriteChar(unsigned char ch){						//Write Char
	while((UART5_FR_R&TXFULL) != 0){}
	UART5_DR_R = ch;
}

unsigned char UART5_ReadChar(void){								//Read Char
	while((UART5_FR_R&RXEMPTY) != 0){}
	return UART5_DR_R&0xFF;
}

void UART5_WriteString(char *str){								//Write String
  while(*str){
    UART5_WriteChar(*str);
    str++;
  }
}

void UART5_ReadString(char *str, char stopCh){		//Read String
	char c = UART5_ReadChar();
	while(c && c != stopCh){
		*str = c;
		str++;
		c = UART5_ReadChar();
	}
	*str = 0x00;
}
//*****************************************************************************
//
// UART7
//
//*****************************************************************************

void UART7_Init(unsigned long baudRate){
	unsigned long uartIBRD, uartFBRD;
	double CLDIV = (16000000.0 / (16.0 * baudRate));
	
	uartIBRD = (int)(CLDIV);
	uartFBRD = (int)((CLDIV - uartIBRD) * 64 + 0.5);
	
	SET(SYSCTL_RCGCUART_R,7);
	SET(SYSCTL_RCGCGPIO_R,4);
	while((SYSCTL_PRGPIO_R & (0x01<<4)) == 0){}
	CLEAR(UART7_CTL_R,0);
	UART7_IBRD_R = uartIBRD;
	UART7_FBRD_R = uartFBRD;
	UART7_LCRH_R |= 0x70;
	UART7_CTL_R |= 0x301;
	GPIO_PORTE_DEN_R |= 0x03;
	GPIO_PORTE_AFSEL_R |= 0x03;
	GPIO_PORTE_AMSEL_R &= ~0x03;
	GPIO_PORTE_PCTL_R |= 0x00000011;
	
}
