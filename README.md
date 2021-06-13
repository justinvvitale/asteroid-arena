# Asteroid Arena

OpenGl ECS game engine + implementations as part of the I3D course.

## Description

Asteroids (Think of that old game - 1979 Atari) was the main theme for this course and as such is what was created.

Course had two assignments, split into two distinct milestones.
1. 2D asteroid arena
2. 3D asteroid arena

Working states of the games are in A1 and A2 branch, respectively.
You can run fairly effortless using the submission zips (Just read the readme and run-in visual studio).

Please note that the code quality is not the best, it wasn't marked.

Final mark for subject was 90/100

## The ECS breakdown:
* Entity
    * Represents an object in the game, everything is an entity (E.g the ship). It's a data holder and has a position & rotation. An entity has many components and can have nested entities in a hierarchical fashion. 
* Component
    * A lego piece which add functionality to an entity. These could be a script component (E.g start & update functions to allow programmatic control) or mesh component (Holds the model details about the entity).
* System
    * Wrangles each component in the scene every "tick" if any special interactions need to happen.

Heavily inspired by Unity's structure
###### Rough diagram (Not exactly what I implemented but good overview)
![](https://miro.medium.com/max/960/1*yoLxDyQoFzC0je_oHkcppw.png)
#### Others
* Renderer
    * Just an abstraction and wrapper for raw OpenGL functions & some helper functions for opengl.
* Scene
    * Glorified container for entities, acts as the current view for the user, anything in the scene will be ran/rendered/updated each tick. You can remove/add stuff to it to disable/enable stuff happening in the game.
* Helpers
    * Math and graphic headers with just structs, function and general helpers for 2D and 3D operations (e.g vector2, vector3, quaternation).


## Gameplay
### A1 
[![A1 Video](https://img.youtube.com/vi/t7iieoqE3ok/0.jpg)](https://www.youtube.com/watch?v=t7iieoqE3ok)

### A2 
[![A2 Video](https://img.youtube.com/vi/D6NsQCRa_hc/0.jpg)](https://www.youtube.com/watch?v=D6NsQCRa_hc)

## Statistics
**27** CPP files
**42** H files

**4675** lines
**2664** lines of actual code

(Ignoring external libraries)
## Acknowledgments

Submission zips contain readmes with acknowledgements.
