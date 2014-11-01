////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Vector2D.h
////////////////////////////////////////////
#ifndef _VECTOR2D_H
#define _VECTOR2D_H

	#include"main.h"

	class Vector2D
	{
		public:

			float fX, fY;
			float fMag;

			Vector2D();
			Vector2D(float x, float y);

			static float Vector2DCrossProduct(Vector2D v1, Vector2D v2);
			void SetVector2D(float x, float y);
	};

#endif