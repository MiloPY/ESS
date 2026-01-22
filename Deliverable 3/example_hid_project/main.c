
#include "KeyboardHID.h"
#include "german_keyboardCodes.h"

/* Macros: */
#define LED1 P1_1
#define LED2 P1_0
#define MAX_MSG_BUFFER 500 // Define the physical limit of your array

int i = 0;
uint8_t msg[90] = {
    GERMAN_KEYBOARD_SC_A,
    GERMAN_KEYBOARD_SC_B,
    GERMAN_KEYBOARD_SC_C,
    GERMAN_KEYBOARD_SC_D,
    GERMAN_KEYBOARD_SC_E,
    GERMAN_KEYBOARD_SC_F,
    GERMAN_KEYBOARD_SC_G,
    GERMAN_KEYBOARD_SC_H,
    GERMAN_KEYBOARD_SC_I,
    GERMAN_KEYBOARD_SC_J,
    GERMAN_KEYBOARD_SC_K,
    GERMAN_KEYBOARD_SC_L,
    GERMAN_KEYBOARD_SC_M,
    GERMAN_KEYBOARD_SC_N,
    GERMAN_KEYBOARD_SC_O,
    GERMAN_KEYBOARD_SC_P,
    GERMAN_KEYBOARD_SC_Q,
    GERMAN_KEYBOARD_SC_R,
    GERMAN_KEYBOARD_SC_S,
    GERMAN_KEYBOARD_SC_T,
    GERMAN_KEYBOARD_SC_U,
    GERMAN_KEYBOARD_SC_V,
    GERMAN_KEYBOARD_SC_W,
    GERMAN_KEYBOARD_SC_X,
    GERMAN_KEYBOARD_SC_Y,
    GERMAN_KEYBOARD_SC_Z,
    GERMAN_KEYBOARD_SC_A,
    GERMAN_KEYBOARD_SC_B,
    GERMAN_KEYBOARD_SC_C,
    GERMAN_KEYBOARD_SC_D,
    GERMAN_KEYBOARD_SC_E,
    GERMAN_KEYBOARD_SC_F,
    GERMAN_KEYBOARD_SC_G,
    GERMAN_KEYBOARD_SC_H,
    GERMAN_KEYBOARD_SC_I,
    GERMAN_KEYBOARD_SC_J,
    GERMAN_KEYBOARD_SC_K,
    GERMAN_KEYBOARD_SC_L,
    GERMAN_KEYBOARD_SC_M,
    GERMAN_KEYBOARD_SC_N,
    GERMAN_KEYBOARD_SC_O,
    GERMAN_KEYBOARD_SC_P,
    GERMAN_KEYBOARD_SC_Q,
    GERMAN_KEYBOARD_SC_R,
    GERMAN_KEYBOARD_SC_S,
    GERMAN_KEYBOARD_SC_T,
    GERMAN_KEYBOARD_SC_U,
    GERMAN_KEYBOARD_SC_V,
    GERMAN_KEYBOARD_SC_W,
    GERMAN_KEYBOARD_SC_X,
    GERMAN_KEYBOARD_SC_Y,
    GERMAN_KEYBOARD_SC_Z,
    GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION,
    GERMAN_KEYBOARD_SC_2_AND_QUOTES,
    GERMAN_KEYBOARD_SC_3_AND_PARAGRAPH,
    GERMAN_KEYBOARD_SC_4_AND_DOLLAR,
    GERMAN_KEYBOARD_SC_5_AND_PERCENTAGE,
    GERMAN_KEYBOARD_SC_6_AND_AMPERSAND,
    GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE,
    GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET,
    GERMAN_KEYBOARD_SC_9_AND_CLOSING_PARENTHESIS_AND_CLOSING_BRACKET,
    GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE,
    GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION, // !
    GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET, // (
    GERMAN_KEYBOARD_SC_9_AND_CLOSING_PARENTHESIS_AND_CLOSING_BRACKET, // )
    GERMAN_KEYBOARD_SC_MINUS_AND_UNDERSCORE, // -
    GERMAN_KEYBOARD_SC_MINUS_AND_UNDERSCORE, // _
    GERMAN_KEYBOARD_SC_PLUS_AND_ASTERISK_AND_TILDE, // +
    GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE, // =
    GERMAN_KEYBOARD_SC_PLUS_AND_ASTERISK_AND_TILDE, // ~
    GERMAN_KEYBOARD_SC_COMMA_AND_SEMICOLON, // ;
    GERMAN_KEYBOARD_SC_DOT_AND_COLON, // :
    GERMAN_KEYBOARD_SC_COMMA_AND_SEMICOLON, // ,
    GERMAN_KEYBOARD_SC_DOT_AND_COLON, // .
    GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE, // <
    GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE, // >
    GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET, // [
    GERMAN_KEYBOARD_SC_9_AND_CLOSING_PARENTHESIS_AND_CLOSING_BRACKET, // ]
    GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE, // {
    GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE, // }
    GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE, // /
    GERMAN_KEYBOARD_SC_SHARP_S_AND_QUESTION_AND_BACKSLASH, // ?
    GERMAN_KEYBOARD_SC_6_AND_AMPERSAND, // &
    GERMAN_KEYBOARD_SC_4_AND_DOLLAR, // $
    GERMAN_KEYBOARD_SC_SPACE,
    GERMAN_KEYBOARD_SC_ENTER
};


uint8_t string2send[30] = {GERMAN_KEYBOARD_SC_L, GERMAN_KEYBOARD_SC_ENTER};
int maxtime = 0;
uint8_t solution_array[100] = {0};
// Global variables
uint8_t* global_string_to_send = NULL;
uint8_t  global_string_len = 168;
volatile uint8_t global_index = 0; // Reset this to 0 to start typing


volatile uint32_t led_toggle_distance = 0; // The public distance value
static uint32_t last_led_tick = 0;         // Helper to remember the previous time
volatile uint32_t public_distance = 0; // Accessible everywhere

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
    msTicks++;
}

// Helper to get current time
uint32_t GetTick(void) {
    return msTicks;
}

int string2sendlen = 2;
void insert(uint8_t arr[], uint8_t	*n, int pos, uint8_t val) {
  
    // Shift elements to the right
    for (int i = *n; i > pos; i--)
        arr[i] = arr[i - 1];

    // Insert val at the specified position
    arr[pos] = val;

    // Increase the current size
    (*n)++;
}

void MeasureLedToggleDistance(void) {
    static uint32_t lastTick = 0;
    uint32_t currentTick = GetTick();

    if (lastTick != 0) {
        // Update the public variable
        public_distance = currentTick - lastTick; 
        if (public_distance > maxtime) {
            maxtime = public_distance;
            solution_array[0]= msg[global_index]; // Store the character that caused the new max time
        }
    lastTick = currentTick; 
    }
}


int string_index = 0;
int current_pos = 0;
int shiftindex = 0;
bool waiting_for_response = false;
void fsm(void) {
    if (global_index >= global_string_len) {
        
        for (int i = string2sendlen; i > 0; i--) {
            // Shift existing elements of string2send array to the right
            string2send[i] = string2send[i - 1];
        }
        
        string2send[string_index] = solution_array[0]; // Insert new character at the start
        string2sendlen++; // Increase the length of string2send
        global_index = 0; // Reset index to start over
        current_pos++;
    }


    string2send[current_pos] = msg[global_index]; // Update the character to send based on the current index
    global_index++;
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
    SysTick_Config(SystemCoreClock / 1000);
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
	static uint8_t characterSent = 0, 
				   indexToSend = 0;
								int i = 0;
	
                            
    if (string_index < 2) {
		if(characterSent) {
			report->Modifier = 0; 
			report->Reserved = 0; 
			report->KeyCode[0] = 0; 
			characterSent = 0;
			string_index++; 
		} else {
			report->Modifier = 0; 
			report->Reserved = 0; 
			report->KeyCode[0] = string2send[string_index];
			characterSent = 1;
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
		XMC_GPIO_SetOutputHigh(LED1);
        MeasureLedToggleDistance();
        fsm();  
    }
	else 
		XMC_GPIO_SetOutputLow(LED1);
	
	
	if(*report & HID_KEYBOARD_LED_CAPSLOCK) 
		XMC_GPIO_SetOutputHigh(LED2);
	else 
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
                            