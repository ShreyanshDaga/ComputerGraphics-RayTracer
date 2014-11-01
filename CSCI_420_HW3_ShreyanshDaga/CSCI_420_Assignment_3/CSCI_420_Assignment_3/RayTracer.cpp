////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: Raytracer.cpp
////////////////////////////////////////////

#include"main.h"
#include<iostream>
#include"RayTracer.h"
#include"ISRes.h"

Vector* ComputeRVec(Vector *pvecL, Vector *pvecN);

extern Pic *picImage;
float fImg[640][480][3];
float ksr,ksg,ksb;

RayTracer::RayTracer(int iWidth, int iHeight)
{
	//this->InitRaytracer(iWidth, iHeight);
}

void RayTracer::InitRaytracer(int iWidth, int iHeight)
{
	//Set Max Light Sources
	this->iMaxLight = 100;
	this->iTotLight = 0;

	//Set Max Spheres
	this->iMaxSphere = 1000;
	this->iTotSphere = 0;

	//Set Max Triangles
	this->iMaxTriangle = 2000;
	this->iTotTriangle = 0;

	this->ptCamLocation.SetLocation(0.00,0.00,0.00);

	this->iWidth = iWidth;
	this->iHeight = iHeight;

	this->fA = (float)this->iWidth/this->iHeight;

	this->fOV = 60;
}

void RayTracer::ReadSceneFile(char *pszName)
{
	float dVar[3];
	char pszType[15];
	this->fp = fopen(pszName,"r");
	
	Triangle T;
	Sphere S;
	Light L;

	//total number of obj	
	fscanf(fp,"%i",&this->iTotObj);

	ParseDoubles(fp, "amb:", dVar);
	this->clrAmb.SetColor(dVar);
	printf("\nABD Light: %f %f %f", clrAmb.GetR(), clrAmb.GetB(), clrAmb.GetG());

	for(int i = 0;i<this->iTotObj;i++)
	{
		fscanf(fp,"%s\n",pszType);
		//printf

		if(stricmp(pszType,"triangle") == 0)
		{
			if(iTotTriangle > iMaxTriangle)
			{
				cout<<"\nError .!!!\n Maximum triangle number reached\nAborting!!";
				exit(0);
			}
			this->iTotTriangle++;
			ParseTriangle(fp, &T);
			this->lstTriangles.push_back(T);
			cout<<"\n Triangle Added: "<<this->lstTriangles.size();

		}
		else if(stricmp(pszType,"sphere") == 0)
		{
			if(iTotSphere > iMaxSphere)
			{
				
				cout<<"\nError .!!!\n Maximum Sphere number reached\nAborting!!";exit(0);
			}

			this->iTotSphere++;
			ParseSphere(fp, &S);
			this->lstSpheres.push_back(S);
			cout<<"\n Sphere Added: "<<this->lstSpheres.size();
		}
		else if(stricmp(pszType,"light") == 0)
		{
			if(iTotLight > iMaxLight)
			{
				cout<<"\nError .!!!\n Maximum number of Lights reached\nAborting!!";
				exit(0);
			}

			this->iTotLight++;
			ParseLight(fp, &L);
			this->lstLights.push_back(L);
			cout<<"\n Light Added: "<<this->lstLights.size();
		}
		else
		{
			cout<<"\nError !!\n Unknown Symbol/Token detected.\n Aborting";
		}
	}

	cout<<"\n Total Objects in scene "<<this->iTotSphere + this->iTotTriangle + this->iTotLight;
	cout<<"\n**Reading Scene FIle complete";
}

void RayTracer::PreComputeParams()
{
	Sphere *S;

	for(int i = 0;i<this->iTotSphere;i++)
	{
		S = &this->lstSpheres[i];

		S->diffX = this->ptCamLocation.GetX() - S->GetLocation().GetX();
		S->diffY = this->ptCamLocation.GetY() - S->GetLocation().GetY();
		S->diffZ = this->ptCamLocation.GetZ() - S->GetLocation().GetZ();

		S->c = S->diffX*S->diffX + S->diffY*S->diffY + S->diffZ*S->diffZ - S->GetRadius()*S->GetRadius();		
	}

	Triangle *T;
	for(int i = 0;i<this->iTotTriangle;i++)
	{
		Vector *pvec;

		T = &this->lstTriangles[i];
		
		pvec = T->GetA().GetPoint().VectorTo(T->GetB().GetPoint());
		T->vecAB = *pvec;
		delete pvec;
		pvec = T->GetA().GetPoint().VectorTo(T->GetC().GetPoint());
		T->vecAC = *pvec;
		delete pvec;
		pvec = Vector::VectorCrossProduct(T->vecAB, T->vecAC);
		T->vecPlane = *pvec;
		delete pvec;
		pvec = T->vecPlane.GetUnitVector();
		T->vecPlane = *pvec;
		delete pvec;

		T->d = -1*(T->vecPlane.GetX() * T->GetA().GetPoint().GetX() + T->vecPlane.GetY() * T->GetA().GetPoint().GetY() + T->vecPlane.GetZ() * T->GetA().GetPoint().GetZ());
		T->fNum = -1 * (T->vecPlane.GetX() *this->ptCamLocation.GetX() + T->vecPlane.GetX()*this->ptCamLocation.GetY() + T->vecPlane.GetZ()*this->ptCamLocation.GetZ() + T->d);		
	}
}

Pic* RayTracer::RenderScene(char *pszFileName, int iMode)
{
	float fXl, fYt, fXr, fYb;
	Pic *picNew = pic_alloc(this->iWidth, this->iHeight,3,0);

	fXl = -this->fA*tan(this->fOV/2*3.14159/180.00);
	fYt = tan(this->fOV/2*3.14159/180.00);
	fXr = -fXl;
	fYb = -fYt;

	float fXlen, fYlen;

	fXlen = fXr - fXl;
	fYlen = fYt - fYb;

	Vector vecD;
	Vector *pvecd = NULL;
	ISRes *presR = NULL, *presSecond = NULL;
	Color clrC, clrS;	
	
	printf("\n");
	
	for(int y = 0;y<this->iHeight;y++)
	{
		for(int x = 0;x<this->iWidth;x++)
		{		
			if(pvecd != NULL)
				delete pvecd;

			vecD.SetVector((fXl + x*fXlen/this->iWidth) - this->ptCamLocation.GetX(), (fYt - y*fYlen/this->iHeight) - this->ptCamLocation.GetY(),-1.0 - this->ptCamLocation.GetZ());
			pvecd = vecD.GetUnitVector();

			presR = this->CheckObjectIntersection(this->ptCamLocation, pvecd, false);
			
			if(presR->GetRes())
			{
				bool bFlag;

				if(iMode == 2)
					bFlag = true;
				else
					bFlag = false;

				clrC = this->ComputePhongColor(presR, pvecd, bFlag);

				if(iMode == 3 && iMode != 1)
				{
					//Calc pvecR
					Vector *pvecV = presR->GetISPoint().VectorTo(ptCamLocation);
					Vector *pvecR = ComputeRVec(pvecV, &presR->GetISNormal());
					
					presSecond = this->CheckObjectIntersection(presR->GetISPoint(), pvecR, false);			
					
					delete pvecV;
					delete pvecR;

					if(presSecond->GetRes())
					{
						float r,g,b;
					
						clrS = this->ComputePhongColor(presSecond, pvecR, true);
					
						r = (1-ksr)*clrC.GetR() + ksr*clrS.GetR();
						g = (1-ksg)*clrC.GetR() + ksg*clrS.GetG();
						b = (1-ksb)*clrC.GetR() + ksb*clrS.GetB();
						
						clrC.SetR(r);
						clrC.SetG(g);
						clrC.SetB(b);				
					}

					PIC_PIXEL(picNew,x,y,0) = clrC.GetR()*255;
					PIC_PIXEL(picNew,x,y,1) = clrC.GetG()*255;
					PIC_PIXEL(picNew,x,y,2) = clrC.GetB()*255;

					delete presSecond;
				}
				else
				{
					PIC_PIXEL(picNew,x,y,0) = clrC.GetR()*255;
					PIC_PIXEL(picNew,x,y,1) = clrC.GetG()*255;
					PIC_PIXEL(picNew,x,y,2) = clrC.GetB()*255;
				}										
			}
			else
			{
				PIC_PIXEL(picNew,x,y,0) = 0;
				PIC_PIXEL(picNew,x,y,1) = 0;
				PIC_PIXEL(picNew,x,y,2) = 0;												
			}

			delete presR;			
		}

		printf("\rPercent Complete: %f",(float)y/this->iHeight*100.00f);
	}		

	if(iMode != 4) 
		jpeg_write(pszFileName,picNew);	
	
	return picNew;
}
		
void RayTracer::ParseSphere(FILE *fp, Sphere *pS)
{
	float faVar[3];
	float fVar=0.00;
	Color clrC;
	Point ptP;

	ParseDoubles(fp,"pos:",faVar);//s.position);
	ptP.SetLocation(faVar[0], faVar[1], faVar[2]); 
	pS->SetLocation(ptP);
	ParseDouble(fp,"rad:", &fVar);//&s.radius);
	pS->SetRadius(fVar);
	ParseDoubles(fp,"dif:", faVar);//s.color_diffuse);
	clrC.SetColor(faVar);
	pS->SetDiffuseColor(clrC);
	ParseDoubles(fp,"spe:", faVar);//s.color_specular);
	clrC.SetColor(faVar);
	pS->SetSpecularColor(clrC);
	ParseDouble(fp,"shi:", &fVar);//&s.shininess);
	pS->SetShine(fVar);	
}

void RayTracer::ParseTriangle(FILE *fp, Triangle *pT)
{
	float fVar[3];
	Vector vecV;
	Color clrC;
	Point ptP;
	float fVar1;

	for(int i = 0;i<3;i++)
	{
		ParseDoubles(fp,"pos:", fVar);
		ptP.SetLocation(fVar[0], fVar[1], fVar[2]);
		pT->GetVertices()[i].SetLocation(ptP);		
		ParseDoubles(fp,"nor:", fVar);
		vecV.SetVector(fVar[0], fVar[1], fVar[2]);
		pT->GetVertices()[i].SetNormal(vecV);
		ParseDoubles(fp,"dif:", fVar);
		clrC.SetColor(fVar);
		pT->GetVertices()[i].SetDiffuseColor(clrC);
		ParseDoubles(fp,"spe:", fVar);
		clrC.SetColor(fVar);
		pT->GetVertices()[i].SetSpecularColor(clrC);
		ParseDouble(fp,"shi:",&fVar1);
		pT->GetVertices()[i].SetShine(fVar1);
	}
}

void RayTracer::ParseLight(FILE *fp, Light *pL)
{
	Point ptP;
	Color clrC;
	float faVar[3];

	ParseDoubles(fp,"pos:",faVar);
	ptP.SetLocation(faVar[0], faVar[1], faVar[2]);
	pL->SetLocation(ptP);
	ParseDoubles(fp,"col:",faVar);
	clrC.SetColor(faVar);
	pL->SetColor(clrC);
}

void RayTracer::ParseCheck(char *pszCheck, char *pszIP)
{
	if(stricmp(pszCheck,pszIP))
    {      
      printf("Expected '%s ' found '%s '\n",pszCheck,pszIP);
      printf("Parser error, abnormal abortion\n");
      exit(1);
    }
}

void RayTracer::ParseDoubles(FILE *fp, char *pszCheck, float fVar[3])
{
	char str[15];
	fscanf(fp,"%s",str);
	this->ParseCheck(pszCheck,str);
	fscanf(fp,"%f %f %f", &fVar[0], &fVar[1], &fVar[2]);
	//printf("%s %f %f %f\n",pszCheck,fVar[0],fVar[1],fVar[2]);
}

void RayTracer::ParseDouble(FILE *fp, char *pszCheck, float *fVar)
{
	char s[15];
	fscanf(fp,"%s",s);		
	this->ParseCheck(pszCheck,s);
	fscanf(fp,"%f",fVar);
	//printf("%s %f\n",pszCheck ,*fVar);
}

Vector* ComputeRVec(Vector *pvecL, Vector *pvecN)
{
	float fDot = Vector::VectorDotProduct(*pvecL, *pvecN);

	fDot *= 2.00;

	Vector *pvecTemp = pvecN->operator*(fDot);
	Vector *pvecR = new Vector((*pvecTemp - *pvecL));

	delete pvecTemp;
	return pvecR;
}

ISRes* RayTracer::CheckObjectIntersection(Point ptP, Vector *pvecD, bool bShadow)
{
	ISRes *presSp = NULL, *presTr = NULL;

	if(bShadow)
	{
		presSp = this->CheckSphereIntersections(ptP, pvecD, bShadow);
		
		if(presSp->GetRes())
		{
			delete presTr;
			return presSp;
		}

		presTr = this->CheckTriangleIntersections(ptP, pvecD, bShadow);
		
		if(presTr->GetRes())
		{
			delete presSp;
			return presTr;
		}

		return presSp;
	}
	else
	{
		presSp =  this->CheckSphereIntersections(ptP, pvecD, false);
	//	presSp = this->SphereFast(ptP, pvecD, false);
	//	presTr = this->TriangleFast(ptP, pvecD, false);
		presTr = this->CheckTriangleIntersections(ptP, pvecD, false);

		if(presTr->GetRes() == false)
		{
			delete presTr;
			return presSp;
		}
		if(presSp->GetRes() == false)	
		{
			delete presSp;
			return presTr;	
		}
		//Compute Which Point is closer to CAM
		if(presTr->GetISPoint().GetAbsDistanceFrom(ptP) < presSp->GetISPoint().GetAbsDistanceFrom(ptP))
		{
			delete presSp;
			return presTr;
		}
		else
		{
			delete presTr;
			return presSp;
		}
	}
}

ISRes* RayTracer::CheckSphereIntersections(Point ptP, Vector *pvecd, bool bShadow)
{
	ISRes *presR = new ISRes;
	Sphere S;
	presR->SetObjType('s');
	presR->SetRes(false);

	Point ptC;
	float b = 0, c = 0;	
	float fPrevt = 1000000;

	if(this->iTotSphere == 0)
		return presR;

	for(int s = 0;s<this->iTotSphere;s++)
	{			
		S = this->lstSpheres[s];		
		
		float diffx, diffy, diffz;

		diffx = -S.GetLocation().GetX() + ptP.GetX();
		diffy = -S.GetLocation().GetY() + ptP.GetY();
		diffz = -S.GetLocation().GetZ() + ptP.GetZ();

		b = 2*(pvecd->GetX() * diffx + pvecd->GetY() * diffy + pvecd->GetZ() * diffz);		
		c = diffx*diffx + diffy*diffy + diffz*diffz - S.GetRadius()*S.GetRadius();

		float t = (b*b - 4*c);

		if(t >= 0)
		{
			float t0, t1;

			t0 = (- b + sqrt(t))/2.00;
			t1 = (- b - sqrt(t))/2.00;

			if(t0 >= 1e-4 || t1 >= 1e-4)
			{
				if(t0 >= 0.00 && t1 >= 0.00)
					t = min(t0,t1);
				else if(t0 >= 0.00 && t1 < 0.00)
					t = t0;
				else if(t1 >= 0.00 && t0 < 0.00)
					t = t1;

				if(t < fPrevt)
				{						
					presR->SetRes(true);
					if(bShadow)
						break;
					Point ptIS(pvecd->GetX()*t + ptP.GetX(), pvecd->GetY()*t + ptP.GetY(), pvecd->GetZ()*t + ptP.GetZ());
					//Vector *pvecN = S.GetLocation().VectorTo(ptIS);
					presR->SetISPoint(ptIS);
					presR->SetSphereID(s);
					//presR->SetISNormal(*pvecN);
					fPrevt = t;					
					//delete pvecN;
				}
			}
		}		
	}

	return presR;
}

ISRes* RayTracer::CheckTriangleIntersections(Point ptP, Vector *pvecd, bool bShadow)
{
	ISRes *presR = new ISRes();

	presR->SetObjType('t');
	presR->SetRes(false);	

	float fPrevDist = 10000000;
	Triangle T;	

	if(this->iTotTriangle == 0)
		return presR;

	for(int t = 0;t<this->iTotTriangle;t++)
	{
		float a,b,c,d;
		float fT;
		
		T = this->lstTriangles[t];	

		a = T.vecPlane.GetX();
		b = T.vecPlane.GetY();
		c = T.vecPlane.GetZ();
		
		d = T.d;

		float fNum, fDen;

		fDen = a*pvecd->GetX() + b*pvecd->GetY() + c*pvecd->GetZ();

		if(fDen == 0.00)
			continue;
		else
		{
			fNum = -1*(a*ptP.GetX() + b*ptP.GetY() + c*ptP.GetZ() + d);

			fT = fNum/fDen;
			
			if(abs(fT) >= 1e-4 && fT >= 1e-4)
			{
				Point ptIS(pvecd->GetX()*fT + ptP.GetX(), pvecd->GetY()*fT + ptP.GetY(), pvecd->GetZ()*fT + ptP.GetZ());					
				
				if(ptIS.GetX()*a + ptIS.GetY()*b+ptIS.GetZ()*c+d >= 1e-5)
				{
					continue;
				}

				if(T.IsPointIn(ptIS))
				{					
					if(bShadow)
					{
						presR->SetRes(true);					
						presR->SetISPoint(ptIS);
						presR->SetTriangleID(t);
						break;
					}

					if(ptIS.GetAbsDistanceFrom(ptP) < fPrevDist)
					{
						//Vector *pvecN = T.GetAvgNormal(ptIS);
						presR->SetRes(true);					
						presR->SetISPoint(ptIS);
						presR->SetTriangleID(t);
						//presR->SetISNormal(*pvecN);
						fPrevDist = ptIS.GetAbsDistanceFrom(ptP);											
						//delete pvecN;
					}
				}
			}
		}
	}			

	return presR;
}

ISRes* RayTracer::SphereFast(Point ptP, Vector *pvecd, bool bShadow)
{
	ISRes *presR = new ISRes;
	presR->SetObjType('s');
	presR->SetRes(false);
	
	float  b = 0;	
	float fPrevt = 1000000;
	Sphere S;

	for(int s = 0;s<this->iTotSphere;s++)
	{
		S = this->lstSpheres[s];		
		
		b = 2*(pvecd->GetX() * S.diffX + pvecd->GetY() * S.diffY + pvecd->GetZ() * S.diffZ);		

		float t = (b*b - 4*S.c);

		if(t >= 0)
		{
			float t0, t1;

			t0 = (- b + sqrt(t))/2.00f;
			t1 = (- b - sqrt(t))/2.00f;

			if(t0 >= 1e-4 || t1 >= 1e-4)
			{
				if(t0 >= 0.00 && t1 >= 0.00)
					t = min(t0,t1);
				else if(t0 >= 0.00 && t1 < 0.00)
					t = t0;
				else if(t1 >= 0.00 && t0 < 0.00)
					t = t1;

				if(t < fPrevt)
				{	
					presR->SetRes(true);					
					Point ptIS(pvecd->GetX()*t + ptP.GetX(), pvecd->GetY()*t + ptP.GetY(), pvecd->GetZ()*t + ptP.GetZ());
					Vector *pvecN = S.GetLocation().VectorTo(ptIS);
					presR->SetISPoint(ptIS);
					presR->SetSphereID(s);
					presR->SetISNormal(*pvecN);
					fPrevt = t;					
					delete pvecN;
					if(bShadow)
						break;
				}
			}
		}		
	}

	return presR;
}

ISRes* RayTracer::TriangleFast(Point ptP,Vector *pvecd, bool bShadow)
{
	ISRes *presR = new ISRes();

	presR->SetObjType('t');
	presR->SetRes(false);	

	float fPrevDist = 100000;
	Triangle T;

	if(this->iTotTriangle == 0)
		return presR;

	for(int t = 0;t<this->iTotTriangle;t++)
	{
		//float a,b,c,d;
		float fT;
		
		T = this->lstTriangles[t];
		
		float fDen;

		fDen = T.vecPlane.GetX() * pvecd->GetX() + T.vecPlane.GetY() * pvecd->GetY() + T.vecPlane.GetZ() * pvecd->GetZ();

		if(fDen == 0.00)
			continue;
		else
		{			
			fT = T.fNum/fDen;
			
			if(abs(fT) >= 1e-4 && fT >= 0.000000)
			{
				Point ptIS(pvecd->GetX() * fT + ptP.GetX(), pvecd->GetY() * fT + ptP.GetY(), pvecd->GetZ() * fT + ptP.GetZ());					
				
				if(T.IsPointIn(ptIS))
				{
					if(ptIS.GetAbsDistanceFrom(ptP) < fPrevDist)
					{
						Vector *pvecN = T.GetAvgNormal(ptIS);
						presR->SetRes(true);					
						presR->SetISPoint(ptIS);
						presR->SetTriangleID(t);
						presR->SetISNormal(*pvecN);
						fPrevDist = ptIS.GetAbsDistanceFrom(ptP);											
						delete pvecN;
						if(bShadow)
							break;
					}
				}
			}
		}
	}			

	return presR;
}

Color RayTracer::ComputePhongColor(ISRes *pres, Vector *pvecd, bool bDepth)
{
	if(pres->GetObjType() == 's')
		return this->ComputeSpherePhong(pres, pvecd, bDepth);	
	else
		return this->ComputeTrianglePhong(pres, pvecd, bDepth);
}

Color RayTracer::ComputeSpherePhong(ISRes *pres, Vector *pvecd, bool bDepth)
{
	Sphere S;
	float faCol[3];	
	Color clrC;

	Vector *pvecN;
	
	float fKdR, fKdG, fKdB;
	float fKsR, fKsG, fKsB;
	
	S = this->lstSpheres[pres->GetSphereID()];
	pvecN = S.GetLocation().VectorTo(pres->GetISPoint());
	
	fKdR = S.GetDiffuseColor().GetR();
	fKdG = S.GetDiffuseColor().GetG();
	fKdB = S.GetDiffuseColor().GetB();
	fKsR = S.GetSpecularColor().GetR();
	fKsG = S.GetSpecularColor().GetG();
	fKsB = S.GetSpecularColor().GetB();
	
	//if(bDepth == false)
	{
		ksr = fKsR;
		ksg = fKsG;
		ksb = fKsB;
	}

	Color clC = this->clrAmb;
		
	Vector *pvecV = ptCamLocation.VectorFrom(pres->GetISPoint());
	Vector *pvecL;						
	Point ptL;

	faCol[0] = clC.GetR();
	faCol[1] = clC.GetG();
	faCol[2] = clC.GetB();

	int light = 1;
	if(bDepth)
		light = 9;

	for(int l = 0;l<this->iTotLight;l++)
	{							
		Light L = this->lstLights[l];
		ptL = L.GetLocation();

		Point ptLA[9] = {ptL, ptL, ptL, ptL, ptL, ptL, ptL, ptL, ptL};
		
		if(bDepth)
		{
			ptLA[0].fX += 0.1; ptLA[0].fY += 0.1;
			ptLA[1].fX -= 0.1; ptLA[1].fY += 0.1;
			ptLA[2].fX -= 0.1; ptLA[2].fY += 0.1;
			ptLA[3].fX += 0.1; ptLA[3].fY -= 0.1;
			ptLA[4].fX -= 0.1; ptLA[4].fY -= 0.1;
			ptLA[5].fX -= 0.1; ptLA[5].fY -= 0.1;
			ptLA[6].fX += 0.1; ptLA[6].fY -= 0.1;
			ptLA[7].fX -= 0.1; ptLA[7].fY -= 0.1;
			ptLA[8].fX -= 0.1; ptLA[8].fY -= 0.1;
		}

		for(int i = 0;i<light;i++)
		{		
			//Find Light Ray
			pvecL = ptLA[i].VectorFrom(pres->GetISPoint());
			Point ptEIS(pres->GetISPoint().GetX() + pvecL->GetX()*0.0005, pres->GetISPoint().GetY() + pvecL->GetY()*0.0005, pres->GetISPoint().GetZ() + pvecL->GetZ()*0.0005);

			//See if in Shadow or not
			ISRes *presS = this->CheckObjectIntersection(ptEIS, pvecL, true);
			
			if(presS->GetRes())
			{
				//faShad[0] += 0.00;
				//faShad[1] += 0.00;
				//faShad[2] += 0.00;
			}
			else
			{
				//if(i)
				{
					//Phong
					Vector *pvecR = ComputeRVec(pvecL, pvecN);

					float LdotN = Vector::VectorDotProduct(*pvecL, *pvecN);
					float RdotV = Vector::VectorDotProduct(*pvecR, *pvecV);

					if(LdotN <= 1e-10)
						LdotN = 0.00;	

					if(RdotV <= 1e-10)
						RdotV = 0.00;
			
					faCol[0] += L.GetColor().GetR() * ((fKdR * (LdotN)) + fKsR * (pow(RdotV, S.GetShine())));
					faCol[1] += L.GetColor().GetG() * ((fKdG * (LdotN)) + fKsG * (pow(RdotV, S.GetShine())));
					faCol[2] += L.GetColor().GetB() * ((fKdB * (LdotN)) + fKsB * (pow(RdotV, S.GetShine())));
					
					delete pvecR;
				}
			}

			delete presS;
			delete pvecL;
		}
	}

	faCol[0] /= light;
	faCol[1] /= light;
	faCol[2] /= light;
	 
	if(faCol[0] >= 1.00)
		faCol[0] = 1.00;
	if(faCol[1] >= 1.00)
		faCol[1] = 1.00;
	if(faCol[2] >= 1.00)
		faCol[2] = 1.00;

	delete pvecN;	
	delete pvecV;	

	clrC.SetColor(faCol);

	return clrC;
}

Color RayTracer::ComputeTrianglePhong(ISRes *pres, Vector *pvecd, bool bDepth)
{
	Color *pclrSpec = new Color(), *pclrDiff = new Color();	
	float faCol[3];
	Triangle T;
	Color clrC;

	float fKdR, fKdG, fKdB;
	float fKsR, fKsG, fKsB;
	float fShine;

	Vector *pvecN;
	T = this->lstTriangles[pres->GetTriangleID()];
	pvecN = T.GetAvgParams(pres->GetISPoint(), pclrSpec, pclrDiff, &fShine);
	
	fKdR = pclrDiff->GetR();
	fKdG = pclrDiff->GetG();
	fKdB = pclrDiff->GetB();
	fKsR = pclrSpec->GetR();
	fKsG = pclrSpec->GetG();
	fKsB = pclrSpec->GetB();
	
	//if(bDepth == false)
	{
		ksr = fKsR;
		ksg = fKsG;
		ksb = fKsB;
	}

	delete pclrDiff;
	delete pclrSpec;

	Color clC = this->clrAmb;
		
	Vector *pvecV = ptCamLocation.VectorFrom(pres->GetISPoint());
	Vector *pvecL;						
	Point ptL;
	//Point ptEIS(pres->GetISPoint().GetX() + pvecN->GetX()*0.004, pres->GetISPoint().GetY() + pvecN->GetY()*0.004, pres->GetISPoint().GetZ() + pvecN->GetZ()*0.004);
	
	faCol[0] = clC.GetR();
	faCol[1] = clC.GetG();
	faCol[2] = clC.GetB();

	int light = 1;

	if(bDepth)
		light = 9;

	for(int l = 0;l<this->iTotLight;l++)
	{							
		Light L = this->lstLights[l];
		ptL = L.GetLocation();
		
		Point ptLA[9] = {ptL, ptL, ptL, ptL, ptL, ptL, ptL, ptL, ptL};		

		if(bDepth)
		{
			ptLA[0].fX += 0.05; ptLA[0].fY += 0.05;
			ptLA[1].fX -= 0.05; ptLA[1].fY += 0.05;
			ptLA[2].fX -= 0.05; ptLA[2].fY += 0.05;
			ptLA[3].fX += 0.05; ptLA[3].fY -= 0.05;
			ptLA[4].fX -= 0.05; ptLA[4].fY -= 0.05;
			ptLA[5].fX -= 0.05; ptLA[5].fY -= 0.05;
			ptLA[6].fX += 0.05; ptLA[6].fY -= 0.05;
			ptLA[7].fX -= 0.05; ptLA[7].fY -= 0.05;
			ptLA[8].fX -= 0.05; ptLA[8].fY -= 0.05;
		}		

		for(int i = 0;i<light;i++)
		{			
			//Find Light Ray
			pvecL = ptLA[i].VectorFrom(pres->GetISPoint());

			//See if in Shadow or not
			Point ptEIS(pres->GetISPoint().GetX() + pvecL->GetX() * 0.00, pres->GetISPoint().GetY() + pvecL->GetY() * 0.00, pres->GetISPoint().GetZ() + pvecL->GetZ() * 0.00);
			
			ISRes *presS = this->CheckObjectIntersection(pres->GetISPoint(), pvecL, true);
			
			float distPL = pres->GetISPoint().GetAbsDistanceFrom(L.GetLocation());
			float distPS = pres->GetISPoint().GetAbsDistanceFrom(presS->GetISPoint());

			if(presS->GetRes())
			{			
				//cout<<"\n In";
				faCol[0] += 0.00;
				faCol[1] += 0.00;
				faCol[2] += 0.00;
			}
			else
			{
				//cout<<"\n Out";
				Vector *pvecR = ComputeRVec(pvecL, pvecN);
				float LdotN, RdotV;

				LdotN = Vector::VectorDotProduct(*pvecL, *pvecN);
				RdotV = Vector::VectorDotProduct(*pvecR, *pvecV);

				if(LdotN <= 1e-10)
					LdotN = 0.00;	

				if(RdotV <= 1e-10)
					RdotV = 0.00;

				faCol[0] += L.GetColor().GetR() * ((fKdR * (LdotN)) + fKsR * (pow(RdotV, fShine)));
				faCol[1] += L.GetColor().GetG() * ((fKdG * (LdotN)) + fKsG * (pow(RdotV, fShine)));
				faCol[2] += L.GetColor().GetB() * ((fKdB * (LdotN)) + fKsB * (pow(RdotV, fShine)));
				
				delete pvecR;
			}

			delete presS;
			delete pvecL;
		}	
	}

	faCol[0] /= light;
	faCol[1] /= light;
	faCol[2] /= light;
	 
	if(faCol[0] >= 1.00)
		faCol[0] = 1.00;
	if(faCol[1] >= 1.00)
		faCol[1] = 1.00;
	if(faCol[2] >= 1.00)
		faCol[2] = 1.00;

	delete pvecN;	
	delete pvecV;	

	clrC.SetColor(faCol);

	return clrC;
}

void RayTracer::Method1()
{
}

void RayTracer::Method2()
{
}

void RayTracer::SetCam(float x, float y, float z)
{
	this->ptCamLocation.SetLocation(x,y,z);
}