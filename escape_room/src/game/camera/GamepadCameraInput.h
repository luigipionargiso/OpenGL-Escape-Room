#pragma once

#include "CameraInputComponent.h"
#include "Camera.h"

class GamepadCameraInput : public CameraInputComponent
{
public:
	void Update(Camera* camera) override;

private:
	float speed_ = 0.02f;
	void UpdatePosition(Camera* camera);
	void UpdateRotation(Camera* camera);
};