#include "Vector.h"

Vector2f newVector2f(float x, float y)
{
	Vector2f n;
	n.x = x;
	n.y = y;
	return n;
}

Vector2f add(Vector2f a, Vector2f b)
{
	Vector2f n;
	n.x = a.x + b.x;
	n.y = a.y + b.y;
	return n;
}