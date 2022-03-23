#ifndef RENDERER_3D_H
#define RENDERER_3D_H

#include "EngineObjects.h"
#include "QuickMath.h"

static Vec3d upDir = {0.0f, 1.0f, 0.0f};
static Vec3d downDir = {0.0f, -1.0f, 0.0f};
static Vec3d forwardDir = {0.0f, 0.0f, 1.0f};
static Vec3d backwardDir = {0.0f, 0.0f, -1.0f};
static Vec3d rightDir = {1.0f, 0.0f, 0.0f};
static Vec3d leftDir = {-1.0f, 0.0f, 0.0f};

typedef struct{
    Mesh** sceneObjects;
    Light** sceneLights;
    Triangle** drawableTrianglesBuffer;

    int sceneObjectCapacity;
    int sceneLightCapacity;
    int drawableTrianglesCapacity;

    float forwardPlaneOffset;

    Vec3d vCameraPosition;
    Quaternion vCameraRotation;
    //DO NOT MESS WITH
    Vec3d vCameraForward;
    Vec3d vCameraRenderPlane;
    Vec3d vCameraPositionInverse;
    Quaternion vCameraRotationInverse;

    Mat4x4 projectionMatrix;
} Renderer3D;

void IncreaseRdrSceneObjectCapacity(Renderer3D* renderer, int increase);
void IncreaseRdrSceneLightCapacity(Renderer3D* renderer, int increase);
void SetRdrDrawableTrianglesCapacity(Renderer3D* renderer, int capacity);

void UpdateRendererPosition(Renderer3D* renderer);
void UpdateRendererRotation(Renderer3D* renderer);

void AddMeshAndTrisToBuffer(Renderer3D* renderer, Mesh* obj);
void AddObjectToScene(Renderer3D* renderer, Mesh* obj);
void AddUMObjectToScene(Renderer3D* renderer, Mesh* obj);

void AddLightToBuffer(Renderer3D* renderer, Light* light);
void AddLightToScene(Renderer3D* renderer, Light* light);
void AddUMLightToScene(Renderer3D* renderer, Light* light);

int RdrNumSceneLights(Renderer3D* renderer);
int RdrNumSceneObjects(Renderer3D* renderer);

void InitializeRenderer(Renderer3D* renderer, int defSceneObjectCap, float forwardPlaneOffset);
void InitializeRdrProjection(Renderer3D* renderer, float fNear, float fFar, float fFov, float fAspectRatio);

void RenderScene(Renderer3D* renderer);


#endif