////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Raytracer.h
////////////////////////////////////////////

#ifndef _RAYTRACER_H
#define _RAYTRACER_H

	#include"main.h"
	#include"Sphere.h"
	#include"Triangle.h"
	#include"Vertex.h"
	#include"Light.h"
	#include<list>
	#include<vector>
	#include"ISRes.h"

	class RayTracer
	{
		public:						
			FILE *fp;

			vector<Sphere> lstSpheres;
			vector<Triangle> lstTriangles;
			vector<Light> lstLights;

			int iMaxSphere;
			int iMaxTriangle;
			int iMaxLight;

			int iWidth;
			int iHeight;
			float fOV;
			float fA;

			int iTotObj;
			int iTotSphere;
			int iTotTriangle;
			int iTotLight;
						
			Point ptCamLocation;
			Color clrAmb;

		public:
			RayTracer(int iWidth, int iHeight);
			void InitRaytracer(int iWidth, int iHeight);

			void ReadSceneFile(char *pszName);
			void PreComputeParams();
			Pic* RenderScene(char *pszFileName, int iMode);

			void ParseSphere(FILE *fp, Sphere *pSphere);
			void ParseTriangle(FILE *fp, Triangle *pTriangle);
			void ParseLight(FILE *fp, Light *pLight);
			void ParseCheck(char *pszCheck, char *pszIP);
			void ParseDoubles(FILE *fp, char *pszCheck, float fVar[3]);
			void ParseDouble(FILE *fp, char *pszCheck, float *fVar);

			ISRes* CheckObjectIntersection(Point ptP, Vector *pvecD, bool bShadow);
			ISRes* CheckSphereIntersections(Point ptP, Vector *pvecD, bool bShadow);
			ISRes* CheckTriangleIntersections(Point ptP, Vector *pvecD, bool bShadow);

			ISRes* SphereFast(Point ptP, Vector *pvecD, bool bShadow);
			ISRes* TriangleFast(Point ptP,Vector *pvecD, bool bShadow);

			Color ComputePhongColor(ISRes *pres, Vector *pvecd, bool bDepth);
			Color ComputeTrianglePhong(ISRes *pres, Vector *pvecd, bool bDepth);
			Color ComputeSpherePhong(ISRes *pres, Vector *pvecd, bool bDepth);

			void Method1();
			void Method2();

			void SetCam(float x, float y, float z);
	};

#endif