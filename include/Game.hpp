#ifndef __GAME_HPP__
# define __GAME_HPP__

#include <Box2D/Box2D.h>
#include <cstdlib>
#include <vector>
#include "IController.hpp"
#include "SFMLKernel.hpp"
#include "ContactListener.hpp"

using namespace std;
using namespace sf;

#define METERTOPIXEL 50.0f

class Explosion
{
public:
    Explosion(double x, double y, Sprite *sprite) : _i(5), _size(16), _x(x), _y(y), _sprite(sprite)  {};
    ~Explosion() {};
    int _i;
    int _size;
    double _x;
    double _y;
    Sprite *_sprite;
};

class GameController : public IController
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
  Texture       _tExplosion[16];
  Sprite        _explosion[16];
  vector<Explosion *> _listExplosions;
  b2Vec2		_gravity;
  b2World		_world;
  b2ParticleSystem*	_particleSystem;
  b2ParticleSystemDef	_particleSystemDef;
  b2Body		*_player;
  MyContactListener	*_contact;

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
    void addExplosion(double x, double y);
  int display();
  void init();
};

#endif
