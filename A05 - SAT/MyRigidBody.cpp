#include "MyRigidBody.h"
using namespace Simplex;
//Allocation
void MyRigidBody::Init(void)
{
	m_pMeshMngr = MeshManager::GetInstance();
	m_bVisibleBS = false;
	m_bVisibleOBB = true;
	m_bVisibleARBB = false;

	m_fRadius = 0.0f;

	m_v3ColorColliding = C_RED;
	m_v3ColorNotColliding = C_WHITE;

	m_v3Center = ZERO_V3;
	m_v3MinL = ZERO_V3;
	m_v3MaxL = ZERO_V3;

	m_v3MinG = ZERO_V3;
	m_v3MaxG = ZERO_V3;

	m_v3HalfWidth = ZERO_V3;
	m_v3ARBBSize = ZERO_V3;

	m_m4ToWorld = IDENTITY_M4;
}
void MyRigidBody::Swap(MyRigidBody& a_pOther)
{
	std::swap(m_pMeshMngr, a_pOther.m_pMeshMngr);
	std::swap(m_bVisibleBS, a_pOther.m_bVisibleBS);
	std::swap(m_bVisibleOBB, a_pOther.m_bVisibleOBB);
	std::swap(m_bVisibleARBB, a_pOther.m_bVisibleARBB);

	std::swap(m_fRadius, a_pOther.m_fRadius);

	std::swap(m_v3ColorColliding, a_pOther.m_v3ColorColliding);
	std::swap(m_v3ColorNotColliding, a_pOther.m_v3ColorNotColliding);

	std::swap(m_v3Center, a_pOther.m_v3Center);
	std::swap(m_v3MinL, a_pOther.m_v3MinL);
	std::swap(m_v3MaxL, a_pOther.m_v3MaxL);

	std::swap(m_v3MinG, a_pOther.m_v3MinG);
	std::swap(m_v3MaxG, a_pOther.m_v3MaxG);

	std::swap(m_v3HalfWidth, a_pOther.m_v3HalfWidth);
	std::swap(m_v3ARBBSize, a_pOther.m_v3ARBBSize);

	std::swap(m_m4ToWorld, a_pOther.m_m4ToWorld);

	std::swap(m_CollidingRBSet, a_pOther.m_CollidingRBSet);
}
void MyRigidBody::Release(void)
{
	m_pMeshMngr = nullptr;
	ClearCollidingList();
}
//Accessors
bool MyRigidBody::GetVisibleBS(void) { return m_bVisibleBS; }
void MyRigidBody::SetVisibleBS(bool a_bVisible) { m_bVisibleBS = a_bVisible; }
bool MyRigidBody::GetVisibleOBB(void) { return m_bVisibleOBB; }
void MyRigidBody::SetVisibleOBB(bool a_bVisible) { m_bVisibleOBB = a_bVisible; }
bool MyRigidBody::GetVisibleARBB(void) { return m_bVisibleARBB; }
void MyRigidBody::SetVisibleARBB(bool a_bVisible) { m_bVisibleARBB = a_bVisible; }
float MyRigidBody::GetRadius(void) { return m_fRadius; }
vector3 MyRigidBody::GetColorColliding(void) { return m_v3ColorColliding; }
vector3 MyRigidBody::GetColorNotColliding(void) { return m_v3ColorNotColliding; }
void MyRigidBody::SetColorColliding(vector3 a_v3Color) { m_v3ColorColliding = a_v3Color; }
void MyRigidBody::SetColorNotColliding(vector3 a_v3Color) { m_v3ColorNotColliding = a_v3Color; }
vector3 MyRigidBody::GetCenterLocal(void) { return m_v3Center; }
vector3 MyRigidBody::GetMinLocal(void) { return m_v3MinL; }
vector3 MyRigidBody::GetMaxLocal(void) { return m_v3MaxL; }
vector3 MyRigidBody::GetCenterGlobal(void){	return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
vector3 MyRigidBody::GetMinGlobal(void) { return m_v3MinG; }
vector3 MyRigidBody::GetMaxGlobal(void) { return m_v3MaxG; }
vector3 MyRigidBody::GetHalfWidth(void) { return m_v3HalfWidth; }
matrix4 MyRigidBody::GetModelMatrix(void) { return m_m4ToWorld; }
void MyRigidBody::SetModelMatrix(matrix4 a_m4ModelMatrix)
{
	//to save some calculations if the model matrix is the same there is nothing to do here
	if (a_m4ModelMatrix == m_m4ToWorld)
		return;

	//Assign the model matrix
	m_m4ToWorld = a_m4ModelMatrix;

	//Calculate the 8 corners of the cube
	vector3 v3Corner[8];
	//Back square
	v3Corner[0] = m_v3MinL;
	v3Corner[1] = vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MinL.z);
	v3Corner[2] = vector3(m_v3MinL.x, m_v3MaxL.y, m_v3MinL.z);
	v3Corner[3] = vector3(m_v3MaxL.x, m_v3MaxL.y, m_v3MinL.z);

	//Front square
	v3Corner[4] = vector3(m_v3MinL.x, m_v3MinL.y, m_v3MaxL.z);
	v3Corner[5] = vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MaxL.z);
	v3Corner[6] = vector3(m_v3MinL.x, m_v3MaxL.y, m_v3MaxL.z);
	v3Corner[7] = m_v3MaxL;

	//Place them in world space
	for (uint uIndex = 0; uIndex < 8; ++uIndex)
	{
		v3Corner[uIndex] = vector3(m_m4ToWorld * vector4(v3Corner[uIndex], 1.0f));
	}

	//Identify the max and min as the first corner
	m_v3MaxG = m_v3MinG = v3Corner[0];

	//get the new max and min for the global box
	for (uint i = 1; i < 8; ++i)
	{
		if (m_v3MaxG.x < v3Corner[i].x) m_v3MaxG.x = v3Corner[i].x;
		else if (m_v3MinG.x > v3Corner[i].x) m_v3MinG.x = v3Corner[i].x;

		if (m_v3MaxG.y < v3Corner[i].y) m_v3MaxG.y = v3Corner[i].y;
		else if (m_v3MinG.y > v3Corner[i].y) m_v3MinG.y = v3Corner[i].y;

		if (m_v3MaxG.z < v3Corner[i].z) m_v3MaxG.z = v3Corner[i].z;
		else if (m_v3MinG.z > v3Corner[i].z) m_v3MinG.z = v3Corner[i].z;
	}

	//we calculate the distance between min and max vectors
	m_v3ARBBSize = m_v3MaxG - m_v3MinG;
}
//The big 3
MyRigidBody::MyRigidBody(std::vector<vector3> a_pointList)
{
	Init();
	//Count the points of the incoming list
	uint uVertexCount = a_pointList.size();

	//If there are none just return, we have no information to create the BS from
	if (uVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3MaxL = m_v3MinL = a_pointList[0];

	//Get the max and min out of the list
	for (uint i = 1; i < uVertexCount; ++i)
	{
		if (m_v3MaxL.x < a_pointList[i].x) m_v3MaxL.x = a_pointList[i].x;
		else if (m_v3MinL.x > a_pointList[i].x) m_v3MinL.x = a_pointList[i].x;

		if (m_v3MaxL.y < a_pointList[i].y) m_v3MaxL.y = a_pointList[i].y;
		else if (m_v3MinL.y > a_pointList[i].y) m_v3MinL.y = a_pointList[i].y;

		if (m_v3MaxL.z < a_pointList[i].z) m_v3MaxL.z = a_pointList[i].z;
		else if (m_v3MinL.z > a_pointList[i].z) m_v3MinL.z = a_pointList[i].z;
	}

	//with model matrix being the identity, local and global are the same
	m_v3MinG = m_v3MinL;
	m_v3MaxG = m_v3MaxL;

	//with the max and the min we calculate the center
	m_v3Center = (m_v3MaxL + m_v3MinL) / 2.0f;

	//we calculate the distance between min and max vectors
	m_v3HalfWidth = (m_v3MaxL - m_v3MinL) / 2.0f;

	//Get the distance between the center and either the min or the max
	m_fRadius = glm::distance(m_v3Center, m_v3MinL);
}
MyRigidBody::MyRigidBody(MyRigidBody const& a_pOther)
{
	m_pMeshMngr = a_pOther.m_pMeshMngr;

	m_bVisibleBS = a_pOther.m_bVisibleBS;
	m_bVisibleOBB = a_pOther.m_bVisibleOBB;
	m_bVisibleARBB = a_pOther.m_bVisibleARBB;

	m_fRadius = a_pOther.m_fRadius;

	m_v3ColorColliding = a_pOther.m_v3ColorColliding;
	m_v3ColorNotColliding = a_pOther.m_v3ColorNotColliding;

	m_v3Center = a_pOther.m_v3Center;
	m_v3MinL = a_pOther.m_v3MinL;
	m_v3MaxL = a_pOther.m_v3MaxL;

	m_v3MinG = a_pOther.m_v3MinG;
	m_v3MaxG = a_pOther.m_v3MaxG;

	m_v3HalfWidth = a_pOther.m_v3HalfWidth;
	m_v3ARBBSize = a_pOther.m_v3ARBBSize;

	m_m4ToWorld = a_pOther.m_m4ToWorld;

	m_CollidingRBSet = a_pOther.m_CollidingRBSet;
}
MyRigidBody& MyRigidBody::operator=(MyRigidBody const& a_pOther)
{
	if (this != &a_pOther)
	{
		Release();
		Init();
		MyRigidBody temp(a_pOther);
		Swap(temp);
	}
	return *this;
}
MyRigidBody::~MyRigidBody() { Release(); };
//--- a_pOther Methods
void MyRigidBody::AddCollisionWith(MyRigidBody* a_pOther)
{
	/*
		check if the object is already in the colliding set, if
		the object is already there return with no changes
	*/
	auto element = m_CollidingRBSet.find(a_pOther);
	if (element != m_CollidingRBSet.end())
		return;
	// we couldn't find the object so add it
	m_CollidingRBSet.insert(a_pOther);
}
void MyRigidBody::RemoveCollisionWith(MyRigidBody* a_pOther)
{
	m_CollidingRBSet.erase(a_pOther);
}
void MyRigidBody::ClearCollidingList(void)
{
	m_CollidingRBSet.clear();
}
bool MyRigidBody::IsColliding(MyRigidBody* const a_pOther)
{
	//check if spheres are colliding as pre-test
	bool bColliding = (glm::distance(GetCenterGlobal(), a_pOther->GetCenterGlobal()) < m_fRadius + a_pOther->m_fRadius);
	
	//if they are colliding check the SAT
	if (bColliding)
	{
		if(SAT(a_pOther) != eSATResults::SAT_NONE)
			bColliding = false;// reset to false
	}

	if (bColliding) //they are colliding
	{
		this->AddCollisionWith(a_pOther);
		a_pOther->AddCollisionWith(this);
	}
	else //they are not colliding
	{
		this->RemoveCollisionWith(a_pOther);
		a_pOther->RemoveCollisionWith(this);
	}

	return bColliding;
}
void MyRigidBody::AddToRenderList(void)
{
	if (m_bVisibleBS)
	{
		if (m_CollidingRBSet.size() > 0)
			m_pMeshMngr->AddWireSphereToRenderList(glm::translate(m_m4ToWorld, m_v3Center) * glm::scale(vector3(m_fRadius)), C_BLUE_CORNFLOWER);
		else
			m_pMeshMngr->AddWireSphereToRenderList(glm::translate(m_m4ToWorld, m_v3Center) * glm::scale(vector3(m_fRadius)), C_BLUE_CORNFLOWER);
	}
	if (m_bVisibleOBB)
	{
		if (m_CollidingRBSet.size() > 0)
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) * glm::scale(m_v3HalfWidth * 2.0f), m_v3ColorColliding);
		else
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) * glm::scale(m_v3HalfWidth * 2.0f), m_v3ColorNotColliding);
	}
	if (m_bVisibleARBB)
	{
		if (m_CollidingRBSet.size() > 0)
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(GetCenterGlobal()) * glm::scale(m_v3ARBBSize), C_YELLOW);
		else
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(GetCenterGlobal()) * glm::scale(m_v3ARBBSize), C_YELLOW);
	}
}

uint MyRigidBody::SAT(MyRigidBody* const a_pOther)
{
	/*
	Your code goes here instead of this comment;

	For this method, if there is an axis that separates the two objects
	then the return will be different than 0; 1 for any separating axis
	is ok if you are not going for the extra credit, if you could not
	find a separating axis you need to return 0, there is an enum in
	Simplex that might help you [eSATResults] feel free to use it.
	(eSATResults::SAT_NONE has a value of 0)
	*/

#pragma region "Old Code"
/*
	//SAT Steps:
	//1. Get the plane/axis we're working with (loops through XYZ A, XYZ B, and 9 crosses of A&B)
	//2. Find normal vector of the plane (cross product of two edges)
	//3. Project all the vertices onto the normal 
	//4. Check the min and max vertices of the shapes for overlaps 
	//5. If there is an overlap, go back to step 1 and test the next axis
	// * If ALL of the projections have overlaps, the shapes are colliding
	// * If AT LEAST ONE of the projections does NOT have an overlap, the shapes are NOT colliding

	MyRigidBody* A = this;
	MyRigidBody* B = a_pOther;
	vector3 normal;

	//Test X axis
	normal = vector3(1.0f, 0.0f, 0.0f);

	//A->GetModelMatrix.

	//X axis on A
	if (
			((A->m_v3MaxG.x * normal.x) + (A->m_v3MaxG.y * normal.y) + (A->m_v3MaxG.z * normal.z)) >=
			((B->m_v3MinG.x * normal.x) + (B->m_v3MinG.y * normal.y) + (B->m_v3MinG.z * normal.z))
		)
	{
		return eSATResults::SAT_AX;
	}
	//X axis on B
	else if (
			((B->m_v3MaxG.x * normal.x) + (B->m_v3MaxG.y * normal.y) + (B->m_v3MaxG.z * normal.z)) >=
			((A->m_v3MinG.x * normal.x) + (A->m_v3MinG.y * normal.y) + (A->m_v3MinG.z * normal.z))
		)
	{
		return eSATResults::SAT_BX;
	}

	
	//Test Y axis
	normal = vector3(0.0f, 1.0f, 0.0f);


	//Y axis on A
	if (
		((A->m_v3MaxG.x * normal.x) + (A->m_v3MaxG.y * normal.y) + (A->m_v3MaxG.z * normal.z)) >=
		((B->m_v3MinG.x * normal.x) + (B->m_v3MinG.y * normal.y) + (B->m_v3MinG.z * normal.z))
		)
	{
		return eSATResults::SAT_AY;
	}
	//Y axis on B
	else if (
		((B->m_v3MaxG.x * normal.x) + (B->m_v3MaxG.y * normal.y) + (B->m_v3MaxG.z * normal.z)) >=
		((A->m_v3MinG.x * normal.x) + (A->m_v3MinG.y * normal.y) + (A->m_v3MinG.z * normal.z))
		)
	{
		return eSATResults::SAT_BY;
	}


	//Test Z axis
	normal = vector3(0.0f, 0.0f, 1.0f);


	//Z axis on A
	if (
		((A->m_v3MaxG.x * normal.x) + (A->m_v3MaxG.y * normal.y) + (A->m_v3MaxG.z * normal.z)) >=
		((B->m_v3MinG.x * normal.x) + (B->m_v3MinG.y * normal.y) + (B->m_v3MinG.z * normal.z))
		)
	{
		return eSATResults::SAT_AZ;
	}
	//Z axis on B
	else if (
		((B->m_v3MaxG.x * normal.x) + (B->m_v3MaxG.y * normal.y) + (B->m_v3MaxG.z * normal.z)) >=
		((A->m_v3MinG.x * normal.x) + (A->m_v3MinG.y * normal.y) + (A->m_v3MinG.z * normal.z))
		)
	{
		return eSATResults::SAT_BZ;
	}

	//Cross AX BX //i(aybz - azby) - j(axbz - azbx) + k(axby - aybx)
	//Cross AX BY
	//Cross AX BZ

	//Cross AY BX
	//Cross AY BY
	//Cross AY BZ

	//Cross AZ BX
	//Cross AZ BY
	//Cross AZ BZ
*/
#pragma endregion
	
	//Two objects being tested
	MyRigidBody* A = this;
	MyRigidBody* B = a_pOther;

	float ra, rb;
	matrix3 R, AbsR;

	//A's axes 
	vector3 aX = vector4(1.0f, 0.0f, 0.0f, 0.0f) * A->m_m4ToWorld; //x axis by a's to world
	vector3 aY = vector4(0.0f, 1.0f, 0.0f, 0.0f) * A->m_m4ToWorld; //y axis by a's to world
	vector3 aZ = vector4(0.0f, 0.0f, 1.0f, 0.0f) * A->m_m4ToWorld; //z axis by a's to world
	vector3 aU[] = { aX, aY, aZ };

	//B's axes
	vector3 bX = vector4(1.0f, 0.0f, 0.0f, 0.0f) * B->m_m4ToWorld; //x axis by b's to world
	vector3 bY = vector4(0.0f, 1.0f, 0.0f, 0.0f) * B->m_m4ToWorld; //y axis by b's to world
	vector3 bZ = vector4(0.0f, 0.0f, 1.0f, 0.0f) * B->m_m4ToWorld; //z axis by b's to world
	vector3 bU[] = { bX, bY, bZ };

	//Creates a translation vector T and puts it into A's coordinates
	vector3 t = B->GetCenterGlobal() - A->GetCenterGlobal();
	t = vector3(dot(t, aU[0]), dot(t, aU[1]), dot(t, aU[2]));

/*
	//Object's half-width vectors along each axis
	vector3 e_aX = A->GetHalfWidth() * aX;
	vector3 e_aY = A->GetHalfWidth() * aY;
	vector3 e_aZ = A->GetHalfWidth() * aZ;
	vector3 e_A[] = { e_aX, e_aY, e_aZ };

	vector3 e_bX = B->GetHalfWidth() * bX;
	vector3 e_bY = B->GetHalfWidth() * bY;
	vector3 e_bZ = B->GetHalfWidth() * bZ;
	vector3 e_B[] = { e_bX, e_bY, e_bZ };
*/
	vector3 eA = A->GetHalfWidth();
	vector3 eB = B->GetHalfWidth();

	//R is the rotation matrix which puts B into A's coordinates
	/*
		R=
		(ax * bx)(ax * by)(ax * bz)
		(ay * bx)(ay * by)(ay * bz)
		(az * bx)(az * by)(az * bz)
	*/
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			R[i][j] = dot(aU[i], bU[j]);
		}
	}

	//Adds Epsilon value to 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			AbsR[i][j] = abs(R[i][j]) + DBL_EPSILON;
		}
	}

	//Test axes aX aY & aZ
	for (int i = 0; i < 3; i++)
	{
		ra = eA[i];
		rb = (eB[0] * AbsR[i][0]) + (eB[1] * AbsR[i][1]) + (eB[2] * AbsR[i][2]);
		if (abs(t[i]) > (ra + rb))
		{
			return eSATResults::SAT_AX;
		}
	}

	//Test axes bX bY & bZ
	for (int i = 0; i < 3; i++)
	{
		ra = (eA[0] * AbsR[0][i]) + (eA[1] * AbsR[1][i]) + (eA[2] * AbsR[2][i]);
		rb = eB[i];
		if (abs((t[0] * R[0][i]) + (t[1] * R[1][i]) + (t[2] * R[2][i])) > (ra + rb))
		{
			return eSATResults::SAT_BX;
		}
	}

	//aX x bX
	ra = (eA[1] * AbsR[2][0]) + (eA[2] * AbsR[1][0]);
	rb = (eB[1] * AbsR[0][2]) + (eB[2] * AbsR[0][1]);
	if (abs((t[2] * R[1][0]) - (t[1] * R[2][0])) > (ra + rb))
	{
		return eSATResults::SAT_AXxBX;
	}

	//aX x bY
	ra = (eA[1] * AbsR[2][1]) + (eA[2] * AbsR[1][1]);
	rb = (eB[0] * AbsR[0][2]) + (eB[2] * AbsR[0][0]);
	if (abs((t[2] * R[1][1]) - (t[1] * R[2][1])) > (ra + rb))
	{
		return eSATResults::SAT_AXxBY;
	}

	//aX x bZ
	ra = (eA[1] * AbsR[2][2]) + (eA[2] * AbsR[1][2]);
	rb = (eB[0] * AbsR[0][1]) + (eB[1] * AbsR[0][0]);
	if (abs((t[2] * R[1][2]) - (t[1] * R[2][2])) > (ra + rb))
	{
		return eSATResults::SAT_AXxBZ;
	}

	//aY x bX
	ra = (eA[0] * AbsR[2][0]) + (eA[2] * AbsR[0][0]);
	rb = (eB[1] * AbsR[1][2]) + (eB[2] * AbsR[1][1]);
	if (abs((t[0] * R[2][0]) - (t[2] * R[0][0])) > (ra + rb))
	{
		return eSATResults::SAT_AYxBX;
	}

	//aY x bY
	ra = (eA[0] * AbsR[2][1]) + (eA[2] * AbsR[0][1]);
	rb = (eB[0] * AbsR[1][2]) + (eB[2] * AbsR[1][0]);
	if (abs((t[0] * R[2][1]) - (t[2] * R[0][1])) > (ra + rb))
	{
		return eSATResults::SAT_AYxBY;
	}

	//aY x bZ
	ra = (eA[0] * AbsR[2][2]) + (eA[2] * AbsR[0][2]);
	rb = (eB[1] * AbsR[1][1]) + (eB[1] * AbsR[1][0]);
	if (abs((t[1] * R[2][2]) - (t[2] * R[0][2])) > (ra + rb))
	{
		return eSATResults::SAT_AYxBZ;

	}

	//aZ x bX
	ra = (eA[0] * AbsR[1][0]) + (eA[1] * AbsR[0][0]);
	rb = (eB[1] * AbsR[2][2]) + (eB[2] * AbsR[2][1]);
	if (abs((t[1] * R[0][0]) - (t[0] * R[1][0])) > (ra + rb))
	{
		return eSATResults::SAT_AZxBX;
	}

	//aZ x bY
	ra = (eA[0] * AbsR[1][1]) + (eA[1] * AbsR[0][1]);
	rb = (eB[0] * AbsR[2][2]) + (eB[2] * AbsR[2][0]);
	if (abs((t[1] * R[0][1]) - (t[0] * R[1][1])) > (ra + rb))
	{
		return eSATResults::SAT_AZxBY;
	}

	//aZ x bZ
	ra = (eA[0] * AbsR[1][2]) + (eA[1] * AbsR[0][2]);
	rb = (eB[0] * AbsR[2][1]) + (eB[1] * AbsR[2][0]);
	if (abs((t[1] * R[0][2]) - (t[0] * R[1][2])) > (ra + rb))
	{
		return eSATResults::SAT_AZxBZ;
	}
	//there is no axis test that separates this two objects
	return eSATResults::SAT_NONE;
}