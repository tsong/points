#ifndef POINTSUTIL_H
#define POINTSUTIL_H

#include "matrix.h"
#include "vector.h"

//utility functions for points
uint hash(uint,uint);
void unhash(uint,uint&,uint&);
bool inCircle(Vector2f, Vector2f, Vector2f, Vector2f);
bool inTriangle(Vector2f, Vector2f, Vector2f, Vector2f);
int pointLineTest (Vector2f, Vector2f, Vector2f);

#endif // POINTSUTIL_H
