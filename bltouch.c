#include "bltouch.h"

#include "servo/servo.h"

#define BLTOUCH_SERVO_PORT 0 
//Output_Analog_Aux0

void bltouchInit(){
//Initialization
    _reset();
    _stow();

    //get pin info
    //

    //bltouchReset;
    //bltouchStow;

}

//Hopefully only called on state-change
void bltouchConfigure(bool is_probe_away, bool probing) {
    if (probing)
        _deploy();
    else
        _stow();
}

bool bltouchIsTriggered() {
    //get digital signal? or..
    return hal.probe.get_state().triggered;
}

bool bltouchCommand(uint16_t cmd, uint16_t ms) {
    uint16_t current_angle = (uint16_t)get_angle(BLTOUCH_SERVO_PORT);
    // If the new command is the same, skip it (and the delay).
    // The previous write should've already delayed to detect the alarm.

    if (cmd != current_angle) {
        set_angle(BLTOUCH_SERVO_PORT,(float)cmd);
        //insert delay here
        //delay(_MAX(ms, (uint32_t)BLTOUCH_DELAY)))
    }
    return bltouchIsTriggered();
}


//Wrapped functions
void bltouchReset() {}




void bltouchClear() {
    _reset();
    _stow();
    _deploy();
    _stow();

}