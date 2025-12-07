
#include <xmc_gpio.h>
#include <stdio.h>
#include <stdint.h>
#include <xmc_scu.h>


#include <xmc_common.h>
#include <XMC4500.h>

#define DOT_DURATION_MS 100
#define DASH_DURATION_MS (3 * DOT_DURATION_MS)

#define SPACE_BETWEEN_SAME_LETTER_MS (DOT_DURATION_MS)
#define SPACE_BETWEEN_LETTERS_MS (3 * DOT_DURATION_MS)
#define SPACE_BETWEEN_WORDS_MS (7 * DOT_DURATION_MS)







#define TICKS_PER_S 1000 // 1 Tick = 1 ms

#define LED1 P1_1
#define LED2 P1_0
#define BUTTON1 P1_14
#define BUTTON2 P1_15

static uint32_t ticks = 0;


int button1_pressed = 0; // Flag for BUTTON1
int button2_pressed = 0; // Flag for BUTTON2
int button_latched = 0;


int input_buffer_iterator = 0;
int output_buffer_iterator = 0;
int past_button_status1 = 1;
int button_status1 = 1;

int past_button_status2 = 1;
int button_status2 = 1;
int last_press_time = 0; // Variable to store the last press time of BUTTON1

int past_press_time = 0;
int press_time = 0;
int past_press_time2 = 0;

int press_time2 = 0;
int delta_time = 0;
int button1_press_counter = 0;
int winner = 0;
/*
Spacing and length of the signals:
A dash is equal to three dots.
The space between the signals forming the same letter is equal to one dot.
The space between two letters is equal to three dots.
The space between two words is equal to seven dots.
*/


char input_buffer[11] = "I CAN MORSE"; //+1 for \0, -1 because start from 0
char delta_buffer[20] = "";
typedef struct  {
    char *morse_code;
    char *letter;
} conversion_table;

conversion_table morse_lut[] = {
    {".-", "A"},
    {"-...", "B"},
    {"-.-.", "C"},
    {"-..", "D"},
    {".", "E"},
    {"..-.", "F"},
    {"--.", "G"},
    {"....", "H"},
    {"..", "I"},
    {".---", "J"},
    {"-.-", "K"},
    {".-..", "L"},
    {"--", "M"},
    {"-.", "N"},
    {"---", "O"},
    {".--.", "P"},
    {"--.-", "Q"},
    {".-.", "R"},
    {"...", "S"},
    {"-", "T"},
    {"..-", "U"},
    {"...-", "V"},
    {".--", "W"},
    {"-..-", "X"},
    {"-.--", "Y"},
    {"--..", "Z"},
    {" ", " "},
    {"-----","0"},
    {".----","1"},
    {"..---","2"},
    {"...--","3"},
    {"....-","4"},
    {".....","5"},
    {"-....","6"},
    {"--...","7"},
    {"---..","8"},
    {"----.","9"}

};

conversion_table output_buffer[20]= {}; //transalated morse code will be stored here, using same struct, only morse column


void SysTick_Handler(void)
{
  ticks++;
  button_status1 = XMC_GPIO_GetInput(BUTTON1);
  button_status2 = XMC_GPIO_GetInput(BUTTON2);


}

void LED_config(void)
{
  XMC_GPIO_CONFIG_t config;
  
  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;

  XMC_GPIO_Init(LED1, &config);
  XMC_GPIO_Init(LED2, &config);


}

void BUTTON_config(void)
{
  XMC_GPIO_CONFIG_t button_config;
   
  button_config.mode = XMC_GPIO_MODE_INPUT_PULL_UP;
 
  XMC_GPIO_Init(BUTTON1, &button_config);
  XMC_GPIO_Init(BUTTON2, &button_config);


} 

conversion_table *translate(char * passed_string)
{
  int input_buffer_iterator = 0;
  int output_buffer_iterator = 0;


    while (passed_string[input_buffer_iterator] != '\0') {
        
        int lut_iterator = 0;


        while (passed_string[input_buffer_iterator] != *morse_lut[lut_iterator].letter){
            lut_iterator++;
        }



         output_buffer[output_buffer_iterator].morse_code = morse_lut[lut_iterator].morse_code;


         input_buffer_iterator++;
         output_buffer_iterator++;

      }
      return output_buffer;
}




//toggle Led and wait for duration
void blink_led(uint32_t duration_ms) {
  XMC_GPIO_ToggleOutput(LED1);
  uint32_t start_ticks = ticks;
  while ((ticks - start_ticks) < duration_ms);
  XMC_GPIO_ToggleOutput(LED1);
}

//delays betweeen toggles
void delay(uint32_t duration_ms) {
  uint32_t start_ticks = ticks;
  while ((ticks - start_ticks) < duration_ms);
}

//main blink function
void blink(void) {
  char *current_buf = NULL;
  int output_buffer_iterator = 0;
  int tempo = ticks;
  int tempo2 = 0;
  int deltatempo = 0;
  while (output_buffer[output_buffer_iterator].morse_code != NULL) {
      current_buf = output_buffer[output_buffer_iterator].morse_code;

      //Check if space between words
      if (current_buf[0] == ' ') {
          delay(SPACE_BETWEEN_WORDS_MS);
      } else {
          //check if string ended
          while (*current_buf != '\0') {
              char current_char = *current_buf;

              if (current_char == '.') {
                  blink_led(DOT_DURATION_MS);
              } else if (current_char == '-') {
                  blink_led(DASH_DURATION_MS);
              }

              //Add a delay only if the next character is part of the same letter
              if (*(current_buf + 1) != '\0' && *(current_buf + 1) != ' ') {
                  delay(SPACE_BETWEEN_SAME_LETTER_MS);
              }

              current_buf++;
          }

          //Add space between letters
          if (output_buffer[output_buffer_iterator + 1].morse_code != NULL &&
              output_buffer[output_buffer_iterator + 1].morse_code[0] != ' ') {
              delay(SPACE_BETWEEN_LETTERS_MS);
          }
      }

      output_buffer_iterator++;
  }
tempo2 = ticks;
deltatempo = tempo2 - tempo;
}


//clean tx buffer
void clean_out_buffer(void){

         for (int i = 0; i < 20; i++) {
            output_buffer[i].morse_code = '\0';
          }

}

void clean_delta_buffer(void){

  for (int i = 0; i < 20; i++) {
    delta_buffer[i] = '\0';
  }

}

int main(void) {

  SysTick_Config(SystemCoreClock / TICKS_PER_S);
  press_time = ticks;
  LED_config();

  BUTTON_config();

  while(1) {
  
//if BUTTON1 is pressed and no button is latched
if (button_status1 == 0 && button_latched == 0) {
    button1_pressed = 1;
    button_latched = 1; //Latch BUTTON1 as winner
    winner = 1;         //Set winner to BUTTON1
    press_time = ticks; //save press time
  }


  
  
  //if BUTTON2 is pressed and no button is latched
  if (button_status2 == 0 && button_latched == 0) { 
    button2_pressed = 1;
    button_latched = 1; //Latch BUTTON2 as winner
    winner = 2;         //Set winner to BUTTON2
    press_time2 = ticks; //Save press time
  }
  
  //If BUTTON1 is latched and released, reset the state
  if (button1_pressed && button_status1 == 1) { // Button released
    button1_pressed = 0;
    button_latched = 0; // Allow new button presses
  }
  
  // If BUTTON2 is latched and released, reset the state
  if (button2_pressed && button_status2 == 1) { // Button released
    button2_pressed = 0;
    button_latched = 0; // Allow new button presses
  }
  
    // Perform actions based on the latched button
    if (winner == 1 && button1_pressed) {
      // Handle BUTTON1 actions
      button1_press_counter++;
      clean_delta_buffer(); // Clear previous delta_buffer content
      delta_time = press_time - last_press_time;

      last_press_time = press_time; // Update the last press time

      translate(input_buffer);
      blink();
      clean_out_buffer();

    } else if (winner == 2 && button2_pressed) {
      // Handle BUTTON2 actions
      switch (button1_press_counter) {
        case 0:
          sprintf(delta_buffer, "%d", 0);
          translate(delta_buffer);
          break;
        case 1:
          sprintf(delta_buffer, "%d", press_time);
          translate(delta_buffer);

          break;
        default:
          sprintf(delta_buffer, "%d", delta_time); // Update delta_buffer with the time difference
          translate(delta_buffer);
          break;
      }
      blink();
      clean_out_buffer();
    }
}
}