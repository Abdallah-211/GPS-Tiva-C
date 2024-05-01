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
}
