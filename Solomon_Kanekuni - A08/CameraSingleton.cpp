#include "CameraSingleton.h"



CameraSingleton::CameraSingleton()
{
	m4_CameraProjection = matrix4(0.0f);
}


CameraSingleton::~CameraSingleton()
{
}

matrix4 CameraSingleton::GetView(void)
{
	// Return the camera's projection.
	return m4_CameraProjection;
}
matrix4 CameraSingleton::GetProjection(bool bOrtho)
{
	// If true
	if (bOrtho) {
		// Return Ortho.
		return m4_OrthoProjection;
		
	}
	else
	{
		// Return Perspective.
		return m4_PerspectiveProjection;
	}
}

void CameraSingleton::SetPosition(vector3 v3Position)
{
	// Set position to argument.
	v3_Position = v3Position;
	m4_CameraView = glm::lookAt(
		v3_Position, // Position
		v3_Target, // What i'm looking at
		v3_Orientation); // rotation orientation - currently up
}
void CameraSingleton::SetTarget(vector3 v3Target)
{
	// Set Target to argument.
	v3_Target = v3Target;
	m4_CameraView = glm::lookAt(
		v3_Position, // Position
		v3_Target, // What i'm looking at
		v3_Orientation); // rotation orientation - currently up
}
void CameraSingleton::SetUp(vector3 v3Up)
{
	// Set Up to argument.
	v3_Orientation = v3Up;
	m4_CameraView = glm::lookAt(
		v3_Position, // Position
		v3_Target, // What i'm looking at
		v3_Orientation); // rotation orientation - currently up
}
void CameraSingleton::MoveForward(float fIncrement)
{

	m4_CameraView *= glm::translate(vector3(0.0f, 0.0f, fIncrement));
	
}
void CameraSingleton::MoveSideways(float fIncrement)
{
	m4_CameraView *= glm::translate(vector3(0.0f, 0.0f, fIncrement));
}
void CameraSingleton::MoveVertical(float fIncrement)
{
	m4_CameraView *= glm::translate(vector3(0.0f, 0.0f, fIncrement));
}
void CameraSingleton::ChangePitch(float fIncrement)
{

}
void CameraSingleton::ChangeRoll(float fIncrement)
{

}
void CameraSingleton::ChangeYaw(float fIncrement)
{

}