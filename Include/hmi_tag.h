#ifndef HMI_TAG_H
#define HMI_TAG_H

enum tag_type {INPUT, OUTPUT, MARKER, DB};

template <typename T>
class HMI_tag
{
public:
    HMI_tag(tag_type type, int byte_dbnumber, int bit_offset);
    HMI_tag(tag_type type, int byte_dbnumber);
    tag_type TYPE ;
    int BYTE_DBNUMBER;
    int BIT_OFFSET;
    T value;
};

#endif // HMI_TAG_H
