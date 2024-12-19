
#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include <ctype.h>
#include "can.h"
#include "uart.h"

#define NULL_CHAR            '\0'
#define MAX_DATA             4

unsigned char ch_count = 0, data_add = 4, no_input = 0, flag = 0;
unsigned char product_id[5], unit_stock[5];

#define BUZZER_PORT     TRISEbits.TRISE0
#define BUZZER          PORTEbits.RE0

#define OUTPUT_PORT     0
#define HIGH            1
#define LOW             0

void data_recived_from_client(unsigned char can_payload[13]);
void data_recived_from_UART(unsigned char ch);

#endif	/* MAIN_H */

