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

/* NOTE: THIS A* CODE BREAKS THE PROGRAM. IT IS NOT WORKING NOR COMPLETE.
	//Added:
	static std::vector<Node> v3Pos; //List of positions turned Nodes
#pragma region "Hardcoded Node Positions"
	//ROW 1
		v3Pos.push_back(Node(vector3(-9, 5, 0),0)); //col 1
		v3Pos.push_back(Node(vector3(-7, 5, 0),1)); //col 2
		v3Pos.push_back(Node(vector3(-5, 5, 0),2)); //col 3
		v3Pos.push_back(Node(vector3(-3, 5, 0),3)); //col 4
		v3Pos.push_back(Node(vector3(-1, 5, 0),4)); //col 5

		v3Pos.push_back(Node(vector3(1, 5, 0),5)); //col 6
		v3Pos.push_back(Node(vector3(3, 5, 0),6)); //col 7
		v3Pos.push_back(Node(vector3(5, 5, 0),7)); //col 8
		v3Pos.push_back(Node(vector3(7, 5, 0),8)); //col 9
		v3Pos.push_back(Node(vector3(9, 5, 0),9)); //col 10

	//ROW 2
		v3Pos.push_back(Node(vector3(-9, 3, 0), 10)); //col 1
		v3Pos.push_back(Node(vector3(-7, 3, 0), 11)); //col 2
		v3Pos.push_back(Node(vector3(-5, 3, 0), 12)); //col 3
		v3Pos.push_back(Node(vector3(-3, 3, 0), 13)); //col 4
		v3Pos.push_back(Node(vector3(-1, 3, 0), 14)); //col 5

		v3Pos.push_back(Node(vector3(1, 3, 0), 15)); //col 6
		v3Pos.push_back(Node(vector3(3, 3, 0), 16)); //col 7
		v3Pos.push_back(Node(vector3(5, 3, 0), 17)); //col 8
		v3Pos.push_back(Node(vector3(7, 3, 0), 18)); //col 9
		v3Pos.push_back(Node(vector3(9, 3, 0), 19)); //col 10

	//ROW 3
		v3Pos.push_back(Node(vector3(-9, 1, 0), 20)); //col 1
		v3Pos.push_back(Node(vector3(-7, 1, 0), 21)); //col 2
		v3Pos.push_back(Node(vector3(-5, 1, 0), 22)); //col 3
		v3Pos.push_back(Node(vector3(-3, 1, 0), 23)); //col 4
		v3Pos.push_back(Node(vector3(-1, 1, 0), 24)); //col 5

		v3Pos.push_back(Node(vector3(1, 1, 0), 25)); //col 6
		v3Pos.push_back(Node(vector3(3, 1, 0), 26)); //col 7
		v3Pos.push_back(Node(vector3(5, 1, 0), 27)); //col 8
		v3Pos.push_back(Node(vector3(7, 1, 0), 28)); //col 9
		v3Pos.push_back(Node(vector3(9, 1, 0), 29)); //col 10

	//ROW 4
		v3Pos.push_back(Node(vector3(-9, -1, 0), 30)); //col 1
		v3Pos.push_back(Node(vector3(-7, -1, 0), 31)); //col 2
		v3Pos.push_back(Node(vector3(-5, -1, 0), 32)); //col 3
		v3Pos.push_back(Node(vector3(-3, -1, 0), 33)); //col 4
		v3Pos.push_back(Node(vector3(-1, -1, 0), 34)); //col 5

		v3Pos.push_back(Node(vector3(1, -1, 0), 35)); //col 6
		v3Pos.push_back(Node(vector3(3, -1, 0), 36)); //col 7
		v3Pos.push_back(Node(vector3(5, -1, 0), 37)); //col 8
		v3Pos.push_back(Node(vector3(7, -1, 0), 38)); //col 9
		v3Pos.push_back(Node(vector3(9, -1, 0), 39)); //col 10

	//ROW 5
		v3Pos.push_back(Node(vector3(-9, -3, 0), 40)); //col 1
		v3Pos.push_back(Node(vector3(-7, -3, 0), 41)); //col 2
		v3Pos.push_back(Node(vector3(-5, -3, 0), 42)); //col 3
		v3Pos.push_back(Node(vector3(-3, -3, 0), 43)); //col 4
		v3Pos.push_back(Node(vector3(-1, -3, 0), 44)); //col 5

		v3Pos.push_back(Node(vector3(1, -3, 0), 45)); //col 6
		v3Pos.push_back(Node(vector3(3, -3, 0), 46)); //col 7
		v3Pos.push_back(Node(vector3(5, -3, 0), 47)); //col 8
		v3Pos.push_back(Node(vector3(7, -3, 0), 48)); //col 9
		v3Pos.push_back(Node(vector3(9, -3, 0), 49)); //col 10

	//ROW 6
		v3Pos.push_back(Node(vector3(-9, -5, 0), 50)); //col 1
		v3Pos.push_back(Node(vector3(-7, -5, 0), 51)); //col 2
		v3Pos.push_back(Node(vector3(-5, -5, 0), 52)); //col 3
		v3Pos.push_back(Node(vector3(-3, -5, 0), 53)); //col 4
		v3Pos.push_back(Node(vector3(-1, -5, 0), 54)); //col 5

		v3Pos.push_back(Node(vector3(1, -5, 0), 55)); //col 6
		v3Pos.push_back(Node(vector3(3, -5, 0), 56)); //col 7
		v3Pos.push_back(Node(vector3(5, -5, 0), 57)); //col 8
		v3Pos.push_back(Node(vector3(7, -5, 0), 58)); //col 9
		v3Pos.push_back(Node(vector3(9, -5, 0), 59)); //col 10
#pragma endregion

	int startNode = 0; //Sets the start Node
	int endNode = 59; //Sets the end/goal Node

	int currentNode = 0; //Sets the current node in the algorithm

	for each(Node n in v3Pos) //Calls findNeighbors on each Node- neighbors are now stored
	{
		n.findNeighbors(v3Pos);
	}

#pragma region "A* Pseudocode from Medium.Com"
	// A* (star) Pathfinding
		// Initialize both open and closed list
			//let the openList equal empty list of nodes
			std::vector<int> openList;
			// the closedList equal empty list of nodes
			std::vector<int> closedList;

			std::vector<Node> path;

		// Add the start node
			//put the startNode on the openList (leave it's f at zero)
			openList.push_back(startNode);

		// Loop until you find the end
			//while the openList is not empty
			while (!openList.empty())
			{
				// Get the current node
					//let the currentNode equal the node with the least f value
				//**STILL NEED:** PERFORM LINEAR SEARCH ON ALL NODES IN OPENLIST BY COMPARING NODE.F
					//remove the currentNode from the openList
				//**STILL NEED:** openList.erase() <- what do I put in here to remove currentNode?
					//add the currentNode to the closedList
				closedList.push_back(currentNode);

				// Found the goal
					//if currentNode is the goal
				if (v3Pos[currentNode].getIndex() == v3Pos[endNode].getIndex())
				{
					//Congratz! You've found the end! Backtrack to get path
					for(int i=openList.size(); i>0; i--)
					{
						path.push_back(v3Pos[openList[i]]);
					}

					openList.clear();
				}

				// Generate children
					//let the children of the currentNode equal the adjacent nodes
				std::vector<Node> children = v3Pos[currentNode].getNeighbors();

				//for each child in the children
				for each (Node n in children)
				{
					bool inClosed = false;
					bool inOpen = false;
					for (int i = 0; i < children.size(); i++)
					{
						if (closedList[i] == n.getIndex())
						{
							inClosed = true;
						}
						if (openList[i] == n.getIndex())
						{
							inOpen = true;
						}
					}

					// Child is on the closedList
						//if child is in the closedList
					if (inClosed || !n.isTraversable())
					{
						//continue to beginning of for loop
						break;
					}

					

					// Create the f, g, and h values
					//child.g = currentNode.g + distance between child and current
					n.setG(

						v3Pos[currentNode].getG() +
						(v3Pos[currentNode].getDistance(n))
					);
					//child.h = distance from child to end
					n.setH(n.getDistance(v3Pos[endNode]));
					//child.f = child.g + child.h
					n.setF(n.getG() + n.getH());

					// Child is already in openList
						//if child.position is in the openList's nodes positions
					if (inOpen)
					{
						//if the child.g is higher than the openList node's g
						if (n.getG() > v3Pos[currentNode].getG()) {
							//continue to beginning of for loop
							break;
						}
					}

					// Add the child to the openList
						//add the child to the openList
					openList.push_back(n.getIndex());
				}
			}
#pragma endregion
*/

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
