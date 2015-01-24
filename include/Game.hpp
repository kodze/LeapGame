#ifndef __GAME_HPP__
# define __GAME_HPP__

#include <Box2D/Box2D.h>
#include <cstdlib>
#include "Controller.hpp"
#include "SFMLKernel.hpp"

using namespace std;
using namespace sf;

#define METERTOPIXEL 50.0f

class GameController : public Controller
{
private:
  Shader		_thresholdShader;
  Shader		_blurh;
  Shader		_blurv;

  Sprite		_background;
  Sprite		_background2;
  Sprite		_water;
  Sprite		_box;
  Sprite		_missile;

  b2Vec2		_gravity;
  b2World		_world;
  b2ParticleSystem*	_particleSystem;
  b2ParticleSystemDef	_particleSystemDef;
  b2Body		*_player;
  
  RenderTexture		_backgroundtext;
  RenderTexture		_backgroundtext2;
  RenderTexture		_backgroundtext3;

  Texture&		LoadImage(const std::string&);
  Clock			_deltaClock;
  string		_boat;
  string		_rock;
  void			RocketFactory();
public:
  GameController(RenderWindow *window, SFMLKernel *kernel, const string &name);
  virtual ~GameController();

  int eventManager(Event event);
  int display();
  void init();
};

#endif
