#pragma once
#include <coreinit/ios.h>

enum DiscStatus{
    DISC_NONE = 0xa,
    DISC_INSERTED = 0x3,
    DISC_WII = 0x5,
    DISC_ERROR = 0x8,
    DISC_WIIU = 0x4,
};

class ODM{
    public:
    static void Open();
    static void StopMotor();
    static DiscStatus GetDiscStatus();  
    static void Close();
    private:
    static IOSHandle odmHandle;
};