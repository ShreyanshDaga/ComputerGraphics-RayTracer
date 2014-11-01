////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Light.cpp
////////////////////////////////////////////

#include"Light.h"
#include"Color.h"
#include"Point.h"


Light::Light()
{

}

Light::Light(Color Col, Point Loc)
{
	//this->cmatAmb = Amb;
	this->clrCol = Col;
	//this->cmatSpec = Spec;
	this->ptLoc = Loc;	
}

void Light::SetLocation(Point ptP)
{
	this->ptLoc = ptP;
}

void Light::SetColor(Color clrC)
{
	this->clrCol = clrC;
}

Point Light::GetLocation()
{
	return this->ptLoc;
}

Color Light::GetColor()
{
	return this->clrCol;
}