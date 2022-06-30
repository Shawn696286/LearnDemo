#pragma once
#include "public.h"
struct AVFrame;
struct SwsContext;

class CSws
{
public:
    CSws();
    ~CSws();

    int YuvToRGB(AVFrame* pFrame, char* out, int outwidth, int outheight);
private:
    SwsContext* m_pSwsCtx;
};

