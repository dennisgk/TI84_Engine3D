#include "GameIO.h"
#include "EngineObjects.h"
#include "QuickMath.h"

void MultiplyMatrixVector4(Vec3d* i, Mat4x4* m, Vec3d* o){
    o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
    o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
    o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
    float w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

    if (w != 0.0f)
    {
        o->x /= w; o->y /= w; o->z /= w;
    }
}

void GetTriangleNormal(Triangle* tri, Vec3d* output){
    Vec3d line1 = {0};
    Vec3d line2 = {0};

    line1.x = tri->p[1].x - tri->p[0].x;
    line1.y = tri->p[1].y - tri->p[0].y;
    line1.z = tri->p[1].z - tri->p[0].z;

    line2.x = tri->p[2].x - tri->p[0].x;
    line2.y = tri->p[2].y - tri->p[0].y;
    line2.z = tri->p[2].z - tri->p[0].z;

    output->x = line1.y * line2.z - line1.z * line2.y;
    output->y = line1.z * line2.x - line1.x * line2.z;
    output->z = line1.x * line2.y - line1.y * line2.x;

    // It's normally normal to normalise the normal
    float l = isqrt_f((output->x*output->x) + (output->y*output->y) + (output->z*output->z));
    output->x *= l; 
    output->y *= l; 
    output->z *= l;
}