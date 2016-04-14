#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");
	

	fDuration = 1.0f;

	//add points to vector array
	points.push_back(vector3(-4.0f, -2.0f, 5.0f));
	points.push_back(vector3(1.0f, -2.0f, 5.0f));
	points.push_back(vector3(-3.0f, -1.0f, 3.0f));
	points.push_back(vector3(2.0f, -1.0f, 3.0f));
	points.push_back(vector3(-2.0f, 0.0f, 0.0f));
	points.push_back(vector3(3.0f, 0.0f, 0.0f));
	points.push_back(vector3(-1.0f, 1.0f, -3.0f));
	points.push_back(vector3(4.0f, 1.0f, -3.0f));
	points.push_back(vector3(0.0f, 2.0f, -5.0f));
	points.push_back(vector3(5.0f, 2.0f, -5.0f));
	points.push_back(vector3(1.0f, 3.0f, -5.0f));

	//spheres for points
	m_pSphere = new PrimitiveClass[11];
	m_pMatrix = new matrix4[11];
	//matrix for character
	m_pMatrixThing= new matrix4();

	//generate spheres for points
	for (uint i = 0; i < 11; i++)
	{
		m_pSphere[i].GenerateSphere(0.1f, 5, RERED /*vector3(1.0f, 0.0f, 0.0f)*/);
		m_pMatrix[i] = glm::translate(points[i]);
	}
	dot = 0;
	m_pMatrixThing[0] = glm::translate(points[0]);
	m_pMeshMngr->SetModelMatrix(m_pMatrixThing[0], "WallEye");


}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here

		
		if (fRunTime > fDuration) {
			//brings back to start if at last point
			if (dot == 10) {
				v3Start = (points[dot]);
				v3End = (points[0]);
				dot = 0;
			}
			//if not at last point goes to next point
			else {
				v3Start = (points[dot]);
				v3End = (points[dot + 1]);
				dot++;
			}
			//resets the time
			fTimeSpan = 0.0f;
			fRunTime = 0.0f;

		}
		//changes the runTime to a position between points
		float fPercent = MapValue(
			static_cast<float>(fRunTime), //value to change
			0.0f,					//original min
			fDuration, //original max
			0.0f, //new min
			1.0f //new max
			);
		//updates position and draws character
		vector3 v3Current = glm::lerp(v3Start, v3End, fPercent);
		m_pMatrixThing[0] = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m_pMatrixThing[0], "WallEye");

#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	//renders points as spheres
	matrix4 mProjection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 mView = m_pCameraMngr->GetViewMatrix();

	for (uint i = 0; i < 11; i++)
	{
		m_pSphere[i].Render(mProjection, mView, m_pMatrix[i]);
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	if (m_pSphere != nullptr)
	{
		delete[] m_pSphere; //new[]->delete[], new()->delete
		m_pSphere = nullptr;
	}
	if (m_pMatrix != nullptr)
	{
		delete[] m_pMatrix; //new[]->delete[], new()->delete
		m_pMatrix = nullptr;
	}
	if (m_pMatrixThing != nullptr)
	{
		delete m_pMatrixThing; //new[]->delete[], new()->delete
		m_pMatrixThing = nullptr;
	}
	super::Release(); //release the memory of the inherited fields
}