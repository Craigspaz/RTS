#ifndef _VECTOR_H
#define _VECTOR_H
/*2D position struct*/

typedef struct
{
	float x;
	float y;
}Vector2f;


Vector2f newVector2f(float x, float y);
Vector2f add(Vector2f a, Vector2f b);

#endif