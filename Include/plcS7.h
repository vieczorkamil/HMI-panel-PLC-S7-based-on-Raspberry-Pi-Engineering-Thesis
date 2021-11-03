#ifndef _PLCS7_H
#define _PLCS7_H

#include "snap7.h"

#define bit bool

/* SIZE TO READ IN BYTES */
#define SINT_SIZE 1
#define USINT_SIZE 1
#define INT_SIZE 2
#define UINT_SIZE 2
#define DINT_SIZE 4
#define UDINT_SIZE 4
#define REAL_SIZE 4

class PlcS7
{

public:
    S7Object Client;
    TS7CpuInfo plcInfo;
    /*-------------------------------------------*/
    
    PlcS7(const char *ip, int rack, int slot);
    ~PlcS7();
    int disconnect();
    int connect();
    int isConnect();
    int getPlcInfo();
    int getPlcMode();
    int stopPlc();

    /* READ INPUT SIGNALS/MEMORY */
    bool readI(int startAdrressByte, int startAdrressBit);
    int8_t readIB_SInt(int startAdrressByte);
    uint8_t readIB_USInt(int startAdrressByte);
    int16_t readIW_Int(int startAdrressByte);
    uint16_t readIW_UInt(int startAdrressByte);
    int32_t readID_DInt(int startAdrressByte);
    uint32_t readID_UDInt(int startAdrressByte);
    float readID_Real(int startAdrressByte);

    /* READ OUTPUT SIGNALS/MEMORY */
    bool readQ(int startAdrressByte, int startAdrressBit);
    int8_t readQB_SInt(int startAdrressByte);
    uint8_t readQB_USInt(int startAdrressByte);
    int16_t readQW_Int(int startAdrressByte);
    uint16_t readQW_UInt(int startAdrressByte);
    int32_t readQD_DInt(int startAdrressByte);
    uint32_t readQD_UDInt(int startAdrressByte);
    float readQD_Real(int startAdrressByte);

    /* READ MARKER MEMORY */
    bool readM(int startAdrressByte, int startAdrressBit);
    int8_t readMB_SInt(int startAdrressByte);
    uint8_t readMB_USInt(int startAdrressByte);
    int16_t readMW_Int(int startAdrressByte);
    uint16_t readMW_UInt(int startAdrressByte);
    int32_t readMD_DInt(int startAdrressByte);
    uint32_t readMD_UDInt(int startAdrressByte);
    float readMD_Real(int startAdrressByte);

    /* READ DATABLOCK */
    bool readDataBlock_Bit(int DBNumber, int offsetByte, int offsetBit);
    int8_t readDataBlock_SInt(int DBNumber, int offset);
    uint8_t readDataBlock_USInt(int DBNumber, int offset);
    int16_t readDataBlock_Int(int DBNumber, int offset);
    uint16_t readDataBlock_UInt(int DBNumber, int offset);
    int32_t readDataBlock_DInt(int DBNumber, int offset);
    uint32_t readDataBlock_UDInt(int DBNumber, int offset);
    float readDataBlock_Real(int DBNumber, int offset);

    /* WRITE INPUT SIGNALS/MEMORY */
    int writeI(bool value, int startAdrressByte, int startAdrressBit);
    int writeIB_SInt(int8_t value, int startAdrressByte);
    int writeIB_USInt(uint8_t value, int startAdrressByte);
    int writeIW_Int(int16_t value, int startAdrressByte);
    int writeIW_UInt(uint16_t value, int startAdrressByte);
    int writeID_DInt(int32_t value, int startAdrressByte);
    int writeID_UDInt(uint32_t value, int startAdrressByte);
    int writeID_Real(float value, int startAdrressByte);

    /* WRITE OUTPUT SIGNALS/MEMORY */
    int writeQ(bool value, int startAdrressByte, int startAdrressBit);
    int writeQB_SInt(int8_t value, int startAdrressByte);
    int writeQB_USInt(uint8_t value, int startAdrressByte);
    int writeQW_Int(int16_t value, int startAdrressByte);
    int writeQW_UInt(uint16_t value, int startAdrressByte);
    int writeQD_DInt(int32_t value, int startAdrressByte);
    int writeQD_UDInt(uint32_t value, int startAdrressByte);
    int writeQD_Real(float value, int startAdrressByte);

    /* WRITE MARKER MEMORY */
    int writeM(bool value, int startAdrressByte, int startAdrressBit);
    int writeMB_SInt(int8_t value, int startAdrressByte);
    int writeMB_USInt(uint8_t value, int startAdrressByte);
    int writeMW_Int(int16_t value, int startAdrressByte);
    int writeMW_UInt(uint16_t value, int startAdrressByte);
    int writeMD_DInt(int32_t value, int startAdrressByte);
    int writeMD_UDInt(uint32_t value, int startAdrressByte);
    int writeMD_Real(float value, int startAdrressByte);

    /* WRITE DATABLOCK */
    int writeDataBlock_Bit(bool value, int DBNumber, int offsetByte, int offsetBit);
    int writeDataBlock_SInt(int8_t value, int DBNumber, int offset);
    int writeDataBlock_USInt(uint8_t value, int DBNumber, int offset);
    int writeDataBlock_Int(int16_t value, int DBNumber, int offset);
    int writeDataBlock_UInt(uint16_t value, int DBNumber, int offset);
    int writeDataBlock_DInt(int32_t value, int DBNumber, int offset);
    int writeDataBlock_UDInt(uint32_t value, int DBNumber, int offset);
    int writeDataBlock_Real(float value, int DBNumber, int offset);

protected:
private:
    const char *ip;
    int rack;
    int slot;
    /*-------------------------------------------*/
    uint8_t getByte(byte *buffer);
    uint16_t getWord(byte *buffer);
    uint32_t getDWord(byte *buffer);
    int8_t getSInt(byte *buffer);
    uint8_t getUSInt(byte *buffer);
    int16_t getInt(byte *buffer);
    uint16_t getUInt(byte *buffer);
    int32_t getDInt(byte *buffer);
    uint32_t getUDInt(byte *buffer);
    float getReal(byte *buffer);
    /*-------------------------------------------*/
    void setByte(byte value, byte *buffer);
    void setSInt(int8_t value, byte *buffer);
    void setUSInt(uint8_t value, byte *buffer);
    void setInt(int16_t value, byte *buffer);
    void setUInt(uint16_t value, byte *buffer);
    void setDInt(int32_t value, byte *buffer);
    void setUDInt(uint32_t value, byte *buffer);
    void setReal(float value, byte *buffer);
    /*-------------------------------------------*/
    uint8_t getUint8(byte *buffer);
    uint16_t getUint16(byte *buffer);
    uint32_t getUint32(byte *buffer);

};

#endif
