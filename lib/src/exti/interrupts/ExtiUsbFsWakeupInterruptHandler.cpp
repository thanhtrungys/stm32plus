/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stm32plus.h"

#if !defined(STM32PLUS_F1_CL)

#include "config/exti.h"


using namespace stm32plus;


// static initialiser for the hack that forces the IRQ handlers to be linked

template<> ExtiInterruptEnabler<18>::FPTR ExtiInterruptEnabler<18>::_forceLinkage=nullptr;
template<> ExtiPeripheral<EXTI_Line18> *ExtiPeripheral<EXTI_Line18>::_extiInstance=nullptr;


#if defined(USE_EXTI_USB_FS_WAKEUP_INTERRUPT)

extern "C" {

  void __attribute__ ((interrupt("IRQ"))) USBWakeUp_IRQHandler(void) {

    if(EXTI_GetITStatus(EXTI_Line18)!=RESET) {
        ExtiUsbFsWakeup::_extiInstance->ExtiInterruptEventSender.raiseEvent(18);
        EXTI_ClearITPendingBit(EXTI_Line18);
    }
    __DSB();      // prevent erroneous recall of this handler due to delayed memory write
  }
}

#endif
#endif
