#ifndef GLUTILS_H
#define GLUTILS_H

#include "vector.h"

#define PRECISION 360
#define PI 3.14159265
#define DEFAULT_RADIUS 0.01

//draws a circle at (x,y) with radius r using OpenGL
void glDrawCircle(float x, float y, float r=DEFAULT_RADIUS) {
    //translate to x,y
    glLoadIdentity();
    glTranslatef(x,y,0);

    //divide circle into sections
    double angleDelta = 2.0*PI/PRECISION;
    double angle = 0;

    //draw points on the circle
    glBegin(GL_POLYGON);
       for (int i = 0; i < PRECISION; i++) {
            double x = r * cos(angle);
            double y = r * sin(angle);
            angle += angleDelta;

            glVertex2d(x,y);
        }
    glEnd();
    glLoadIdentity();
}


#endif // GLUTILS_H
