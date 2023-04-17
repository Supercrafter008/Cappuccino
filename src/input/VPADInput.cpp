#include "VPADInput.h"

bool VPAD::m_Connected = false;
VPADStatus VPAD::m_Status = {0};

void VPAD::Update(){
    VPADReadError error;
    VPADRead(VPAD_CHAN_0, &m_Status, 1, &error);
    switch(error){
        case VPAD_READ_UNINITIALIZED:
            VPADInit();
            break;
        case VPAD_READ_INVALID_CONTROLLER:
            m_Connected = false;
            break;
        case VPAD_READ_SUCCESS:
            m_Connected = true;
            VPADGetTPCalibratedPointEx(VPAD_CHAN_0, VPAD_TP_1920X1080, &m_Status.tpNormal, &m_Status.tpNormal);
            break;
        default:
            break;
    }
};

glm::vec2 VPAD::GetTouchPos(){
    if(m_Status.tpNormal.touched){
        return {m_Status.tpNormal.x, m_Status.tpNormal.y};
    }
    return {-1,-1};
}

bool VPAD::ButtonDown(VPADButtons button){
    if(m_Status.hold & button) return true;
    return false;
}

bool VPAD::ButtonPressed(VPADButtons button){
    if(m_Status.trigger & button) return true;
    return false;
}