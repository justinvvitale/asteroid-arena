//
// Created by Dimme on 11/03/2021.
//

#include "Game.h"
#include "input/KeyRegistry.h"

#if _WIN32

#   include <Windows.h>

#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else

#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#include <freeglut.h>

#endif

float Game::lastIdleTime = 0.0;
float Game::dt = 1;
long int Game::tick = 0;

bool Game::restartRequested = false;

Engine* Game::engine = nullptr;
Game::defaultScenePointer Game::getDefaultScene = nullptr;
std::queue<Entity*>* Game::toDelete;

void Game::start(int argc, char **argv, const std::string& name, Scene* (*defaultScene)()) {
    engine = new Engine();
    toDelete = new std::queue<Entity*>();
    getDefaultScene = defaultScene;
    engine->setScene(getDefaultScene());

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    glutInitWindowSize(1000,1000);

    glutCreateWindow(name.c_str());

    //glutFullScreen();

    init();
    KeyRegistry::init();

    // Callbacks
    glutDisplayFunc(Game::display);
    glutReshapeFunc(Game::reshape);
    glutIdleFunc(Game::idle);
    glutKeyboardFunc(KeyRegistry::keyPress);
    glutKeyboardUpFunc(KeyRegistry::keyUp);

    glutMainLoop();
}

void Game::init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    // Set last idle
    lastIdleTime = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
}

// Callbacks

void Game::reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = (GLfloat) w / (GLfloat) h;

    if (w <= h)
        glOrtho(-1000, 1000, -1000 / aspectRatio, 1000 / aspectRatio, 1.0, -1.0);
    else
        glOrtho(-1000 * aspectRatio, 1000 * aspectRatio, -1000, 1000, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Game::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    engine->render();

    int err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("display: %s\n", gluErrorString(err));
    }

    glutSwapBuffers();
}

void Game::idle() {
    if(restartRequested){
        performEntityCleanup();
        engine->ResetSystems();
        engine->setScene(getDefaultScene());
        restartRequested = false;
    }

    float cur_time = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    dt = cur_time - Game::lastIdleTime;
    lastIdleTime = cur_time;

    tick++;
    engine->tick();

    // Perform costly operation that aren't crucial
    if(Game::tick % 100){
        performEntityCleanup();
    }

    glutPostRedisplay();
}

Engine* Game::getEngine() {
    return engine;
}

Entity* Game::getEntity(EntityTag tag) {
    return engine->getScene()->getEntity(tag);
}

void Game::restart() {
    restartRequested = true;
}

void Game::stop() {
    exit(0);
}

void Game::queueCleanup(Entity* item) {
    toDelete->push(item);
}

void Game::performEntityCleanup() {
    while(!toDelete->empty()){
        delete toDelete->front();
        toDelete->pop();
    }
}

