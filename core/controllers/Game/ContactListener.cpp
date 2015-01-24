//
// ContactListener.cpp for LeapGame in /home/gouy_e/rendu/LeapGame/core/controllers/Game
// 
// Made by Elliot Gouy
// Login   <gouy_e@epitech.net>
// 
// Started on  Sat Jan 24 16:45:40 2015 Elliot Gouy
// Last update Sat Jan 24 17:11:49 2015 Elliot Gouy
//

#include "ContactListener.hpp"

MyContactListener::MyContactListener() : _contacts()
{}

MyContactListener::~MyContactListener()
{}

void	 MyContactListener::BeginContact(b2Contact* contact)
{
  MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
  _contacts.push_back(myContact);
}

void	MyContactListener::EndContact(b2Contact* contact)
{
  MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
  std::vector<MyContact>::iterator pos;
  pos = std::find(_contacts.begin(), _contacts.end(), myContact);
  if (pos != _contacts.end()) {
    _contacts.erase(pos);
  }
}
