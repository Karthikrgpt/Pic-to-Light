#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include "external_interrupt.h"
#include "isr.h"
#include "ssd_display.h"
#include "digital_keypad.h"
#include "internal_eeprom.h"
#include "can.h"

#define U               0xE5
#define _               0x08
#define S               0x6E
#define t               0xCC
#define P               0x8F
#define I               0x21
#define d               0xE9

#define BUZZER_PORT     TRISEbits.TRISE0
#define BUZZER          PORTEbits.RE0

#define OUTPUT_PORT     0
#define HIGH            1
#define LOW             0

unsigned char ssd[MAX_SSD_CNT], key;
unsigned char digit[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
unsigned char digit_dot[] = {ZERO + DOT, ONE + DOT, TWO + DOT, THREE + DOT, FOUR + DOT, FIVE + DOT, SIX + DOT, SEVEN + DOT, EIGHT + DOT, NINE + DOT};

unsigned char client_flag = 0, client_option = 0;
unsigned char inc_flag = 0, field_flag = 1, write_flag = 0;
unsigned char data_a = 0, data_b = 0, data_c = 0, data_d = 0; 
unsigned char id_a = 0, id_b = 0, id_c = 0, id_d = 0; 
unsigned char can_a = 0, can_b = 0, can_c = 0, can_d = 0; 
unsigned short i, receive_flag;

unsigned int key_detected;

void client_main(unsigned char key);
void get_data_from_eeprom(void);
void reset_client_flags(void);
unsigned char data_recive(unsigned char can_payload[13]);
void unit_stock(unsigned char key);
void product_id(unsigned char key);
unsigned char data_update(unsigned char key);

#endif