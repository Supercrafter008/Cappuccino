#include "Resources.h"
#include "filelist.h"

#include <string.h>
#include <string>
#include <wut_types.h>
#include <malloc.h>



const uint8_t* Resources::GetFile(std::string path) {
    for (int32_t i = 0; ResourceList[i].filename != nullptr; ++i) {
        if (path.compare(ResourceList[i].filename) == 0) {
            uint8_t* memory = (uint8_t*)malloc(ResourceList[i].FileSize);
            memcpy(memory, ResourceList[i].File, ResourceList[i].FileSize);
            return memory;
        }
    }
    
    FILE* file = fopen(path.c_str(), "r");
    if(file != nullptr){
        fseek(file, 0, SEEK_END);
        uint32_t fileSize = ftell(file);
        rewind(file);
        uint8_t* dataBuf = (uint8_t*)memalign(0x40, fileSize);
        fread(dataBuf, fileSize, 1, file);
        fclose(file);
        return dataBuf;
    }
    
    return nullptr;
}

uint32_t Resources::GetFileSize(std::string path) {
    for (int32_t i = 0; ResourceList[i].filename != nullptr; ++i) {
        if (path.compare(ResourceList[i].filename) == 0) {
            return ResourceList[i].FileSize;
        }
    }

    FILE* file = fopen(path.c_str(), "r");
    if(file != NULL){
        fseek(file, 0, SEEK_END);
        uint32_t fileSize = ftell(file);
        fclose(file);
        return fileSize;
    }
    
    return 0;
}

