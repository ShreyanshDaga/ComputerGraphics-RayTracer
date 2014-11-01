////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: ISRes.h
////////////////////////////////////////////

#ifndef _ISRES_H
#define _ISRES_H

	#include"main.h"
	#include"Point.h"
	
	class ISRes
	{
		private:
			bool bRes;
			char cType;
			Point ptIS;
			int iSphereID;
			int iTriangleID;
			Vector vecISNormal;

		public:
			float fsr,ksg,ksb;
			ISRes();
			
			void SetRes(bool bRes);
			void SetObjType(char cT);
			void SetISPoint(Point ptIS);
			void SetSphereID(int iID);
			void SetTriangleID(int iID);
			void SetISNormal(Vector ISNormal);
			bool GetRes();
			char GetObjType();
			Point GetISPoint();
			int GetSphereID();
			int GetTriangleID();
			Vector GetISNormal();
	};

#endif