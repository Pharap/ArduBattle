// 'characterPlaneFlash', 5x7px
#pragma once

#include <stdint.h>

constexpr uint8_t characterPlaneFlashWidth = 5;
constexpr uint8_t characterPlaneFlashHeight = 7;

const unsigned char characterPlaneFlash[] PROGMEM = {
  // Dimensions
  characterPlaneFlashWidth, characterPlaneFlashHeight,

  // Frame 0 - characterPlaneFlash
  0x10, 0x60, 0x7e, 0x60, 0x10,
};
