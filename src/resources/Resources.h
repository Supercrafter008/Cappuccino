#pragma once

#include <map>
#include <stdint.h>
#include <string>
#include <gx2/enum.h>
#include <glm/vec2.hpp>
#include <gfx/Texture.h>


class Resources {
public:
    static const uint8_t *GetFile(const char *filename);
    static uint32_t GetFileSize(const char *filename);
};