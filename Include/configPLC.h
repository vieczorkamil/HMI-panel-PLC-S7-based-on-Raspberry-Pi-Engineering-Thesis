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

typedef struct{
    char MODULE_TYPE_NAME[33];
    char SERIAL_NUMBER[25];
    char AS_NAME[25];
    char COPYRIGHT[27];
    char MODULE_NAME[25];
    bool IS_CONNECTED;
} infoPLC_t;

extern infoPLC_t infoPLC;

#endif // CONFIGPLC_H
