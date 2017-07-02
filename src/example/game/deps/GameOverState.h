#ifndef GAMEOVERSTATE_H_DEFINED
#define GAMEOVERSTATE_H_DEFINED

#include <vector>

#include "Game.h"
#include "GameState.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "TextureManager.h"

class GameObject;

class GameOverState : public GameState
{
public:
  virtual void update();
  virtual void render();
  virtual bool onEnter();
  virtual bool onExit();

  virtual std::string getStateID() const {return s_gameOverID;}

private:
  static void s_gameOverToMain();
  static void s_restartPlay();

  static const std::string ;

  std::vector<GameObject*> m_gameObjects;
};

#endif
