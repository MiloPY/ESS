
#include <xmc_gpio.h>

#define DOT_DURATION_MS 100
#define DASH_DURATION_MS (3 * DOT_DURATION_MS)
#define SPACE_BETWEEN_SAME_LETTER_MS (DOT_DURATION_MS)

#define SPACE_BETWEEN_LETTERS_MS (3 * DOT_DURATION_MS)
#define SPACE_BETWEEN_WORDS_MS (7 * DOT_DURATION_MS)

#define TICKS_PER_S 1000 // 1 Tick = 1 ms

#define LED1 P1_1
#define LED2 P1_0


int input_buffer_iterator = 0;
int output_buffer_iterator = 0;


/*
Spacing and length of the signals:
A dash is equal to three dots.
The space between the signals forming the same letter is equal to one dot.
The space between two letters is equal to three dots.
The space between two words is equal to seven dots.
*/


char input_buffer[11] = "I CAN MORSE"; //+1 for \0, -1 because start from 0

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
static uint32_t ticks = 0;


void SysTick_Handler(void)
{
  ticks++;
  }

void LED_config(void)
{
  const XMC_GPIO_CONFIG_t LED_config = \
        {.mode=XMC_GPIO_MODE_OUTPUT_PUSH_PULL,\
         .output_level=XMC_GPIO_OUTPUT_LEVEL_LOW,\
         .output_strength=XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE};

  XMC_GPIO_CONFIG_t config;
  
  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;


  XMC_GPIO_Init(LED1, &config);

}

void translate(void)
{
  int input_buffer_iterator = 0;
  int output_buffer_iterator = 0;


    while (input_buffer[input_buffer_iterator] != '\0') {
        
        int lut_iterator = 0;


        while (input_buffer[input_buffer_iterator] != *morse_lut[lut_iterator].letter){
            lut_iterator++;
        }



         output_buffer[output_buffer_iterator].morse_code = morse_lut[lut_iterator].morse_code;


         input_buffer_iterator++;
         output_buffer_iterator++;

      }
    
    }


    /*
void blink(void)  
{
  char *current_buf = "";
  char next_buf;
  int input_buffer_iterator = 0;
  int output_buffer_iterator = 0;
  int tempo = ticks;
  int tempo2 = 0;
  int deltatempo = 0;
  while (output_buffer[output_buffer_iterator].morse_code != NULL) {
    current_buf = output_buffer[output_buffer_iterator].morse_code;



    while (*current_buf != '\0') {
      tempo = ticks;

      next_buf = *(current_buf + 1);

      if (*current_buf == ' ') {
        //intra-character gap
        uint32_t start_ticks = ticks;
        while ((ticks - start_ticks) < SPACE_BETWEEN_WORDS_MS);
      }


      else 
      {
      if (*current_buf == '.') {
        XMC_GPIO_ToggleOutput(LED1);
        uint32_t start_ticks = ticks;
        while ((ticks - start_ticks) < DOT_DURATION_MS);
        XMC_GPIO_ToggleOutput(LED1);
            
        if (next_buf != '\0') {        
          start_ticks = ticks;
          while ((ticks - start_ticks) < SPACE_BETWEEN_SAME_LETTER_MS);
        }
        else if (next_buf == '\0')
        {
          if (output_buffer[output_buffer_iterator + 1].morse_code == " ");
          else
          {
            start_ticks = ticks;
            while ((ticks - start_ticks) < SPACE_BETWEEN_LETTERS_MS);         
          }
        }


      }

      else if (*current_buf == '-') {

        XMC_GPIO_ToggleOutput(LED1);
        uint32_t start_ticks = ticks;
        while ((ticks - start_ticks) < DASH_DURATION_MS);
        XMC_GPIO_ToggleOutput(LED1);
        if (next_buf != '\0') {        
          start_ticks = ticks;
          while ((ticks - start_ticks) < SPACE_BETWEEN_SAME_LETTER_MS);
        }
        else if (next_buf == '\0')
        {
          if (output_buffer[output_buffer_iterator + 1].morse_code == " ");
          else
          {
            start_ticks = ticks;
            while ((ticks - start_ticks) < SPACE_BETWEEN_LETTERS_MS);         
          }
        }
      }
   
      }
      


      
      current_buf++; 

    }

    tempo2 = ticks;
    deltatempo = tempo2 - tempo;

    output_buffer_iterator++;

    }



    uint32_t start_ticks = ticks;
    while ((ticks - start_ticks) < DOT_DURATION_MS*50);
  }

*/

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
  // Final delay after the entire message
  delay(DOT_DURATION_MS * 50);
}



int main(void) {

  LED_config();
  SysTick_Config(SystemCoreClock / TICKS_PER_S);

  while(1) {

    translate();
    blink();

  }
    
  return 0;
}
