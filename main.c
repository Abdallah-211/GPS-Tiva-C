#include"tm4c123gh6pm.h"
void SystemINit() {}
	void UART1Init()
	{
		SYSCTL_RCGCUART_R |= SYSCTL_RCGCGPIO_R1;
		SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
		UART1_CTL_R &=~ UART_CTL_UARTEN;
		UART1_IBRD_R = 104;
        UART1_FBRD_R = 11;
		UART1_LCRH_R =(UART_LCRH_WLEN_8 | UART_LCRH_FEN);
		UART1_CTL_R |= (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);
		GPIO_PORTB_AFSEL_R |= 0X03;
		GPIO_PORTB_PCTL_R |=(GPIO_PORTB_AHB_PCTL_R &~ 0XFFFFFF00) | (GPIO_PCTL_PB0_U1RX|GPIO_PCTL_PB1_U1TX);
		GPIO_PORTB_AHB_DEN_R |= 0X03;

	}

// Function to send a character via UART1 for GPS communication
void UART_GPS_SendChar(char data)
{
    // Wait until UART1 is ready to transmit
    while ((UART1_FR_R & 0x20) != 0);

    // Send the character
    UART1_DR_R = data;
}

// Function to receive a character via UART1 for GPS communication
char UART_GPS_ReceiveChar()
{
    // Wait until UART1 has received a character
    while ((UART1_FR_R & 0x10) != 0);

    // Read the received character
    return UART1_DR_R;
}

// Function to send a string via UART1 for GPS communication
void UART_GPS_SendString(const char* str)
{
    // Iterate through each character in the string and send it via UART1
    while (*str != '\0')
    {
        UART_GPS_SendChar(*str);
        str++;
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
void UART7_WriteChar(unsigned char ch){						//Write Char
	while((UART7_FR_R&TXFULL) != 0){}
	UART7_DR_R = ch;
}

unsigned char UART7_ReadChar(void){								//Read Char
	while((UART7_FR_R&RXEMPTY) != 0){}
	return UART7_DR_R&0xFF;
}

void UART7_WriteString(char *str){								//Write String
  while(*str){
    UART7_WriteChar(*str);
    str++;
  }
}

void UART7_ReadString(char *str, char stopCh){		//Read String
	char c = UART7_ReadChar();
	while(c != stopCh){//while(c && c != stopCh){
		*str = c;
		str++;
		c = UART7_ReadChar();
	}
	*str = 0x00;
}
