#ifndef I3D_GAMECONFIG_H
#define I3D_GAMECONFIG_H
// Config for game (Relates to everything with A2)
// You can find ENGINECONFIG.h under core, it is the config for the engine, mainly debug stuff, but gameplay related is all here.

// What the value means:
// > Colours are defined as a vector3 (R, G, B) from a value from 0-1
// > Any other value is either relative to the +-1000 by +-1000 game space or an in-line comment explaining.

// Arena
// Find this in GAMECONFIG


// Ship
const float SHIP_COLLIDER_SIZE = 1.4f; // How large the collider sphere is

const float SHIP_MAX_SPEED = 700;
const float SHIP_BULLET_DAMAGE = 10; // How much damage each bullet does to thins it hit (with health)
const float SHIP_SHOOT_VELOCITY = 2; // Speed which bullets shoot
const int SHIP_SHOOT_COOLDOWN = 180; // MS seconds between shooting

const float SHIP_ACCELERATION = 0.4f; // % increase * dt
const float SHIP_DECELERATION = 0.4f; // % decrease * dt

const float SHIP_VERTICAL_SENSITIVITY = 0.03;
const float SHIP_HORIZONTAL_SENSITIVITY = 0.03;

// Controls
const char SHIP_FORWARD_KEY = 'w';
const char SHIP_MOVE_UP = 'e';
const char SHIP_MOVE_DOWN = 'q';
const char SHIP_VIEW_LEFT = 'a';
const char SHIP_VIEW_RIGHT = 'd';
const char SHIP_VIEW_BEHIND = 's';

// Camera
const bool CAMERA_LERP_POSITION = true; // Smooth camera follow (DISABLE IF TOO JITTERY)
const float CAMERA_POSITION_DAMP = 0.30; // Position delta 0-1
const float CAMERA_ROTATION_DAMP = 5; // Radian  delta

// WaveManagement
const int ASTEROID_WAVE_CD = 5000; // Wait X ms before next wave
const int ASTEROID_SPAWN_INCREMENT = 3; // Amount of asteroids to increase per wave
const int ASTEROID_CLEAR_RATE = 1000; // Clear asteroids out of range every X ms

// Misc

// Scoring
const int SCORE_AMOUNT_ASTEROID_KILL = 1;


// Asteroids
const float ASTEROID_HEALTH_MULTIPLIER = 0.2; // Multiplier * Radius = health
const int ASTEROID_STACK_MIN = 5; // How many stacks min
const int ASTEROID_STACK_MAX = 20; // How stacks max
const int ASTEROID_SECTOR_MIN = 5; // How many sectors min
const int ASTEROID_SECTOR_MAX = 20; // How sectors max
const float ASTEROID_MIN_RADIUS = 25; // Min size of asteroid  (All these are inclusive)
const float ASTEROID_MAX_RADIUS = 150; // Max size of asteroid
const float ASTEROID_MIN_SPEED = 200; // Min speed of asteroid
const float ASTEROID_MAX_SPEED = 400; // Max speed of asteroid
const float ASTEROID_MIN_ROTATION = 0; // Min speed of asteroid rotation
const float ASTEROID_MAX_ROTATION = 2; // Max speed of asteroid rotation

// 4.2 Bouncies 2 (Toggle) - Still works for A2 lol
const bool ASTEROID_COLLISION = true;

// Asteroid destroyed particles
const int ASTEROID_PARTICLE_DESTROY_COUNT = 120;
const int ASTEROID_PARTICLE_VELOCITY_RANGE = 340;
const int ASTEROID_PARTICLE_LIFESPAN = 2000;
const int ASTEROID_PARTICLE_LIFESPAN_VARIATION = 700;

#endif //I3D_GAMECONFIG_H
