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

/* READ DATABLOCK */
bool PlcS7::readDataBlock_Bit(int DBNumber, int offsetByte, int offsetBit)
{
    bool out;
    int offset = offsetByte * 8 + offsetBit;
    Cli_ReadArea(Client, S7AreaDB, DBNumber, offset, 1, S7WLBit, &out);
    return out;
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
