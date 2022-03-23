#ifndef QUICK_MATH_H
#define QUICK_MATH_H

//FOR LCD_WIDTH AND LCD_HEIGHT
#include <tice.h>
#include "EngineObjects.h"

static float fLCD_WIDTH = (float)LCD_WIDTH;
static float fLCD_HEIGHT = (float)LCD_HEIGHT;

static float PI = 3.141592;
static float doublePI = 6.28318531;
static float negPI = -3.141592;
static float halfPI = 1.57079633;
static float negHalfPI = -1.57079633;

float absf_s(float value);
float negf_s(float f);

float cosf(float rad);
float sinf(float rad);
float cosf_s(float rad);
float sinf_s(float rad);
float tanf_s(float rad);
float cotanf_s(float rad);

float arcsinf(float rad);
float arccosf(float rad);

float sqrt_f(float x);
float isqrt_f( float number );

float flmod(float og, float mod);

void swap(void** a, void** b);
int partition (void** arr, int low, int high, int (*compare)(void*, void*));
void quickSort(void** arr, int low, int high, int (*compare)(void*, void*));

void swapTri(Triangle** a, Triangle** b);
int partitionTri (Triangle* arr[], int low, int high);
void quickSortTri(Triangle* arr[], int low, int high);

#endif