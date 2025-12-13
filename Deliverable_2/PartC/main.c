/* Main source file for assignment 2 part A, which implements shitty homebrewn crypto together with
 * a nasty little stack based buffer overflow
 *
 * Copyright 2018 TUM
 * Created: 2018-11-15 Florian Wilde <florian.wilde@tum.de>
 **************************************************************************************************/

 #include "VirtualSerial.h"
 #include "packetizer.h"
 #include "crypto.h"
 #include <sodium.h>
 #include "randombytes_salsa20XMC_random.h"



 
 int main(void) {


   pt_s plaintext = { 0 };
   ct_s ciphertext = { 0 };
   uint8_t key[32] = { 0xc1, 0x0, 0x86, 0xe, 0x15, 0x80, 0x32, 0xeb, 0x82, 0x6, 0x0, 0x10, 0xa, 0x0, 0x0, 0x0,
                      0xc1, 0x0, 0x86, 0xe, 0x15, 0x80, 0x32, 0xeb, 0x82, 0x6, 0x0, 0x10, 0xa, 0x0, 0x0, 0x0 };

   //extern struct randombytes_implementation randombytes_salsa20XMC_implementation;

   
 
  //  memcpy(key, g_chipid, 16);
  //  memcpy(&key[16], g_chipid, 16);




    randombytes_set_implementation(&randombytes_salsa20XMC_implementation);
    if (sodium_init() < 0) {
     /* panic! the library couldn't be initialized */
     return 1;
   }
  USB_Init();
  while(1) {
     /* Consumes incoming data and parses it until we received a valid packet.
        If so, it will fill the plaintextJob struct with the appropriate information. */
     if(packetizerReceive(&plaintext) == 0) {
       /* If the sender did not sent a nonce, generate one */
       if(plaintext.nonce == NULL) {
         plaintext.nonce = sodium_malloc(crypto_secretbox_NONCEBYTES);
        
         randombytes_buf(plaintext.nonce, crypto_secretbox_NONCEBYTES); 
       }
       /* Now encrypt the plaintext */
    
    
    
       ciphertext.textLen = plaintext.textLen+crypto_secretbox_MACBYTES;
       ciphertext.text = sodium_malloc(ciphertext.textLen);


       if(crypto_secretbox_easy(ciphertext.text, plaintext.text, plaintext.textLen, plaintext.nonce,
                  key) == 0) {
                    
                    ciphertext.textLen = plaintext.textLen+crypto_secretbox_MACBYTES;
                    /* Finally, if encryption was successful, send ciphertext back in a packet */
         packetizerSend(&ciphertext);
       }
       /* Free all buffers that were allocated in the meantime */
       sodium_free(plaintext.nonce);
       plaintext.nonce = NULL;
       sodium_free(ciphertext.text);
       ciphertext.text = NULL;
       free(plaintext.text);
       plaintext.text = NULL;


     }
   }

  }