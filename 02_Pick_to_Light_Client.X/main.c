
#include "main.h"

unsigned char can_payload[13];

static void init_config(void) {
    
    BUZZER_PORT =  OUTPUT_PORT;

    PEIE = 1;
    init_external_interrupt();
    GIE = 1;

    init_can();
    init_digital_keypad();
    init_ssd_control();

}

void main(void) {

    init_config();

    get_data_from_eeprom();

    while (1) {

        key = read_digital_keypad(STATE_CHANGE);

        if (can_receive()) receive_flag = data_recive(can_payload);

        if (key_detected) client_main(key);
        else if (receive_flag) receive_flag = data_update(key);
        else {

            ssd[0] = BLANK;
            ssd[1] = BLANK;
            ssd[2] = BLANK;
            ssd[3] = BLANK;
            display(ssd);
        }
    }
}