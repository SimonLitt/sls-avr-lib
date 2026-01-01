My developments for working with AVR MCUs.

Depends on:
  * avr-uart: https://github.com/andygock/avr-uart

As testing and documentation progress, I will release additional functionality.

The following functionality is available today:
  * LCD HD44780 (pin connected): 4-bit & 8-bit support, read & delay modes support, support for connecting multiple displays to one MCU(Not optimal, but you can use one of the displays for debugging, in normal mode it is better to use only one display);
  * Simple LED indication with support for up to 3 LEDs;
  * Helper functions for working with button states: Almost everything is customizable. Short-press, long-press, and press-and-hold modes;
  * UART asserts: For some reason, normal operation in the AVR GCC is not restored after calling `__assert`.

I'll add test examples as soon as I can, but if you have any questions, don't be afraid to ask or hurry me up with publishing the test examples.
