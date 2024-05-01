#define CR 0x0D
void UART0_Init(void);
void UART0_WriteChar(unsigned char ch);
unsigned char UART0_ReadChar(void);
void UART_outstring (char str);
void UART0_ReadString(char*str ,int len);
void UART1_Init(void);
void UART1_WriteChar(unsigned char ch);
unsigned char UART1_ReadChar(void);
void getCommand(char *str, int maxLen);
void printStr(char str);
