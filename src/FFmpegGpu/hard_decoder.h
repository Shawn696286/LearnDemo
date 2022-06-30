#pragma once
#include "public.h"

#define USE_HARD_DEVICE 1
class HardEnDecoder
{
public:
    HardEnDecoder();
    ~HardEnDecoder() {}

    void doDecode();
    void doEncode();
};
