#include <xmc_gpio.h>
#include <xmc_rtc.h>
#include <xmc_scu.h>
#include <xmc_ccu4.h>


// 2 Spacing and length of the signals
// 2.1 A dash is equal to three dots.
// 2.2 The space between the signals forming the same letter is equal to one dot.
// 2.3 The space between two letters is equal to three dots.
// 2.4 The space between two words is equal to seven dots. 


char buf[11] = "I CAN MORSE";

//0 = dot
//1 = dash


#define DOT 0
#define DASH 1

const uint8_t A[] = {DOT, DASH};
const uint8_t B[] = {DASH, DOT, DOT, DOT};
const uint8_t C[] = {DASH, DOT, DASH, DOT};
const uint8_t D[] = {DASH, DOT, DOT};
const uint8_t E[] = {DOT};
const uint8_t F[] = {DOT, DOT, DASH, DOT};
const uint8_t G[] = {DASH, DASH, DOT};
const uint8_t H[] = {DOT, DOT, DOT, DOT};
const uint8_t I[] = {DOT, DOT};
const uint8_t J[] = {DOT, DASH, DASH, DASH};
const uint8_t K[] = {DASH, DOT, DASH};
const uint8_t L[] = {DOT, DASH, DOT, DOT};
const uint8_t M[] = {DASH, DASH};
const uint8_t N[] = {DASH, DOT};
const uint8_t O[] = {DASH, DASH, DASH};
const uint8_t P[] = {DOT, DASH, DASH, DOT};
const uint8_t Q[] = {DASH, DASH, DOT, DASH};
const uint8_t R[] = {DOT, DASH, DOT};
const uint8_t S[] = {DOT, DOT, DOT};
const uint8_t T[] = {DASH};
const uint8_t U[] = {DOT, DOT, DASH};
const uint8_t V[] = {DOT, DOT, DOT, DASH};
const uint8_t W[] = {DOT, DASH, DASH};
const uint8_t X[] = {DASH, DOT, DOT, DASH};
const uint8_t Y[] = {DASH, DOT, DASH, DASH};
const uint8_t Z[] = {DASH, DASH, DOT, DOT};











int main(void) {
  const XMC_GPIO_CONFIG_t LED_config = \
        {.mode=XMC_GPIO_MODE_OUTPUT_PUSH_PULL,\
         .output_level=XMC_GPIO_OUTPUT_LEVEL_LOW,\
         .output_strength=XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE};

  XMC_GPIO_Init(XMC_GPIO_PORT1, 0, &LED_config);

  while(1) {
    for(int32_t waiter=(1<<20); waiter >= 0; waiter--);
    XMC_GPIO_ToggleOutput(XMC_GPIO_PORT1, 0);
  }
  return 0;
}
