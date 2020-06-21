// 'Bullet', 5x7px
#pragma once

#include <stdint.h>

constexpr uint8_t characterBulletWidth = 5;
constexpr uint8_t characterBulletHeight = 7;

const unsigned char characterBullet[] PROGMEM = {
  // Dimensions
  characterBulletWidth, characterBulletHeight,

  // Frame 0 - characterBullet
  0x10, 0x60, 0x7e, 0x60, 0x10,
};
