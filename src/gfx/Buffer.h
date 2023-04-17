#pragma once

#include <gx2/enum.h>

class Buffer{
    public:
    Buffer(uint32_t elemCount, GX2AttribFormat format);
    ~Buffer();

    void Bind(uint32_t index);

    void SetData(void* data, uint32_t size);

    uint32_t Size() { return m_ElemCount; };

    private:
    uint32_t m_ElemCount;
    uint32_t m_ElemSize;
    void* m_BufferData;
};