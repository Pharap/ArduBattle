#include <Arduboy2.h>
Arduboy2 arduboy;

#include "characterPlane.h"
#include "TitleScreen.h"

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
  arduboy.print(F("ArduBattle 1943"));
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
  characterBulletX = characterPlaneX + 9;
  characterBulletY = characterPlaneY - 2;
  
  if(arduboy.pressed(A_BUTTON)) {
    --characterBulletY;
    drawCharacterBullet();
  }
}

void drawCharacterBullet()
{
  arduboy.drawLine(characterBulletX,characterBulletY,characterBulletX,characterBulletY,WHITE);
}
