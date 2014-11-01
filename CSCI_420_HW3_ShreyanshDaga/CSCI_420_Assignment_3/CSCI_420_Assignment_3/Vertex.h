////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Vertex.h
////////////////////////////////////////////
#ifndef _VERTEX_H
#define _VERTEX_H

	#include"main.h"
	#include"Point.h"

	class Vertex
	{
		private:
			Point ptLoc;
			Color clrDiffuse;
			Color clrSpec;
			Vector faNormal;
			float fShine;

		public:
			Vertex();
			Vertex(float fX, float fY, float fZ);
			
			Color GetDiffuseColor();
			Color GetSpecularColor();
			float GetShine();
			Vector GetNormal();
			Point GetPoint();

			void SetDiffuseColor(Color clr);
			void SetSpecularColor(Color clr);
			void SetNormal(Vector vecNormal);
			void SetShine(float fShine);
			void SetLocation(Point ptLoc);
			void SetLocation(float faLoc[3]);			
	};

#endif