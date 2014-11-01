////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: ISRes.cpp
////////////////////////////////////////////
#include"main.h"
#include"ISRes.h"

ISRes::ISRes()
{
	this->bRes = false;
}
			
void ISRes::SetRes(bool bRes)
{
	this->bRes = bRes;
}

void ISRes::SetObjType(char cT)
{
	this->cType = cT;
}

void ISRes::SetISPoint(Point ptIS)
{
	this->ptIS = ptIS;
}

void ISRes::SetSphereID(int iID)
{
	this->iSphereID = iID;
}

void ISRes::SetTriangleID(int iID)
{
	this->iTriangleID = iID;
}

void ISRes::SetISNormal(Vector vecN)
{
	this->vecISNormal = vecN;
}

bool ISRes::GetRes()
{
	return this->bRes;
}

char ISRes::GetObjType()
{
	return this->cType;
}

Point ISRes::GetISPoint()
{
	return this->ptIS;
}

int ISRes::GetSphereID()
{
	return this->iSphereID;
}

int ISRes::GetTriangleID()
{
	return this->iTriangleID;
}

Vector ISRes::GetISNormal()
{
	return this->vecISNormal;
}