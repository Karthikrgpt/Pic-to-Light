#include "main.h"

unsigned char ch;
extern unsigned char can_payload[13];

static void init_config(void) {

    init_uart();
    PEIE = 1;
    GIE = 1;
    
    BUZZER_PORT =  OUTPUT_PORT;

    init_can();
    
    puts("\n\rInitialization is successful..\n\n\r");
    
}

int main() {

    init_config();

    while (1) {

        if (can_receive()) data_recived_from_client(can_payload);

        if ( isdigit(ch) ) {
            data_recived_from_UART(ch);
            ch = NULL_CHAR;
        }
        
        if (ch_count == 0 && flag == 0) {
            puts("\n\rEnter the product id : ");
            flag = 1;
        } else if (ch_count == 4 && flag == 1) {
            puts("\n\rEnter the Amount of stock : ");
            flag = 2;
        }

    }

}

