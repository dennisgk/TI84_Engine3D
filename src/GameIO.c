#include "GameIO.h"
#include "EngineObjects.h"
#include "QuickMath.h"

void MultiplyMatrixVector4(Vec3d* i, Mat4x4* m, Vec3d* o){
    o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
    o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
    o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
    float w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

    if (absf_s(w) > 0.0001f)
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

    output->x = (line1.y * line2.z) - (line1.z * line2.y);
    output->y = (line1.z * line2.x) - (line1.x * line2.z);
    output->z = (line1.x * line2.y) - (line1.y * line2.x);

    float l = isqrt_f((output->x*output->x) + (output->y*output->y) + (output->z*output->z));
    output->x *= l; 
    output->y *= l; 
    output->z *= l;
}

void QuaternionMultiply(Quaternion* quat1, Quaternion* quat2, Quaternion* output){
    output->w = (quat2->w*quat1->w)-(quat2->x*quat1->x)-(quat2->y*quat1->y)-(quat2->z*quat1->z);
    output->x = (quat2->w*quat1->x)+(quat2->x*quat1->w)-(quat2->y*quat1->z)+(quat2->z*quat1->y);
    output->y = (quat2->w*quat1->y)+(quat2->x*quat1->z)+(quat2->y*quat1->w)-(quat2->z*quat1->x);
    output->z = (quat2->w*quat1->z)-(quat2->x*quat1->y)+(quat2->y*quat1->x)+(quat2->z*quat1->w);
}

void QuaternionInverse(Quaternion* quat, Quaternion* output){
    output->w = quat->w;
    output->x = negf_s(quat->x);
    output->y = negf_s(quat->y);
    output->z = negf_s(quat->z);
}

void VectorInverse(Vec3d* vec, Vec3d* out){
    out->x = negf_s(vec->x);
    out->y = negf_s(vec->y);
    out->z = negf_s(vec->z);
}

void QuaternionAboutAxis(float theta, Vec3d* axis, Quaternion* output){
    float halftheta = theta * 0.5f;
    float sinHalftheta = sinf_s(halftheta);
    output->w = cosf_s(halftheta);
    output->x = axis->x * sinHalftheta;
    output->y = axis->y * sinHalftheta;
    output->z = axis->z * sinHalftheta;
}

void RotateVectorByQuaternion(Vec3d* vec, Quaternion* quat, Vec3d* output){
    Quaternion r = {0};
    r.w = 0.0f;
    r.x = vec->x;
    r.y = vec->y;
    r.z = vec->z;

    Quaternion quat_conj = {0};
    QuaternionInverse(quat, &quat_conj);

    Quaternion intermediateQuat1 = {0};
    Quaternion intermediateQuat2 = {0};

    QuaternionMultiply(quat, &r, &intermediateQuat1);
    QuaternionMultiply(&intermediateQuat1, &quat_conj, &intermediateQuat2);

    output->x = intermediateQuat2.x;
    output->y = intermediateQuat2.y;
    output->z = intermediateQuat2.z;

}

void AddVectors(Vec3d* vec1, Vec3d* vec2, Vec3d* output){
    output->x = vec1->x + vec2->x;
    output->y = vec1->y + vec2->y;
    output->z = vec1->z + vec2->z;
}

void SubtractVectors(Vec3d* vec1, Vec3d* vec2, Vec3d* output){
    output->x = vec1->x - vec2->x;
    output->y = vec1->y - vec2->y;
    output->z = vec1->z - vec2->z;
}

void NormalizeVector(Vec3d* vec, Vec3d* output){
    float l = isqrt_f((vec->x*vec->x) + (vec->y*vec->y) + (vec->z*vec->z));
    output->x = vec->x * l;
    output->y = vec->y * l;
    output->z = vec->z * l;
}

float VectorDotProduct(Vec3d* v1, Vec3d* v2){
    return ((v1->x*v2->x) + (v1->y*v2->y) + (v1->z*v2->z));
}

void MultiplyVectorByScalar(Vec3d* v, float scalar, Vec3d* output){
    output->x = scalar * v->x;
    output->y = scalar * v->y;
    output->z = scalar * v->z;
}
