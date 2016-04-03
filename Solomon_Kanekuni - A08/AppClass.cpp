#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("E10_Projections"); // Window Name
}
void AppClass::InitVariables(void)
{
	//Generate the Cone
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCone(1.0f, 1.0f, 10, RERED);

	//Generate the Cylinder
	m_pCylinder = new PrimitiveClass();
	m_pCylinder->GenerateCylinder(1.0f, 1.0f, 10, REGREEN);

	//Calculate the first projections
	m_m4Projection = glm::perspective(
		45.0f, // Camera viewing angle
		1080.0f / 768.0f, // Camera viewing ratio
		0.01f,
		1000.0f);

	m_m4View = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 15.0f), // Position
		glm::vec3(0.0f, 0.0f, 14.0f), // What i'm looking at
		glm::vec3(0.0f, 1.0f, 0.0f)); // rotation orientation - currently up
	
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");
	/*
	m_m4Projection = glm::perspective(
		45.0f, // Camera viewing angle
		1080.0f / 768.0f, // Camera viewing ratio
		0.01f,
		1000.0f);
		*/

	/*glm::ortho(
		-20.0f,//left 
		20.0f,//right 
		-10.0f,//bottom
		10.0f,///top
		0.01f,//near, 
		1000.0f);//far);
		*/
		
	
	/*
	m_m4View = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 15.0f), // Position
		glm::vec3(m_quatOrientation.x, m_quatOrientation.y, m_quatOrientation.z), // What i'm looking at
		glm::vec3(0.0f, 1.0f, 0.0f)); // rotation orientation - currently up
	*/
	int nFPS = m_pSystem->GetFPS();
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("X:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_quatOrientation.x), RERED);
	m_pMeshMngr->Print("Y:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_quatOrientation.y), RERED);
	m_pMeshMngr->Print("Z:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_quatOrientation.z), RERED);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	
}

void AppClass::Display(void)
{
	//Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render the grid
	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY);

	//Render the cone
	m_pCone->Render(m_m4Projection, m_m4View, IDENTITY_M4);

	//Render the cylinder
	m_pCylinder->Render(m_m4Projection, m_m4View, glm::translate(IDENTITY_M4, REAXISZ * -3.0f));

	//Render the rest of the meshes
	m_pMeshMngr->Render();

	//Swaps the OpenGL buffers
	m_pGLSystem->GLSwapBuffers();
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);

	//Release the memory of the inherited fields
	super::Release(); 
}

/*matrix4 AppClass::GetView(void)
{

}
matrix4 AppClass::GetProjection(bool bOrtographic)
{

}
										 
void AppClass::SetPosition(vector3 v3Position)
{

}
void AppClass::SetTarget(vector3 v3Target)
{

}
void AppClass::SetUp(vector3 v3Up)
{

}
void AppClass::MoveForward(float fIncrement)
{

}
void AppClass::MoveSideways(float fIncrement)
{

}
void AppClass::MoveVertical(float fIncrement)
{

}
void AppClass::ChangePitch(float fIncrement)
{

}
void AppClass::ChangeRoll(float fIncrement)
{

}
void AppClass::ChangeYaw(float fIncrement)
{

}*/


