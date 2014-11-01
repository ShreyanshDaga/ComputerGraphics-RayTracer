////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Vector2D.cpp
////////////////////////////////////////////

#include"main.h"
#include"Vector2D.h"

Vector2D::Vector2D()
{
}

Vector2D::Vector2D(float x, float y)
{	
	this->fMag = x*x + y*y;

	this->fX = x/this->fMag;
	this->fY = y/this->fMag;
}

float Vector2D::Vector2DCrossProduct(Vector2D v1, Vector2D v2)
{
	float fAns = v1.fX*v2.fY - v1.fY*v2.fY;

	return fAns;
}

void Vector2D::SetVector2D(float x, float y)
{
	this->fX = x;
	this->fY = y;
}
