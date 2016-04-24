#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("E10_Projections"); // Window Name
}
void AppClass::InitVariables(void)
{
	//Generate the Cone
	m_pCone = new PrimitiveClass();
<<<<<<< HEAD
<<<<<<< HEAD
	m_pCone->GenerateCone(1.0f, 2.0f, 10, RERED);

	//Generate the Cylinder
	m_pCylinder = new PrimitiveClass();
	m_pCylinder->GenerateCylinder(1.0f, 2.0f, 10, REGREEN);
=======
	m_pCone->GenerateCone(1.0f, 3.0f, 10, RERED);

	//Generate the Cylinder
	m_pCylinder = new PrimitiveClass();
	m_pCylinder->GenerateCylinder(1.0f, 3.0f, 10, REGREEN);
>>>>>>> 31d1d82aa61d5f53c28e2bdab18374f5dd8780cc
=======
	m_pCone->GenerateCone(1.0f, 1.0f, 10, RERED);

	//Generate the Cylinder
	m_pCylinder = new PrimitiveClass();
	m_pCylinder->GenerateCylinder(1.0f, 1.0f, 10, REGREEN);
>>>>>>> 6aafa2bba23367993a586b81edcfefb2a4d59d61

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 14.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");
<<<<<<< HEAD

<<<<<<< HEAD
	//Calculate the first projections
	/*m_m4Projection = glm::perspective(
		45.0f, 
		1080.0f / 768.0f, 
		0.01f, 
		1000.0f);*/

	m_m4Projection = glm::ortho(
		-20.0f, //left 
		20.0f, //right 
		-10.0f, //bottom 
		10.0f, //top
		0.01f, //near
		1000.0f //far
		);
	
	m_m4View = glm::lookAt(
		glm::vec3(0.0f, 3.0f, 15.0f), //position
		glm::vec3(0.0f, 0.0f, 0.0f), //what i'm looking at
		glm::vec3(0.0f, 1.0f, 0.0f)); //up
=======
	m_m4View = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 15.0f),
		glm::vec3(0.0f, 0.0f, 14.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//Field of view fovy, ratio, near, far)
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	//left, rightj, bottom, top, near, far);
	m_m4Projection = glm::ortho(-20.0f, 20.0f, 20.0f, -20.0f, 0.01f, 1000.0f);
>>>>>>> 31d1d82aa61d5f53c28e2bdab18374f5dd8780cc
=======
>>>>>>> 6aafa2bba23367993a586b81edcfefb2a4d59d61
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Render the grid
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY);

	//Render the cone
	m_pCone->Render(m_m4Projection, m_m4View, IDENTITY_M4);

	//Render the cylinder
	m_pCylinder->Render(m_m4Projection, m_m4View, glm::translate(IDENTITY_M4, REAXISZ * -3.0f));

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ResetRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);

	//Release the memory of the inherited fields
	super::Release(); 
}