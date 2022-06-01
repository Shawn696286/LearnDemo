#pragma once
struct AVFrame;
class CSws;
class IRender
{
public:
    IRender();
    ~IRender();

    virtual void Repaint(AVFrame* pFrame) = 0;

protected:
    void YuvToRgb(AVFrame* pFrame, char* pBufOut, int nOutW, int nOutH);

    void FreeFrame(AVFrame* pFrame);
private:
    CSws* m_pSws;
};

