////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Sphere.h
////////////////////////////////////////////

#ifndef _SPHERE_H
#define _SPHERE_H

	#include"main.h"	

	class Sphere
	{
		private:
			float fRad;
			Color clrDiffuse;
			Color clrSpec;
			float fShine;
			Point ptLoc;

		public:
			float diffX, diffY, diffZ, c;

		public:
			Sphere();
			Sphere(float fRad, Point ptLoc);

			void SetDiffuseColor(Color clr);
			void SetSpecularColor(Color clr);
			void SetShine(float fShine);
			void SetLocation(Point ptLoc);
			void SetRadius(float fRadius);

			float GetRadius();
			Point GetLocation();
			Color GetSpecularColor();
			Color GetDiffuseColor();
			float GetShine();
	};

#endif