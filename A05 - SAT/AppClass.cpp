#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Gen Varela - gmv1758@rit.edu";

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUp(
		vector3(0.0f, 3.0f, 13.0f), //Position
		vector3(0.0f, 3.0f, 12.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light(0 is reserved for global light)

	//creeper
	m_pCreeper = new Model();
	m_pCreeper->Load("Minecraft\\Creeper.obj");
	m_pCreeperRB = new MyRigidBody(m_pCreeper->GetVertexList());

	//steve
	m_pSteve = new Model();
	m_pSteve->Load("Minecraft\\Steve.obj");
	m_pSteveRB = new MyRigidBody(m_pSteve->GetVertexList());

	//Added: Dividing Plane
	//m_pMeshMngr->GeneratePlane(1.0f, C_MAGENTA);
	//dPlane = new Mesh();
	//dPlane->GeneratePlane(6.0f, C_MAGENTA);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Set model matrix to the creeper
	matrix4 mCreeper = glm::translate(m_v3Creeper) * ToMatrix4(m_qCreeper) * ToMatrix4(m_qArcBall);
	m_pCreeper->SetModelMatrix(mCreeper);
	m_pCreeperRB->SetModelMatrix(mCreeper);
	m_pMeshMngr->AddAxisToRenderList(mCreeper);

	//Set model matrix to Steve
	matrix4 mSteve = glm::translate(vector3(2.25f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	m_pSteve->SetModelMatrix(mSteve);
	m_pSteveRB->SetModelMatrix(mSteve);
	m_pMeshMngr->AddAxisToRenderList(mSteve);

	bool bColliding = m_pCreeperRB->IsColliding(m_pSteveRB);

	m_pCreeper->AddToRenderList();
	m_pCreeperRB->AddToRenderList();

	m_pSteve->AddToRenderList();
	m_pSteveRB->AddToRenderList();

	m_pMeshMngr->Print("Colliding: ");
	if (bColliding)
		m_pMeshMngr->PrintLine("YES!", C_RED);
	else
		m_pMeshMngr->PrintLine("no", C_YELLOW);

	//Added:
	matrix4 mdPlane_Basic = glm::translate(m_pCreeperRB->GetCenterGlobal()) * ToMatrix4(m_qCreeper) * ToMatrix4(m_qArcBall); //Dividing Plane's basic transformation matrix
	mdPlane_Basic = mdPlane_Basic * glm::scale(vector3(2.0f)); //Make it bigger so it's easier to see

	//m_pMeshMngr->AddPlaneToRenderList(mdPlane_Basic, C_MAGENTA, RENDER_SOLID); //Renders the dividing plane

	if (m_pCreeperRB->GetFlag() == eSATResults::SAT_AX)
	{
		//matrix4 mdPlane_SAT = mdPlane_Basic * glm::rotate(90.0f, AXIS_Y);
		//m_pMeshMngr->AddPlaneToRenderList(mdPlane_SAT, C_YELLOW, RENDER_SOLID);
		m_pMeshMngr->AddPlaneToRenderList(mdPlane_Basic, C_MAGENTA, RENDER_SOLID);
	}

	if (m_pCreeperRB->GetFlag() == eSATResults::SAT_BX)
	{
		m_pMeshMngr->AddPlaneToRenderList(mdPlane_Basic, C_YELLOW, RENDER_SOLID);
	}

#pragma region "Old Code"
	//dPlane->Render(m4Projection, m4View, glm::rotate(glm::translate(dPlanePos), 45.0f, AXIS_Y));

	//Cube - Taken from previous exercise
	//v3Position = vector3(glm::sin(glm::radians(dAngle * 0)) * 3.0f, glm::cos(glm::radians(dAngle * 0)) * 3.0f, 0.0f);
	//m_pCube->Render(m4Projection, m4View, glm::rotate(glm::translate(v3Position), glm::radians(static_cast<float>(dTimer) * 20.0f), AXIS_X));
	
	//dPlane->Render()

	//vector3 dPlanePos = m_pCreeperRB->GetCenterGlobal();
	//vector3 dPlaneRot = vector3(0.0f, 0.0f, 0.0f);
	//if (m_pCreeperRB->GetFlag() == eSATResults::SAT_AX)
	//{
	//	m_pMeshMngr->AddPlaneToRenderList(glm::translate(dPlanePos) * glm::scale(vector3(2.0f)), C_MAGENTA, RENDER_SOLID);
		//glm::rotate(glm::translate(dPlaneRot), 90.0f, AXIS_Y);
	//}

	//matrix4 m4Model = glm::translate(IDENTITY_M4, dPlanePos);
	//dPlane->Render(m4Projection, m4View, m4Model);

	//matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	//matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix

	//vector3 dPlanePos = m_pCreeperRB->GetCenterGlobal();

	//dPlane->Render(m4Projection, m4View, mdPlane);
#pragma endregion
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}

void Application::Release(void)
{

	//release the model
	SafeDelete(m_pCreeper);

	//release the rigid body for the model
	SafeDelete(m_pCreeperRB);

	//release the model
	SafeDelete(m_pSteve);

	//release the rigid body for the model
	SafeDelete(m_pSteveRB);

	//Added:
	//SafeDelete(dPlane);

	//release GUI
	ShutdownGUI();
}