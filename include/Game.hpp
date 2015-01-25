#ifndef __GAME_HPP__
# define __GAME_HPP__

#include <Box2D/Box2D.h>
#include <cstdlib>
#include <complex>
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
  Sprite		_boatRocket;
  Sprite		_box_blue;
  Sprite		_box_purple;
  Sprite		_box_red;
  Sprite		_box_green;
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

  Texture&		LoadImage(const std::string&, bool=false);
  void			popRocket();
  Clock			_deltaClock;
  Clock			_swapClock;
  Clock			_modClock;
  Clock			_pointClock;
  string		_boat;
  string		_boatRock;
  string		_rock;
  string		_blue;
  string		_purple;
  string		_red;
  string		_green;
  void			RocketFactory();
  void			BonusFactory();
  int			_life;
  int			_point;
  bool			_swap;
  int			_mod;
  Font			_font;
  Text			_score;
  Music			_sRocket;
  Music			_sMalus;
  Music			_sBonus;
public:
  GameController(RenderWindow *window, SFMLKernel *kernel, const string &name);
  virtual ~GameController();

  int eventManager(Event event);
  void addExplosion(double x, double y);
  int display();
  void init();
  int	getPoint() const
  {
    return (_point);
  }
};

#endif
