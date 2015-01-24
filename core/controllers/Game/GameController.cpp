#include "../../../include/Game.hpp"


GameController::GameController(RenderWindow *window, SFMLKernel *kernel, const string &name) : Controller(window, kernel, name), _gravity(0.0f, 30.f) ,_world(_gravity), _boat("boat")
{
  this->init();
}

GameController::~GameController()
{

}

int GameController::eventManager(Event event)
{
  if (event.type == sf::Event::MouseButtonPressed)
    {
      if (event.mouseButton.button == sf::Mouse::Left)
	{
	  b2Vec2 force(0, 150);
	  _particleSystem->ApplyLinearImpulse(0, _particleSystem->GetParticleCount() - 1, force);
	}
    }

}

int	GameController::display()
{
  float32 timeStep = 1.0f / 60.0f;
  int32 iterations = 8;

  _window->clear();
  _backgroundtext.clear(sf::Color(0, 0, 0, 0));
  _backgroundtext2.clear(sf::Color(0, 0, 0, 0));
  _backgroundtext3.clear(sf::Color(0, 0, 0, 0));
  _world.Step(timeStep, iterations, 2);

  _background.move(-5.f, 0);
  _background2.move(-5.f, 0);
  if (_background.getPosition().x <= -1920.f)
    _background.setPosition(1920.f, 0);
  if (_background2.getPosition().x <= -1920.f)
    _background2.setPosition(1920.f, 0);
  _window->draw(_background);
  _window->draw(_background2);

  for(int x = 0; x < _particleSystem->GetParticleCount();++x)
    {
      b2Vec2 pos = _particleSystem->GetPositionBuffer()[x];
      _water.setPosition(pos.x * METERTOPIXEL, pos.y * METERTOPIXEL);
      _backgroundtext.draw(_water);
    }
  _backgroundtext.display();
  
  Sprite sprite(_backgroundtext.getTexture());
  _backgroundtext2.draw(sprite, &_blurh);
  _backgroundtext2.display();

  Sprite sprite2(_backgroundtext2.getTexture());
  _backgroundtext3.draw(sprite2, &_blurv);
  _backgroundtext3.display();

  Sprite sprite3(_backgroundtext3.getTexture());
  _thresholdShader.setParameter("time", _deltaClock.getElapsedTime().asSeconds());
  _window->draw(sprite3, &_thresholdShader);

  for (b2Body* BodyIterator = _world.GetBodyList(); BodyIterator != 0;
       BodyIterator = BodyIterator->GetNext())
    {
      if (BodyIterator->GetUserData() != NULL)
	{
	  Sprite	box(_box);
	  
	  box.setPosition(METERTOPIXEL * (BodyIterator->GetPosition().x - 1.5f),
			  METERTOPIXEL * (BodyIterator->GetPosition().y + 0.3f));
	  _window->draw(box);
	}
    }  
  _window->display();
}

Texture&	GameController::LoadImage(const std::string& img)
{
  sf::Image	tmp;
  tmp.loadFromFile(img);
  tmp.createMaskFromColor(sf::Color(255,0,255),0);
  sf::Texture *tex = new sf::Texture();
  tex->loadFromImage(tmp);
  return *tex;
}

void		GameController::init()
{
  _window->setFramerateLimit(60);
  
  _thresholdShader.loadFromFile("data/threshold.glsl", sf::Shader::Fragment);
  _thresholdShader.setParameter("resolution", sf::Vector2f(128.0,96.0));
  _blurh.loadFromFile("data/blurh.glsl", sf::Shader::Fragment);
  _blurv.loadFromFile("data/blurv.glsl", sf::Shader::Fragment);

  _background.setTexture(LoadImage("data/background.jpg"));
  _background.setOrigin(0,0);
  _background.setPosition(0,0);
  _background2.setTexture(LoadImage("data/background.jpg"));
  _background2.setOrigin(0,0);
  _background2.setPosition(1920, 0);
  _water.setTexture(LoadImage("data/water.png"));
  _water.setOrigin(8, 8);
  _box.setTexture(LoadImage("data/boat.png"));
  
  _backgroundtext.create(WIDTH, HEIGHT);
  _backgroundtext2.create(WIDTH, HEIGHT);
  _backgroundtext3.create(WIDTH, HEIGHT);

  _particleSystemDef.radius = 6/METERTOPIXEL;
  _particleSystem = _world.CreateParticleSystem(&_particleSystemDef);

  b2ParticleDef		pd;
  
  pd.lifetime = 0.0f;
  pd.flags = b2_tensileParticle;
  pd.velocity.Set(1, 0);

  for (int j = 1000; j < HEIGHT; j += 2)
    {
      for (int i = 0; i <= WIDTH; i += 10)
	{
	  pd.position.Set(i / METERTOPIXEL, j /METERTOPIXEL);
	  _particleSystem->CreateParticle(pd);
	}
    }

  b2BodyDef floorDef;
  floorDef.position = b2Vec2(0/METERTOPIXEL, HEIGHT/METERTOPIXEL);
  floorDef.type = b2_staticBody;
  b2Body* Floor = _world.CreateBody(&floorDef);
  b2PolygonShape floorShape;
  floorShape.SetAsBox(WIDTH/METERTOPIXEL, 1.f/METERTOPIXEL);
  b2FixtureDef floorFixDef;
  floorFixDef.density = 0.f;
  floorFixDef.shape = &floorShape;
  Floor->CreateFixture(&floorFixDef);

  b2BodyDef leftWallDef;
  leftWallDef.position = b2Vec2(WIDTH/METERTOPIXEL, 0/METERTOPIXEL);
  leftWallDef.type = b2_staticBody;
  b2Body* LeftWall = _world.CreateBody(&leftWallDef);
  b2PolygonShape leftWallShape;
  leftWallShape.SetAsBox(1.f/METERTOPIXEL, HEIGHT/METERTOPIXEL);
  b2FixtureDef leftWallFixDef;
  leftWallFixDef.density = 0.f;
  leftWallFixDef.shape = &leftWallShape;
  LeftWall->CreateFixture(&leftWallFixDef);

  b2BodyDef rightWallDef;
  rightWallDef.position = b2Vec2(0/METERTOPIXEL, 0/METERTOPIXEL);
  rightWallDef.type = b2_staticBody;
  b2Body* RightWall = _world.CreateBody(&rightWallDef);
  b2PolygonShape rightWallShape;
  rightWallShape.SetAsBox(1.f/METERTOPIXEL, HEIGHT/METERTOPIXEL);
  b2FixtureDef rightWallFixDef;
  rightWallFixDef.density = 0.f;
  rightWallFixDef.shape = &rightWallShape;
  RightWall->CreateFixture(&rightWallFixDef);

  b2Vec2 mVertices[2];
  mVertices[0].x = 0/METERTOPIXEL;
  mVertices[1].x = 0/METERTOPIXEL;

  mVertices[0].y = 0/METERTOPIXEL;
  mVertices[1].y = 100/METERTOPIXEL;
  
  b2BodyDef CubeDef;
  CubeDef.position = b2Vec2(850/METERTOPIXEL, 0/METERTOPIXEL);
  CubeDef.type = b2_dynamicBody;
  CubeDef.userData = &_boat;
  CubeDef.fixedRotation = true;
  b2Body* Cube = _world.CreateBody(&CubeDef);
  b2PolygonShape CubeShape;
  CubeShape.Set(mVertices, 2);
  b2FixtureDef CubeFixDef;
  CubeFixDef.density = 0.f;
  CubeFixDef.friction = 0.7f;
  CubeFixDef.shape = &CubeShape;
  Cube->CreateFixture(&CubeFixDef);
}
