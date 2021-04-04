//
// Created by Justin on 3/04/2021.
//

#ifndef I3D_GLOBAL_H
#define I3D_GLOBAL_H
// Random helper header which tracks variables which have to be persisted and any other random functions used for A1
// which don't have a place

// Global state constants
static const int STATE_BEGIN = 0;
static const int STATE_PLAY = 1;
static const int STATE_DEAD = 2;

// Track screen overlays and general state
// 0 = Initial await, 1 = Playing, 2 = GameOver
static int STATE_GLOBAL = STATE_BEGIN;

#endif //I3D_GLOBAL_H
