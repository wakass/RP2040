
#ifndef _PWM_H_
#define _PWM_H_
#include <stdint.h>
#include <stdbool.h>

// Precalculated values that may be set/used by HAL driver to speed up RPM to PWM conversions
typedef struct {
    //Input
    float freq; //Frequency of the pwm modulation
    uint32_t clock_hz;

    //Output
    uint_fast16_t period; // Period corresponding to frequency
    uint_fast16_t off_value; // NOTE: this value holds the inverted version if software PWM inversion is enabled by the driver.
    uint_fast16_t min_period; //Value maximum for /period/
    uint_fast16_t max_period;
    float gradient;
    
    bool invert_pwm; // NOTE: set (by driver) when inversion is done in code
    bool always_on;
    int_fast16_t offset;
} pwm_t;

bool precompute_pwm_values (pwm_t *pwm_data, uint32_t clock_hz, float minvalue, float maxvalue, float pwm_off_value);
static inline uint_fast16_t invert_pwm (pwm_t *pwm_data, uint_fast16_t pwm_value);

#endif