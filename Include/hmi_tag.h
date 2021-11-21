#ifndef HMI_TAG_H
#define HMI_TAG_H

#include <cstdint>

enum tag_type {INPUT, OUTPUT, MARKER, DB};

template <typename T>
struct HMI_tag{
    tag_type TYPE;
    int BYTE_DBNUMBER;
    int BIT_OFFSET;
    T VALUE;
};

extern struct HMI_tag<int> lampka;

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

#endif // HMI_TAG_H
