#include "io_expander_led.h"

// function for change in blinking of IO expander LEDs based on different states.
// if the state is fast, blink the LED fast
// medium = medium speed
// slow = slow speed

extern bool Alert_Timer0B;
uint8_t count = 7;
led_blink_rate blink_rate = FAST;


//void led_blink(led_blink_rate rate) {

//    uint8_t led_number = 0x80;

//    if(rate == DROP && count >= 0) {
//        count = count - 1;
//        if(count == 6) {
//            io_expander_blink_state(set_blink_rate, LED6);
//        } else if(count == 5) {
//            io_expander_blink_state(set_blink_rate, LED5);
//        } else if(count == 4) {
//            io_expander_blink_state(set_blink_rate, LED4);
//        } else if(count == 3) {
//            io_expander_blink_state(set_blink_rate, LED3);
//        } else if(count == 2) {
//            io_expander_blink_state(set_blink_rate, LED2);
//        } else if(count == 1) {
//            io_expander_blink_state(set_blink_rate, LED1);
//        } else if(count == 0) {
//            io_expander_blink_state(set_blink_rate, LED0);
//        } else {
//            io_expander_blink_state(set_blink_rate, NOT_LED);
//        }
//    } else {
//        io_expander_blink_state(set_blink_rate, led_number);
//    }
//}