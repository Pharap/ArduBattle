#include <Arduboy2.h>
Arduboy2 arduboy;

#include "characterPlane.h"
#include "TitleScreen.h"
#include "characterBullet.h"

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

void reset()
{
  characterPlaneX = 45;
  characterPlaneY =  30;
  characterBulletX = characterPlaneX + 23;
  characterBulletY = characterPlaneY - 2;
}

void setup() {
  arduboy.begin();
  arduboy.clear();
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
  if(arduboy.pressed(LEFT_BUTTON)) --characterPlaneX;
  if(arduboy.pressed(RIGHT_BUTTON)) ++characterPlaneX;
  if(arduboy.pressed(UP_BUTTON)) --characterPlaneY;
  if(arduboy.pressed(DOWN_BUTTON)) ++characterPlaneY;
  updateCharacterBullet();
}

void drawCharacterPlane()
{
  Sprites::drawOverwrite(characterPlaneX, characterPlaneY, characterPlane, 0);
}

//Character Bullet
void updateCharacterBullet()
{
  characterBulletX = characterPlaneX + 7;
  characterBulletY = characterPlaneY - 8;
  
  if(arduboy.pressed(A_BUTTON)) {
    drawCharacterBullet();
  }
}

void drawCharacterBullet()
{
  if(arduboy.everyXFrames(6)) {
    Sprites::drawOverwrite(characterBulletX, characterBulletY, characterBullet, 0);
  }
}
