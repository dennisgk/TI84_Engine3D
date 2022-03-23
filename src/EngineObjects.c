#include "EngineObjects.h"
#include <graphx.h>
#include <string.h>
#include "QuickMath.h"

void InitializeMeshCube(Mesh* cube){
    
    static Triangle defaultCubeVerts[12] = {

		// SOUTH
		{{ {-1.0f, -1.0f, -1.0f},    {-1.0f, 1.0f, -1.0f},    {1.0f, 1.0f, -1.0f} }, 0},
		{{ {-1.0f, -1.0f, -1.0f},    {1.0f, 1.0f, -1.0f},    {1.0f, -1.0f, -1.0f} }, 0},

		// EAST                                                      
		{{ {1.0f, -1.0f, -1.0f},    {1.0f, 1.0f, -1.0f},    {1.0f, 1.0f, 1.0f} }, 0},
		{{ {1.0f, -1.0f, -1.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, -1.0f, 1.0f} }, 0},

		// NORTH                                                     
		{{ {1.0f, -1.0f, 1.0f},    {1.0f, 1.0f, 1.0f},    {-1.0f, 1.0f, 1.0f} }, 0},
		{{ {1.0f, -1.0f, 1.0f},    {-1.0f, 1.0f, 1.0f},    {-1.0f, -1.0f, 1.0f} }, 0},

		// WEST                                                      
		{{ {-1.0f, -1.0f, 1.0f},    {-1.0f, 1.0f, 1.0f},    {-1.0f, 1.0f, -1.0f} }, 0},
		{{ {-1.0f, -1.0f, 1.0f},    {-1.0f, 1.0f, -1.0f},    {-1.0f, -1.0f, -1.0f} }, 0},

		// TOP                                                       
		{{ {-1.0f, 1.0f, -1.0f},    {-1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 1.0f} }, 0},
		{{ {-1.0f, 1.0f, -1.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, -1.0f} }, 0},

		// BOTTOM                                                    
		{{ {1.0f, -1.0f, 1.0f},    {-1.0f, -1.0f, 1.0f},    {-1.0f, -1.0f, -1.0f} }, 0},
		{{ {1.0f, -1.0f, 1.0f},    {-1.0f, -1.0f, -1.0f},    {1.0f, -1.0f, -1.0f} }, 0}

    };

    cube->numberTriangles = 12;
    cube->tris = (Triangle*)malloc(sizeof(Triangle) * 12);
    memcpy((void*)cube->tris, (void*)defaultCubeVerts, sizeof(Triangle) * 12);
    cube->rotation.w = 1.0f;

}

void InitializeDirectionalLight(Light* light, Vec3d* direction, float power){
    light->type = LT_DIRECTIONAL;

    Vec3d light_direction = {0};
    light_direction.x = direction->x;
    light_direction.y = direction->y;
    light_direction.z = direction->z;
    float l = isqrt_f((light_direction.x*light_direction.x) + (light_direction.y*light_direction.y) + (light_direction.z*light_direction.z));
    light_direction.x *= l; light_direction.y *= l; light_direction.z *= l;

    LSC_DirectionalLight* dirLight = malloc(sizeof(LSC_DirectionalLight));
    dirLight->direction = light_direction;
    dirLight->power = power;

    light->info = (void*)dirLight;

}

void InitializeAmbientLight(Light* light, float power){
    light->type = LT_AMBIENT;

    LSC_AmbientLight* ambLight = malloc(sizeof(LSC_AmbientLight));
    ambLight->power = power;

    light->info = (void*)ambLight;
}

void FreeLight(Light* light){
    if(light->info){
        free(light->info);
    }
    free(light);
}
