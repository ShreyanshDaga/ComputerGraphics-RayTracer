////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Sphere.cpp
////////////////////////////////////////////

#include"main.h"
#include"Sphere.h"

Sphere::Sphere()
{

}

Sphere::Sphere(float fRad, Point ptLoc)
{
	this->fRad = fRad;
	this->ptLoc = ptLoc;
}

void Sphere::SetDiffuseColor(Color clr)
{
	this->clrDiffuse = clr;
}

void Sphere::SetSpecularColor(Color clr)
{
	this->clrSpec = clr;
}

void Sphere::SetShine(float fShine)
{
	this->fShine = fShine;
}

void Sphere::SetLocation(Point ptLoc)
{
	this->ptLoc = ptLoc;
}

void Sphere::SetRadius(float fRadius)
{
	this->fRad = fRadius;
}

float Sphere::GetRadius()
{
	return this->fRad;
}

Point Sphere::GetLocation()
{
	return this->ptLoc;
}

Color Sphere::GetSpecularColor()
{
	return this->clrSpec;
}

Color Sphere::GetDiffuseColor()
{
	return this->clrDiffuse;
}

float Sphere::GetShine()
{
	return this->fShine;
}