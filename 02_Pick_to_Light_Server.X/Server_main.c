#include "main.h"

unsigned char can_data[9];

void data_recived_from_client(unsigned char can_payload[13]) {

    puts("\rReceived signal from the client\n\r");

    product_id[0] = can_payload[D0] + '0';
    product_id[1] = can_payload[D1] + '0';
    product_id[2] = can_payload[D2] + '0';
    product_id[3] = can_payload[D3] + '0';
    unit_stock[0] = can_payload[D4] + '0';
    unit_stock[1] = can_payload[D5] + '0';
    unit_stock[2] = can_payload[D6] + '0';
    unit_stock[3] = can_payload[D7] + '0';

    if (can_payload[D4] == 'S') {

        puts("\rThe product ID of ");
        puts((const char *) product_id);
        puts(" having stock stock less then 10.");
        puts("\n\rPlease, Update the stock.");

    } else if (can_payload[D4] == 'L') {

        puts("\rThe product ID : ");
        puts((const char *) product_id);
        puts(" having lesser stock ");
        puts("\n\rPlease, Enter the lesser stock or update the stock.");

    } else {

        puts("\rThe Stock of product ID ");
        puts((const char *) product_id);
        puts(" is updated to ");
        puts((const char *) unit_stock);

    }

    puts("\n\n\r");

    ch_count = 0;
    data_add = 0;
    flag = 0;

    BUZZER = HIGH;
    for (unsigned int delay = 10000; delay--;);
    BUZZER = LOW;
    
}

void data_recived_from_UART(unsigned char ch) {

    can_data[ch_count++] = ch - '0';
    putch(ch);

    if (ch_count == 2 * MAX_DATA) {

        can_transmit();

        puts("\n\rThe Stock has been updated successfully\n\n\r");
        ch_count = 0;
        data_add = 0;
        flag = 0;
    }
}
