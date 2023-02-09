#pragma once

#include "CameraInputComponent.h"
#include "Camera.h"

class DefaultCameraInput : public CameraInputComponent
{
public:
	void Update(Camera* camera) override;

private:
	float speed_ = 0.05f;
	void UpdatePosition(Camera* camera);
	void UpdateRotation(Camera* camera);
};