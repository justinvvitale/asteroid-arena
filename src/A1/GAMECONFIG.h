//
// Created by dim on 21/03/2021.
//

#ifndef I3D_GAMECONFIG_H
#define I3D_GAMECONFIG_H

// Config for game (Relates to everything with A1)
// You can find ENGINECONFIG.h under core, it is the config for the engine, mainly debug stuff, but gameplay related is all here.


// What the value means:
// > Colours are defined as a vector3 (R, G, B) from a value from 0-1
// > Any other value is either relative to the +-1000 by +-1000 game space or an in-line comment explaining.

// Arena
const float ARENA_WIDTH = 1990;
const float ARENA_HEIGHT = 1990;
const Vector3 ARENA_COLOUR = Vector3(1, 1, 1);
const Vector3 ARENA_WARN_COLOUR = Vector3(1, 0, 0);
const float ARENA_WARN_DIST = 250;


// Ship
const int SHIP_SIZE = 70;
const float SHIP_COLLIDER_RELAX = 0.5f; // How much % smaller collider should be, allows more friendly collision detection.

const Vector3 SHIP_COLOUR = Vector3(0, 0, 0);
const Vector3 SHIP_COLOUR_OUTLINE = Vector3(1, 1, 1);

const float SHIP_MAX_SPEED = 400;
const float SHIP_SHOOT_VELOCITY = 5 ; // Speed which bullets shoot
const int SHIP_SHOOT_COOLDOWN = 150 ; // MS seconds between shooting
const float SHIP_ACCELERATION = 0.8f; // % increase * dt
const float SHIP_DECELERATION = 0.6f; // % decrease * dt
const float SHIP_TURN_SPEED = 200;

const char SHIP_FORWARD_KEY = 'w';
const char SHIP_TURN_LEFT_KEY = 'a';
const char SHIP_TURN_RIGHT_KEY = 'd';
const char SHIP_SHOOT_KEY = 32;

// WaveManagement
const int ASTEROID_SPAWN_RATE = 500; // Spawn asteroid every X ms
const int ASTEROID_CLEAR_RATE = 1000; // Clear asteroids out of range every X ms
const int ASTEROID_MAX = 50; // How many asteroids can be in the game at any one point (Prevent spawn).


// Asteroids
const float ASTEROID_SEGMENTS_MIN = 6; // How many points an asteroid should have MIN. 360 = full circle
const float ASTEROID_SEGMENTS_MAX = 20; // How many points an asteroid should have MAX. 360 = full circle
const float ASTEROID_MIN_RADIUS = 100; // Min size of asteroid  (All these are inclusive)
const float ASTEROID_MAX_RADIUS = 100; // Max size of asteroid
const float ASTEROID_MIN_SPEED = 200; // Min speed of asteroid
const float ASTEROID_MAX_SPEED = 700; // Max speed of asteroid
const float ASTEROID_MIN_ROTATION = 0; // Min speed of asteroid rotation
const float ASTEROID_MAX_ROTATION = 50; // Max speed of asteroid rotation
const float ASTEROID_RADIUS_VARIATION_RANGE = 30; // The range += the that radius can vary per point

// Debug (Not directly related to engine)
const bool DEBUG_DRAW_LAUNCH_CIRCLE = false;
const Vector3 DEBUG_DRAW_LAUNCH_CIRCLE_COLOUR = Vector3(1, 0.5, 1);

#endif //I3D_GAMECONFIG_H
