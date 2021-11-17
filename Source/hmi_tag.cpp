#include "hmi_tag.h"

template <typename T>
HMI_tag<T>::HMI_tag(tag_type type, int byte_dbnumber, int bit_offset)
{
    TYPE = type;
    BYTE_DBNUMBER = byte_dbnumber;
    BIT_OFFSET = bit_offset;
}

template <typename T>
HMI_tag<T>::HMI_tag(tag_type type, int byte_dbnumber)
{
    TYPE = type;
    BYTE_DBNUMBER = byte_dbnumber;
}
