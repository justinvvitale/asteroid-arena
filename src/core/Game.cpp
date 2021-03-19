//
// Created by Dimme on 11/03/2021.
//

#include "Game.h"
#include "Engine.h"

void Game::start(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("I3D Assignment 1 (S3718796)");
    init();
    reshape(500, 500);

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

}

// Callbacks

void Game::reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspect = (double)w/h;
    if(w <= h)
        glOrtho(-1.0, 1.0,-1.0/aspect, 1.0/aspect, -1.0,1.0);
    else
        glOrtho(-1.0*aspect, 1.0*aspect,-1.0, 1.0, -1.0, 1.0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(0.0, 0.0, -5.0);
}

void Game::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glColor3ub( 255, 255, 255 );
    glBegin( GL_LINE_LOOP );
        glVertex2f( -1, -1 );
        glVertex2f(  1, -1 );
        glVertex2f(  1,  1 );
        glVertex2f( -1,  1 );

//    glVertex2f( -0.9, -0.9 );
//    glVertex2f(  0.9, -0.9 );
//    glVertex2f(  0.9,  0.9 );
//    glVertex2f( -0.9,  0.9 );

    glEnd();
//    glColor3f(1,1,1);
//
//    glPointSize(10);
//    glBegin(GL_LINE_LOOP);
//        glVertex3f(-0.5, -0.5, -0.5);
//        glVertex3f(0.5, -0.5, -0.5);
//        glVertex3f(0.5, 0.5, -0.5);
//        glVertex3f(-0.5, 0.5, -0.5);
//    glEnd();
//
//    glBegin(GL_QUADS);
//        glColor3f(0,1,0);
//
//        glVertex3f(-0.25, -0.25, -0.75); // 1
//        glVertex3f(0.75, -0.25, -0.75); // 2
//        glVertex3f(0.75, 0.75, -0.75); // 3
//        glVertex3f(-0.25,0.75, -0.75); // 4
//    glEnd();


    int err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("display: %s\n", gluErrorString(err));
    }

    glutSwapBuffers();
}

void Game::idle() {
    glutPostRedisplay();
}

