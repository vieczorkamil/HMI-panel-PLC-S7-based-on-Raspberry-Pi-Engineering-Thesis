#include "hmi_tag.h"

struct HMI_tag<int> lampka{OUTPUT,2};

/* INPUT */
struct HMI_tag<bool> I0_0{INPUT,0,0,0};
struct HMI_tag<bool> I0_1{INPUT,0,1,0};
struct HMI_tag<bool> I0_2{INPUT,0,2,0};
struct HMI_tag<bool> I0_3{INPUT,0,3,0};
struct HMI_tag<bool> I0_4{INPUT,0,4,0};
struct HMI_tag<bool> I0_5{INPUT,0,5,0};
struct HMI_tag<bool> I0_6{INPUT,0,6,0};
struct HMI_tag<bool> I0_7{INPUT,0,7,0};

struct HMI_tag<int8_t> IB1{INPUT,1,0,0};
struct HMI_tag<uint8_t> IB2{INPUT,2,0,0};
struct HMI_tag<int16_t> IW3{INPUT,3,0,0};
struct HMI_tag<uint16_t> IW5{INPUT,5,0,0};
struct HMI_tag<float> ID7{INPUT,7,0,0.0};
struct HMI_tag<float> ID11{INPUT,11,0,0.0};

/* OUTPUT */
struct HMI_tag<bool> Q0_0{OUTPUT,0,0,0};
struct HMI_tag<bool> Q0_1{OUTPUT,0,1,0};
struct HMI_tag<bool> Q0_2{OUTPUT,0,2,0};
struct HMI_tag<bool> Q0_3{OUTPUT,0,3,0};
struct HMI_tag<bool> Q0_4{OUTPUT,0,4,0};
struct HMI_tag<bool> Q0_5{OUTPUT,0,5,0};
struct HMI_tag<bool> Q0_6{OUTPUT,0,6,0};
struct HMI_tag<bool> Q0_7{OUTPUT,0,7,0};

struct HMI_tag<int8_t> QB1{OUTPUT,1,0,0};
struct HMI_tag<uint8_t> QB2{OUTPUT,2,0,0};
struct HMI_tag<int16_t> QW3{OUTPUT,3,0,0};
struct HMI_tag<uint16_t> QW5{OUTPUT,5,0,0};
struct HMI_tag<float> QD7{OUTPUT,7,0,0.0};
struct HMI_tag<float> QD11{OUTPUT,11,0,0.0};
