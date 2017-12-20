#include "./config.h"

#include "./Headers/usart.h"

void usart_0_rec(uint8_t data) {

}

int main(void) {

    // init
    usart_init(USART_0, F_CPU, 115200, 0x00, SETB(RXCIE1) | SETB(TXEN1) | SETB(RXEN1), SETB(UCSZ11) | SETB(UCSZ10), usart_0_rec);

    while (1) {

    }

}
