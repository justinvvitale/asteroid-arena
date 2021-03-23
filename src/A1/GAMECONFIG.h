//
// Created by dim on 21/03/2021.
//

#ifndef I3D_GAMECONFIG_H
#define I3D_GAMECONFIG_H

// Config for game (Relates to everything with A1)
// You can find ENGINECONFIG.h under core, it is the config for the engine, mainly debug stuff, but gameplay related is all here.


// What the value means:
// > Colours are defined as a vector3 (R, G, B) from a value from 0-1
// > Any other value is either relative to the 1000 by 1000 game space or an in-line comment explaining.

// Arena
const float ARENA_SIZE = 995;


// Ship
const int SHIP_SIZE = 80;

const Vector3 SHIP_COLOUR = Vector3(0, 0, 0);
const Vector3 SHIP_COLOUR_OUTLINE = Vector3(1, 1, 1);

const float SHIP_MAX_SPEED = 800;
const float SHIP_ACCELERATION = 0.1; // 0.1 = 10% increase in velocity per tick
const float SHIP_DECELERATION = 0.07; // 0.1 = 10% decrease in velocity per tick
const float SHIP_TURN_SPEED = 5;

const char SHIP_FORWARD_KEY = 'w';
const char SHIP_TURN_LEFT_KEY = 'a';
const char SHIP_TURN_RIGHT_KEY = 'd';

#endif //I3D_GAMECONFIG_H
