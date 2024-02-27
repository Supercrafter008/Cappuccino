#pragma once

#include <map>
#include <stdint.h>
#include <string>
#include <gx2/enum.h>
#include <glm/vec2.hpp>
#include <gfx/Texture.h>
#include <string>


class Resources {
public:
    static const uint8_t *GetFile(std::string filename);
    static uint32_t GetFileSize(std::string filename);
};