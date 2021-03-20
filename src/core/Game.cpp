//
// Created by Dimme on 11/03/2021.
//

#include "Game.h"
#include "Engine.h"

float Game::lastIdleTime = 0.0;
float Game::dt = 1;
Engine* Game::engine = nullptr;

void Game::start(int argc, char **argv, const std::string& name, Engine* gEngine) {
    Game::engine = gEngine;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(name.c_str());

    //glutFullScreen();

    init();

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
    lastIdleTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
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
    float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    Game::dt = cur_time - Game::lastIdleTime;
    Game::lastIdleTime = cur_time;

    engine->tick();

    glutPostRedisplay();
}

Engine* Game::getEngine() {
    return engine;
}

