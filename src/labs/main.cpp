#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

#define KEY_ESC 27

#define PLATFORM_ROTATION_DELTA 5.0
#define CANNON_ROTATION_DELTA 5.0
#define CAMERA_ROTATION_DELTA 5.0

bool g_show_axes = true;

float g_camera_position_x, g_camera_position_y, g_camera_position_z;
float g_camera_rotation = 0.0;

float g_platform_rotation = 0.0;
float g_cannon_rotation = 0.0;

// Calculate the camera position based on the g_camera_rotation variable
// which should be between 0 and 360, and represents the camera POSITION
// along a circle around the cannon. In the place_camera() function we will
// make the camera look at the origin from this position.
void update_camera_position()
{
    //g_camera_position_x = 0.0;
    g_camera_position_y = 20.0;                                        // *** EXERCISE 2c
    //g_camera_position_z = 30.0;                                      // *** EXERCISE 2c

    g_camera_position_x = 30.0 * cos(g_camera_rotation * 3.14/180.0);  // *** EXERCISE 8
    g_camera_position_z = 30.0 * sin(g_camera_rotation * 3.14/180.0);  // *** EXERCISE 8
}

void on_key_press(unsigned char key, int x, int y)
{
    switch (key) {
        // toggle axes display
        case 'X':
        case 'x':
            g_show_axes = !g_show_axes;                                 // *** EXERCISE 1
            break;
            // rotate platform clockwise
        case 'A':
        case 'a':
            g_platform_rotation -= PLATFORM_ROTATION_DELTA;             // *** EXERCISE 7
            break;
            // rotate platform counter-clockwise
        case 'D':
        case 'd':
            g_platform_rotation += PLATFORM_ROTATION_DELTA;             // *** EXERCISE 7
            break;
            // rotate cannon up
        case 'W':
        case 'w':
            g_cannon_rotation += CANNON_ROTATION_DELTA;                 // *** EXERCISE 7
            break;
            // rotate cannon down
        case 'S':
        case 's':
            g_cannon_rotation -= CANNON_ROTATION_DELTA;                 // *** EXERCISE 7
            break;
            // rotate camera clockwise
        case '<':
        case ',':
            g_camera_rotation -= CAMERA_ROTATION_DELTA;                 // *** EXERCISE 8
            break;
            // rotate camera counterclockwise
        case '>':
        case '.':
            g_camera_rotation += CAMERA_ROTATION_DELTA;                 // *** EXERCISE 8
            break;
            // quit
        case KEY_ESC:
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
}

void draw_cannon()
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();

    // draw platform
    glRotatef(g_platform_rotation, 0.0, 1.0, 0.0);                // *** EXERCISE 4
    glTranslatef(0.0, 1.0, 0.0);                                  // *** EXERCISE 3
    glPushMatrix();                                               // *** EXERCISE 3
    glScalef(10.0, 1.0, 10.0);                                  // *** EXERCISE 3
    glutWireCube(1.0);
    glPopMatrix();                                                // *** EXERCISE 3

    // draw cannon
    glRotatef(g_cannon_rotation, 0.0, 0.0, 1.0);                  // *** EXERCISE 6
    glTranslatef(2.5, 0.0, 0.0);                                  // *** EXERCISE 5
    glPushMatrix();
    glScalef(5.0, 2.0, 2.0);                                    // *** EXERCISE 5
    glutWireCube(1.0);
    glPopMatrix();                                                // *** EXERCISE 5

    glPopMatrix();
}

void draw_axes()
{
    if(!g_show_axes) return;                                      // *** EXERCISE 1
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-10.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -10.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -10.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
}

void place_camera()
{
    gluLookAt(g_camera_position_x, g_camera_position_y, g_camera_position_z,
              0, 0, 0,
              0, 1, 0);                                             // *** EXERCISE 2b
}

void render_frame()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    place_camera();
    draw_axes();
    draw_cannon();
}

void on_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_frame();
    glutSwapBuffers();
    int err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("Error: %s\n", gluErrorString(err));
    }
}

void on_idle()
{
    update_camera_position();
    glutPostRedisplay();
}

void on_reshape(int w, int h)
{
    // Setup the viewport transform
    glViewport(0, 0, w, h);

    // Setup the projection transform
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 1000.0);                     // *** EXERCISE 2a
}

void init_app(int *argcp, char **argv)
{
    glutInit(argcp, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Tutorial 7");
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_key_press);
    glutDisplayFunc(on_display);
    glutIdleFunc(on_idle);
}

int main(int argc, char **argv)
{
    init_app(&argc, argv);
    glutMainLoop();
    return(EXIT_SUCCESS);
}
