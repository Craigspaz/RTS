#include "Camera.h"


Camera::Camera(Vector2f position, Vector2f size, int zoom) :
_position(position),
_size(size),
_zoom(zoom),
_movementSpeed(9)
{
	_previousPosition = position;
	_offset = newVector2f(0, 0);
	_totalCameraOffset = newVector2f(0, 0);
	_startPosition = _position;
}
void Camera::update()
{
	_offset.x = _position.x - _previousPosition.x; //Sets offsets
	_offset.y = _position.y - _previousPosition.y; //Sets offsets
	_totalCameraOffset.x = _position.x - _startPosition.x; //Sets offsets
	_totalCameraOffset.y = _position.y - _startPosition.y; //Sets offsets
}
Camera::~Camera()
{

}
//Controls the camera moving
void Camera::moveRight()
{
	_position.x += _movementSpeed; 
}
void Camera::moveLeft()
{
	_position.x -= _movementSpeed;
}
void Camera::moveDown()
{
	_position.y -= _movementSpeed;
}
void Camera::moveUp()
{
	_position.y += _movementSpeed;
}



Vector2f Camera::getPosition()
{
	return _position;
}
Vector2f Camera::getSize()
{
	return _size;
}
void Camera::setPosition(Vector2f position)
{
	_position = position;
}
void Camera::setSize(Vector2f size)
{
	_size = size; //This sets the width and height of the camera
}
int Camera::getZoom()
{
	return _zoom;
}
void Camera::setZoom(int zoom)
{
	_zoom = zoom; 
}
float Camera::getMovementSpeed()
{
	return _movementSpeed;
}
void Camera::setMovementSpeed(float movementSpeed)
{
	_movementSpeed = movementSpeed;
}


Vector2f Camera::getOffset()
{
	return _offset;
}
void Camera::setOffset(Vector2f offset)
{
	_offset = offset;
}


Vector2f Camera::getTotalCameraOffset()
{
	return _totalCameraOffset;
}
void Camera::setTotalCameraOffset(Vector2f totalOffset)
{
	_totalCameraOffset = totalOffset;
}