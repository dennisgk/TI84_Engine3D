#ifndef GAME_IO_H
#define GAME_IO_H

#include "EngineObjects.h"

void MultiplyMatrixVector4(Vec3d* i, Mat4x4* m, Vec3d* o);
void GetTriangleNormal(Triangle* tri, Vec3d* output);

#endif