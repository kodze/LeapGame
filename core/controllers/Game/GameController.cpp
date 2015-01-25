#include "../../../include/Game.hpp"

void loadSprite(int height, int width, int cotePx, Sprite *tabDst, string fileName, Texture *tExplosion)
{
    int size = width * height;
    int pos = 0;

    int x;
    int y;
    while (pos < size)
    {
        x = pos % width;
        y = pos / height;
        tExplosion[pos].loadFromFile(fileName, sf::IntRect(x * cotePx + 10, y * cotePx + 10, cotePx - 15, cotePx - 15));
        tabDst[pos].setTexture(tExplosion[pos]);
	tabDst[pos].setOrigin((cotePx - 15) / 2, (cotePx - 15) / 2);
        ++pos;
    }
}


GameController::GameController(RenderWindow *window, SFMLKernel *kernel, const string &name) : IController(window, kernel, name), _gravity(0.0f, 30.f) ,_world(_gravity), _boat("boat"), _rock("rock"), _life(100) , _blue("blue") , _purple("purple") , _red("red") , _green("green"), _point(0), _swap(false), _mod(40)
{
  this->init();
  loadSprite(4, 4, 128, _explosion, "res/img/explosion.png", _tExplosion);
}

GameController::~GameController()
{

}

int GameController::eventManager(Event event)
{
  if (event.type == sf::Event::KeyPressed)
    {
    }

}

void    GameController::addExplosion(double x, double y) {
    _listExplosions.push_back(new Explosion(x, y, _explosion));
}

void		GameController::BonusFactory()
{
  int r;
  if (random() % 307 == 17)
    {
      b2BodyDef	RockDef;
      b2Vec2	move(-6.f, 5.f);
      b2FixtureDef RockFixDef;
      RockDef.linearVelocity = move;
      RockDef.bullet = true;
      RockDef.position = b2Vec2((random() % (WIDTH - 200) + 100) /METERTOPIXEL,0.f);
      RockDef.type = b2_kinematicBody;
      RockDef.fixedRotation = true;
      r = random() % 4;
      if (r == 0)
	{
	  RockDef.userData = &_blue;
	  RockFixDef.userData = &_blue;
	}
      else if (r == 1)
	{
	  RockDef.userData = &_purple;
	  RockFixDef.userData = &_purple;
	}
      else if (r == 2)
	{
	  RockDef.userData = &_red;
	  RockFixDef.userData = &_red;
	}
      else
	{
	  RockDef.userData = &_green;
	  RockFixDef.userData = &_green;
	}
      b2Body* Rock = _world.CreateBody(&RockDef);
      b2PolygonShape RockShape;
      RockShape.SetAsBox(20/METERTOPIXEL, 20/METERTOPIXEL);
      RockFixDef.density = 0.f;
      RockFixDef.friction = 0.f;
      RockFixDef.shape = &RockShape;
      Rock->CreateFixture(&RockFixDef);
    }
}

void		GameController::RocketFactory()
{
  if (random() % _mod == 2)
    {
      b2BodyDef	RockDef;
      b2Vec2	move((random() % 25 + 8) * -1, 0);
      RockDef.linearVelocity = move;
      RockDef.bullet = true;
      RockDef.position = b2Vec2(WIDTH/METERTOPIXEL, (random() % (HEIGHT - 200) + 100) /METERTOPIXEL);
      RockDef.type = b2_kinematicBody;
      RockDef.fixedRotation = true;
      RockDef.userData = &_rock;
      b2Body* Rock = _world.CreateBody(&RockDef);
      b2PolygonShape RockShape;
      RockShape.SetAsBox(30/METERTOPIXEL, 5/METERTOPIXEL);
      b2FixtureDef RockFixDef;
      RockFixDef.density = 0.f;
      RockFixDef.friction = 0.f;
      RockFixDef.shape = &RockShape;
      RockFixDef.userData = &_rock;
      Rock->CreateFixture(&RockFixDef);
      
    }
}

int	GameController::display()
{

  float32 timeStep = 1.0f / 60.0f;
  int32 iterations = 8;

  RocketFactory();
  BonusFactory();
  
  _window->clear();
  _backgroundtext.clear(sf::Color(0, 0, 0, 0));
  _backgroundtext2.clear(sf::Color(0, 0, 0, 0));
  _backgroundtext3.clear(sf::Color(0, 0, 0, 0));
  _world.Step(timeStep, iterations, 2);

  _background.move(-6.f, 0);
  _background2.move(-6.f, 0);
  if (_background.getPosition().x <= -15360.f)
    _background.setPosition(15360.f, 0);
  if (_background2.getPosition().x <= -15360.f)
    _background2.setPosition(15360.f, 0);
  _window->draw(_background);
  _window->draw(_background2);

  std::vector<int>::size_type sz = _contact->_contacts.size();

  if (_swapClock.getElapsedTime().asSeconds() >= 5.f)
    _swap = false;
  if (_modClock.getElapsedTime().asSeconds() >= 5.f)
    _mod = 40;
  
  for (unsigned int i = 0; i < sz; i++)
    {
      string	*A = (string *)(_contact->_contacts[i].fixtureA->GetUserData());
      string	*B = (string *)(_contact->_contacts[i].fixtureB->GetUserData());

      if (A != NULL && B != NULL  &&
	  ((*A == "boat" && *B == "rock")
	   || (*A == "rock" && *B == "boat")))
	{
	  b2Vec2 vec = _contact->_contacts[i].fixtureA->GetBody()->GetPosition();
	  // std::cout << "Add Explosion in X: " << vec.x << " Y: " << vec.y << endl;
	  addExplosion(vec.x * METERTOPIXEL, vec.y * METERTOPIXEL);
	  if (*B == "rock")
	    {
	      _life += _contact->_contacts[i].fixtureA->GetBody()->GetLinearVelocity().x;
	      _world.DestroyBody(_contact->_contacts[i].fixtureB->GetBody());
	    }
	  else if (*A == "rock")
	    {
	      _life += _contact->_contacts[i].fixtureB->GetBody()->GetLinearVelocity().x;
	      _world.DestroyBody(_contact->_contacts[i].fixtureA->GetBody());
	    }
	}
      else if (A != NULL && B != NULL  &&
	       ((*A == "boat" && *B == "green")
		|| (*A == "green" && *B == "boat")))
	{
	  _life += 30;
	  if (_life > 100)
	    _life = 100;
	  if (*B == "green")
	    _world.DestroyBody(_contact->_contacts[i].fixtureB->GetBody());
	  else if (*A == "green")
	    _world.DestroyBody(_contact->_contacts[i].fixtureA->GetBody());
	}
      else if (A != NULL && B != NULL  &&
	       ((*A == "boat" && *B == "blue")
		|| (*A == "blue" && *B == "boat")))
	{
	  _point += 30;
	  if (*B == "blue")
	    _world.DestroyBody(_contact->_contacts[i].fixtureB->GetBody());
	  else if (*A == "blue")
	    _world.DestroyBody(_contact->_contacts[i].fixtureA->GetBody());
	}
      else if (A != NULL && B != NULL  &&
	       ((*A == "boat" && *B == "purple")
		|| (*A == "purple" && *B == "boat")))
	{
	  _swapClock.restart();
	  _swap = true;
	  if (*B == "purple")
	    _world.DestroyBody(_contact->_contacts[i].fixtureB->GetBody());
	  else if (*A == "purple")
	    _world.DestroyBody(_contact->_contacts[i].fixtureA->GetBody());
	}
      else if (A != NULL && B != NULL  &&
	       ((*A == "boat" && *B == "red")
		|| (*A == "red" && *B == "boat")))
	{
	  _modClock.restart();
	  _mod = 10;
	  if (*B == "red")
	    _world.DestroyBody(_contact->_contacts[i].fixtureB->GetBody());
	  else if (*A == "red")
	    _world.DestroyBody(_contact->_contacts[i].fixtureA->GetBody());
	}
    }

  if (_kernel->_listener->swipe_b)
    {
      b2Vec2 force(0, _kernel->_listener->vector_h[1] * -333);
      _particleSystem->ApplyLinearImpulse(0, _particleSystem->GetParticleCount() - 1, force);

      // b2Vec2 force2(_kernel->_listener->vector_h[0] * 600, 0);
      // _player->ApplyForceToCenter(force2, true);

      _kernel->_listener->swipe_b = 0;
    }

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
      if (BodyIterator->GetUserData())
	{
	  if (*((string *)(BodyIterator->GetUserData())) == string("boat"))
	    {
	      Sprite	box(_box);
	      double	hand_tmp;
	      
	      b2Vec2 force2 = _player->GetLinearVelocity();

	      hand_tmp = _kernel->_listener->hand[0];
	      if (_swap == true)
		hand_tmp *= -1.f;
	      force2.x += hand_tmp / 80.f;
	      _player->SetLinearVelocity(force2);
	      if ((BodyIterator->GetPosition().y * METERTOPIXEL) < HEIGHT / 2)
	      	{
	      	  b2Vec2 force2 = _player->GetLinearVelocity();
	      	  force2.y += 3;
	      	  _player->SetLinearVelocity(force2);
	      	}
	      if ((BodyIterator->GetPosition().y * METERTOPIXEL) > (HEIGHT - HEIGHT / 4))
	      	{
	      	  b2Vec2 force2(0, -40);
	      	  _player->ApplyForceToCenter(force2, true);
	      	}
	      box.setPosition(METERTOPIXEL * (BodyIterator->GetPosition().x),
			      METERTOPIXEL * (BodyIterator->GetPosition().y));
	      b2Vec2 force = _player->GetLinearVelocity();

	      if (force.x > 20.f)
		force.x = 20.f;
	      if (force.y > 10.f)
		force.y = 10.f;

	      _player->SetLinearVelocity(force);

	      _window->draw(box);

	    }
	  else if (*((string *)(BodyIterator->GetUserData())) == string("rock"))
	    {
	      Sprite	rock(_missile);

	      rock.setPosition(METERTOPIXEL * (BodyIterator->GetPosition().x),
			       METERTOPIXEL * (BodyIterator->GetPosition().y));
	      _window->draw(rock);
	    }
	  else if (*((string *)(BodyIterator->GetUserData())) == string("blue"))
	    {
	      Sprite	box_blue(_box_blue);

	      box_blue.setPosition(METERTOPIXEL * (BodyIterator->GetPosition().x),
			       METERTOPIXEL * (BodyIterator->GetPosition().y));
	      _window->draw(box_blue);
	    }
	  else if (*((string *)(BodyIterator->GetUserData())) == string("purple"))
	    {
	      Sprite	box_purple(_box_purple);

	      box_purple.setPosition(METERTOPIXEL * (BodyIterator->GetPosition().x),
			       METERTOPIXEL * (BodyIterator->GetPosition().y));
	      _window->draw(box_purple);
	    }
	  else if (*((string *)(BodyIterator->GetUserData())) == string("red"))
	    {
	      Sprite	box_red(_box_red);

	      box_red.setPosition(METERTOPIXEL * (BodyIterator->GetPosition().x),
			       METERTOPIXEL * (BodyIterator->GetPosition().y));
	      _window->draw(box_red);
	    }
	  else if (*((string *)(BodyIterator->GetUserData())) == string("green"))
	    {
	      Sprite	box_green(_box_green);

	      box_green.setPosition(METERTOPIXEL * (BodyIterator->GetPosition().x),
			       METERTOPIXEL * (BodyIterator->GetPosition().y));
	      _window->draw(box_green);
	    }
	}
    }

    // Display Sprite


    int size = _listExplosions.size();
    Explosion *tmp;
    for (int i = 0; i < size; i++)
    {
        tmp = _listExplosions.at(i);
        if (tmp->_i < 16)
        {
            tmp->_sprite[tmp->_i].setPosition(tmp->_x, tmp->_y);

            _window->draw(tmp->_sprite[tmp->_i]);
            ++tmp->_i;
            if (tmp->_x - 15 >= 0)
                tmp->_x -= 15;
            else
                tmp->_x = 0;
        }
        else
	  {
	    _listExplosions.erase(_listExplosions.begin() + i);
	    size = _listExplosions.size();
	  }
    }
    sf::RectangleShape rectangle(sf::Vector2f(200, 15));
    rectangle.setPosition(20, HEIGHT - 35.);
    _window->draw(rectangle);
    sf::RectangleShape rectangle2(sf::Vector2f(194, 9));
    rectangle2.setPosition(23, HEIGHT - 32.);
    rectangle2.setFillColor(sf::Color(0, 0, 0));
    _window->draw(rectangle2);
    sf::RectangleShape rectangle3(sf::Vector2f(_life * 194.f / 100.f, 9));
    rectangle3.setPosition(23, HEIGHT - 32.);
    rectangle3.setFillColor(sf::Color(255 * ((100.f - _life) / 100.f), 255 * (_life / 100.f), 0));
    _window->draw(rectangle3);
}

Texture&	GameController::LoadImage(const std::string& img, bool b)
{
  sf::Image	tmp;
  tmp.loadFromFile(img);
  if (b)
    tmp.createMaskFromColor(sf::Color(255,255,255),0);
  else
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

  _background.setTexture(LoadImage("data/background.png"));
  _background.setOrigin(0,0);
  _background.setPosition(0,0);
  _background2.setTexture(LoadImage("data/background2.png"));
  _background2.setOrigin(0,0);
  _background2.setPosition(15360.f, 0);
  _water.setTexture(LoadImage("data/water.png"));
  _water.setOrigin(8, 8);
  _box.setTexture(LoadImage("data/boat.png"));
  _box.setOrigin(107.5f, 140.5f);
  _missile.setTexture(LoadImage("data/missile.jpg"));
  _box_blue.setTexture(LoadImage("data/box_blue.png", true));
  _box_purple.setTexture(LoadImage("data/box_purple.png", true));
  _box_red.setTexture(LoadImage("data/box_red.png", true));
  _box_green.setTexture(LoadImage("data/box_green.png", true));

  
  _backgroundtext.create(WIDTH, HEIGHT);
  _backgroundtext2.create(WIDTH, HEIGHT);
  _backgroundtext3.create(WIDTH, HEIGHT);

  _particleSystemDef.radius = 6/METERTOPIXEL;
  _particleSystem = _world.CreateParticleSystem(&_particleSystemDef);
  _contact = new MyContactListener();
  _world.SetContactListener(_contact);
  
  b2ParticleDef		pd;

  pd.lifetime = 0.0f;
  pd.flags = b2_tensileParticle;
  pd.velocity.Set(1, 0);
  
  for (int j = 1000; j < HEIGHT; j += 2)
    {
      for (int i = 0; i <= WIDTH; i += 5)
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

  b2BodyDef topDef;
  topDef.position = b2Vec2(0/METERTOPIXEL, 0/METERTOPIXEL);
  topDef.type = b2_staticBody;
  b2Body* Top = _world.CreateBody(&topDef);
  b2PolygonShape topShape;
  topShape.SetAsBox(WIDTH/METERTOPIXEL, 1.f/METERTOPIXEL);
  b2FixtureDef topFixDef;
  topFixDef.density = 0.f;
  topFixDef.shape = &topShape;
  Top->CreateFixture(&topFixDef);

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

  b2Vec2 mVertices[8];
  mVertices[0].x = -70/ METERTOPIXEL;
  mVertices[0].y = -16/ METERTOPIXEL;
  mVertices[1].x = -10/ METERTOPIXEL;
  mVertices[1].y = -16/ METERTOPIXEL;
  mVertices[2].x = -10/ METERTOPIXEL;
  mVertices[2].y = -56/ METERTOPIXEL;
  mVertices[3].x = 10/ METERTOPIXEL;
  mVertices[3].y = -56/ METERTOPIXEL;
  mVertices[4].x = 10/ METERTOPIXEL;
  mVertices[4].y = -16/ METERTOPIXEL;
  mVertices[5].x = 70/ METERTOPIXEL;
  mVertices[5].y = -16/ METERTOPIXEL;
  mVertices[6].x = 30/ METERTOPIXEL;
  mVertices[6].y = 24/ METERTOPIXEL;
  mVertices[7].x = -30/ METERTOPIXEL;
  mVertices[7].y = 24/ METERTOPIXEL;

  b2BodyDef CubeDef;
  CubeDef.position = b2Vec2(850/METERTOPIXEL, 750/METERTOPIXEL);
  CubeDef.type = b2_dynamicBody;
  CubeDef.userData = &_boat;
  CubeDef.fixedRotation = true;
  _player = _world.CreateBody(&CubeDef);
  b2PolygonShape CubeShape;
  CubeShape.Set(mVertices, 8);
  //CubeShape.SetAsBox(70/METERTOPIXEL, 20/METERTOPIXEL);
  b2FixtureDef CubeFixDef;
  CubeFixDef.density = 0.f;
  CubeFixDef.friction = 0.f;
  CubeFixDef.shape = &CubeShape;
  CubeFixDef.userData = &_boat;
  _player->CreateFixture(&CubeFixDef);
}
