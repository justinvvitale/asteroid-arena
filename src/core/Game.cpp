//
// Created by Dimme on 11/03/2021.
//

#include "Game.h"
#include "input/KeyRegistry.h"
#include "ENGINECONFIG.h"

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

int Game::state = 0;


float Game::lastIdleTime = 0.0;
float Game::dt = 1;
long int Game::tick = 0;

long int Game::elapsed = 0;
long int Game::elapsedSeconds = 0;

long int Game::lastSecondCheck = -1;

bool Game::restartRequested = false;

Engine* Game::engine = nullptr;
Game::defaultScenePointer Game::getDefaultScene = nullptr;
std::set<Entity*> Game::toDelete;

void Game::start(int argc, char** argv, const std::string& name, Scene* (* defaultScene)()) {
    engine = new Engine();
    toDelete = std::set<Entity*>();
    getDefaultScene = defaultScene;
    engine->setScene(getDefaultScene());

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    glutInitWindowSize(1000, 1000);

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
    glEnable(GL_SCISSOR_TEST);

    glPointSize(POINT_SIZE);

    // Set last idle
    lastIdleTime = (float) glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
}

// Callbacks

void Game::reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = (GLfloat) w / (GLfloat) h;


    float size;

    if (w <= h) {
        glOrtho(-1000, 1000, -1000 / aspectRatio, 1000 / aspectRatio, 1.0, -1.0);
        size = h * aspectRatio;
    } else {
        glOrtho(-1000 * aspectRatio, 1000 * aspectRatio, -1000, 1000, 1.0, -1.0);
        size = w / aspectRatio;
    }

    glScissor((w / 2) - (size / 2), (h / 2) - (size / 2), size, size);

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
    if (restartRequested) {
        performEntityCleanup();
        engine->resetSystems();
        engine->setScene(getDefaultScene());
        restartRequested = false;
    }

    // State variables
    auto timeMS = (float) glutGet(GLUT_ELAPSED_TIME);
    float elapsedTimeSeconds = timeMS / 1000;
    dt = elapsedTimeSeconds - Game::lastIdleTime;
    lastIdleTime = elapsedTimeSeconds;

    elapsedSeconds = (int) elapsedTimeSeconds;
    elapsed = (int) timeMS;

    // Management
    tick++;

    engine->tick();

    // Perform costly operation that aren't crucial
    if (lastSecondCheck != (int) elapsedTimeSeconds) {
        lastSecondCheck = elapsedSeconds;

        performEntityCleanup();
    }

    glutPostRedisplay();
}

Engine* Game::getEngine() {
    return engine;
}

Entity* Game::getEntity(const std::string& tag) {
    return engine->getScene()->getEntity(tag);
}

void Game::restart() {
    restartRequested = true;
}

void Game::stop() {
    exit(0);
}

void Game::queueEntityCleanup(Entity* item) {
    toDelete.emplace(item);
}

void Game::performEntityCleanup() {
    for (auto it = toDelete.begin(); it != toDelete.end();) {
        delete *it;
        toDelete.erase(it++);
    }
}

