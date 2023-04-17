#include "odm.h"

#include <coreinit/ios.h>
#include <whb/log.h>
#include <whb/log_udp.h>

IOSHandle ODM::odmHandle = 0;

void ODM::Open(){
    odmHandle = IOS_Open("/dev/odm", (IOSOpenMode)0);
}

DiscStatus ODM::GetDiscStatus(){
    uint32_t out = 0;
    IOS_Ioctl(odmHandle, 0x04, &out, sizeof(uint32_t), &out, sizeof(uint32_t));
    return (DiscStatus)out;
}

void ODM::Close(){
    IOS_Close(odmHandle);
}