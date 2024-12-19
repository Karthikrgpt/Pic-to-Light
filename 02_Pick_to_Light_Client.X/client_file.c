#include "main.h"

unsigned char can_data[9];

void client_main(unsigned char key) {

    if (client_option && !client_flag) unit_stock(key);
    else if (client_option && client_flag) product_id(key);
    else {

        if (key == SWITCH2) client_option = 1;
        else if (key == SWITCH3) {
            client_flag = ~client_flag;
        }

        if (!client_flag) {
            ssd[0] = U; //U
            ssd[1] = _; //-
            ssd[2] = S; //S
            ssd[3] = t; //t
        } else {
            ssd[0] = P; //P
            ssd[1] = _; //-
            ssd[2] = I; //I
            ssd[3] = d; //d
        }
    }

    display(ssd);
}

unsigned char data_recive(unsigned char can_payload[13]) {

    if (can_payload[D0] != id_d || can_payload[D1] != id_c || can_payload[D2] != id_b || can_payload[D3] != id_a)
        return FALSE;

    can_d = can_payload[D4];
    can_c = can_payload[D5];
    can_b = can_payload[D6];
    can_a = can_payload[D7];

    return TRUE;

}

unsigned char data_update(unsigned char key) {

    ssd[3] = digit[can_a];
    ssd[2] = digit[can_b];
    ssd[1] = digit[can_c];
    ssd[0] = digit[can_d];

    short server_data = can_d * 1000 + can_c * 100 + can_b * 10 + can_a;
    short client_data = data_d * 1000 + data_c * 100 + data_b * 10 + data_a;
    short res = client_data - server_data;

    if (server_data > client_data) {

        can_data[0] = id_d;
        can_data[1] = id_c;
        can_data[2] = id_b;
        can_data[3] = id_a;
        can_data[4] = 'L';
        can_data[5] = 'E';
        can_data[6] = 'S';
        can_data[7] = 'S';
        can_transmit();

        return FALSE;
    }

    if (key == SWITCH1) {

        if (res <= 10) {

            can_data[0] = id_d;
            can_data[1] = id_c;
            can_data[2] = id_b;
            can_data[3] = id_a;
            can_data[4] = 'S';
            can_data[5] = ' ';
            can_data[6] = '1';
            can_data[7] = '0';

            can_transmit();
            
            return FALSE;
        }

        data_d = (res / 1000) % 10;
        data_c = (res / 100) % 10;
        data_b = (res / 10) % 10;
        data_a = (res / 1) % 10;

        write_internal_eeprom(0x06, data_d);
        write_internal_eeprom(0x07, data_c);
        write_internal_eeprom(0x08, data_b);
        write_internal_eeprom(0x09, data_a);

        BUZZER = HIGH;
        for (unsigned int delay = 10000; delay--;);
        BUZZER = LOW;
        
        return FALSE;
    }

    display(ssd);

    return TRUE;

}

void product_id(unsigned char key) {

    if (key == SWITCH1) {

        if (field_flag == 1 && ++id_a == 10) id_a = 0;
        else if (field_flag == 2 && ++id_b == 10) id_b = 0;
        else if (field_flag == 3 && ++id_c == 10) id_c = 0;
        else if (field_flag == 4 && ++id_d == 10) id_d = 0;

    } else if (key == SWITCH2 && ++field_flag == 5) field_flag = 1;
    else if (key == SWITCH3) {
        //to store product id data
        write_internal_eeprom(0x00, 'P');
        write_internal_eeprom(0x01, id_d);
        write_internal_eeprom(0x02, id_c);
        write_internal_eeprom(0x03, id_b);
        write_internal_eeprom(0x04, id_a);

        can_data[0] = id_d;
        can_data[1] = id_c;
        can_data[2] = id_b;
        can_data[3] = id_a;

        reset_client_flags();
    }

    switch (field_flag) {
        case 1:
            ssd[3] = digit_dot[id_a];
            ssd[2] = digit[id_b];
            ssd[1] = digit[id_c];
            ssd[0] = digit[id_d];
            break;
        case 2:
            ssd[3] = digit[id_a];
            ssd[2] = digit_dot[id_b];
            ssd[1] = digit[id_c];
            ssd[0] = digit[id_d];
            break;
        case 3:
            ssd[3] = digit[id_a];
            ssd[2] = digit[id_b];
            ssd[1] = digit_dot[id_c];
            ssd[0] = digit[id_d];
            break;
        case 4:
            ssd[3] = digit[id_a];
            ssd[2] = digit[id_b];
            ssd[1] = digit[id_c];
            ssd[0] = digit_dot[id_d];
            break;
    }

}

void unit_stock(unsigned char key) {

    if (key == SWITCH1) {

        if (field_flag == 1 && ++data_a == 10) data_a = 0;
        else if (field_flag == 2 && ++data_b == 10) data_b = 0;
        else if (field_flag == 3 && ++data_c == 10) data_c = 0;
        else if (field_flag == 4 && ++data_d == 10) data_d = 0;

    } else if (key == SWITCH2 && ++field_flag == 5) field_flag = 1;
    else if (key == SWITCH3) {
        //to store unit stock data
        write_internal_eeprom(0x05, 'U');
        write_internal_eeprom(0x06, data_a);
        write_internal_eeprom(0x07, data_b);
        write_internal_eeprom(0x08, data_c);
        write_internal_eeprom(0x09, data_d);

        can_data[0] = id_d;
        can_data[1] = id_c;
        can_data[2] = id_b;
        can_data[3] = id_a;
        can_data[4] = data_d;
        can_data[5] = data_c;
        can_data[6] = data_b;
        can_data[7] = data_a;

        can_transmit();

        BUZZER = HIGH;
        for (unsigned int delay = 10000; delay--;);
        BUZZER = LOW;

        reset_client_flags();
    }

    switch (field_flag) {
        case 1:
            ssd[3] = digit_dot[data_a];
            ssd[2] = digit[data_b];
            ssd[1] = digit[data_c];
            ssd[0] = digit[data_d];
            break;
        case 2:
            ssd[3] = digit[data_a];
            ssd[2] = digit_dot[data_b];
            ssd[1] = digit[data_c];
            ssd[0] = digit[data_d];
            break;
        case 3:
            ssd[3] = digit[data_a];
            ssd[2] = digit[data_b];
            ssd[1] = digit_dot[data_c];
            ssd[0] = digit[data_d];
            break;
        case 4:
            ssd[3] = digit[data_a];
            ssd[2] = digit[data_b];
            ssd[1] = digit[data_c];
            ssd[0] = digit_dot[data_d];
            break;
    }

}

void reset_client_flags(void) {

    client_flag = 0;
    client_option = 0;
    field_flag = 1;
    key_detected = 0;

}

void get_data_from_eeprom(void) {

    id_d = read_internal_eeprom(0x01);
    id_c = read_internal_eeprom(0x02);
    id_b = read_internal_eeprom(0x03);
    id_a = read_internal_eeprom(0x04);
    data_a = read_internal_eeprom(0x06);
    data_b = read_internal_eeprom(0x07);
    data_c = read_internal_eeprom(0x08);
    data_d = read_internal_eeprom(0x09);

}