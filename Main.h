// Main.h: interface for the CMain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAIN_H__05A74DD2_C37A_4085_A563_7ED88F625CB7__INCLUDED_)
#define AFX_MAIN_H__05A74DD2_C37A_4085_A563_7ED88F625CB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<opencv/cv.h>
#include<opencv/highgui.h>
#define MAX_DIS 80
#define MIN_DIS 0

class CMain  
{
public:
	
	virtual BOOL Initialize();
	virtual void Deinitialize();
	virtual void Update (DWORD milliseconds);
	virtual void Draw();

public:
	BOOL KeyPressed( int nCode );
		
	

	CMain();
	virtual ~CMain();
public :
	float zPos;
	float xAngle;
	float yAngle;

	IplImage* m_clrImg;
	IplImage* m_disImg;

};

#endif // !defined(AFX_MAIN_H__05A74DD2_C37A_4085_A563_7ED88F625CB7__INCLUDED_)
