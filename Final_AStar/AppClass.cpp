#include "AppClass.h"
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);
	m_pCameraMngr->SetCameraMode(CAM_ORTHO_Z);
	
	//init the mesh

/*
	//Makes new meshes, adds them to the list of meshes and increments index
	int n = 60; //CHANGE THIS TO CHANGE NUMBER OF SHAPES
	for (int i = 0; i < n; i++)
	{
		m_pMeshG = new MyMesh();
		meshList.push_back(m_pMeshG);
		ml_index++;
	}

	//Added:
	for (int i = -10; i > 8; i + 2)
	{
		for (int j = 4; j < -6; j - 2)
		{
			m_pMeshG->GenerateQuad(vector3(i, j, 0), vector3(i + 2, j, 0),
				vector3(i, j + 2, 0), vector3(i + 2, j + 2, 0),
				C_WHITE);
		}

	}
*/

	m_pMesh = new MyMesh();
	//m_pMesh->GenerateCone(0.5f, 1.0f, 5, C_WHITE);
	m_pMesh->GenerateSphere(1.75f, 3, C_MAGENTA);

#pragma region "A* Pseudocode from Medium.Com"
	// A* (star) Pathfinding
		// Initialize both open and closed list
			//let the openList equal empty list of nodes
			std::vector<vector3*> openList;
			// the closedList equal empty list of nodes
			std::vector<vector3*> closedList;

		// Add the start node
			//put the startNode on the openList (leave it's f at zero)
			//openList.push_back();

		// Loop until you find the end
			//while the openList is not empty
			while (!openList.empty())
			{
				// Get the current node
					//let the currentNode equal the node with the least f value
					//remove the currentNode from the openList
					//add the currentNode to the closedList

				// Found the goal
					//if currentNode is the goal
					//Congratz! You've found the end! Backtrack to get path

				// Generate children
					//let the children of the currentNode equal the adjacent nodes

				//for each child in the children
					// Child is on the closedList
						//if child is in the closedList
						//continue to beginning of for loop

					// Create the f, g, and h values
						//child.g = currentNode.g + distance between child and current
						//child.h = distance from child to end
						//child.f = child.g + child.h

					// Child is already in openList
						//if child.position is in the openList's nodes positions
							//if the child.g is higher than the openList node's g
							//continue to beginning of for loop

				// Add the child to the openList
				//add the child to the openList

			}
#pragma endregion

}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix

	
	//Matrix of the model, its position in the world
	/* //Sol 1
	float fStartPos = -5.0f;
	float fEndPos = 5.0f;
	static DWORD dStartTime = GetTickCount();
	DWORD dCurrentTime = GetTickCount();
	DWORD dTime = dCurrentTime - dStartTime;
	float fTime = dTime / 1000.0f;
	float fTotalAnimationTime = 10.0f;
	//fTotal -> 1.0f
	//fTime -> x
	float fPercentage = fTime  / fTotalAnimationTime;
	float fCurrentPos = glm::lerp(fStartPos, fEndPos, fPercentage);
	matrix4 m4Model = glm::translate(IDENTITY_M4, vector3(fCurrentPos, 0.0f, 0.0f));
	*/

	//Sol2
	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	//Calculate list of Stops
	static std::vector<vector3> v3Stop;
	static bool bInit = false; //Initialize once
	if (!bInit)
	{
	
	/* Added: These loops cause memory leaks or runtime errors 
		for (int i = -9; i < 9; i + 2)
		{
			for (int j = 5; i > -5; i - 2)
			{
				v3Stop.push_back(vector3(i, j, 0));
			}
		}
	*/

	//	for (int i = 0; i < 9; i +2)
	//	{
	//		v3Stop.push_back(vector3(i, 5, 0));
	//	}

#pragma region "Hardcoded Stops"
	//ROW 1
		v3Stop.push_back(vector3(-9, 5, 0)); //col 1
		v3Stop.push_back(vector3(-7, 5, 0)); //col 2
		v3Stop.push_back(vector3(-5, 5, 0)); //col 3
		v3Stop.push_back(vector3(-3, 5, 0)); //col 4
		v3Stop.push_back(vector3(-1, 5, 0)); //col 5

		v3Stop.push_back(vector3(1, 5, 0)); //col 6
		v3Stop.push_back(vector3(3, 5, 0)); //col 7
		v3Stop.push_back(vector3(5, 5, 0)); //col 8
		v3Stop.push_back(vector3(7, 5, 0)); //col 9
		v3Stop.push_back(vector3(9, 5, 0)); //col 10

	//ROW 2
		v3Stop.push_back(vector3(-9, 3, 0)); //col 1
		v3Stop.push_back(vector3(-7, 3, 0)); //col 2
		v3Stop.push_back(vector3(-5, 3, 0)); //col 3
		v3Stop.push_back(vector3(-3, 3, 0)); //col 4
		v3Stop.push_back(vector3(-1, 3, 0)); //col 5

		v3Stop.push_back(vector3(1, 3, 0)); //col 6
		v3Stop.push_back(vector3(3, 3, 0)); //col 7
		v3Stop.push_back(vector3(5, 3, 0)); //col 8
		v3Stop.push_back(vector3(7, 3, 0)); //col 9
		v3Stop.push_back(vector3(9, 3, 0)); //col 10

	//ROW 3
		v3Stop.push_back(vector3(-9, 1, 0)); //col 1
		v3Stop.push_back(vector3(-7, 1, 0)); //col 2
		v3Stop.push_back(vector3(-5, 1, 0)); //col 3
		v3Stop.push_back(vector3(-3, 1, 0)); //col 4
		v3Stop.push_back(vector3(-1, 1, 0)); //col 5

		v3Stop.push_back(vector3(1, 1, 0)); //col 6
		v3Stop.push_back(vector3(3, 1, 0)); //col 7
		v3Stop.push_back(vector3(5, 1, 0)); //col 8
		v3Stop.push_back(vector3(7, 1, 0)); //col 9
		v3Stop.push_back(vector3(9, 1, 0)); //col 10

	//ROW 4
		v3Stop.push_back(vector3(-9, -1, 0)); //col 1
		v3Stop.push_back(vector3(-7, -1, 0)); //col 2
		v3Stop.push_back(vector3(-5, -1, 0)); //col 3
		v3Stop.push_back(vector3(-3, -1, 0)); //col 4
		v3Stop.push_back(vector3(-1, -1, 0)); //col 5

		v3Stop.push_back(vector3(1, -1, 0)); //col 6
		v3Stop.push_back(vector3(3, -1, 0)); //col 7
		v3Stop.push_back(vector3(5, -1, 0)); //col 8
		v3Stop.push_back(vector3(7, -1, 0)); //col 9
		v3Stop.push_back(vector3(9, -1, 0)); //col 10

	//ROW 5
		v3Stop.push_back(vector3(-9, -3, 0)); //col 1
		v3Stop.push_back(vector3(-7, -3, 0)); //col 2
		v3Stop.push_back(vector3(-5, -3, 0)); //col 3
		v3Stop.push_back(vector3(-3, -3, 0)); //col 4
		v3Stop.push_back(vector3(-1, -3, 0)); //col 5

		v3Stop.push_back(vector3(1, -3, 0)); //col 6
		v3Stop.push_back(vector3(3, -3, 0)); //col 7
		v3Stop.push_back(vector3(5, -3, 0)); //col 8
		v3Stop.push_back(vector3(7, -3, 0)); //col 9
		v3Stop.push_back(vector3(9, -3, 0)); //col 10

	//ROW 6
		v3Stop.push_back(vector3(-9, -5, 0)); //col 1
		v3Stop.push_back(vector3(-7, -5, 0)); //col 2
		v3Stop.push_back(vector3(-5, -5, 0)); //col 3
		v3Stop.push_back(vector3(-3, -5, 0)); //col 4
		v3Stop.push_back(vector3(-1, -5, 0)); //col 5

		v3Stop.push_back(vector3(1, -5, 0)); //col 6
		v3Stop.push_back(vector3(3, -5, 0)); //col 7
		v3Stop.push_back(vector3(5, -5, 0)); //col 8
		v3Stop.push_back(vector3(7, -5, 0)); //col 9
		v3Stop.push_back(vector3(9, -5, 0)); //col 10
#pragma endregion

		//v3Stop.push_back(vector3(-3, -0, 0));
		//v3Stop.push_back(vector3(3, -0, 0));
		//v3Stop.push_back(vector3(0, 2.5, 0));
		//v3Stop.push_back(vector3(0, -2.5, 0));

		bInit = true;
	}

	vector3 v3Start; //start point
	vector3 v3End; //end point

	//Route is a number that determines the index of the array of stops to visit 
	static uint route = 0; //current route
	v3Start = v3Stop[route]; //start at the current route
	v3End = v3Stop[(route + 1) % v3Stop.size()]; //end at route +1 (if overboard will restart from 0)
	
	//get the percentace
	float fTimeBetweenStops = 0.5;//in seconds
	//map the value to be between 0.0 and 1.0
	float fPercentage = MapValue(fTimer, 0.0f, fTimeBetweenStops, 0.0f, 1.0f);

	//calculate the current position
	vector3 v3CurrentPos = glm::lerp(v3Start, v3End, fPercentage);
	matrix4 m4Model = glm::translate(IDENTITY_M4, v3CurrentPos);

	//if we are done with this route
	if (fPercentage >= 1.0f)
	{
		route++; //go to the next route
		fTimer = m_pSystem->GetDeltaTime(uClock);//restart the clock
		route %= v3Stop.size();//make sure we are within boundries
	}
		
	// render the object
	m_pMesh->Render(m4Projection, m4View, m4Model);
	
	// draw a skybox
	//m_pMeshMngr->AddSkyboxToRenderList();
	m_v4ClearColor = vector4(C_BLACK, 1.0f);

	// draw stops to know we are within stops
	for (uint i = 0; i < v3Stop.size(); ++i)
	{
		m_pMeshMngr->AddCubeToRenderList(glm::translate(v3Stop[i]) * glm::scale(vector3(1.5f)), C_WHITE, RENDER_SOLID);
	}

	
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
	//release the mesh
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}
