#ifndef GAME_IO_H
#define GAME_IO_H

#include "EngineObjects.h"

void MultiplyMatrixVector4(Vec3d* i, Mat4x4* m, Vec3d* o);
void GetTriangleNormal(Triangle* tri, Vec3d* output);

void RotateVectorByQuaternion(Vec3d* vec, Quaternion* quat, Vec3d* output);

void QuaternionMultiply(Quaternion* quat1, Quaternion* quat2, Quaternion* output);
void QuaternionInverse(Quaternion* quat, Quaternion* output);
void QuaternionAboutAxis(float theta, Vec3d* axis, Quaternion* output);

void NormalizeVector(Vec3d* vec, Vec3d* output);
void AddVectors(Vec3d* vec1, Vec3d* vec2, Vec3d* output);
void SubtractVectors(Vec3d* vec1, Vec3d* vec2, Vec3d* output);
float VectorDotProduct(Vec3d* v1, Vec3d* v2);
void VectorInverse(Vec3d* vec, Vec3d* out);
void MultiplyVectorByScalar(Vec3d* v, float scalar, Vec3d* output);

#endif