//
// Created by Dimme on 8/03/2021.
//

#ifndef I3D_KEYREGISTRY_H
#define I3D_KEYREGISTRY_H

#include <iostream>
#include <set>
#include <vector>

class KeyRegistry {
private:
    KeyRegistry() = default;

    static std::set<unsigned char>* keyState;
public:
    static void init();

    static void keyPress(unsigned char key, int x, int y);

    static void keyUp(unsigned char key, int x, int y);

    static void clear();

    static bool isPressed(unsigned char key);

    static std::vector<unsigned char> getPressed();

};


#endif //I3D_KEYREGISTRY_H
