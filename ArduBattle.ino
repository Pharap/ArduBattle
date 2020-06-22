#include <Arduboy2.h>
Arduboy2 arduboy;

#include "characterPlane.h"
#include "TitleScreen.h"
#include "characterBullet.h"
#include "characterPlaneFlash.h"

enum class GameState
{
  TitleScreen,
  GamePlay,
  GameOver,
};
GameState gameState = GameState::TitleScreen;

//Variables
int characterPlaneX;
int characterPlaneY;
int characterBulletX;
int characterBulletY;

int cursor_x;
int cursor_y;

void reset()
{
  characterPlaneX = 55;
  characterPlaneY =  35;
  characterBulletX = characterPlaneX + 10;
  characterBulletY = characterPlaneY - 15;
}

void setup() {
  arduboy.begin();
  reset();

}

void loop() {
  if(!arduboy.nextFrame()) return;
  arduboy.pollButtons();
  arduboy.clear();

  switch(gameState)
  {
    case GameState::TitleScreen:
      updateTitleScreen();
      drawTitleScreen();
      break;
      
    case GameState::GamePlay:
      updateGamePlay();
      drawGamePlay();
      break;
      
    case GameState::GameOver:
      updateGameOver();
      drawGameOver();
      break;
  }
  arduboy.display();
}

//TitleScreen
void updateTitleScreen()
{
  if(arduboy.justPressed(A_BUTTON)) gameState = GameState::GamePlay;
}

void drawTitleScreen()
{
  Sprites::drawOverwrite(6, 14, titleScreen, 0);
  arduboy.setCursor(17,35);
  arduboy.print(F("Press A to Start"));
}

//GamePlay
void updateGamePlay()
{ 
  updateCharacterPlane();
}

void drawGamePlay()
{
  drawCharacterPlane();
}

//GameOver
void updateGameOver()
{
  if(arduboy.justPressed(A_BUTTON)) gameState = GameState::TitleScreen;
}

void drawGameOver()
{
  arduboy.print(F("Game Over!"));
}

//Character
void updateCharacterPlane()
{
  characterBulletX = characterPlaneX + 9;
  characterBulletY = characterPlaneY - 15;
  
  if(arduboy.pressed(LEFT_BUTTON)) --characterPlaneX;
  if(arduboy.pressed(RIGHT_BUTTON)) ++characterPlaneX;
  if(arduboy.pressed(UP_BUTTON)) --characterPlaneY;
  if(arduboy.pressed(DOWN_BUTTON)) ++characterPlaneY;
  updateCharacterBullet();
  updatePlaneCollision();

  arduboy.setCursor(characterPlaneX, characterPlaneY);
  cursor_x = arduboy.getCursorX();
  {
    arduboy.setCursor(74,0);
    arduboy.print(F("x:"));
    arduboy.print(cursor_x);
  }
  arduboy.setCursor(characterPlaneX, characterPlaneY);
  cursor_y = arduboy.getCursorY();
  {
    arduboy.setCursor(105,0);
    arduboy.print(F("y:"));
    arduboy.print(cursor_y);
  }
}

void drawCharacterPlane()
{
  Sprites::drawOverwrite(characterPlaneX, characterPlaneY, characterPlane, 0);
}

//Character Bullet
void updateCharacterBullet()
{ 
  if(arduboy.pressed(A_BUTTON)) {
    if(characterBulletY > 0) --characterBulletY;
    drawPlaneBulletFlash();
    drawCharacterBullet();
  }
}

void drawCharacterBullet()
{
  Sprites::drawOverwrite(characterBulletX, characterBulletY, characterBullet, 0);
}

void drawPlaneBulletFlash()
{
  if(arduboy.everyXFrames(6)) {
    Sprites::drawOverwrite(characterPlaneX + 7, characterPlaneY - 8, characterPlaneFlash, 0);
  }
}

void updatePlaneCollision()
{
  if(characterPlaneX > 109) --characterPlaneX;
  if(characterPlaneX < 0) ++characterPlaneX;
  if(characterPlaneY > 51) --characterPlaneY;
  if(characterPlaneY < 0) ++characterPlaneY;
}
