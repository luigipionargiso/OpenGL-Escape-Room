#pragma once

class Camera;

class CameraInputComponent
{
public:
	virtual void Update(Camera* camera) = 0;
};