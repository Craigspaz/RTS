#ifndef _CAMERA_H
#define _CAMERA_H
/*This is the camera. This is controls the view of the world.*/
#include "Vector.h"
class Camera
{
public:
	Camera(Vector2f position,Vector2f size, int zoom);
	void update();
	~Camera();
	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();

	Vector2f getPosition();
	Vector2f getSize();
	void setPosition(Vector2f position);
	void setSize(Vector2f size);
	int getZoom();
	void setZoom(int zoom);
	float getMovementSpeed();
	void setMovementSpeed(float movementSpeed);

	Vector2f getOffset();
	void setOffset(Vector2f offset);

	Vector2f getTotalCameraOffset();
	void setTotalCameraOffset(Vector2f totalOffset);
private:
	Vector2f _position;
	Vector2f _previousPosition;
	Vector2f _offset;
	Vector2f _size;
	int _zoom; // Not yet fully implemented
	float _movementSpeed;

	Vector2f _totalCameraOffset;
	Vector2f _startPosition;
};

#endif