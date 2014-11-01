////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Light.h
////////////////////////////////////////////

#ifndef _LIGHT_H
#define _LIGHT_H

	#include"main.h"
	#include"Color.h"
	#include"Point.h"

	class Light
	{
		private:
			Color clrCol;
			Point ptLoc;

		public:
			Light();
			Light(Color Col, Point Loc);

			void SetLocation(Point ptP);
			void SetColor(Color clrC);

			Point GetLocation();
			Color GetColor();
	};

#endif