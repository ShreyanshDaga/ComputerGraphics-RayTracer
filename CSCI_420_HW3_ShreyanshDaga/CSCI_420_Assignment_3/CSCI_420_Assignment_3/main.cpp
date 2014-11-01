////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: main.cpp
////////////////////////////////////////////

#include"main.h"
#include"RayTracer.h"

Pic *picImage;

void main(int argc, char* argv[])
{
	GlutWinObj glWin1(400, 300, 200, 100);	
	
	glWin1.InitGlut(argc,argv);
	glWin1.GlutCreateWindow("CSCI420_ASSIGNMENT 2");		
	glWin1.Reg_Callbacks_Prime();	

	//Main Loop start
	glWin1.StartGlutLoop();
}