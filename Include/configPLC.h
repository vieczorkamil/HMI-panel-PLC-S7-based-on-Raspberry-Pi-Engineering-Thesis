#ifndef CONFIGPLC_H
#define CONFIGPLC_H

#include <QString>

/* connection parameters */
/* Jak chcę zmieniać to extern jak ie to const */
//extern QString PLC_IP = "192.168.137.10";
//extern int PLC_RACK = 0;
//extern int PLC_SLOT = 1;
extern QString PLC_IP;
extern int PLC_RACK;
extern int PLC_SLOT;

extern double value;

typedef struct{
    char MODULE_TYPE_NAME[33];
    char SERIAL_NUMBER[25];
    char AS_NAME[25];
    char COPYRIGHT[27];
    char MODULE_NAME[25];
} infoPLC_t;

typedef struct{
    bool I0_0;
    bool I0_1;
    bool I0_2;
    bool I0_3;
    bool I0_4;
    bool I0_5;
    bool I0_6;
    bool I0_7;

    int8_t IB1;
    uint8_t IB2;
    int16_t IW3;
    uint16_t IW5;
    float ID7;
    float ID11;
} inputPLC_t;

extern inputPLC_t inputPLC;
extern infoPLC_t infoPLC;

#endif // CONFIGPLC_H
