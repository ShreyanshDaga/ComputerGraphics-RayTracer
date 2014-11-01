////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Triangle.h
////////////////////////////////////////////

#ifndef _TRIANGLE_H
#define _TRIANGLE_H

	#include"main.h"
	#include"Vertex.h"

	class Triangle
	{
		private:
			Vertex vxABC[3];

		public:
			Vector vecPlane;
			Vector vecAB, vecAC;
			float d, fNum;
			
		public:
			Triangle();
			Triangle(Vertex A, Vertex B, Vertex C);
			Triangle(Vertex ABC[3]);

			Vector* GetAvgParams(Point ptP, Color *pclrSpec, Color *pclrDiff, float *pfShine);
			Vector* GetAvgNormal(Point ptP);
			Vertex GetA();
			Vertex GetB();
			Vertex GetC();
			Vertex* GetVertices();

			bool IsPointIn(Point ptP);
			bool IsPointIn(Point ptP, bool b);
			bool IsVertexIn(Vertex vxV);
	};

#endif