////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Point.h
////////////////////////////////////////////

#ifndef _POINT_H
#define _POINT_H

	#include"main.h"
	#include"Color.h"
	//#include"Triangle.h"

	class Point
	{
		public:
			//Co-ordinate
			float fX;
			float fY;
			float fZ;			

		public:
			Point();
			Point(float fX, float fY, float fZ);			

			float GetX();
			float GetY();
			float GetZ();			
			float GetAbsDistanceFrom(Point ptP);
			
			void SetLocation(float fX, float fY, float fZ);
			
			Vector* VectorTo(Point ptP);
			Vector* VectorFrom(Point ptP);
			Vector* VectorFromNu(Point ptP);
			//bool IsInTriangle(Triangle T);

			void operator = (Point &ptP);
			Point operator + (Point &ptP);
	};

#endif
