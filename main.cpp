#include "tools.h"

using namespace std;



//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // background color is white
    glColor3f(0.0f, 0.0f, 0.0f); // drawing color is black
    glPointSize(2.0); // a 'dot' is 2 by 2 pixels

    glMatrixMode(GL_PROJECTION); // set "camera shape"
    glLoadIdentity();

    gluOrtho2D(AXIS_X_MIN, AXIS_X_MAX, AXIS_Y_MIN, AXIS_Y_MAX);
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>






//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Cancer Plot"); // open the screen window
    myInit();
    
    CancerVisual::Setup();
    
    glViewport(0, 0, screenWidth, screenHeight);
    glutDisplayFunc(CancerVisual::myDisplay); // register redraw function
    glutMouseFunc(CancerVisual::myMouse);
    glutKeyboardFunc(CancerVisual::myKeyboard);
    
    glutMainLoop(); // go into a perpetual loop
}