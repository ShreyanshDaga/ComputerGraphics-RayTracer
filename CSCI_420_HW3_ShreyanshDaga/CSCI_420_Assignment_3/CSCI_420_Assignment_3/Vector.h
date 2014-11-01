////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Vector.h
////////////////////////////////////////////

#ifndef _VECTOR_H
#define _VECTOR_H

	class Vector
	{
		private:
			float fX;
			float fY;
			float fZ;
			float fMag;			

		public:
			Vector();
			Vector(float fX, float fY, float fZ);

			Vector* GetUnitVector();
			float GetMagnitude();
			float GetX();
			float GetY();
			float GetZ();
			
			void SetVector(float fX, float fY, float fZ);
			void SetVector(Vector vecV);
			
			static Vector* VectorCrossProduct(Vector V1, Vector V2);
			static float VectorDotProduct(Vector V1, Vector V2);

			void operator = (Vector &vecV);
			Vector* operator * (float fScal);
			Vector operator - (Vector &vecV);
			Vector operator - ();
			Vector operator + (Vector &vecV);
			void operator *= (float fScale);

	};

#endif