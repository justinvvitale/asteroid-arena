//
// Created by dim on 21/03/2021.
//

#ifndef I3D_ENGINECONFIG_H
#define I3D_ENGINECONFIG_H

// Control
// Audio - Doesn't mix but also not in the spec so :)
const bool SOUND_ENABLED = false;

// Colours are defined as a vector3 (R, G, B) from a value from 0-1
const Vector3 DEFAULT_COLOUR = Vector3(1, 1, 1);

// Colours are defined as a vector3 (R, G, B) from a value from 0-1
const Vector3 UI_COLOUR = Vector3(1, 0, 1);

// A2
const float ARENA_SIZE = 2500;
const float ARENA_SPACING = ARENA_SIZE/20;
const float ARENA_WARN_DIST = 500;
const Vector3 ARENA_COLOUR = Vector3(0.82, 0.82,0.82);
const Vector3 ARENA_WARN_COLOUR = Vector3(0.7, 0,0);

const float POINT_SIZE = 5;

// Debugging
const bool DEBUG_DRAW_COLLIDERS = false;
const Vector3 DEBUG_DRAW_COLLIDERS_COLOUR = Vector3(1, 0, 1);

const bool DEBUG_DRAW_PARTICLE_EMITTERS = false;
const Vector3 DEBUG_DRAW_PARTICLE_EMITTERS_COLOUR = Vector3(0.5, 0, 1);


#endif //I3D_ENGINECONFIG_H
