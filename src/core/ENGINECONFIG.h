//
// Created by dim on 21/03/2021.
//

#ifndef I3D_ENGINECONFIG_H
#define I3D_ENGINECONFIG_H

// Colours are defined as a vector3 (R, G, B) from a value from 0-1
const Vector3 DEFAULT_COLOUR = Vector3(1, 1, 1);

const bool is3D = true;

const float POINT_SIZE = 5;

// Debugging
const bool DEBUG_DRAW_COLLIDERS = false;
const Vector3 DEBUG_DRAW_COLLIDERS_COLOUR = Vector3(1, 0, 1);

const bool DEBUG_DRAW_PARTICLE_EMITTERS = false;
const Vector3 DEBUG_DRAW_PARTICLE_EMITTERS_COLOUR = Vector3(0.5, 0, 1);


#endif //I3D_ENGINECONFIG_H
