#ifndef I3D_GAMECONFIG_H
#define I3D_GAMECONFIG_H
// Config for game (Relates to everything with A2)
// You can find ENGINECONFIG.h under core, it is the config for the engine, mainly debug stuff, but gameplay related is all here.

// What the value means:
// > Colours are defined as a vector3 (R, G, B) from a value from 0-1
// > Any other value is either relative to the +-1000 by +-1000 game space or an in-line comment explaining.

// Arena
const float ARENA_SIZE = 5000;
const Vector3 ARENA_COLOUR = Vector3(1, 1, 1);
const Vector3 ARENA_WARN_COLOUR = Vector3(1, 0, 0);
const float ARENA_WARN_DIST = 500;


// Ship
const int SHIP_SIZE = 70;
const float SHIP_COLLIDER_RELAX = 0.7f; // How much % smaller collider should be, allows more friendly collision detection.

const Vector3 SHIP_COLOUR = Vector3(0, 0, 0);
const Vector3 SHIP_COLOUR_OUTLINE = Vector3(1, 1, 1);

const float SHIP_MAX_SPEED = 700;
const float SHIP_BULLET_DAMAGE = 5; // How much damage each bullet does to thins it hit (with health)
const float SHIP_SHOOT_VELOCITY = 5; // Speed which bullets shoot
const int SHIP_SHOOT_COOLDOWN = 180; // MS seconds between shooting
const float SHIP_ACCELERATION = 0.8f; // % increase * dt
const float SHIP_DECELERATION = 0.7f; // % decrease * dt
const float SHIP_TURN_SPEED = 320;

const int SHIP_EXHAUST_DROP_RATE = 60; // Drop exhaust every X ms
const float SHIP_EXHAUST_START_SIZE = 2.5; // scale
const float SHIP_EXHAUST_END_SIZE = 0.5; // scale
const float SHIP_EXHAUST_LIFE = 150; // decay ms
const float SHIP_EXHAUST_SPEED = 200; // decay ms

const char SHIP_FORWARD_KEY = 'w';
const char SHIP_TURN_LEFT_KEY = 'a';
const char SHIP_TURN_RIGHT_KEY = 'd';

// WaveManagement
const int ASTEROID_WAVE_CD = 2000; // Wait X ms before next wave
const int ASTEROID_SPAWN_INCREMENT = 1; // Amount of asteroids to increase per wave
const int ASTEROID_CLEAR_RATE = 1000; // Clear asteroids out of range every X ms

// Misc
const bool DRAW_OUTER_ARENA_MASK = true; // Hide asteroids which aren't in the arena, adds more suspense.

// Scoring
const int SCORE_AMOUNT_ASTEROID_KILL = 1;


// Asteroids
const float ASTEROID_HEALTH_MULTIPLIER = 0.2; // Multiplier * Radius = health
const float ASTEROID_SEGMENTS_MIN = 6; // How many points an asteroid should have MIN. 360 = full circle
const float ASTEROID_SEGMENTS_MAX = 20; // How many points an asteroid should have MAX. 360 = full circle
const float ASTEROID_MIN_RADIUS = 100; // Min size of asteroid  (All these are inclusive)
const float ASTEROID_MAX_RADIUS = 100; // Max size of asteroid
const float ASTEROID_MIN_SPEED = 200; // Min speed of asteroid
const float ASTEROID_MAX_SPEED = 400; // Max speed of asteroid
const float ASTEROID_MIN_ROTATION = 0; // Min speed of asteroid rotation
const float ASTEROID_MAX_ROTATION = 50; // Max speed of asteroid rotation
const float ASTEROID_RADIUS_VARIATION_RANGE = 30; // The range += the that radius can vary per point
const Vector3 ASTEROID_COLOUR = Vector3(0.3, 0.3, 0.3);
const bool ASTEROID_SOLID = true;

// 4.2 Bouncies 2 (Toggle)
const bool ASTEROID_COLLISION = true;

// Asteroid destroyed particles
const int ASTEROID_PARTICLE_DESTROY_COUNT = 40;
const int ASTEROID_PARTICLE_VELOCITY_RANGE = 340;
const int ASTEROID_PARTICLE_LIFESPAN = 2000;
const int ASTEROID_PARTICLE_LIFESPAN_VARIATION = 700;

// Debug (Not directly related to engine), only shows corners
const bool DEBUG_DRAW_LAUNCH_CIRCLE = false;
const Vector3 DEBUG_DRAW_LAUNCH_CIRCLE_COLOUR = Vector3(1, 0.5, 1);


#endif //I3D_GAMECONFIG_H
