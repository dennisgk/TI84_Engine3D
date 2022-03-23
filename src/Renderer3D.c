#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>

#include "Renderer3D.h"

void IncreaseRdrSceneObjectCapacity(Renderer3D* renderer, int increase){
    int befCapacity = renderer->sceneObjectCapacity;
    if(befCapacity == 0){
        renderer->sceneObjectCapacity += increase;

        Mesh** newBuffer = malloc(sizeof(Mesh*) * renderer->sceneObjectCapacity);
        memset(newBuffer, 0, sizeof(Mesh*) * renderer->sceneObjectCapacity);
        renderer->sceneObjects = newBuffer;
    }
    else{
        renderer->sceneObjectCapacity += increase;

        Mesh** newBuffer = malloc(sizeof(Mesh*) * renderer->sceneObjectCapacity);
        memset(newBuffer, 0, sizeof(Mesh*) * renderer->sceneObjectCapacity);
        memcpy(newBuffer, renderer->sceneObjects, sizeof(Mesh*) * befCapacity);

        free(renderer->sceneObjects);
        renderer->sceneObjects = newBuffer;
    }
}

void IncreaseRdrSceneLightCapacity(Renderer3D* renderer, int increase){
    int befCapacity = renderer->sceneLightCapacity;
    if(befCapacity == 0){
        renderer->sceneLightCapacity += increase;

        Light** newBuffer = malloc(sizeof(Light*) * renderer->sceneLightCapacity);
        memset(newBuffer, 0, sizeof(Light*) * renderer->sceneLightCapacity);
        renderer->sceneLights = newBuffer;
    }
    else{
        renderer->sceneLightCapacity += increase;

        Light** newBuffer = malloc(sizeof(Light*) * renderer->sceneLightCapacity);
        memset(newBuffer, 0, sizeof(Light*) * renderer->sceneLightCapacity);
        memcpy(newBuffer, renderer->sceneLights, sizeof(Light*) * befCapacity);

        free(renderer->sceneLights);
        renderer->sceneLights = newBuffer;
    }
}

void SetRdrDrawableTrianglesCapacity(Renderer3D* renderer, int capacity){
    //THIS DATA DOES NOT NEED SAVED ONLY USED IN RENDER LOOP
    if((renderer->drawableTrianglesBuffer) != NULL){
        free(renderer->drawableTrianglesBuffer);
    }

    Triangle* arr = malloc(sizeof(Triangle) * capacity);
    Triangle** arr2 = malloc(sizeof(Triangle*) * capacity);
    for(int i = 0; i < capacity; i++){
        arr2[i] = (arr + i);
    }

    renderer->drawableTrianglesBuffer = arr2;
}


void AddMeshAndTrisToBuffer(Renderer3D* renderer, Mesh* obj){

    for(int i = 0; i < renderer->sceneObjectCapacity; i++){
        if(renderer->sceneObjects[i] == NULL){
            renderer->drawableTrianglesCapacity += obj->numberTriangles;
            SetRdrDrawableTrianglesCapacity(renderer, renderer->drawableTrianglesCapacity);
            renderer->sceneObjects[i] = obj;
            break;
        }
    }

}

void AddObjectToScene(Renderer3D* renderer, Mesh* obj){
    int numObjects = RdrNumSceneObjects(renderer);
    if(numObjects == renderer->sceneObjectCapacity){
        IncreaseRdrSceneObjectCapacity(renderer, 1);
    }

    AddMeshAndTrisToBuffer(renderer, obj);
}

void AddUMObjectToScene(Renderer3D* renderer, Mesh* obj){
    int numObjects = RdrNumSceneObjects(renderer);
    if(numObjects == renderer->sceneObjectCapacity){
        IncreaseRdrSceneObjectCapacity(renderer, 1);
    }

    Mesh* objCopy = malloc(sizeof(Mesh));
    memcpy(objCopy, obj, sizeof(Mesh));

    AddMeshAndTrisToBuffer(renderer, objCopy);
}


void AddLightToBuffer(Renderer3D* renderer, Light* light){

    for(int i = 0; i < renderer->sceneLightCapacity; i++){
        if(renderer->sceneLights[i] == NULL){
            renderer->sceneLights[i] = light;
            break;
        }
    }

}

void AddLightToScene(Renderer3D* renderer, Light* light){
    int numLights = RdrNumSceneLights(renderer);
    if(numLights == renderer->sceneLightCapacity){
        IncreaseRdrSceneLightCapacity(renderer, 1);
    }

    AddLightToBuffer(renderer, light);
}

void AddUMLightToScene(Renderer3D* renderer, Light* light){
    int numLights = RdrNumSceneLights(renderer);
    if(numLights == renderer->sceneLightCapacity){
        IncreaseRdrSceneLightCapacity(renderer, 1);
    }

    Light* lightCopy = malloc(sizeof(Light));
    memcpy(lightCopy, light, sizeof(Light));

    AddLightToBuffer(renderer, lightCopy);
}

int RdrNumSceneObjects(Renderer3D* renderer){
    int numObjects = 0;
    for(int i = 0; i < renderer->sceneObjectCapacity; i++){
        if(renderer->sceneObjects[i] != NULL){
            numObjects++;
        }
    }
    return numObjects;
}

int RdrNumSceneLights(Renderer3D* renderer){
    int numLights = 0;
    for(int i = 0; i < renderer->sceneLightCapacity; i++){
        if(renderer->sceneLights[i] != NULL){
            numLights++;
        }
    }
    return numLights;
}


void InitializeRenderer(Renderer3D* renderer, int defSceneObjectCap){
    renderer->sceneObjectCapacity = 0;
    renderer->sceneLightCapacity = 0;
    renderer->drawableTrianglesCapacity = 0;

    renderer->sceneLights = NULL;
    renderer->sceneObjects = NULL;
    renderer->drawableTrianglesBuffer = NULL;
    IncreaseRdrSceneObjectCapacity(renderer, defSceneObjectCap);

    renderer->vCameraPosition.x = 0.0f;
    renderer->vCameraPosition.y = 0.0f;
    renderer->vCameraPosition.z = 0.0f;

    renderer->vCameraRotation.w = 1.0f;
    renderer->vCameraRotation.x = 0.0f;
    renderer->vCameraRotation.y = 0.0f;
    renderer->vCameraRotation.z = 0.0f;

    memcpy(&forwardDir, &renderer->vCameraForward, sizeof(Vec3d));
    memcpy(&rightDir, &renderer->vCameraRight, sizeof(Vec3d));
    memcpy(&upDir, &renderer->vCameraUp, sizeof(Vec3d));

}

void InitializeRdrProjection(Renderer3D* renderer, float fNear, float fFar, float fFov, float fAspectRatio){
    float fFovRad = cotanf_s((fFov * 0.5f) * (PI / 180.0f));
    Mat4x4 matProj = {0};
    matProj.m[0][0] = fAspectRatio * fFovRad;
    matProj.m[1][1] = fFovRad;
    matProj.m[2][2] = fFar / (fFar - fNear);
    matProj.m[3][2] = ((-1.0 * fFar) * fNear) / (fFar - fNear);
    matProj.m[2][3] = 1.0f;
    matProj.m[3][3] = 0.0f;

    renderer->projectionMatrix = matProj;
}


void RenderScene(Renderer3D* renderer, float elapsed){
    int drawableTrianglesIt = 0;

    for(int i = 0; i < renderer->sceneObjectCapacity; i++){
        if(renderer->sceneObjects[i] != NULL){
            for(int j = 0; j < renderer->sceneObjects[i]->numberTriangles; j++){

                Triangle* writeTri = renderer->drawableTrianglesBuffer[drawableTrianglesIt];
                memset(writeTri, 0, sizeof(Triangle)); // WILL HAVE TO PUT LATER

                

            }
        }
    }

    quickSortTri(renderer->drawableTrianglesBuffer, 0, drawableTrianglesIt - 1);

    for(int i = 0; i < drawableTrianglesIt; i++){
        gfx_SetColor(renderer->drawableTrianglesBuffer[i]->color);
        gfx_FillTriangle(renderer->drawableTrianglesBuffer[i]->p[0].x, renderer->drawableTrianglesBuffer[i]->p[0].y, renderer->drawableTrianglesBuffer[i]->p[1].x, renderer->drawableTrianglesBuffer[i]->p[1].y, renderer->drawableTrianglesBuffer[i]->p[2].x, renderer->drawableTrianglesBuffer[i]->p[2].y);
        
        gfx_SetColor(0);
        gfx_Line(renderer->drawableTrianglesBuffer[i]->p[0].x, renderer->drawableTrianglesBuffer[i]->p[0].y, renderer->drawableTrianglesBuffer[i]->p[1].x, renderer->drawableTrianglesBuffer[i]->p[1].y);
        gfx_Line(renderer->drawableTrianglesBuffer[i]->p[1].x, renderer->drawableTrianglesBuffer[i]->p[1].y, renderer->drawableTrianglesBuffer[i]->p[2].x, renderer->drawableTrianglesBuffer[i]->p[2].y);
        gfx_Line(renderer->drawableTrianglesBuffer[i]->p[2].x, renderer->drawableTrianglesBuffer[i]->p[2].y, renderer->drawableTrianglesBuffer[i]->p[0].x, renderer->drawableTrianglesBuffer[i]->p[0].y);
    }

}