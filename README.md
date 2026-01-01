My developments for working with AVR MCUs.

Depends on:
  * avr-uart: https://github.com/andygock/avr-uart

As testing and documentation progress, I will release additional functionality.

The following functionality is available today:
  * LCD HD44780 (pin connected): 4-bit & 8-bit support, read & delay modes support, support for connecting multiple displays to one MCU(Not optimal, but you can use one of the displays for debugging, in normal mode it is better to use only one display);
  * Simple LED indication with support for up to 3 LEDs;
  * Helper functions for working with button states: Almost everything is customizable. Short-press, long-press, and press-and-hold modes;
  * UART no abort assert: Due to implementation, in the AVR GCC calls the abort() function after calling `__assert`. However, immediately disabling global interrupts prevents anything from being displayed in the stderr. Only the user-defined function for stderr using NONATOMIC_BLOCK allows the output to be completed.

I'll add test examples as soon as I can, but if you have any questions, don't be afraid to ask or hurry me up to publish test examples.

For more detailed information, please refer to the [docs](https://github.com/SimonLitt/sls-avr-lib/tree/main/docs/html) directory.
