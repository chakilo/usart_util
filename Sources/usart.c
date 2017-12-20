/*
 * usart.c
 *
 * Created: 2017/10/2 9:41:56
 *  Author: konar
 */ 

#include "../Headers/usart.h"


#include "../config.h"

#include <avr/interrupt.h>

// usart receive callback
static struct {
	void (*rx_callback_for_usart_0)(uint8_t);
	void (*rx_callback_for_usart_1)(uint8_t);
} usart_rx_callbacks;

// usart 0 receiving interrupt
ISR(USART0_RX_vect) {

	// read data
	uint8_t data = UDR0;

	// run callback
	if (NULL != usart_rx_callbacks.rx_callback_for_usart_0) {
		usart_rx_callbacks.rx_callback_for_usart_0(data);
	}

}

// usart 1 receiving interrupt
ISR(USART1_RX_vect) {

	// read data
	uint8_t data = UDR1;

	// run callback
	if (NULL != usart_rx_callbacks.rx_callback_for_usart_1) {
		usart_rx_callbacks.rx_callback_for_usart_1(data);
	}

}

// init usart
int8_t usart_init(usart_num unum, uint32_t fsoc, uint32_t baud, uint8_t ucsra, uint8_t ucsrb, uint8_t ucsrc, void (*rx_callback)(uint8_t)) {
	switch (unum) {
		case USART_0:
			// 1. close
			UCSR0B = 0x00;
			UCSR0A = 0x00;

			// 2. set baud rate
			UBRR0L = (fsoc / 16 / (baud + 1)) % 256;
			UBRR0H = (fsoc / 16 / (baud + 1)) / 256;

			UCSR0C = ucsrc;
			UCSR0B = ucsrb;
			UCSR0A = ucsra;

			// 3. save callback
			usart_rx_callbacks.rx_callback_for_usart_0 = rx_callback;

			break;

		case USART_1:
			// 1. close
			UCSR1B = 0x00;
			UCSR1A = 0x00;

			// 2. set baud rate
			UBRR1L = (fsoc / 16 / (baud + 1)) % 256;
			UBRR1H = (fsoc / 16 / (baud + 1)) / 256;

			UCSR1C = ucsrc;
			UCSR1B = ucsrb;
			UCSR1A = ucsra;

			// 3. save callback
			usart_rx_callbacks.rx_callback_for_usart_1 = rx_callback;

			break;

		default:
			return -1;
	}

	return 0;
}

// send single char
int8_t usart_send_char(usart_num unum, uint8_t data) {
	switch (unum) {
		case USART_0:
			// wait for the last transmission
			while(!(UCSR0A&(1<<UDRE0)));
			// send
			UDR0 = data;

			break;

		case USART_1:
			// wait for the last transmission
			while(!(UCSR1A&(1<<UDRE1)));
			// send
			UDR1 = data;
			
			break;

		default:
			return -1;
	}
	return 0;
}

// send string
void usart_send_string(usart_num unum, uint8_t *data) {
	while(*data) {
		usart_send_char(unum, *data);
		data++;
	}
}
