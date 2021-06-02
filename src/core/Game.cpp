//
// Created by Dimme on 11/03/2021.
//

#include "Game.h"
#include "input/InputRegistry.h"
#include "Renderer.h"

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

#endif

int Game::state = 0;


float Game::lastIdleTime = 0.0;
float Game::dt = 1;
long int Game::tick = 0;

long int Game::elapsed = 0;
long int Game::elapsedSeconds = 0;

long int Game::lastSecondCheck = -1;

bool Game::paused = false;
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
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(1000, 1000);

    glutCreateWindow(name.c_str());

    glutFullScreen();

    init();
    InputRegistry::init();

    // Callbacks
    glutDisplayFunc(Game::display);
    glutReshapeFunc(Game::reshape);
    glutIdleFunc(Game::idle);

    glutMouseFunc(InputRegistry::mouse);
    glutPassiveMotionFunc(InputRegistry::mouseMotion);
    glutMotionFunc(InputRegistry::mouseMotion);
    glutKeyboardFunc(InputRegistry::keyPress);
    glutKeyboardUpFunc(InputRegistry::keyUp);

    glutMainLoop();
}

void Game::init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    // Enable lighting
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Lighting config
    GLfloat qaAmbientLight[]	= {0.1, 0.1, 0.1, 1.0};
//    GLfloat qaDiffuseLight[]	= {0.8, 0.8, 0.8, 1.0};
//    GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    // Set global
    GLfloat qaLightPosition[]	= {0, 0, 0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutSetCursor(GLUT_CURSOR_NONE);

    glPointSize(POINT_SIZE);

    // Set last idle
    lastIdleTime = (float) glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    Renderer::glInitialized();
}

// Callbacks

void Game::reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = (GLfloat) w / (GLfloat) h;

    gluPerspective(45.0, aspectRatio, 1.0, 100000000000.0 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Game::display() {
    if(engine == nullptr) return;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLoadIdentity();

    engine->render();

    int err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("display: %s\n", gluErrorString(err));
    }

    glutSwapBuffers();
}

void Game::idle() {
    if(engine == nullptr) return;

    if (restartRequested) {
        performEntityCleanup();
        engine->resetSystems();
        engine->setScene(getDefaultScene());
        restartRequested = false;
        paused = false;
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

    if(InputRegistry::isPressed(27)){
        exit(0);
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



