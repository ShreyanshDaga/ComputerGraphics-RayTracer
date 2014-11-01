////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Point.cpp
////////////////////////////////////////////

#include"main.h"
#include"Point.h"
#include"Triangle.h"

Point::Point()
{
	this->fX = 0.00;
	this->fY = 0.00;
	this->fZ = 0.00;	
}

Point::Point(float fX, float fY, float fZ)
{
	this->fX = fX;
	this->fY = fY;
	this->fZ = fZ;	
}

float Point::GetX()
{
	return this->fX;
}

float Point::GetY()
{
	return this->fY;
}

float Point::GetZ()
{
	return this->fZ;
}

float Point::GetAbsDistanceFrom(Point ptP)
{
	float fX2, fY2, fZ2;
	float fDist;

	fX2 = this->fX - ptP.GetX();
	fY2 = this->fY - ptP.GetY();
	fZ2 = this->fZ - ptP.GetZ();

	fX2 = fX2*fX2;
	fY2 = fY2*fY2;
	fZ2 = fZ2*fZ2;

	fDist = sqrt(fX2 + fY2 + fZ2);

	return fDist;
}

void Point::SetLocation(float fX, float fY, float fZ)
{
	this->fX = fX;
	this->fY = fY;
	this->fZ = fZ;
}

Vector* Point::VectorTo(Point ptP)
{	
	float fX = ptP.GetX() - this->fX, fY = ptP.GetY() - this->fY, fZ = ptP.GetZ() - this->fZ;

	float fMag = sqrt(fX*fX + fY*fY + fZ*fZ);

	Vector *pUNew;

	if(fMag <= 1e-15)	
		pUNew = new Vector(0,0,0);	
	else
		pUNew = new Vector(fX/fMag,fY/fMag,fZ/fMag);

	return pUNew;
}

Vector* Point::VectorFrom(Point ptP)
{
	float fX = -ptP.GetX() + this->fX, fY = -ptP.GetY() + this->fY, fZ = -ptP.GetZ() + this->fZ;

	float fMag = sqrt(fX*fX + fY*fY + fZ*fZ);
	Vector *pUNew;
		
	if(fMag <= 1e-15)	
		pUNew = new Vector(0,0,0);	
	else
		pUNew = new Vector(fX/fMag, fY/fMag, fZ/fMag);

	return pUNew;
}

Vector* Point::VectorFromNu(Point ptP)
{
	float fX = ptP.GetX() - this->fX, fY = ptP.GetY() - this->fY, fZ = ptP.GetZ() - this->fZ;

	float fMag = sqrt(fX*fX + fY*fY + fZ*fZ);
	Vector *pUNew;
		
	if(fMag <= 1e-15)
		pUNew = new Vector(0,0,0);	
	else
		pUNew = new Vector(-fX, -fY, -fZ);

	return pUNew;
}

/*
bool Point::IsInTriangle(Triangle T)
{
	Point A = T.GetA().GetPoint(), B  = T.GetB().GetPoint(), C  = T.GetC().GetPoint();

	Vector *pvecPA = this->VectorTo(A);
	Vector *pvecPB = this->VectorTo(B);
	Vector *pvecPC = this->VectorTo(C);

	bool bSignPA[3], bSignPB[3], bSignPC[3];

	//PA
	bSignPA[0] = (pvecPA->GetX() >= 0.00) ? true : false;
	bSignPA[1] = (pvecPA->GetY() >= 0.00) ? true : false;
	bSignPA[2] = (pvecPA->GetZ() >= 0.00) ? true : false;

	//PB
	bSignPB[0] = (pvecPB->GetX() >= 0.00) ? true : false;
	bSignPB[1] = (pvecPB->GetY() >= 0.00) ? true : false;
	bSignPB[2] = (pvecPB->GetZ() >= 0.00) ? true : false;

    //PC
	bSignPC[0] = (pvecPC->GetX() >= 0.00) ? true : false;
	bSignPC[1] = (pvecPC->GetY() >= 0.00) ? true : false;
	bSignPC[2] = (pvecPC->GetZ() >= 0.00) ? true : false;

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
}*/

void Point::operator=(Point &ptP)
{
	this->fX = ptP.GetX();
	this->fY = ptP.GetY();
	this->fZ = ptP.GetZ();
}

Point Point::operator + (Point &ptP)
{
	Point pt;

	pt.fX = this->GetX() + ptP.GetX();
	pt.fY = this->GetY() + ptP.GetY();
	pt.fZ = this->GetZ() + ptP.GetZ();

	return pt;
}