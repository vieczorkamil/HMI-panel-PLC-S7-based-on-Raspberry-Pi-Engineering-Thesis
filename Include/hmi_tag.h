#ifndef HMI_TAG_H
#define HMI_TAG_H

#include <cstdint>

enum tag_type
{
    INPUT,
    OUTPUT,
    MARKER,
    DB
};
/*
template <typename T>
struct HMI_tag{
    tag_type TYPE;
    int BYTE_DBNUMBER = 0;
    int BIT_OFFSET = 0;
    T VALUE = static_cast<T>(0.0);
};
*/
template <typename T>
struct HMI_tag
{
    tag_type TYPE;
    double ADDRESS = 0.0;
    int DB_NUMBER = 0;
    T VALUE = static_cast<T>(0.0);
};

/* INPUTS */
extern struct HMI_tag<bool> I0_0;
extern struct HMI_tag<bool> I0_1;
extern struct HMI_tag<bool> I0_2;
extern struct HMI_tag<bool> I0_3;
extern struct HMI_tag<bool> I0_4;
extern struct HMI_tag<bool> I0_5;
extern struct HMI_tag<bool> I0_6;
extern struct HMI_tag<bool> I0_7;

extern struct HMI_tag<int8_t> IB1;
extern struct HMI_tag<uint8_t> IB2;
extern struct HMI_tag<int16_t> IW3;
extern struct HMI_tag<uint16_t> IW5;
extern struct HMI_tag<float> ID7;
extern struct HMI_tag<float> ID11;

/* OUTPUTS */
extern struct HMI_tag<bool> Q0_0;
extern struct HMI_tag<bool> Q0_1;
extern struct HMI_tag<bool> Q0_2;
extern struct HMI_tag<bool> Q0_3;
extern struct HMI_tag<bool> Q0_4;
extern struct HMI_tag<bool> Q0_5;
extern struct HMI_tag<bool> Q0_6;
extern struct HMI_tag<bool> Q0_7;

extern struct HMI_tag<int8_t> QB1;
extern struct HMI_tag<uint8_t> QB2;
extern struct HMI_tag<int16_t> QW3;
extern struct HMI_tag<uint16_t> QW5;
extern struct HMI_tag<float> QD7;
extern struct HMI_tag<float> QD11;

/* DB3 */
extern struct HMI_tag<bool> START;
extern struct HMI_tag<bool> SENSOR1;
extern struct HMI_tag<bool> SENSOR2;
extern struct HMI_tag<bool> SENSOR3;
extern struct HMI_tag<bool> MIXER;
extern struct HMI_tag<bool> HEATER;
extern struct HMI_tag<bool> VALVE1;
extern struct HMI_tag<bool> VALVE2;
extern struct HMI_tag<bool> VALVE3;
extern struct HMI_tag<bool> VALVE4;
extern struct HMI_tag<float> TEMPERATURE;
extern struct HMI_tag<float> LEVEL1;
extern struct HMI_tag<float> LEVEL2;

extern struct HMI_tag<float> LEVEL1SETPOINT;
extern struct HMI_tag<float> LEVEL2SETPOINT;
extern struct HMI_tag<float> TEMPERATURESETPOINT;
//extern struct HMI_tag<int> TIMESETPOINT;

extern struct HMI_tag<bool> STOP;
extern struct HMI_tag<bool> RESET;
#endif // HMI_TAG_H
