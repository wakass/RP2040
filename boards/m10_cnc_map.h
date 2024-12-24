/*
  pico_cnc_map.h - driver code for RP2040 ARM processors

  Part of grblHAL

  Copyright (c) 2021-2022 Terje Io

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>

#undef TRINAMIC_ENABLE
#undef TRINAMIC_UART_ENABLE
#define TRINAMIC_ENABLE 2209
#define TRINAMIC_UART_ENABLE 1
#define TRINAMIC_STREAM 1   //This links bank to the SERIAL1_PORT stream number, i hope

#undef TRINAMIC_MIXED_DRIVERS
#define TRINAMIC_MIXED_DRIVERS 1

#undef UART_TX_PIN
#undef UART_RX_PIN
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define SERIAL1_PORT  1
#ifdef SERIAL1_PORT
    // UART 1 (Trinamic)
    #define UART_1_TX_PIN 4
    #define UART_1_RX_PIN 5
#endif

#if N_ABC_MOTORS > 1
#error "Axis configuration is not supported!"
#endif

#define BOARD_NAME "M10 CNC"
#define HAS_BOARD_INIT

typedef union {
    uint32_t value;
    struct {
        uint32_t dont_care   :1,
                 aux8_out    :1,
                 aux7_out    :1,
                 aux6_out    :1,
                 aux5_out    :1,
                 aux4_out    :1,
                 aux3_out    :1,
                 aux2_out    :1,
                 aux1_out    :1,
                 aux0_out    :1,
                 m5_ena      :1,
                 m4_ena      :1,
                 m3_ena      :1,
                 z_ena       :1,
                 y_ena       :1,
                 x_ena       :1,
                 unused      :16;
    };
} output_sr_t;

typedef union {
    uint16_t value;
    struct {
        uint16_t 
                
                c_dir   :1, //lsb (right side)
                b_dir   :1,
                a_dir   :1,
                z_dir   :1,
                y_dir   :1,
                x_dir   :1,
                c_step  :1,
                b_step  :1,
                a_step  :1,
                z_step  :1,
                y_step  :1,
                x_step  :1, //msb
                not_conn_pad  :4;
                
    };
} step_dir_t;
// e.g.
// sd_sr.value = 0x88008801;
// set -> 8801
//      --> set.c_dir = 1
//      --> set.x_step =1
//      --> set.nc = 8
// reset -> 8800
typedef union {
    uint32_t value;
    struct {
        step_dir_t set;
        step_dir_t reset;
    };
} step_dir_sr_t;

// Define step pulse output pins.
#define SD_SHIFT_REGISTER   8
#define SD_SR_DATA_PIN      10
#define SD_SR_SCK_PIN       11 // includes next pin (13)

// Define output signals pins.
#define OUT_SHIFT_REGISTER  16
#define OUT_SR_DATA_PIN     6
#define OUT_SR_SCK_PIN      7 // includes next pin (8)

#define STEP_PORT           GPIO_SR8
#define DIRECTION_PORT      GPIO_SR8
#define ENABLE_PORT         GPIO_SR16

#define AUX_N_OUT           8
#define AUX_OUT_MASK        0xFF

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 0
#define M3_AVAILABLE
#define M3_STEP_PIN         0 // Not referenced by driver code
#define M3_DIRECTION_PIN    0 // Not referenced by driver code
#define M3_LIMIT_PIN        3
#define M3_ENABLE_PIN       0 // Not referenced by driver code
#endif

// Define homing/hard limit switch input pins.
#define X_LIMIT_PIN         9
#define Y_LIMIT_PIN         13
#define Z_LIMIT_PIN         14

#define SPINDLE_PORT        GPIO_OUTPUT
// #define COOLANT_PORT        GPIO_SR16

#define HAS_IOPORTS
#define SERVO

// Define servo PWM pins
#define AUXOUTPUT0_PWM_PIN  15
#define SERVO0_PWM_IOPORT   Output_Analog_Aux0

// BLtouch - trigger input
#define PROBE_PIN           28
#define AUXINPUT3_PIN       PROBE_PIN

// Define spindle PWM output pin.
#define SPINDLE_PWM_PORT    GPIO_OUTPUT
#define SPINDLE_PWM_PIN     22

// Define user-control controls (cycle start, reset, feed hold) input pins.
#define RESET_PIN           23
#define FEED_HOLD_PIN       24
#define CYCLE_START_PIN     25
#if SAFETY_DOOR_ENABLE
#define SAFETY_DOOR_PIN     9
#endif

#if I2C_ENABLE
#define I2C_PORT            0
#define I2C_SDA             20
#define I2C_SCL             21
#endif

#if SDCARD_ENABLE
#define SPI_PORT            1
#define SPI_SCK_PIN         AUX_IO0_PIN
#define SPI_MOSI_PIN        AUX_IO1_PIN
#define SPI_MISO_PIN        AUX_IO2_PIN
#define SD_CS_PIN           AUX_IO3_PIN
#elif MPG_MODE == 1
#define MPG_MODE_PIN        AUX_IO3_PIN
#endif

#if ETHERNET_ENABLE
#define SPI_PORT            1
#define SPI_SCK_PIN         AUX_IO0_PIN
#define SPI_MOSI_PIN        AUX_IO1_PIN
#define SPI_MISO_PIN        AUX_IO2_PIN
#define SPI_CS_PIN          AUX_IO3_PIN
#define SPI_IRQ_PIN         26
//#define SPI_RST_PORT        GPIO_SR16
#define SPI_RST_PIN         0 // 15
#endif

#if I2C_STROBE_ENABLE
#define I2C_STROBE_PIN      26
#endif
