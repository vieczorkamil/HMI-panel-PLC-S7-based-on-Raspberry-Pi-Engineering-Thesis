#include "hmi_tag.h"

/* INPUT */
struct HMI_tag<bool> I0_0{INPUT,0.0};
struct HMI_tag<bool> I0_1{INPUT,0.1};
struct HMI_tag<bool> I0_2{INPUT,0.2};
struct HMI_tag<bool> I0_3{INPUT,0.3};
struct HMI_tag<bool> I0_4{INPUT,0.4};
struct HMI_tag<bool> I0_5{INPUT,0.5};
struct HMI_tag<bool> I0_6{INPUT,0.6};
struct HMI_tag<bool> I0_7{INPUT,0.7};

struct HMI_tag<int8_t> IB1{INPUT,1};
struct HMI_tag<uint8_t> IB2{INPUT,2};
struct HMI_tag<int16_t> IW3{INPUT,3};
struct HMI_tag<uint16_t> IW5{INPUT,5};
struct HMI_tag<float> ID7{INPUT,7};
struct HMI_tag<float> ID11{INPUT,11};

/* OUTPUT */
struct HMI_tag<bool> Q0_0{OUTPUT,0.0};
struct HMI_tag<bool> Q0_1{OUTPUT,0.1};
struct HMI_tag<bool> Q0_2{OUTPUT,0.2};
struct HMI_tag<bool> Q0_3{OUTPUT,0.3};
struct HMI_tag<bool> Q0_4{OUTPUT,0.4};
struct HMI_tag<bool> Q0_5{OUTPUT,0.5};
struct HMI_tag<bool> Q0_6{OUTPUT,0.6};
struct HMI_tag<bool> Q0_7{OUTPUT,0.7};

struct HMI_tag<int8_t> QB1{OUTPUT,1};
struct HMI_tag<uint8_t> QB2{OUTPUT,2};
struct HMI_tag<int16_t> QW3{OUTPUT,3};
struct HMI_tag<uint16_t> QW5{OUTPUT,5};
struct HMI_tag<float> QD7{OUTPUT,7};
struct HMI_tag<float> QD11{OUTPUT,11};

/* DB3 */
struct HMI_tag<bool> START{DB, 0.0, 3};
struct HMI_tag<bool> SENSOR1{DB, 0.1, 3};
struct HMI_tag<bool> SENSOR2{DB, 0.2, 3};
struct HMI_tag<bool> SENSOR3{DB, 0.3, 3};
struct HMI_tag<bool> MIXER{DB, 0.4, 3};
struct HMI_tag<bool> HEATER{DB, 0.5, 3};
struct HMI_tag<bool> VALVE1{DB, 0.6, 3};
struct HMI_tag<bool> VALVE2{DB, 0.7, 3};
struct HMI_tag<bool> VALVE3{DB, 1.0, 3};
struct HMI_tag<bool> VALVE4{DB, 1.1, 3};
struct HMI_tag<float> TEMPERATURE{DB, 2, 3};
struct HMI_tag<float> LEVEL1{DB, 6, 3};
struct HMI_tag<float> LEVEL2{DB, 10, 3};

struct HMI_tag<float> LEVEL1SETPOINT{DB, 14, 3};
struct HMI_tag<float> LEVEL2SETPOINT{DB, 18, 3};
struct HMI_tag<float> TEMPERATURESETPOINT{DB, 22, 3};
//struct HMI_tag<float> TIMESETPOINT{DB, 26, 3};

struct HMI_tag<bool> STOP{DB, 30.0, 3};
struct HMI_tag<bool> RESET{DB, 30.1, 3};
