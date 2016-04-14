#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("Instance Rendering");
}

/*void AppClass::createTri(int num) {
	//if (num <= 1) {
	//	return 1;
	//}
	m_fMatrixArray = new float[ 3 * 16];
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
		
		const float* m4MVP = glm::value_ptr(glm::translate(vector3(1.0f, 0.0f, 0)));
		//const float* m4MVPTwo = glm::value_ptr(glm::translate(vector3(num * 2.0f, num * 2.0f, 0)));

		memcpy(&m_fMatrixArray[ 0 * 16], m4MVP, 16 * sizeof(float));
		//memcpy(&m_fMatrixArray[32], m4MVPTwo, 32 * sizeof(float));
		//return createTri(num - 1);
		}

		if (i == 1) {
			//m_fMatrixArray = new float[16];
			const float* m4MVP = glm::value_ptr(glm::translate(vector3(-1.0f,  -1.0f, 0)));
			//const float* m4MVPTwo = glm::value_ptr(glm::translate(vector3(num * 2.0f, num * 2.0f, 0)));
		
			memcpy(&m_fMatrixArray[ 1* 16], m4MVP, 16 * sizeof(float));
			//memcpy(&m_fMatrixArray[32], m4MVPTwo, 32 * sizeof(float));
			//return createTri(num - 1);
		}


		if (i == 2) {
			//m_fMatrixArray = new float[16];
			const float* m4MVP = glm::value_ptr(glm::translate(vector3(1.0f, -1.0f, 0)));
			//const float* m4MVPTwo = glm::value_ptr(glm::translate(vector3(num * 2.0f, num * 2.0f, 0)));

			memcpy(&m_fMatrixArray[ 2 * 16], m4MVP, 16 * sizeof(float));
			//memcpy(&m_fMatrixArray[32], m4MVPTwo, 32 * sizeof(float));
			//return createTri(num - 1);
		}
		
	}
}*/

int AppClass::createTri(int num) {
	if (num <= 1) {
		return 1;
	}

	if (prevRow > num) {
		col--;

	}
	
		const float* m4MVP = glm::value_ptr(glm::translate(vector3(num * 2, col, 0)));
		memcpy(&m_fMatrixArray[num * 16], m4MVP, 16 * sizeof(float));
		prevRow = num;

		return createTri(num - 1);
		
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pMesh = new MyMesh();

	

	//Creating the Mesh points
	m_pMesh->AddVertexPosition(vector3(-1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(REGREEN);
	m_pMesh->AddVertexPosition(vector3( 1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(0.0f,  1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	/*m_pMesh->AddVertexPosition(vector3(-1.0f,  1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3(1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3( 1.0f, 1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);*/

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();

	/*m_nObjects = 100;

	m_fMatrixArray = new float[m_nObjects * 16];

	for (uint n = 0; n < m_nObjects; n++) {
		const float* m4MVP = glm::value_ptr(glm::translate(vector3(n * 2, 0, 0)));
		memcpy(&m_fMatrixArray[n * 16], m4MVP, 16 * sizeof(float));
	}*/

	m_fMatrixArray = new float[60 * 16];
	createTri(3);
}

/*int AppClass::factorial(int num) {
	if (num <= 1) {
		return 1;
	}

	return num * factorial(num - 1);
}*/



void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d   \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

/*	m_nObjects = 100;

	m_fMatrixArray = new float[m_nObjects * 16];

	for (uint n = 0; n < m_nObjects; n++) {
		const float* m4MVP = glm::value_ptr(glm::translate(vector3(n * 2, 0, 0)));
		memcpy(&m_fMatrixArray[n * 16], m4MVP, 16 * sizeof(float));
	}*/



	

	
}



void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	m_pMesh->RenderList(m4Projection, m4View,m_fMatrixArray, m_nObjects);//Rendering nObjects

	m_pMeshMngr->Render();

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}