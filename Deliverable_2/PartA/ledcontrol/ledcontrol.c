#include <xmc_common.h>




int main(void) {

  PORT1->IOCR0 |= 0x8080; // set P1.0 and P1.1 as output

  PORT1->OUT |= 0x3; // set P1.0 and P1.1 high
  while(1){
    return 0;
  }
  
}

