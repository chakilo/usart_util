/*
 * usart.h
 *
 * Created: 2017/10/2 9:41:44
 *  Author: konar
 */ 


#ifndef USART_H_
#define USART_H_

#include <stdint.h>

typedef enum USART_NUM {
	USART_0 = 0,
	USART_1 = 1
} usart_num;

// init usart
int8_t usart_init(usart_num unum, uint32_t fsoc, uint32_t baud, uint8_t ucsra, uint8_t ucsrb, uint8_t ucsrc, void (*rx_callback)(uint8_t));

// send single char
int8_t usart_send_char(usart_num unum, uint8_t data);

// send string
void usart_send_string(usart_num unum, uint8_t *data);

#endif /* USART_H_ */