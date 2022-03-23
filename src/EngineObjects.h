#ifndef ENGINE_OBJECTS_H
#define ENGINE_OBJECTS_H

typedef struct {
    float x, y, z;
} Vec3d;

typedef struct {
    Vec3d p[3];
    unsigned char color;
} Triangle;

typedef struct {
    float w;
    float x;
    float y;
    float z;
} Quaternion;

typedef struct {
    Triangle* tris;
    int numberTriangles;
    char name[10];
    Vec3d position;
    Quaternion rotation;
} Mesh;

typedef struct{
    float m[4][4];
} Mat4x4;

typedef enum { LT_DIRECTIONAL } LightType;

typedef struct{
    LightType type;
    void* info;
} Light;

typedef struct{
    Vec3d direction;
} LSC_DirectionalLight;

void InitializeMeshCube(Mesh* cube);
void InitializeDirectionalLight(Light* light, Vec3d* direction);
void FreeLight(Light* light);


#endif