#ifndef __GAME_HPP__
# define __GAME_HPP__

#include <Box2D/Box2D.h>
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

  b2Vec2		_gravity;
  b2World		_world;
  b2ParticleSystem*	_particleSystem;
    b2ParticleSystem*	_particleSystem2;
  b2ParticleSystemDef	_particleSystemDef;

  RenderTexture		_backgroundtext;
  RenderTexture		_backgroundtext2;
  RenderTexture		_backgroundtext3;

  Texture&		LoadImage(const std::string&);
  Clock			_deltaClock;
  string		_boat;
public:
  GameController(RenderWindow *window, SFMLKernel *kernel, const string &name);
  virtual ~GameController();

  int eventManager(Event event);
  int display();
  void init();
};

#endif
