#include "Buffer.h"

#include <wut_types.h>
#include <string>
#include <memory.h>
#include <gx2/draw.h>
#include <gx2/mem.h>
#include <malloc.h>

Buffer::Buffer(uint32_t elemCount, GX2AttribFormat format){
    m_ElemCount = elemCount;
    switch (format)
    {
    case GX2_ATTRIB_FORMAT_FLOAT_32:
        m_ElemSize = 4;
        break;
    case GX2_ATTRIB_FORMAT_FLOAT_32_32:
        m_ElemSize = 8;
        break;
    case GX2_ATTRIB_FORMAT_FLOAT_32_32_32:
        m_ElemSize = 12;
        break;
    case GX2_ATTRIB_FORMAT_FLOAT_32_32_32_32:
        m_ElemSize = 16;
        break;
    case GX2_ATTRIB_FORMAT_UNORM_8:
    case GX2_ATTRIB_FORMAT_UINT_8:
    case GX2_ATTRIB_FORMAT_SNORM_8:
    case GX2_ATTRIB_FORMAT_SINT_8:
        m_ElemSize = 1;
        break;
    case GX2_ATTRIB_FORMAT_UNORM_8_8:
    case GX2_ATTRIB_FORMAT_UINT_8_8:
    case GX2_ATTRIB_FORMAT_SNORM_8_8:
    case GX2_ATTRIB_FORMAT_SINT_8_8:
        m_ElemSize = 2;
        break;
    case GX2_ATTRIB_FORMAT_UNORM_8_8_8_8:
    case GX2_ATTRIB_FORMAT_UINT_8_8_8_8:
    case GX2_ATTRIB_FORMAT_SNORM_8_8_8_8:
    case GX2_ATTRIB_FORMAT_SINT_8_8_8_8:
        m_ElemSize = 4;
        break;
    default:
        break;
    }
    m_BufferData = memalign(0x40 , m_ElemSize * elemCount);
}

Buffer::~Buffer(){
    free(m_BufferData);
}

void Buffer::Bind(uint32_t index){
    GX2SetAttribBuffer(index, m_ElemSize * m_ElemCount, m_ElemSize, m_BufferData);
}

void Buffer::SetData(void* data, uint32_t size){
    memcpy(m_BufferData, data, size * m_ElemSize);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_ATTRIBUTE_BUFFER, m_BufferData, size * m_ElemSize);
}