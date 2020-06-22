// 'Bullet', 1x2px
#pragma once

#include <stdint.h>

constexpr uint8_t characterBulletWidth = 1;
constexpr uint8_t characterBulletHeight = 2;

const unsigned char characterBullet[] PROGMEM = {
  // Dimensions
  characterBulletWidth, characterBulletHeight,

  // Frame 0 - characterBullet
  0xc0,
};
