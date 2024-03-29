////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Color.cpp
////////////////////////////////////////////

#include"main.h"
#include"Color.h"

Color::Color()
{
	this->fR = 0.00;
	this->fG = 0.00;
	this->fB = 0.00;
}

Color::Color(float fR, float fG, float fB)
{
	this->fR = fR;
	this->fG = fG;
	this->fB = fB;
}

Color::Color(float fR, float fG, float fB, float fA)
{
	this->fR = fR;
	this->fG = fG;
	this->fB = fB;
	this->fA = fA;
}

void Color::SetR(float fR)
{
	this->fR = fR;
}

void Color::SetG(float fG)
{
	this->fG = fG;
}

void Color::SetB(float fB)
{
	this->fB = fB;
}

void Color::SetA(float fA)
{
	this->fA = fA;
}

float Color::GetR()
{
	return this->fR;
}

float Color::GetG()
{
	return this->fG;
}

float Color::GetB()
{
	return this->fB;
}

float Color::GetA()
{
	return this->fA;
}

void Color::SetColor(float faCol[3])
{
	this->fR = faCol[0];
	this->fG = faCol[1];
	this->fB = faCol[2];
}

void Color::SetColor(Color *pclColor)
{
	glColor3f(pclColor->GetR(), pclColor->GetG(), pclColor->GetB());
}

void Color::operator = (Color &clArg)
{
	this->fR = clArg.GetR();
	this->fG = clArg.GetG();
	this->fB = clArg.GetB();
	this->fA = clArg.GetA();
}

bool Color::operator==(Color &clArg)
{
	if(this->fR == clArg.GetR() && this->fG == clArg.GetG() && this->fB == clArg.GetB() &&  this->fA == clArg.GetA())
		return true;
	else
		return false;
}