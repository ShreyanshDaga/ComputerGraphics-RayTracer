////////////////////////////////////////////
// Name: Shreyansh Daga
// Course: CSCI 420 Computer Graphics
// HW: 3
// Date: 04/19/2014
// File: GlutWInObj.cpp
////////////////////////////////////////////


#include"main.h"
#include"glutWinObj.h"
#include"RayTracer.h"

using namespace std;

extern Pic *picImage;
extern float fImg[640][480][3];

void SaveFrame(char *pszName);
void SoftShadows();
void BasicRT();
void RecRT();
void MotionBlur();
void DisplayImage(Pic *pic, int iH, int iW);
void Animation();

RayTracer rt(0,0);

//Stores the prev value of mouse points
int iPrevX, iPrevY;
int iDelay = 1;
static GLuint texName[3];
                                                                                                                                                                  
//Initializing all the GlutWinObjate variables
int GlutWinObj::iMenuID=0;
	
float GlutWinObj::fZMultiplier = 1;

float GlutWinObj::fTranX = 0;
float GlutWinObj::fTranY = 0;
float GlutWinObj::fTranZ = 0;

float GlutWinObj::fRotX = 0;
float GlutWinObj::fRotY = 0;
float GlutWinObj::fRotZ = 0;
	
float GlutWinObj::fScaleX = 1;
float GlutWinObj::fScaleY = 1;
float GlutWinObj::fScaleZ = 1;
	
unsigned int GlutWinObj::cRenderMode = 1;
int GlutWinObj::iMode = 0;

bool GlutWinObj::bToggleSun = true;
bool GlutWinObj::bToggleDefAnim = true;
bool GlutWinObj::bRecAnim = false;

//Ctor for GLutWinObj
GlutWinObj::GlutWinObj(int iW, int iH, int iX, int iY)
{
	//Fill up values
	this->iHeight = iH;
	this->iWidth = iW;
	this->iPosX = iX;
	this->iPosY = iY;

	//Init Handle to 0
	this->iWinHandle = 0;
	this->bGlutReady = false;
}

void GlutWinObj::InitGlut(int argc, char* argv[])
{
	//Perform all the initialization tasks
	glutInit(&argc,(char**)argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(this->iWidth, this->iHeight);
	glutInitWindowPosition(this->iPosX, this->iPosY);	

}

int GlutWinObj::GlutCreateWindow(const char *pszTitle)
{
	//Create window here and also set required flags
	this->iWinHandle = glutCreateWindow_ATEXIT_HACK(pszTitle);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0,this->iWidth,0,this->iHeight,1,-1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);	
		
	this->bGlutReady = true;
	rt.InitRaytracer(this->iWidth, this->iHeight);	
	return this->iWinHandle;
}

void GlutWinObj::StartGlutLoop()
{	
	if(this->bGlutReady)
	{
		cout<<"\n* glut Main Loop started..";
		glutMainLoop();	
	}
}

void GlutWinObj::Reg_Callbacks_Prime()
{
	//Register all the callbacks
	this->RegCallback_RenderDisplay();
	this->RegCallback_HandleMouse();
	this->RegCallback_HandleMouseDrag();
	this->RegCallback_HandleMouseIdle();
	this->RegCallback_HandleReshape();
	this->RegCallback_Idle();
	this->RegCallback_HandleKeyboard();
	this->RegCallback_HandleSpecialKey();
	this->InitContextMenu();
}

void GlutWinObj::RegCallback_RenderDisplay()
{
	glutDisplayFunc(&GlutWinObj::DisplayFunc);
}

void GlutWinObj::RegCallback_HandleMouse()
{
	glutMouseFunc(GlutWinObj::MouseFunc);
}

void GlutWinObj::RegCallback_HandleMouseDrag()
{
	glutMotionFunc(GlutWinObj::MouseDragFunc);
}

void GlutWinObj::RegCallback_HandleMouseIdle()
{
	glutPassiveMotionFunc(GlutWinObj::MouseIdleFunc);
}

void GlutWinObj::RegCallback_HandleKeyboard()
{
	glutKeyboardFunc(GlutWinObj::KeyboardFunc);
}

void GlutWinObj::RegCallback_HandleSpecialKey()
{
	glutSpecialFunc(GlutWinObj::SpecialKeyFunc);
}

void GlutWinObj::RegCallback_Idle()
{
	glutIdleFunc(GlutWinObj::IdleFunc);
}

void GlutWinObj::RegCallback_HandleReshape()
{
	glutReshapeFunc(GlutWinObj::ReshapeFunc);
}

void GlutWinObj::InitContextMenu()
{
	iMenuID = glutCreateMenu(GlutWinObj::ContextMenuFunc);
	glutSetMenu(iMenuID);		
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void GlutWinObj::DisplayFunc()
{	
}

void GlutWinObj::MouseFunc(int iButton, int iState, int iX, int iY)
{	
	
}

void GlutWinObj::MouseDragFunc(int iX, int iY)
{
	
}

void GlutWinObj::MouseIdleFunc(int iX, int iY)
{
	
}

void GlutWinObj::KeyboardFunc(unsigned char cKey, int iX, int iY)
{	
	
}

void GlutWinObj::SpecialKeyFunc(int iKey, int iX, int iY)
{
	
}

void GlutWinObj::IdleFunc()
{
	static int ince = 0;
	char pszName[20];

	if(!ince)
	{
		int iCh;

		cout<<"\n *Resolution is kept at 400x300 it can be at max 640 x 480";
		cout<<"\n1. Basic Ray Tracer";
		cout<<"\n2. Soft Shadows";
		cout<<"\n3. Recursive Ray Tracer";
		cout<<"\n4. Motion Blur";
		cout<<"\n5. Animation";
		cout<<"\n Enter Choice: ";
		cin>>iCh;

		switch(iCh)
		{
			case 1:
				BasicRT();
			break;

			case 2:
				SoftShadows();
			break;

			case 3:
				RecRT();
			break;

			case 4:
				MotionBlur();
			break;

			case 5:
				Animation();
			break;

			default:
			break;
		}
	}

	ince++;
}

void GlutWinObj::ReshapeFunc(int iW, int iH)
{	
}

void GlutWinObj::ContextMenuFunc(int iVal)
{
	
}

void GlutWinObj::ResetGlutWinParam()
{
	//Reset all the parameters to original vaues
	
	iMenuID;
	
	fZMultiplier = 1.0;

	fTranX = 0;
	fTranY = 0;
	fTranZ = 0;
	
	fRotX = 0;
	fRotY = 0;
	fRotZ = 0;
	
	fScaleX = 1;
	fScaleY = 1;
	fScaleZ = 1;
	
	cRenderMode = 1;
	iMode;
}

void SaveFrame(char *pszTitle)
{
	//Saves the frame
	int i, j;
	Pic *in = NULL;

	 if (pszTitle == NULL)
		return;
	
	in = pic_alloc(640, 480, 3, NULL);

	printf("File to save to: %s\n", pszTitle);

	for (i=479; i>=0; i--) 
	{
		glReadPixels(0, 479-i, 640, 1, GL_RGB, GL_UNSIGNED_BYTE, &in->pix[i*in->nx*in->bpp]);
	}

	if (jpeg_write(pszTitle, in))
		printf("File saved Successfully\n");
	else
		printf("Error in Saving\n");

	pic_free(in);
}

void DisplayImage(Pic *pic, int iH, int iW)
{
	glBegin(GL_POINTS);
	for(int i = 0;i<iH;i++)
	{
		for(int j = 0;j<iW;j++)
		{
			float r, g, b;

			r = PIC_PIXEL(pic,j,i,0);
			g = PIC_PIXEL(pic,j,i,1);
			b = PIC_PIXEL(pic,j,i,2);

			glColor3f(r/255.00, g/255.00, b/255.00);
			glVertex2i(j,iH - i -1);
		}
	}
	glEnd();
	glFlush();
}

void SoftShadows()
{
	char pszFileName[20];
	char pszOpName[20];

	Pic* pic;

	cout<<"\nEnter Scene File for Soft Shadow: ";
	cin>>pszFileName;

	rt.ReadSceneFile(pszFileName);
	rt.SetCam(0,0,0);
	rt.PreComputeParams();
	sprintf(pszOpName,"op_SoftShadow.jpeg");
	pic = rt.RenderScene(pszOpName, 2);

	cout<<"\n Rendering Complete.!";
	cout<<"\n Output FIile: "<<pszOpName;

	DisplayImage(pic,rt.iHeight, rt.iWidth);
	
	pic_free(pic);
}

void BasicRT()
{
	char pszFileName[20];
	char pszOpName[20];

	Pic* pic;

	cout<<"\nEnter Scene File for Basic Ray Tracer: ";
	cin>>pszFileName;

	rt.ReadSceneFile(pszFileName);
	rt.SetCam(0,0,0);
	rt.PreComputeParams();

	sprintf(pszOpName,"op_BasicRT.jpeg");
	pic = rt.RenderScene(pszOpName, 1);

	cout<<"\n Rendering Complete.!";
	cout<<"\n Output FIile: "<<pszOpName;

	DisplayImage(pic,rt.iHeight, rt.iWidth);
	
	pic_free(pic);
}

void RecRT()
{
	char pszFileName[20];
	char pszOpName[20];

	Pic* pic;

	cout<<"\nEnter Scene File for Recursive Ray Rtacer: ";
	cin>>pszFileName;

	rt.ReadSceneFile(pszFileName);
	rt.SetCam(0,0,0);
	rt.PreComputeParams();
	sprintf(pszOpName,"op_RecRT.jpeg");
	pic = rt.RenderScene(pszOpName, 3);

	cout<<"\n Rendering Complete.!";
	cout<<"\n Output FIile: "<<pszOpName;

	DisplayImage(pic,rt.iHeight, rt.iWidth);
	
	pic_free(pic);
}

void Animation()
{
	Pic *pic;
	char pszName[20];
	char pszOpName[20];
	
	for(int i = 0;i<150;i++)
	{
		float x,y,z;

		rt.SetCam(0.00, 0.00, 0.00);

		//Sphere 1
		x = rt.lstSpheres[0].GetLocation().GetX();
		y = rt.lstSpheres[0].GetLocation().GetY();
		z = rt.lstSpheres[0].GetLocation().GetZ();
		
		y = y + 1*sin((float)i/75.00f*3.14159f);

		Point ptP(x, y, z);
		rt.lstSpheres[0].SetLocation(ptP);
		
		//Sphere 2
		x = rt.lstSpheres[1].GetLocation().GetX();
		y = rt.lstSpheres[1].GetLocation().GetY();
		z = rt.lstSpheres[1].GetLocation().GetZ();
		
		y = y + 3*sin((float)2*i/75.00f*3.14159f*2);

		Point ptP1(x, y, z);
		rt.lstSpheres[1].SetLocation(ptP1);
		
		//Sphere 3
		x = rt.lstSpheres[2].GetLocation().GetX();
		y = rt.lstSpheres[2].GetLocation().GetY();
		z = rt.lstSpheres[2].GetLocation().GetZ();
		
		y = y + 5*sin((float)4*i/75.00f*3.14159f*2);

		Point ptP2(x, y, z);
		rt.lstSpheres[2].SetLocation(ptP2);
		
		x = rt.lstLights[0].GetLocation().GetX();
		y = rt.lstLights[0].GetLocation().GetY();
		z = rt.lstLights[0].GetLocation().GetZ();

		x = 80.00f*(float)i/150 - 40.00f;

		Point pt3(x,y,z);
		rt.lstLights[0].SetLocation(pt3);

		x = rt.lstLights[1].GetLocation().GetX();
		y = rt.lstLights[1].GetLocation().GetY();
		z = rt.lstLights[1].GetLocation().GetZ();

		z = 40.00f*(float)i/150 - 20.00f - 35.00;

		Point pt4(x,y,z);
		rt.lstLights[1].SetLocation(pt4);

		rt.PreComputeParams();
		sprintf(pszName,"%0.3d.jpg",i);
		pic = rt.RenderScene(pszName, 5);
	}


}

void MotionBlur()
{
	char pszFileName[20];
	char pszOpName[20];

	Pic* pic;
	//float fImg[400][300][3];

	Pic *pTemp = pic_alloc(rt.iWidth, rt.iHeight,3,0);

	for(int i = 0;i<rt.iWidth;i++)
	{
		for(int j = 0;j<rt.iHeight;j++)
		{
			//PIC_PIXEL(pTemp, i, j, 0) = 0;
			//PIC_PIXEL(pTemp, i, j, 1) = 0;
			//PIC_PIXEL(pTemp, i, j, 2) = 0;
			fImg[j][i][0] = 0;
			fImg[j][i][1] = 0;
			fImg[j][i][2] = 0;
		}
	}

	cout<<"\nEnter Scene File for Motion Blur: ";
	cin>>pszFileName;

	rt.ReadSceneFile(pszFileName);
	rt.SetCam(0,0,0);

	sprintf(pszOpName,"op_MotionBlurr.jpeg");

	for(int i = 0;i<20;i++)
	{
		float x,y,z;

		x = rt.lstSpheres[0].GetLocation().GetX();
		y = rt.lstSpheres[0].GetLocation().GetY();
		z = rt.lstSpheres[0].GetLocation().GetZ();

		rt.SetCam(0.00, 0.00, 0.00);
		Point ptP(x, y + i*0.01, z);
		rt.lstSpheres[0].SetLocation(ptP);
		
		rt.PreComputeParams();

		pic = rt.RenderScene(pszOpName, 4);

		for(int i = 0;i<rt.iWidth;i++)
		{
			for(int j = 0;j<rt.iHeight;j++)
			{
				fImg[j][i][0] += PIC_PIXEL(pic, i, j, 0);
				fImg[j][i][1] += PIC_PIXEL(pic, i, j, 1);
				fImg[j][i][2] += PIC_PIXEL(pic, i, j, 2);
			}
		}		

		pic_free(pic);
	}

	for(int i = 0;i<rt.iWidth;i++)
	{
		for(int j = 0;j<rt.iHeight;j++)
		{
			PIC_PIXEL(pTemp, i, j, 0) = fImg[j][i][0] /20.00f;
			PIC_PIXEL(pTemp, i, j, 1) = fImg[j][i][1] /20.00f;
			PIC_PIXEL(pTemp, i, j, 2) = fImg[j][i][2] /20.00f;
		}
	}

	cout<<"\n Rendering Complete.!";
	cout<<"\n Output FIile: "<<pszOpName;

	jpeg_write(pszOpName, pTemp);

	DisplayImage(pTemp,rt.iHeight, rt.iWidth);
	
	pic_free(pTemp);
}