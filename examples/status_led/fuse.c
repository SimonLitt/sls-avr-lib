#include <avr/io.h>

FUSES = {
    .low = 0xFF,
    .high = 0xDA,
    .extended = EFUSE_DEFAULT
};
