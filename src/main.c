/*
 *--------------------------------------
 * Program Name: Engine3d
 * Author:  Dennis Kountouris
 * License: ur mom 
 * Description: hah
 *--------------------------------------
*/

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>

#include "EngineObjects.h"
#include "QuickMath.h"
#include "GameIO.h"
#include "Renderer3D.h"


float getElapsed(){
    return (float)timer_GetSafe(1, TIMER_UP) / 32768;
}

int main(void)
{
    //INITIALIZE GFX
    gfx_Begin();

    //ZERO ON SCREEN BUFFER
    gfx_SetDrawBuffer();
    gfx_ZeroScreen();

    //ZERO OTHER BUFFER
    gfx_SwapDraw();
    gfx_ZeroScreen();

    //DISABLE TIMER THEN SET IT
    timer_Disable(1);
    timer_Set(1, 0);
    timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_UP);

    //CREATE AND INITIALIZE THE RENDERER
    Renderer3D rdr = {0};
    InitializeRenderer(&rdr, 5, 1.0f);
    InitializeRdrProjection(&rdr, 0.2f, 1000.0f, 75.0f, (fLCD_HEIGHT / fLCD_WIDTH));

    //CREATE AND INITIALIZE A TEST CUBE
    Mesh* mCube = malloc(sizeof(Mesh));
    memset(mCube, 0, sizeof(Mesh));
    InitializeMeshCube(mCube);
    mCube->position.z = 8;

    //CREATE AND INTIIALIZE A DIRECTIONAL LIGHT THAT IS POINTING DIRECTLY FORWARD
    Light* dirLight = malloc(sizeof(Light));
    memset(dirLight, 0, sizeof(Light));
    Vec3d direction = {0.0f, 0.0f, 1.0f};
    InitializeDirectionalLight(dirLight, &direction, 1.0f);

    //CREATE AND INITIALIZE AN AMBIENT LIGHT WITH POWER
    Light* ambientLight = malloc(sizeof(Light));
    memset(ambientLight, 0, sizeof(Light));
    InitializeAmbientLight(ambientLight, 0.2f);

    //ADD OBJECT AND LIGHT TO SCENE
    AddObjectToScene(&rdr, mCube);
    AddLightToScene(&rdr, ambientLight);
    AddLightToScene(&rdr, dirLight);

    //DELTA STUFF FOR RENDER LOOP
    float lastElapsed = 0.0f;
    float delta = 0.0f;
    float elapsedTime = 0.0f;

    //FOR UPDATING ROT POS LATER
    bool positionUpdated = false;
    bool rotationUpdated = false;

    while(1){
        kb_Scan();

        if(kb_Data[6] & kb_Clear){
            break;
        }

        gfx_ZeroScreen();

        elapsedTime = getElapsed();
        delta = elapsedTime - lastElapsed;

        if(kb_Data[7] & kb_Right){
            Quaternion rightRotationQuat = {0};
            QuaternionAboutAxis(1.0f * delta, &upDir, &rightRotationQuat);
            Quaternion intermediate = rdr.vCameraRotation;
            QuaternionMultiply(&intermediate, &rightRotationQuat, &rdr.vCameraRotation);
            rotationUpdated = true;
        }
        if(kb_Data[7] & kb_Left){
            Quaternion rightRotationQuat = {0};
            QuaternionAboutAxis(-1.0f * delta, &upDir, &rightRotationQuat);
            Quaternion intermediate = rdr.vCameraRotation;
            QuaternionMultiply(&intermediate, &rightRotationQuat, &rdr.vCameraRotation);
            rotationUpdated = true;
        }
        if(kb_Data[7] & kb_Up){
            Vec3d intermediate = {0};
            RotateVectorByQuaternion(&forwardDir, &rdr.vCameraRotation, &intermediate);
            MultiplyVectorByScalar(&intermediate, 7.0f * delta, &intermediate);
            AddVectors(&rdr.vCameraPosition, &intermediate, &rdr.vCameraPosition);
            positionUpdated = true;
        }
        if(kb_Data[7] & kb_Down){
            
            Vec3d intermediate = {0};
            RotateVectorByQuaternion(&forwardDir, &rdr.vCameraRotation, &intermediate);
            MultiplyVectorByScalar(&intermediate, -7.0f * delta, &intermediate);
            AddVectors(&rdr.vCameraPosition, &intermediate, &rdr.vCameraPosition);
            positionUpdated = true;
        }

        if(positionUpdated){
            UpdateRendererPosition(&rdr);
        }
        if(rotationUpdated){
            UpdateRendererRotation(&rdr);
        }

        Quaternion cubeRotQuat = {0};
        QuaternionAboutAxis(-1.0f * delta, &upDir, &cubeRotQuat);
        Quaternion cubeIntermediate = mCube->rotation;
        QuaternionMultiply(&cubeIntermediate, &cubeRotQuat, &mCube->rotation);

        RenderScene(&rdr);

        gfx_SwapDraw();

        lastElapsed = elapsedTime;
        positionUpdated = false;
        rotationUpdated = false;
    }

    gfx_End();

    return 0;
}
