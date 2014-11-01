////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Color.h
////////////////////////////////////////////

#ifndef _COLOR_H
#define _COLOR_H

	#include"main.h"

	class Color
	{
		private:
			float fR;
			float fG;
			float fB;
			float fA;

		public:
			Color();
			Color(float fR, float fG, float fB);
			Color(float fR, float fG, float fB, float fA);

			void SetR(float fR);
			void SetG(float fG);
			void SetB(float fB);
			void SetA(float fA);
			void SetColor(float faCol[3]);

			float GetR();
			float GetG();
			float GetB();
			float GetA();

			static void SetColor(Color *pclColor);

			void operator = (Color &clColArg);
			bool operator == (Color &clColArg);
	};

#endif
