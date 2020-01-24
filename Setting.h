#pragma once

//define 
#define KeyPressing sf::Event::KeyPressed
#define KeyReleasing sf::Event::KeyReleased
#define KeyEvent(EV) (Keyboard::isKeyPressed(Keyboard::EV))

//Gravity Setting:
const float GRAVITY = 0.7f;

//Position File Path:

//Source File Path:
#define Player_f "Source\\player_first.png"
#define PlatForm "Source\\Platform.png"
