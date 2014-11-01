////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Vertex.cpp
////////////////////////////////////////////

#include"main.h"
#include"Vertex.h"
#include"Point.h"

Vertex::Vertex()
{
	this->ptLoc.SetLocation(0,0,0);
}

Vertex::Vertex(float fX, float fY, float fZ)
{
	this->ptLoc.SetLocation(fX,fY,fZ);
}

Color Vertex::GetDiffuseColor()
{
	return this->clrDiffuse;
}

Color Vertex::GetSpecularColor()
{
	return this->clrSpec;
}

float Vertex::GetShine()
{
	return this->fShine;
}

Vector Vertex::GetNormal()
{
	return this->faNormal;
}

Point Vertex::GetPoint()
{
	return this->ptLoc;
}

void Vertex::SetDiffuseColor(Color clr)
{
	this->clrDiffuse = clr;
}

void Vertex::SetSpecularColor(Color clr)
{
	this->clrSpec = clr;
}

void Vertex::SetNormal(Vector vecNormal)
{
	this->faNormal = vecNormal;
}

void Vertex::SetShine(float fShine)
{
	this->fShine = fShine;
}

void Vertex::SetLocation(Point ptLoc)
{
	this->ptLoc = ptLoc;
}

void Vertex::SetLocation(float faLoc[3])
{
	this->ptLoc.SetLocation(faLoc[0], faLoc[1], faLoc[2]);
}