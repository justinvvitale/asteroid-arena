//
// Created by dim on 21/03/2021.
//

#ifndef I3D_CONFIG_H
#define I3D_CONFIG_H

// Colours are defined as a vector3 (R, G, B) from a value from 0-1

// Ship
const int SHIP_SIZE = 80;

const Vector3 SHIP_COLOUR = Vector3(0,0,0);
const Vector3 SHIP_COLOUR_OUTLINE = Vector3(1,1,1);

const float SHIP_SPEED = 800;
const float SHIP_TURN_SPEED = 5;

const char SHIP_FORWARD_KEY = 'w';
const char SHIP_TURN_LEFT_KEY = 'a';
const char SHIP_TURN_RIGHT_KEY = 'd';

#endif //I3D_CONFIG_H
