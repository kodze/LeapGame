/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#include "../include/leap.hpp"

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
    const Frame frame = controller.frame();
    HandList handList = frame.hands();
    GestureList  gesture = frame.gestures();
    nbHand = frame.hands().count();

    hand[0] = 0.f;
    hand[1] = 0.f;
    hand[2] = 0.f;
    for(HandList::const_iterator hl = handList.begin(); hl != handList.end(); hl++) {
      Hand h = *hl;
      hand[0] = h.palmPosition().x;
      hand[1] = h.palmPosition().y;
      hand[2] = h.palmPosition().z;
    }

    for (GestureList::const_iterator gl = gesture.begin(); gl != gesture.end(); gl++) {
        Gesture gest = *gl;
        if (gest.type() == Gesture::TYPE_SWIPE)
        {
            SwipeGesture swipe = gest;
            vector_h[0] = swipe.direction().x;
            vector_h[1] = swipe.direction().y;
            vector_h[2] = swipe.direction().z;
            gest_duration = gest.duration();
            speed = swipe.speed();
            swipe_b = true;
        }
	if (gest.type() == Gesture::TYPE_KEY_TAP)
	  click = true;
    }
}

void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}
