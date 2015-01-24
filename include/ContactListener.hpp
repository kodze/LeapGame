//
// ContactListener.hpp for LeapGame in /home/gouy_e/rendu/LeapGame/include
// 
// Made by Elliot Gouy
// Login   <gouy_e@epitech.net>
// 
// Started on  Sat Jan 24 16:48:13 2015 Elliot Gouy
// Last update Sat Jan 24 17:08:08 2015 Elliot Gouy
//

#include <Box2D/Box2D.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct MyContact {
  b2Fixture *fixtureA;
  b2Fixture *fixtureB;
  bool operator==(const MyContact& other) const
  {
    return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
  }
};

class MyContactListener : public b2ContactListener {

public:
  std::vector<MyContact>	_contacts;

  MyContactListener();
  ~MyContactListener();

  virtual void BeginContact(b2Contact *);
  virtual void EndContact(b2Contact *);
};
