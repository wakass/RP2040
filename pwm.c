#include "pwm.h"


/// @brief 
/// @param pwm_data struct to be filled with computed values
/// @param clock_hz Effective clock frequency of system. (e.g. real-clock divided by prescaler). 
/// @param minvalue Minimum pulse width (us)
/// @param maxvalue Maximum pulse width (us)
/// @param pwm_off_value 
/// @return 
bool precompute_pwm_values (pwm_t *pwm_data, uint32_t clock_hz, float minvalue, float maxvalue, float pwm_off_value)
{
    if(maxvalue > minvalue) {
        pwm_data->period = (uint_fast16_t)((float)clock_hz / pwm_data->freq);
        
        pwm_data->off_value = invert_pwm(pwm_data, (uint_fast16_t)(pwm_data->period * pwm_off_value / 100.0f));

        pwm_data->min_period = (uint_fast16_t)(pwm_data->period * minvalue / 100.0f);
        pwm_data->max_period = (uint_fast16_t)(pwm_data->period * maxvalue / 100.0f);

        pwm_data->gradient = (float)(pwm_data->max_period - pwm_data->min_period) / (maxvalue - minvalue);
        pwm_data->always_on = pwm_off_value != 0.0f;
    }

    return maxvalue > minvalue;
}


//
// The following functions are not called by the core, may be called by driver code.
//

// calculate inverted pwm value if configured
static inline uint_fast16_t invert_pwm (pwm_t *pwm_data, uint_fast16_t pwm_value)
{
    return pwm_data->invert_pwm ? pwm_data->period - pwm_value - 1 : pwm_value;
}