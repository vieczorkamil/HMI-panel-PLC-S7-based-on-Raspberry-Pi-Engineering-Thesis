/*
 * PlcS7 - wrapper class for snap7 lib
 *
 * Copyright (C) 2021 Kamil Wieczorek <kamiwie749@student.polsl.pl>
*/

#include "plcS7.h"

#include <cmath>
#include <iostream>

#define DEBUG(msg) std::cout << msg << std::endl

PlcS7::PlcS7()
{
    DEBUG("Cli_Create()");
    Client = Cli_Create();
    isPlcConnect = false;
}

PlcS7::PlcS7(const char *ip, int rack, int slot)
{
    DEBUG("Cli_Create()");
    Client = Cli_Create();
    isPlcConnect = false;
    this->ip = ip;
    this->rack = rack;
    this->slot = slot;
}

PlcS7::~PlcS7()
{
    DEBUG("Cli_Destroy()");
    Cli_Destroy(&Client);
}

void PlcS7::setParms(const char *ip, int rack, int slot)
{
    this->ip = ip;
    this->rack = rack;
    this->slot = slot;
}

int PlcS7::disconnect()
{
    DEBUG("Cli_Disconnect()");
    if (!Cli_Connect(Client))
    {
        DEBUG("ACTIVE CONNECTION - TRY TO DISCONNECT");
        int err = Cli_Disconnect(Client);
        if (err == 0)
        {
            isPlcConnect = false;
        }
        else
        {
            isPlcConnect = true;
        }
        return err;
    }
    else
    {
        isPlcConnect = false;
        DEBUG("NOT ACTIVE CONNECTION");
        return Cli_Connect(Client);
    }
}

int PlcS7::connect()
{
    DEBUG("Cli_Connect()");

    if (Cli_Connect(Client))
    {
        int err = Cli_ConnectTo(Client, ip, rack, slot);
        if (err == 0)
        {
            isPlcConnect = true;
        }
        else
        {
            isPlcConnect = false;
        }
        return err;
    }
    else
    {
        DEBUG("ALREADY CONNECTED");
        isPlcConnect = true;
        return Cli_Connect(Client);
    }
}

bool PlcS7::isConnect()
{
    /* Return true if PLC is connected correctly and false if not */
    return isPlcConnect;
}

int PlcS7::getPlcInfo()
{
    return Cli_GetCpuInfo(Client, &plcInfo);
}

int PlcS7::getPlcMode()
{
    int status;
    int err = Cli_GetPlcStatus(Client, &status);
    if (!err)
    {
        if (status == 0x08)
            return 1; // The CPU is running
        else if (status == 0x04)
            return 0; // The CPU is stopped
        else
            return -1; // The CPU status is unknown
    }
    else
        return err;
}

int PlcS7::stopPlc()
{
    /* MAY NOT WORK IN SIMULATION */
    return Cli_PlcStop(Client);
}

/* READ INPUT SIGNALS/MEMORY */

bool PlcS7::readI(int startAdrressByte, int startAdrressBit)
{
    bit out;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_ReadArea(Client, S7AreaPE, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
        return false;
    }
    else
        return out;
}

bool PlcS7::readI(HMI_tag<bool> *tag)
{
    int bit = 10 * (tag->ADDRESS - stattic_cast<int>(tag->ADDRESS));
    if (bit < 0 || bit > 7)
    {
        DEBUG("Bit address error");
        return false;
    }
    else
    {
        return readI(static_cast<int>(tag->ADDRESS), bit);
    }
}

int8_t PlcS7::readIB_SInt(int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPE, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getSInt(&buffer);
    }
}

int8_t PlcS7::readIB_SInt(HMI_tag<int8_t> *tag)
{
    return readIB_SInt(static_cast<int>(tag->ADDRESS));
}

uint8_t PlcS7::readIB_USInt(int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPE, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUSInt(&buffer);
    }
}

uint8_t PlcS7::readIB_USInt(HMI_tag<uint8_t> *tag)
{
    return readIB_USInt(static_cast<int>(tag->ADDRESS));
}

int16_t PlcS7::readIW_Int(int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPE, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getInt(buffer);
    }
}

int16_t PlcS7::readIW_Int(HMI_tag<int16_t> *tag)
{
    return readIW_Int(static_cast<int>(tag->ADDRESS));
}

uint16_t PlcS7::readIW_UInt(int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPE, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUInt(buffer);
    }
}

uint16_t PlcS7::readIW_UInt(HMI_tag<uint16_t> *tag)
{
    return readIW_UInt(static_cast<int>(tag->ADDRESS));
}

int32_t PlcS7::readID_DInt(int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPE, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getDInt(buffer);
    }
}

int32_t PlcS7::readID_DInt(HMI_tag<int32_t> *tag)
{
    return readID_DInt(static_cast<int>(tag->ADDRESS));
}

uint32_t PlcS7::readID_UDInt(int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPE, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUDInt(buffer);
    }
}

uint32_t PlcS7::readID_UDInt(HMI_tag<uint32_t> *tag)
{
    return readID_UDInt(static_cast<int>(tag->ADDRESS));
}

float PlcS7::readID_Real(int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPE, 0, Start, 1, S7WLReal, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0.0;
    }
    else
    {
        return getReal(buffer);
    }
}

float PlcS7::readID_Real(HMI_tag<float> *tag)
{
    return readID_Real(static_cast<int>(tag->ADDRESS));
}

/* READ OUTPUT SIGNALS/MEMORY */

bool PlcS7::readQ(int startAdrressByte, int startAdrressBit)
{
    bit out;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_ReadArea(Client, S7AreaPA, 0, Start, 1, S7WLBit, &out);
    /* if Cli_ReadArea catch error PlcS7::readQ will return allways false */
    if (err)
    {
        DEBUG("error : " << err);
        return false;
    }
    else
        return out;
}

bool PlcS7::readQ(HMI_tag<bool> *tag)
{
    int bit = 10 * (tag->ADDRESS - static_cast<int>(tag->ADDRESS);
    if(bit < 0 || bit > 7)
    {
        DEBUG("Bit address error");
        return false;
    }
    else
    {
        return readQ(static_cast<int>(tag->ADDRESS), bit);
    }
}

int8_t PlcS7::readQB_SInt(int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPA, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getSInt(&buffer);
    }
}

int8_t PlcS7::readQB_SInt(HMI_tag<int8_t> *tag)
{
    return readQB_SInt(static_cast<int>(tag->ADDRESS));
}

uint8_t PlcS7::readQB_USInt(int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPA, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUSInt(&buffer);
    }
}

uint8_t PlcS7::readQB_USInt(HMI_tag<uint8_t> *tag)
{
    return readQB_USInt(static_cast<int>(tag->ADDRESS));
}

int16_t PlcS7::readQW_Int(int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPA, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getInt(buffer);
    }
}

int16_t PlcS7::readQW_Int(HMI_tag<int16_t> *tag)
{
    return readQW_Int(static_cast<int>(tag->ADDRESS));
}

uint16_t PlcS7::readQW_UInt(int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPA, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUInt(buffer);
    }
}

uint16_t PlcS7::readQW_UInt(HMI_tag<uint16_t> *tag)
{
    return readQW_UInt(static_cast<int>(tag->ADDRESS));
}

int32_t PlcS7::readQD_DInt(int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPA, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getDInt(buffer);
    }
}

int32_t PlcS7::readQD_DInt(HMI_tag<int32_t> *tag)
{
    return readQD_DInt(static_cast<int>(tag->ADDRESS));
}

uint32_t PlcS7::readQD_UDInt(int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPA, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUDInt(buffer);
    }
}

uint32_t PlcS7::readQD_UDInt(HMI_tag<uint32_t> *tag)
{
    return readQD_UDInt(static_cast<int>(tag->ADDRESS));
}

float PlcS7::readQD_Real(int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaPA, 0, Start, 1, S7WLReal, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0.0;
    }
    else
    {
        return getReal(buffer);
    }
}

float PlcS7::readQD_Real(HMI_tag<float> *tag)
{
    return readQD_Real(static_cast<int>(tag->ADDRESS));
}

/* READ MARKER MEMORY */

bool PlcS7::readM(int startAdrressByte, int startAdrressBit)
{
    bit out;
    /* if Cli_ReadArea catch error PlcS7::readQ will return allways false */
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_ReadArea(Client, S7AreaMK, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
        return false;
    }
    else
        return out;
}

bool PlcS7::readM(HMI_tag<bool> *tag)
{
    int bit = 10 * (tag->ADDRESS - static_cast<int>(tag->ADDRESS));
    if (bit < 0 || bit > 7)
    {
        DEBUG("Bit address error");
        return false;
    }
    else
    {
        return readM(static_cast<int>(tag->ADDRESS), bit);
    }
}

int8_t PlcS7::readMB_SInt(int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaMK, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getSInt(&buffer);
    }
}

int8_t PlcS7::readMB_SInt(HMI_tag<int8_t> *tag)
{
    return readMB_SInt(static_cast<int>(tag->ADDRESS));
}

uint8_t PlcS7::readMB_USInt(int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaMK, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUSInt(&buffer);
    }
}

uint8_t PlcS7::readMB_USInt(HMI_tag<uint8_t> *tag)
{
    return readMB_USInt(static_cast<int>(tag->ADDRESS));
}

int16_t PlcS7::readMW_Int(int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaMK, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getInt(buffer);
    }
}

int16_t PlcS7::readMW_Int(HMI_tag<int16_t> *tag)
{
    return readMW_Int(static_cast<int>(tag->ADDRESS));
}

uint16_t PlcS7::readMW_UInt(int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaMK, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUInt(buffer);
    }
}

uint16_t PlcS7::readMW_UInt(HMI_tag<uint16_t> *tag)
{
    return readMW_UInt(static_cast<int>(tag->ADDRESS));
}

int32_t PlcS7::readMD_DInt(int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaMK, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getDInt(buffer);
    }
}

int32_t PlcS7::readMD_DInt(HMI_tag<int32_t> *tag)
{
    return readMD_DInt(static_cast<int>(tag->ADDRESS));
}

uint32_t PlcS7::readMD_UDInt(int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaMK, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUDInt(buffer);
    }
}

uint32_t PlcS7::readMD_UDInt(HMI_tag<uint32_t> *tag)
{
    return readMD_UDInt(static_cast<int>(tag->ADDRESS));
}

float PlcS7::readMD_Real(int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    int err = Cli_ReadArea(Client, S7AreaMK, 0, Start, 1, S7WLReal, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0.0;
    }
    else
    {
        return getReal(buffer);
    }
}

float PlcS7::readMD_Real(HMI_tag<float> *tag)
{
    return readMD_Real(static_cast<int>(tag->ADDRESS));
}

/* READ DATABLOCK */
bool PlcS7::readDataBlock_Bit(int DBNumber, int offsetByte, int offsetBit)
{
    bool out;
    int offset = offsetByte * 8 + offsetBit;
    Cli_ReadArea(Client, S7AreaDB, DBNumber, offset, 1, S7WLBit, &out);
    return out;
}

bool PlcS7::readDataBlock_Bit(HMI_tag<bool> *tag)
{
    int bit = 10 * (tag->ADDRESS - <int>(tag->ADDRESS));
    if (bit < 0 || bit > 7)
    {
        DEBUG("Bit address error");
        return false;
    }
    else
    {
        return readDataBlock_Bit(tag->DB_NUMBER, static_cast<int>(tag->ADDRESS), bit);
    }
}

int8_t PlcS7::readDataBlock_SInt(int DBNumber, int offset)
{
    byte buffer;
    int err = Cli_DBRead(Client, DBNumber, offset, SINT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getSInt(&buffer);
    }
}

int8_t PlcS7::readDataBlock_SInt(HMI_tag<int8_t> *tag)
{
    return readDataBlock_SInt(tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

uint8_t PlcS7::readDataBlock_USInt(int DBNumber, int offset)
{
    byte buffer;
    int err = Cli_DBRead(Client, DBNumber, offset, USINT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUSInt(&buffer);
    }
}

uint8_t PlcS7::readDataBlock_USInt(HMI_tag<uint8_t> *tag)
{
    return readDataBlock_USInt(tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

int16_t PlcS7::readDataBlock_Int(int DBNumber, int offset)
{
    byte buffer[2];
    int err = Cli_DBRead(Client, DBNumber, offset, INT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getInt(buffer);
    }
}

int16_t PlcS7::readDataBlock_Int(HMI_tag<int16_t> *tag)
{
    return readDataBlock_Int(tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

uint16_t PlcS7::readDataBlock_UInt(int DBNumber, int offset)
{
    byte buffer[2];
    int err = Cli_DBRead(Client, DBNumber, offset, UINT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUInt(buffer);
    }
}

uint16_t PlcS7::readDataBlock_UInt(HMI_tag<uint16_t> *tag)
{
    return readDataBlock_UInt(tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

int32_t PlcS7::readDataBlock_DInt(int DBNumber, int offset)
{
    byte buffer[4];
    int err = Cli_DBRead(Client, DBNumber, offset, DINT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getDInt(buffer);
    }
}

int32_t PlcS7::readDataBlock_DInt(HMI_tag<int32_t> *tag)
{
    return readDataBlock_DInt(tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

uint32_t PlcS7::readDataBlock_UDInt(int DBNumber, int offset)
{
    byte buffer[4];
    int err = Cli_DBRead(Client, DBNumber, offset, UDINT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0;
    }
    else
    {
        return getUDInt(buffer);
    }
}

uint32_t PlcS7::readDataBlock_UDInt(HMI_tag<uint32_t> *tag)
{
    return readDataBlock_UDInt(tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

float PlcS7::readDataBlock_Real(int DBNumber, int offset)
{
    byte buffer[4];
    int err = Cli_DBRead(Client, DBNumber, offset, REAL_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
        return 0.0;
    }
    else
    {
        return getReal(buffer);
    }
}

float PlcS7::readDataBlock_Real(HMI_tag<float> *tag)
{
    return readDataBlock_Real(tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

/* READ HMI_TAG */
bool PlcS7::readValue(HMI_tag<bool> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return readI(tag);
    case OUTPUT:
        return readQ(tag);
    case MARKER:
        return readM(tag);
    case DB:
        return readDataBlock_Bit(tag);
    default:
        return false;
    }
}

int8_t PlcS7::readValue(HMI_tag<int8_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return readIB_SInt(tag);
    case OUTPUT:
        return readQB_SInt(tag);
    case MARKER:
        return readMB_SInt(tag);
    case DB:
        return readDataBlock_SInt(tag);
    default:
        return 0;
    }
}

uint8_t PlcS7::readValue(HMI_tag<uint8_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return readIB_USInt(tag);
    case OUTPUT:
        return readQB_USInt(tag);
    case MARKER:
        return readMB_USInt(tag);
    case DB:
        return readDataBlock_USInt(tag);
    default:
        return 0;
    }
}

int16_t PlcS7::readValue(HMI_tag<int16_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return readIW_Int(tag);
    case OUTPUT:
        return readQW_Int(tag);
    case MARKER:
        return readMW_Int(tag);
    case DB:
        return readDataBlock_Int(tag);
    default:
        return 0;
    }
}

uint16_t PlcS7::readValue(HMI_tag<uint16_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return readIW_UInt(tag);
    case OUTPUT:
        return readQW_UInt(tag);
    case MARKER:
        return readMW_UInt(tag);
    case DB:
        return readDataBlock_UInt(tag);
    default:
        return 0;
    }
}

int32_t PlcS7::readValue(HMI_tag<int32_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return readID_DInt(tag);
    case OUTPUT:
        return readQD_DInt(tag);
    case MARKER:
        return readMD_DInt(tag);
    case DB:
        return readDataBlock_DInt(tag);
    default:
        return 0;
    }
}

uint32_t PlcS7::readValue(HMI_tag<uint32_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return readID_UDInt(tag);
    case OUTPUT:
        return readQD_UDInt(tag);
    case MARKER:
        return readMD_UDInt(tag);
    case DB:
        return readDataBlock_UDInt(tag);
    default:
        return 0;
    }
}

float PlcS7::readValue(HMI_tag<float> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return readID_Real(tag);
    case OUTPUT:
        return readQD_Real(tag);
    case MARKER:
        return readMD_Real(tag);
    case DB:
        return readDataBlock_Real(tag);
    default:
        return 0.0;
    }
}

/* WRITE INPUT SIGNALS/MEMORY */

int PlcS7::writeI(bool value, int startAdrressByte, int startAdrressBit)
{
    bit out = value;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeI(HMI_tag<bool> *tag)
{
    bit = 10 * (tag->ADDRESS - static_cast<int>(tag->ADDRESS));
    if (bit < 0 || bit > 7)
    {
        DEBUG("Bit address error");
        return false;
    }
    else
    {
        return writeI(tag->VALUE, static_cast<int>(tag->ADDRESS), bit);
    }
}

int PlcS7::writeIB_SInt(int8_t value, int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    setSInt(value, &buffer);
    int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeIB_SInt(HMI_tag<int8_t> *tag)
{
    return writeIB_SInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeIB_USInt(uint8_t value, int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    setUSInt(value, &buffer);
    int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeIB_USInt(HMI_tag<uint8_t> *tag)
{
    return writeIB_USInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeIW_Int(int16_t value, int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    setInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeIW_Int(HMI_tag<int16_t> *tag)
{
    return writeIW_Int(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeIW_UInt(uint16_t value, int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    setUInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeIW_UInt(HMI_tag<uint16_t> *tag)
{
    return writeIW_UInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeID_DInt(int32_t value, int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    setDInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeID_DInt(HMI_tag<int32_t> *tag)
{
    return writeID_DInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeID_UDInt(uint32_t value, int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    setUDInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeID_UDInt(HMI_tag<uint32_t> *tag)
{
    return writeID_UDInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeID_Real(float value, int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    setReal(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLReal, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeID_Real(HMI_tag<float> *tag)
{
    return writeID_Real(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

/* WRITE OUTPUT SIGNALS/MEMORY */

int PlcS7::writeQ(bool value, int startAdrressByte, int startAdrressBit)
{
    bit out = value;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeQ(HMI_tag<bool> *tag)
{
    int bit = 10 * (tag->ADDRESS - static_cast<int>(tag->ADDRESS));
    if (bit < 0 || bit > 7)
    {
        DEBUG("Bit address error");
        return false;
    }
    else
    {
        return writeQ(tag->VALUE, static_cast<int>(tag->ADDRESS), bit);
    }
}

int PlcS7::writeQB_SInt(int8_t value, int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    setSInt(value, &buffer);
    int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeQB_SInt(HMI_tag<int8_t> *tag)
{
    return writeQB_SInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeQB_USInt(uint8_t value, int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    setUSInt(value, &buffer);
    int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeQB_USInt(HMI_tag<uint8_t> *tag)
{
    return writeQB_USInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeQW_Int(int16_t value, int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    setInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeQW_Int(HMI_tag<int16_t> *tag)
{
    return writeQW_Int(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeQW_UInt(uint16_t value, int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    setUInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeQW_UInt(HMI_tag<uint16_t> *tag)
{
    return writeQW_UInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeQD_DInt(int32_t value, int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    setDInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeQD_DInt(HMI_tag<int32_t> *tag)
{
    return writeQD_DInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeQD_UDInt(uint32_t value, int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    setUDInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeQD_UDInt(HMI_tag<uint32_t> *tag)
{
    return writeQD_UDInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeQD_Real(float value, int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    setReal(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLReal, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeQD_Real(HMI_tag<float> *tag)
{
    return writeQD_Real(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

/* WRITE MARKER MEMORY */

int PlcS7::writeM(bool value, int startAdrressByte, int startAdrressBit)
{
    bit out = value;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeM(HMI_tag<bool> *tag)
{
    int bit = 10 * (tag->ADDRESS - static_cast<int>(tag->ADDRESS));
    if (bit < 0 || bit > 7)
    {
        DEBUG("Bit address error");
        return false;
    }
    else
    {
        return writeM(tag->VALUE, static_cast<int>(tag->ADDRESS), bit);
    }
}

int PlcS7::writeMB_SInt(int8_t value, int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    setSInt(value, &buffer);
    int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeMB_SInt(HMI_tag<int8_t> *tag)
{
    return writeMB_SInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeMB_USInt(uint8_t value, int startAdrressByte)
{
    byte buffer;
    int Start = startAdrressByte;
    setUSInt(value, &buffer);
    int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLByte, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeMB_USInt(HMI_tag<uint8_t> *tag)
{
    return writeMB_USInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeMW_Int(int16_t value, int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    setInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeMW_Int(HMI_tag<int16_t> *tag)
{
    return writeMW_Int(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeMW_UInt(uint16_t value, int startAdrressByte)
{
    byte buffer[2];
    int Start = startAdrressByte;
    setUInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeMW_UInt(HMI_tag<uint16_t> *tag)
{
    return writeMW_UInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeMD_DInt(int32_t value, int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    setDInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeMD_DInt(HMI_tag<int32_t> *tag)
{
    return writeMD_DInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeMD_UDInt(uint32_t value, int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    setUDInt(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLDWord, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeMD_UDInt(HMI_tag<uint32_t> *tag)
{
    return writeMD_UDInt(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeMD_Real(float value, int startAdrressByte)
{
    byte buffer[4];
    int Start = startAdrressByte;
    setReal(value, buffer);
    int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLReal, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeMD_Real(HMI_tag<float> *tag)
{
    return writeMD_Real(tag->VALUE, static_cast<int>(tag->ADDRESS));
}

/* WRITE DATABLOCK */
int PlcS7::writeDataBlock_Bit(bool value, int DBNumber, int offsetByte, int offsetBit)
{
    bool out = value;
    int offset = offsetByte * 8 + offsetBit;
    int err = Cli_WriteArea(Client, S7AreaDB, DBNumber, offset, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeDataBlock_Bit(HMI_tag<bool> *tag)
{
    int bit = 10 * (tag->ADDRESS - <int>(tag->ADDRESS));
    if (bit < 0 || bit > 7)
    {
        DEBUG("Bit address error");
        return false;
    }
    else
    {
        return writeDataBlock_Bit(tag->VALUE, tag->DB_NUMBER, static_cast<int>(tag->ADDRESS), bit);
    }
}

int PlcS7::writeDataBlock_SInt(int8_t value, int DBNumber, int offset)
{
    byte buffer;
    setSInt(value, &buffer);
    int err = Cli_DBWrite(Client, DBNumber, offset, SINT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeDataBlock_SInt(HMI_tag<int8_t> *tag)
{
    return writeDataBlock_SInt(tag->VALUE, tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeDataBlock_USInt(uint8_t value, int DBNumber, int offset)
{
    byte buffer;
    setUSInt(value, &buffer);
    int err = Cli_DBWrite(Client, DBNumber, offset, USINT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeDataBlock_USInt(HMI_tag<uint8_t> *tag)
{
    return writeDataBlock_USInt(tag->VALUE, tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeDataBlock_Int(int16_t value, int DBNumber, int offset)
{
    byte buffer[2];
    setInt(value, buffer);
    int err = Cli_DBWrite(Client, DBNumber, offset, INT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeDataBlock_Int(HMI_tag<int16_t> *tag)
{
    return writeDataBlock_Int(tag->VALUE, tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeDataBlock_UInt(uint16_t value, int DBNumber, int offset)
{
    byte buffer[2];
    setUInt(value, buffer);
    int err = Cli_DBWrite(Client, DBNumber, offset, UINT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeDataBlock_UInt(HMI_tag<uint16_t> *tag)
{
    return writeDataBlock_UInt(tag->VALUE, tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeDataBlock_DInt(int32_t value, int DBNumber, int offset)
{
    byte buffer[4];
    setDInt(value, buffer);
    int err = Cli_DBWrite(Client, DBNumber, offset, DINT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeDataBlock_DInt(HMI_tag<int32_t> *tag)
{
    return writeDataBlock_DInt(tag->VALUE, tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeDataBlock_UDInt(uint32_t value, int DBNumber, int offset)
{
    byte buffer[4];
    setUDInt(value, buffer);
    int err = Cli_DBWrite(Client, DBNumber, offset, UDINT_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeDataBlock_UDInt(HMI_tag<uint32_t> *tag)
{
    return writeDataBlock_UDInt(tag->VALUE, tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

int PlcS7::writeDataBlock_Real(float value, int DBNumber, int offset)
{
    byte buffer[4];
    setReal(value, buffer);
    int err = Cli_DBWrite(Client, DBNumber, offset, REAL_SIZE, &buffer);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::writeDataBlock_Real(HMI_tag<float> *tag)
{
    return writeDataBlock_Real(tag->VALUE, tag->DB_NUMBER, static_cast<int>(tag->ADDRESS));
}

/* WRITE HMI_TAG */
int PlcS7::writeValue(HMI_tag<bool> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return writeI(tag);
    case OUTPUT:
        return writeQ(tag);
    case MARKER:
        return writeM(tag);
    case DB:
        return writeDataBlock_Bit(tag);
    default:
        return false;
    }
}

int PlcS7::writeValue(HMI_tag<int8_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return writeIB_SInt(tag);
    case OUTPUT:
        return writeQB_SInt(tag);
    case MARKER:
        return writeMB_SInt(tag);
    case DB:
        return writeDataBlock_SInt(tag);
    default:
        return 0;
    }
}

int PlcS7::writeValue(HMI_tag<uint8_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return writeIB_USInt(tag);
    case OUTPUT:
        return writeQB_USInt(tag);
    case MARKER:
        return writeMB_USInt(tag);
    case DB:
        return writeDataBlock_USInt(tag);
    default:
        return 0;
    }
}

int PlcS7::writeValue(HMI_tag<int16_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return writeIW_Int(tag);
    case OUTPUT:
        return writeQW_Int(tag);
    case MARKER:
        return writeMW_Int(tag);
    case DB:
        return writeDataBlock_Int(tag);
    default:
        return 0;
    }
}

int PlcS7::writeValue(HMI_tag<uint16_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return writeIW_UInt(tag);
    case OUTPUT:
        return writeQW_UInt(tag);
    case MARKER:
        return writeMW_UInt(tag);
    case DB:
        return writeDataBlock_UInt(tag);
    default:
        return 0;
    }
}

int PlcS7::writeValue(HMI_tag<int32_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return writeID_DInt(tag);
    case OUTPUT:
        return writeQD_DInt(tag);
    case MARKER:
        return writeMD_DInt(tag);
    case DB:
        return writeDataBlock_DInt(tag);
    default:
        return 0;
    }
}

int PlcS7::writeValue(HMI_tag<uint32_t> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return writeID_UDInt(tag);
    case OUTPUT:
        return writeQD_UDInt(tag);
    case MARKER:
        return writeMD_UDInt(tag);
    case DB:
        return writeDataBlock_UDInt(tag);
    default:
        return 0;
    }
}

int PlcS7::writeValue(HMI_tag<float> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return writeID_Real(tag);
    case OUTPUT:
        return writeQD_Real(tag);
    case MARKER:
        return writeMD_Real(tag);
    case DB:
        return writeDataBlock_Real(tag);
    default:
        return 0.0;
    }
}

/* TOGGLE BIT */

int PlcS7::toggleBitI(int startAdrressByte, int startAdrressBit)
{
    bit out;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_ReadArea(Client, S7AreaPE, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
        return false;
    }
    else
    {
        out = !out;
        int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLBit, &out);
        if (err)
        {
            DEBUG("error : " << err);
        }
        return err;
    }
}

int PlcS7::toggleBitQ(int startAdrressByte, int startAdrressBit)
{
    bit out;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_ReadArea(Client, S7AreaPA, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
        return false;
    }
    else
    {
        out = !out;
        int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLBit, &out);
        if (err)
        {
            DEBUG("error : " << err);
        }
        return err;
    }
}

int PlcS7::toggleBitM(int startAdrressByte, int startAdrressBit)
{
    bit out;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_ReadArea(Client, S7AreaMK, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
        return false;
    }
    else
    {
        out = !out;
        int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLBit, &out);
        if (err)
        {
            DEBUG("error : " << err);
        }
        return err;
    }
}

int PlcS7::toggleBitDB(int DBNumber, int offsetByte, int offsetBit)
{
    bit out;
    int Start = offsetByte * 8 + offsetBit;
    int err = Cli_ReadArea(Client, S7AreaDB, DBNumber, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
        return false;
    }
    else
    {
        out = !out;
        int err = Cli_WriteArea(Client, S7AreaDB, DBNumber, Start, 1, S7WLBit, &out);
        if (err)
        {
            DEBUG("error : " << err);
        }
        return err;
    }
}

int PlcS7::toggleBit(HMI_tag<bool> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return toggleBitI(tag);
    case OUTPUT:
        return toggleBitQ(tag);
    case MARKER:
        return toggleBitM(tag);
    case DB:
        return toggleBitDB(tag);
    default:
        return -1;
    }
}

/* SET BIT */
int PlcS7::setBitI(int startAdrressByte, int startAdrressBit)
{
    bit out = true;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::setBitQ(int startAdrressByte, int startAdrressBit)
{
    bit out = true;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::setBitM(int startAdrressByte, int startAdrressBit)
{
    bit out = true;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::setBitM(int DBNumber, int offsetByte, int offsetBit)
{
    bit out = true;
    int Start = offsetByte * 8 + offsetBit;
    int err = Cli_WriteArea(Client, S7AreaDB, DBNumber, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::setBit(HMI_tag<bool> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return setBitI(tag);
    case OUTPUT:
        return setBitQ(tag);
    case MARKER:
        return setBitM(tag);
    case DB:
        return setBitDB(tag);
    default:
        return -1;
    }
}

/* RESET BIT */
int PlcS7::resetBitI(int startAdrressByte, int startAdrressBit)
{
    bit out = false;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_WriteArea(Client, S7AreaPE, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::resetBitQ(int startAdrressByte, int startAdrressBit)
{
    bit out = false;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_WriteArea(Client, S7AreaPA, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::resetBitM(int startAdrressByte, int startAdrressBit)
{
    bit out = false;
    int Start = startAdrressByte * 8 + startAdrressBit;
    int err = Cli_WriteArea(Client, S7AreaMK, 0, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::resetBitM(int DBNumber, int offsetByte, int offsetBit)
{
    bit out = false;
    int Start = offsetByte * 8 + offsetBit;
    int err = Cli_WriteArea(Client, S7AreaDB, DBNumber, Start, 1, S7WLBit, &out);
    if (err)
    {
        DEBUG("error : " << err);
    }
    return err;
}

int PlcS7::resetBit(HMI_tag<bool> *tag)
{
    switch (tag->TYPE)
    {
    case INPUT:
        return resetBitI(tag);
    case OUTPUT:
        return resetBitQ(tag);
    case MARKER:
        return resetBitM(tag);
    case DB:
        return resetBitDB(tag);
    default:
        return -1;
    }
}

/*-----------------------PRIVATE--------------------------*/

uint8_t PlcS7::getByte(byte *buffer)
{
    return getUint8(buffer);
}

uint16_t PlcS7::getWord(byte *buffer)
{
    return getUint16(buffer);
}

uint32_t PlcS7::getDWord(byte *buffer)
{
    return getUint32(buffer);
}

int8_t PlcS7::getSInt(byte *buffer)
{
    int8_t sign = ((buffer[0] & 0b10000000) >> 7) * static_cast<int8_t>(pow(-2, 7));
    int8_t value;
    value = buffer[0] & 0b01111111;

    return value + sign;
}

uint8_t PlcS7::getUSInt(byte *buffer)
{
    return getUint8(buffer);
}

int16_t PlcS7::getInt(byte *buffer)
{
    int16_t sign = ((buffer[0] & 0b10000000) >> 7) * static_cast<int16_t>(pow(-2, 15));
    int16_t value;
    value = getUint16(buffer) & 0x7FFF;

    return value + sign;
}

uint16_t PlcS7::getUInt(byte *buffer)
{
    return getUint16(buffer);
}

int32_t PlcS7::getDInt(byte *buffer)
{
    int32_t sign = ((buffer[0] & 0b10000000) >> 7) * static_cast<int32_t>(pow(-2, 31));
    int32_t value;
    value = getUint32(buffer) & 0x7FFFFFFF;

    return value + sign;
}

uint32_t PlcS7::getUDInt(byte *buffer)
{
    return getUint32(buffer);
}

float PlcS7::getReal(byte *buffer)
{
    /* IEEE-754 */
    int i = 0, j = 0;
    uint8_t exponent;
    uint32_t fraction;
    float fractionSum = 0.0;
    uint32_t result = getUint32(buffer);

    exponent = static_cast<uint8_t>(result >> 23);
    exponent &= 0xFF;

    fraction = result & 0x7FFFFF;

    for (i = -23; i < 0; i++)
    {
        fractionSum += ((fraction << (31 - j)) >> 31) * static_cast<float>(pow(2, i));
        j++;
    }
    if (result & (1 << 31))
        return -1.0f * (1.0f + fractionSum) * static_cast<float>(pow(2, exponent - 127));
    else
        return (1.0f + fractionSum) * static_cast<float>(pow(2, exponent - 127));
}

void PlcS7::setByte(byte value, byte *buffer)
{
    buffer[0] = value;
}

void PlcS7::setSInt(int8_t value, byte *buffer)
{
    if (value < 0)
    {
        buffer[0] = 1 << 7;
        value = value - static_cast<int8_t>(pow(-2, 7));
    }
    else
        buffer[0] = 0x00;

    buffer[0] |= value & 0x7F;
}

void PlcS7::setUSInt(uint8_t value, byte *buffer)
{
    buffer[0] = value;
}

void PlcS7::setInt(int16_t value, byte *buffer)
{
    if (value < 0)
    {
        buffer[0] = 1 << 7;
        value = value - static_cast<int16_t>(pow(-2, 15));
    }
    else
        buffer[0] = 0x00;

    buffer[0] |= (value >> 8) & 0x7F;
    buffer[1] = value & 0xFF;
}

void PlcS7::setUInt(uint16_t value, byte *buffer)
{
    buffer[0] = value >> 8;
    buffer[1] = value & 0xFF;
}

void PlcS7::setDInt(int32_t value, byte *buffer)
{
    if (value < 0)
    {
        buffer[0] = 1 << 7;
        value = value - static_cast<int32_t>(pow(-2, 31));
    }
    else
        buffer[0] = 0x00;

    buffer[0] |= (value >> 24) & 0x7F;
    buffer[1] = (value << 8) >> 24;
    buffer[2] = (value << 16) >> 24;
    buffer[3] = value & 0xFF;
}

void PlcS7::setUDInt(uint32_t value, byte *buffer)
{
    buffer[0] = (value >> 24);
    buffer[1] = (value << 8) >> 24;
    buffer[2] = (value << 16) >> 24;
    buffer[3] = value & 0xFF;
}

void PlcS7::setReal(float value, byte *buffer)
{
    bool binaryIEEE754[32] = {0};
    bool mantissaPrecision[46] = {0};
    bool sign = value > 0 ? 0 : 1;
    float mantissa;
    int i = 0;
    int j = 0;
    int k = 0;
    int exponent;

    if (value == 0.0f)
    {
        buffer[0] = 0x00;
        buffer[1] = 0x00;
        buffer[2] = 0x00;
        buffer[3] = 0x00;
        return;
    }

    if (sign)
        value = static_cast<float>(fabs(static_cast<double>(value)));

    if (value < 1.0f)
    {
        mantissa = value - static_cast<int>((value));

        /* set mantissa */
        while (mantissa > 0)
        {
            mantissa *= 2;
            if (mantissa >= 1)
            {
                mantissaPrecision[i] = 1;
                mantissa--;
            }
            else
            {
                mantissaPrecision[i] = 0;
            }
            i++;
        }
        i = 0;
        i--;
        while (mantissaPrecision[j] == 0)
        {
            i--;
            j++;
        }

        for (k = 9; k < 32; k++)
        {
            binaryIEEE754[k] = mantissaPrecision[k - 9 + (j + 1)];
        }
        exponent = i + 127;
    }
    else
    {
        while (value > 2.0f)
        {
            value /= 2.0f;
            i++;
        }
        exponent = i + 127;
        mantissa = value - static_cast<int>(value);
        i = 0;
        while (mantissa > 0)
        {
            mantissa *= 2;
            if (mantissa >= 1)
            {
                binaryIEEE754[9 + i] = 1;
                mantissa--;
            }
            else
                binaryIEEE754[9 + i] = 0;
            i++;
        }
    }

    /* set sign */
    binaryIEEE754[0] = sign;

    /* set exponent */
    i = 0;
    while (exponent >= 0)
    {
        int mod = exponent % 2;
        binaryIEEE754[8 - i] = static_cast<bool>(mod);
        i++;
        exponent /= 2.0;
        if (i >= 8)
            break;
    }

    /* prepare output */
    buffer[0] = 0x00;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    buffer[3] = 0x00;

    for (int j = 0; j < 8; j++)
        buffer[0] |= binaryIEEE754[0 + j] << (7 - j);
    for (int j = 0; j < 8; j++)
        buffer[1] |= binaryIEEE754[8 + j] << (7 - j);
    for (int j = 0; j < 8; j++)
        buffer[2] |= binaryIEEE754[16 + j] << (7 - j);
    for (int j = 0; j < 8; j++)
        buffer[3] |= binaryIEEE754[24 + j] << (7 - j);
}

uint8_t PlcS7::getUint8(byte *buffer)
{
    return buffer[0];
}

uint16_t PlcS7::getUint16(byte *buffer)
{
    uint16_t result;
    result = buffer[0];
    result <<= 8;
    result |= buffer[1];

    return result;
}

uint32_t PlcS7::getUint32(byte *buffer)
{
    uint32_t result;
    result = buffer[0];
    result <<= 8;
    result |= buffer[1];
    result <<= 8;
    result |= buffer[2];
    result <<= 8;
    result |= buffer[3];

    return result;
}
