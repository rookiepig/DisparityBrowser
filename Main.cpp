/****************************************
*   Nehe MFC by Yvo van Dillen based on *
*   Jeff Molofee's Basecode Example     *
*          nehe.gamedev.net             *
*             2001/2004                 *
*                                       *
*****************************************/

#include "stdafx.h"
#include "NeheMFC.h"
#include "NeheWindow.h"
#include "Main.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static float angle=0,rot1,rot2;

CMain::CMain()
{
	// Start Of User Initialization	
}

CMain::~CMain()
{

}

// Function name	: CMain::KeyPressed
// Description	    : Checks for a key press
//                    if( KeyPressed(VK_ESCAPE) ) { ... Escape was pressed ... }
// Return type		: BOOL 
// Argument         : int nCode
BOOL CMain::KeyPressed(int nCode)
{
	if( nCode >= 0 && nCode <= 255 )
	{
		return theApp.keyDown[ nCode ];
	}
	return FALSE;
}


// Function name	: CMain::Initialize
// Description	    : This function will initialize your opengl application
//					  Put in what you need
// Return type		: BOOL 
//					  return TRUE on success or FALSE on error (example :texture/model not found = FALSE)
BOOL CMain::Initialize()
{
	angle		= 0.0f;											// Set Starting Angle To Zero
	zPos        = 0.0f;
	xAngle      = 0.0f;
	yAngle      = 0.0f;

	m_clrImg = NULL;
	m_disImg = NULL;

	glClearColor (1.0f, 1.0f, 1.0f, 0.5f);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate

	return TRUE;
}


// Function name	: CMain::Deinitialize
// Description	    : This function will Deinitialize your opengl application
//					  destroy all objects here
// Return type		: void 
void CMain::Deinitialize()
{
	cvReleaseImage( &m_clrImg );
	cvReleaseImage( &m_disImg );
	m_clrImg = NULL;
	m_disImg = NULL;
}


// Function name	: CMain::Update
// Description	    : this function will be called every xx milliseconds
//					  update your variables through milliseconds
// Return type		: void 
// Argument         : DWORD milliseconds
void CMain::Update(DWORD milliseconds)
{	
	if (KeyPressed(VK_ESCAPE) == TRUE)						// Is ESC Being Pressed?
	{
		theApp.TerminateApplication ();						// Terminate The Program
	}

	if (KeyPressed(VK_F1) == TRUE)							// Is F1 Being Pressed?
	{		
		theApp.ToggleFullScreen ();							// Toggle Fullscreen Mode
	}

	if( KeyPressed( VK_UP ) == TRUE ) {
		yAngle += 1.0;
	}
	if( KeyPressed( VK_DOWN ) == TRUE ){
		yAngle -= 1.0;
	}
	if( KeyPressed( VK_LEFT ) == TRUE ) {
		xAngle += 1.0;
	}
	if( KeyPressed( VK_RIGHT ) == TRUE )  {
		xAngle -= 1.0;
	}
	//angle += (float)(milliseconds) / 5.0f;					// Update angle Based On The Clock
}


// Function name	: CMain::Draw
// Description	    : this function will draw (blt) your opengl scene to the window
// Return type		: void 
void CMain::Draw()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer	
	glLoadIdentity ();											// Reset The Modelview Matrix
	
	glTranslatef(0.0f, 0.0f, zPos-100 );							// Translate 6 Units Into The Screen
	glRotatef( xAngle, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angle
	glRotatef( yAngle, 1.0f, 0.0f, 0.0f );

	if( m_disImg != NULL && m_clrImg != NULL ) {
		if( m_clrImg->width != m_disImg->width || 
			m_clrImg->height != m_disImg->height ) {
				AfxMessageBox( "Image size not same!" );
				Deinitialize();
		} else {
			glBegin( GL_POINTS );
			for( int x = 0; x < m_clrImg->width; x++ ) {
				for( int y = 0; y < m_clrImg->height; y ++ ) {
					CvScalar clr = cvGet2D( m_clrImg, y, x );
					CvScalar dis = cvGet2D( m_disImg, y, x );
					float z = ( dis.val[ 0 ] / 255 ) * ( MAX_DIS - MIN_DIS );
					glColor3f( clr.val[ 2 ] / 255, clr.val[ 1 ] / 255, clr.val[ 0 ] / 255 );
					glVertex3f( ( x - m_clrImg->width / 2 ) * 0.1,
						        ( m_clrImg->height / 2 - y ) * 0.1,
								z );
				}
			}
			glEnd();
		}
	}

	glFlush ();													// Flush The GL Rendering Pipeline
}


