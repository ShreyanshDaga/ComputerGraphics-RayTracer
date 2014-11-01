////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Triangle.cpp
////////////////////////////////////////////

#include"main.h"
#include"Triangle.h"
#include"Vector2D.h"

char Maximum(float a, float b, float c);

Triangle::Triangle()
{
}

Triangle::Triangle(Vertex A, Vertex B, Vertex C)
{
	this->vxABC[0] = A;
	this->vxABC[1] = B;
	this->vxABC[2] = C;
}

Triangle::Triangle(Vertex ABC[3])
{
	this->vxABC[0] = ABC[0];
	this->vxABC[1] = ABC[1];
	this->vxABC[2] = ABC[2];
}

Vector* Triangle::GetAvgParams(Point ptP, Color *pclrSpec, Color *pclrDiff, float *pfShine)
{
	Vector *pvecN = new Vector();

	float alpha, beta, gamma;

	Vector *pvecPA = this->vxABC[0].GetPoint().VectorFromNu(ptP), *pvecPB = this->vxABC[1].GetPoint().VectorFromNu(ptP), *pvecPC = this->vxABC[2].GetPoint().VectorFromNu(ptP);
	Vector *pvecPAPB = Vector::VectorCrossProduct(*pvecPA, *pvecPB);
	Vector *pvecPBPC = Vector::VectorCrossProduct(*pvecPB, *pvecPC);
	Vector *pvecPCPA = Vector::VectorCrossProduct(*pvecPC, *pvecPA);

	alpha = pvecPBPC->GetMagnitude() / (pvecPBPC->GetMagnitude() + pvecPCPA->GetMagnitude() + pvecPAPB->GetMagnitude());
	beta = pvecPCPA->GetMagnitude() / (pvecPBPC->GetMagnitude() + pvecPCPA->GetMagnitude() + pvecPAPB->GetMagnitude());
	gamma = pvecPAPB->GetMagnitude() / (pvecPBPC->GetMagnitude() + pvecPCPA->GetMagnitude() + pvecPAPB->GetMagnitude());	

	delete pvecPA;
	delete pvecPB;
	delete pvecPC;
	delete pvecPAPB;
	delete pvecPBPC;
	delete pvecPCPA;

	Vector *pvecN1 = this->vxABC[0].GetNormal() * alpha;
	Vector *pvecN2 = this->vxABC[1].GetNormal() * beta;
	Vector *pvecN3 = this->vxABC[2].GetNormal() * gamma;

	float nx, ny, nz;	

	nx = pvecN1->GetX() + pvecN2->GetX() + pvecN3->GetX();
	ny = pvecN1->GetY() + pvecN2->GetY() + pvecN3->GetY();
	nz = pvecN1->GetZ() + pvecN2->GetZ() + pvecN3->GetZ();

	pvecN->SetVector(nx, ny, nz);

	delete pvecN1;
	delete pvecN2;
	delete pvecN3;
			
	pclrSpec->SetR(alpha * this->vxABC[0].GetSpecularColor().GetR() + beta * this->vxABC[1].GetSpecularColor().GetR() + gamma * this->vxABC[2].GetSpecularColor().GetR());
	pclrSpec->SetG(alpha * this->vxABC[0].GetSpecularColor().GetG() + beta * this->vxABC[1].GetSpecularColor().GetG() + gamma * this->vxABC[2].GetSpecularColor().GetG());
	pclrSpec->SetB(alpha * this->vxABC[0].GetSpecularColor().GetB() + beta * this->vxABC[1].GetSpecularColor().GetB() + gamma * this->vxABC[2].GetSpecularColor().GetB());

	pclrDiff->SetR(alpha * this->vxABC[0].GetDiffuseColor().GetR() + beta * this->vxABC[1].GetDiffuseColor().GetR() + gamma * this->vxABC[2].GetDiffuseColor().GetR());
	pclrDiff->SetG(alpha * this->vxABC[0].GetDiffuseColor().GetG() + beta * this->vxABC[1].GetDiffuseColor().GetG() + gamma * this->vxABC[2].GetDiffuseColor().GetG());
	pclrDiff->SetB(alpha * this->vxABC[0].GetDiffuseColor().GetB() + beta * this->vxABC[1].GetDiffuseColor().GetB() + gamma * this->vxABC[2].GetDiffuseColor().GetB());
	
	*pfShine = alpha * this->vxABC[0].GetShine() + beta * this->vxABC[1].GetShine() + gamma * this->vxABC[2].GetShine();

	return pvecN;
}

Vertex Triangle::GetA()
{
	return this->vxABC[0];
}

Vertex Triangle::GetB()
{
	return this->vxABC[1];
}

Vertex Triangle::GetC()
{
	return this->vxABC[2];
}

Vertex* Triangle::GetVertices()
{
	return this->vxABC;
}

Vector* Triangle::GetAvgNormal(Point ptP)
{
	Vector *pvecN = new Vector();

	float alpha, beta, gamma;

	Vector *pvecPA = this->vxABC[0].GetPoint().VectorFromNu(ptP), *pvecPB = this->vxABC[1].GetPoint().VectorFromNu(ptP), *pvecPC = this->vxABC[2].GetPoint().VectorFromNu(ptP);
	Vector *pvecPAPB = Vector::VectorCrossProduct(*pvecPA, *pvecPB);
	Vector *pvecPBPC = Vector::VectorCrossProduct(*pvecPB, *pvecPC);
	Vector *pvecPCPA = Vector::VectorCrossProduct(*pvecPC, *pvecPA);

	alpha = pvecPBPC->GetMagnitude() / (pvecPBPC->GetMagnitude() + pvecPCPA->GetMagnitude() + pvecPAPB->GetMagnitude());
	beta = pvecPCPA->GetMagnitude() / (pvecPBPC->GetMagnitude() + pvecPCPA->GetMagnitude() + pvecPAPB->GetMagnitude());
	gamma = pvecPAPB->GetMagnitude() / (pvecPBPC->GetMagnitude() + pvecPCPA->GetMagnitude() + pvecPAPB->GetMagnitude());	

	delete pvecPA;
	delete pvecPB;
	delete pvecPC;
	delete pvecPAPB;
	delete pvecPBPC;
	delete pvecPCPA;

	Vector *pvecN1 = this->vxABC[0].GetNormal() * alpha;
	Vector *pvecN2 = this->vxABC[1].GetNormal() * beta;
	Vector *pvecN3 = this->vxABC[2].GetNormal() * gamma;

	float nx, ny, nz;	

	nx = pvecN1->GetX() + pvecN2->GetX() + pvecN3->GetX();
	ny = pvecN1->GetY() + pvecN2->GetY() + pvecN3->GetY();
	nz = pvecN1->GetZ() + pvecN2->GetZ() + pvecN3->GetZ();

	pvecN->SetVector(nx, ny, nz);

	delete pvecN1;
	delete pvecN2;
	delete pvecN3;

	return pvecN;
}

bool Triangle::IsPointIn(Point ptP)
{
	Point A = this->GetA().GetPoint(), B  = this->GetB().GetPoint(), C  = this->GetC().GetPoint();

	Vector *pvecPA = ptP.VectorTo(A);
	Vector *pvecPB = ptP.VectorTo(B);
	Vector *pvecPC = ptP.VectorTo(C);

	Vector *pvecPAPB = Vector::VectorCrossProduct(*pvecPA, *pvecPB);
	Vector *pvecPBPC = Vector::VectorCrossProduct(*pvecPB, *pvecPC);
	Vector *pvecPCPA = Vector::VectorCrossProduct(*pvecPC, *pvecPA);

	//Vector *U1 = pvecPAPB->GetUnitVector();
	//Vector *U2 = pvecPBPC->GetUnitVector();
	//Vector *U3 = pvecPCPA->GetUnitVector();

	//float fDiffX1, fDiffX2;
	//float fDiffY1, fDiffY2;
	//float fDiffZ1, fDiffZ2;

	//fDiffX1 = U1->GetX() - U2->GetX();
	//fDiffX2 = U1->GetX() - U3->GetX();
	//
	//fDiffY1 = U1->GetY() - U2->GetY();
	//fDiffY2 = U1->GetY() - U3->GetY();
	//
	//fDiffZ1 = U1->GetZ() - U2->GetZ();
	//fDiffZ2 = U1->GetZ() - U3->GetZ();
	
	bool bSignPA[3], bSignPB[3], bSignPC[3];	

	//PA
	bSignPA[0] = (pvecPAPB->GetX() >= 1e-10 || abs(pvecPAPB->GetX()) <= 1e-10) ? true : false;
	bSignPA[1] = (pvecPAPB->GetY() >= 1e-10 || abs(pvecPAPB->GetY()) <= 1e-10) ? true : false;
	bSignPA[2] = (pvecPAPB->GetZ() >= 1e-10 || abs(pvecPAPB->GetZ()) <= 1e-10) ? true : false;

	//PB
	bSignPB[0] = (pvecPBPC->GetX() >= 1e-10 || abs(pvecPBPC->GetX()) <= 1e-10) ? true : false;
	bSignPB[1] = (pvecPBPC->GetY() >= 1e-10 || abs(pvecPBPC->GetY()) <= 1e-10) ? true : false;
	bSignPB[2] = (pvecPBPC->GetZ() >= 1e-10 || abs(pvecPBPC->GetZ()) <= 1e-10) ? true : false;

    //PC
	bSignPC[0] = (pvecPCPA->GetX() >= 1e-10 || abs(pvecPCPA->GetX()) <= 1e-10) ? true : false;
	bSignPC[1] = (pvecPCPA->GetY() >= 1e-10 || abs(pvecPCPA->GetY()) <= 1e-10) ? true : false;
	bSignPC[2] = (pvecPCPA->GetZ() >= 1e-10 || abs(pvecPCPA->GetZ()) <= 1e-10) ? true : false;
	
	delete pvecPA;
	delete pvecPB;
	delete pvecPC;
	delete pvecPAPB;
	delete pvecPBPC;
	delete pvecPCPA;
	//delete U1;
	//delete U2;
	//delete U3;

	/*
	if(abs(fDiffX1) >= 1e-10 && abs(fDiffX2) >= 1e-10)
	{
		if(abs(fDiffY1) >= 1e-10 && abs(fDiffY2) >= 1e-10)
		{
			if(abs(fDiffZ1) >= 1e-10 && abs(fDiffZ2) >= 1e-10)
			{
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;*/
	
	if(bSignPA[0] == bSignPB[0] && bSignPA[0] == bSignPC[0])
	{
		if(bSignPA[1] == bSignPB[1] && bSignPA[1] == bSignPC[1])
		{
			if(bSignPA[2] == bSignPB[2] && bSignPA[2] == bSignPC[2])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Triangle::IsVertexIn(Vertex vxV)
{
	Point ptP = vxV.GetPoint();

	return (this->IsPointIn(ptP));
}

bool Triangle::IsPointIn(Point ptP, bool b12)
{
	float a,b,c;

	a = this->vecPlane.GetX();
	b = this->vecPlane.GetY();
	c = this->vecPlane.GetZ();

	bool bSign[3];

	char cPlane = Maximum(a,b,c);

	float fPAPB, fPBPC, fPCPA;
	Vector2D PA, PB, PC;

	switch(cPlane)
	{
		case 'a':
			//YZ-plane
			PA.SetVector2D(this->GetA().GetPoint().GetY() - ptP.GetY(), this->GetA().GetPoint().GetZ() - ptP.GetZ());
			PB.SetVector2D(this->GetB().GetPoint().GetY() - ptP.GetY(), this->GetB().GetPoint().GetZ() - ptP.GetZ());
			PC.SetVector2D(this->GetC().GetPoint().GetY() - ptP.GetY(), this->GetC().GetPoint().GetZ() - ptP.GetZ());

			fPAPB = Vector2D::Vector2DCrossProduct(PA,PB), fPBPC  = Vector2D::Vector2DCrossProduct(PB,PC), fPCPA  = Vector2D::Vector2DCrossProduct(PC,PA);
			
			bSign[0] = (fPAPB >= 1e-5) ? true : false;
			bSign[1] = (fPAPB >= 1e-5) ? true : false;
			bSign[2] = (fPAPB >= 1e-5) ? true : false;
			
			if(bSign[0] == bSign[1] && bSign[0] == bSign[2])
				return true;
			else
				return false;

		break;

		case 'b':
			//XZ-Plane
			PA.SetVector2D(this->GetA().GetPoint().GetX() - ptP.GetX(), this->GetA().GetPoint().GetZ() - ptP.GetZ());
			PB.SetVector2D(this->GetB().GetPoint().GetX() - ptP.GetX(), this->GetB().GetPoint().GetZ() - ptP.GetZ());
			PC.SetVector2D(this->GetC().GetPoint().GetX() - ptP.GetX(), this->GetC().GetPoint().GetZ() - ptP.GetZ());

			fPAPB = Vector2D::Vector2DCrossProduct(PA,PB), fPBPC  = Vector2D::Vector2DCrossProduct(PB,PC), fPCPA  = Vector2D::Vector2DCrossProduct(PC,PA);
			
			bSign[0] = (fPAPB >= 1e-5) ? true : false;
			bSign[1] = (fPAPB >= 1e-5) ? true : false;
			bSign[2] = (fPAPB >= 1e-5) ? true : false;
			
			if(bSign[0] == bSign[1] && bSign[0] == bSign[2])
				return true;
			else
				return false;
		break;

		case 'c':
			//XY-Plane
			PA.SetVector2D(this->GetA().GetPoint().GetX() - ptP.GetX(), this->GetA().GetPoint().GetY() - ptP.GetY());
			PB.SetVector2D(this->GetB().GetPoint().GetX() - ptP.GetX(), this->GetB().GetPoint().GetY() - ptP.GetY());
			PC.SetVector2D(this->GetC().GetPoint().GetX() - ptP.GetX(), this->GetC().GetPoint().GetY() - ptP.GetY());

			fPAPB = Vector2D::Vector2DCrossProduct(PA,PB), fPBPC  = Vector2D::Vector2DCrossProduct(PB,PC), fPCPA  = Vector2D::Vector2DCrossProduct(PC,PA);
			
			bSign[0] = (fPAPB >= 1e-5) ? true : false;
			bSign[1] = (fPAPB >= 1e-5) ? true : false;
			bSign[2] = (fPAPB >= 1e-5) ? true : false;
			
			if(bSign[0] == bSign[1] && bSign[0] == bSign[2])
				return true;
			else
				return false;
		break;

	}	
}

char Maximum(float a, float b, float c)
{
	if(abs(a) > abs(b))
	{
		if(abs(a) > abs(c))
		{
			return 'a';
		}		
	}

	if(abs(b) > abs(a))
	{
		if(abs(b) > abs(c))
		{
			return 'b';
		}		
	}
	
	if(abs(c) > abs(b))
	{
		if(abs(c) > abs(a))
		{
			return 'c';
		}		
	}
}