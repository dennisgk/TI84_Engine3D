#include "QuickMath.h"

float absf_s(float f) {
    if (sizeof(float) == sizeof(uint32_t)) {
        union {
            float f;
            uint32_t i;
        } u;
        u.f = f;
        u.i &= 0x7fffffff;
        return u.f;
    }
    return (f < 0.0f) ? f * -1.0f : f;
}

float negf_s(float f){
    if (sizeof(float) == sizeof(uint32_t)) {
        union {
            float f;
            uint32_t i;
        } u;
        u.f = f;
        u.i ^= 0x80000000;
        return u.f;
    }
    return f * -1.0f;
}


float cosf(float rad){
    
    if(rad < negHalfPI){
        rad = negPI - rad;
    }
    else if(rad > halfPI){
        rad = PI - rad;
    }

    rad = rad * 1.0138f;
    
    float radrad = rad * rad;

    return (1 - (radrad / 2.0f) + ((radrad * radrad) / 24.0f));
}

float sinf(float rad){
    
    if(rad < negHalfPI){
        rad = negPI - rad;
    }
    else if(rad > halfPI){
        rad = PI - rad;
    }

    rad = rad * 1.0138f;
    
    float radrad = rad * rad;
    float radradrad = rad * rad * rad;

    return (rad - ((radradrad) / 6.0f) + ((radradrad * radrad) / 120.0f));
}

float cosf_s(float rad){
    if(rad > PI){
        while(rad > PI){
            rad = rad - doublePI;
        }
    }
    else{
        if(rad < negPI){
            while(rad < negPI){
                rad = rad + doublePI;
            }
        }
    }

    return cosf(rad);
}

float sinf_s(float rad){
    if(rad > PI){
        while(rad > PI){
            rad = rad - doublePI;
        }
    }
    else{
        if(rad < negPI){
            while(rad < negPI){
                rad = rad + doublePI;
            }
        }
    }

    return sinf(rad);
}

float tanf_s(float rad){
    if(rad > PI){
        while(rad > PI){
            rad = rad - doublePI;
        }
    }
    else{
        if(rad < negPI){
            while(rad < negPI){
                rad = rad + doublePI;
            }
        }
    }

    return (sinf(rad) / cosf(rad));
}

float cotanf_s(float rad){
    if(rad > PI){
        while(rad > PI){
            rad = rad - doublePI;
        }
    }
    else{
        if(rad < negPI){
            while(rad < negPI){
                rad = rad + doublePI;
            }
        }
    }

    return (cosf(rad) / sinf(rad));
}

float arcsinf(float rad){
    float radradrad = rad * rad * rad;
    return (rad + (radradrad / 6.0f) + ((3.0f * radradrad * rad * rad) / 40.0f) + ((30.0f * radradrad * radradrad * rad) / 112.0f));
}

float arccosf(float rad){
    return ((-1.0f * arcsinf(rad)) + halfPI);
}

float sqrt_f(float x)
{
    unsigned int i = *(unsigned int*) &x; 
    // adjust bias
    i  += 127 << 23;
    // approximation of square root
    i >>= 1; 
    return *(float*) &i;
}

float isqrt_f( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       
	i  = 0x5f3759df - ( i >> 1 );               
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   

	return y;
}

float flmod(float og, float mod){
    if(og < 0.0f){
        og = og * -1.0f;
    }
    while(og > mod){
        og -= mod;
    }
    return og;
}

void swap(void** a, void** b)
{
    void* t = *a;
    *a = *b;
    *b = t;
}

int partition (void** arr, int low, int high, int (*compare)(void*, void*))
{
    void* pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
 
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if ((*compare)(pivot, arr[j]) > 0)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(void** arr, int low, int high, int (*compare)(void*, void*))
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high, compare);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1, compare);
        quickSort(arr, pi + 1, high, compare);
    }
}

void swapTri(Triangle** a, Triangle** b)
{
    Triangle* t = *a;
    *a = *b;
    *b = t;
}

int partitionTri (Triangle** arr, int low, int high)
{
    Triangle* pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
    float z1 = (pivot->p[0].z + pivot->p[1].z + pivot->p[2].z) / 3.0f;
 
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        float z2 = (arr[j]->p[0].z + arr[j]->p[1].z + arr[j]->p[2].z) / 3.0f;
        if (z2 > z1)
        {
            i++; // increment index of smaller element
            swapTri(&arr[i], &arr[j]);
        }
    }
    swapTri(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortTri(Triangle** arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partitionTri(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSortTri(arr, low, pi - 1);
        quickSortTri(arr, pi + 1, high);
    }
}