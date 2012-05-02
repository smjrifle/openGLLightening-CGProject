// Computer Graphics Project - "Object Lighting"
//Saurav Raj 1ST09CS091
//Shailesh Man Joshi (@smjrifle) 1ST09CS085

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h> // Header file for Graphics Library Utility Toolkit (GLUT)

// Constants defined for use in the program
#define FLAT_MODE 0
#define SMOOTH_MODE 1
#define WIREFRAME 2
#define LIGHTING 3
#define TEAPOT 4
#define TORUS 5
#define CONE 6
#define SPHERE 7
#define CUBE 8
#define EXIT 9

// Default values for the scene
static int mode = SMOOTH_MODE;
static int wireframe = 0;
static int lighting = 1;
static int xspin = 0, yspin = 0;
static int xbegin, ybegin;
static int object = TEAPOT;
static int slices = 16;
static int stacks = 16;
//used for animation and moves
int col=0;
float teasize=40.0f;
int cube=45;
int animi=0;
int objanimi=0;
float x1=0;
float x2=0,y2=0,z2=0;
int color_anim=0;
int ch=1;
int x10=0;
int y10=0;
int replay=0, resume=0;
int s1[1000],s2[1000],s3[1000],topy=0, topx=0,top=0;

// Rotation amounts
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

// Light values and coordinates
GLfloat	 lightPos[] = { 0.0f, 0.0f, 75.0f, 1.0f };
GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  ambientLight[] = { 0.5f, 0.5f, 0.5f, 0.2f};
GLfloat  spotDir[] = { 0.0f, 0.0f, -1.0f };

void Sprint( int x, int y, char *st)
{
	int l,i;

	l=strlen( st ); // see how many characters are in text string.
	glRasterPos2i( x, y); // location to start printing text
	for( i=0; i < l; i++)  // loop until i is greater then l
		{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]); // Print a character on the screen
	}

}

// This function does any needed initialization on the rendering context
void init()
{
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	
	// Setup and enable light 0
	// Supply a slight ambient light so the objects can be seen
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	// The light is composed of just a diffuse and specular components
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// Specific spot effects
	// Cut off angle is 50 degrees
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.0f);

	// Enable this light in particular
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	
	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    xbegin = x;
	ybegin = y;
  }
}
//Function for replay in demo mode
void repla()
{
	if(replay==1){if(s3[top++]==1) {x10=s2[topx++]; }else {y10=s1[topy++]; }
	glutPostRedisplay();glutTimerFunc(100, repla,1);
	}
}
//Moves for Replay in demo mode, Object Moves using the following Co-ordinates x10 and y10
void moves()
{	
	if(resume==1) Sprint(-10, 68, "Replay, Press 'X' to resume");
	if(replay==1 && y10!=120) Sprint(-10, 68,"Replay, Press 'Z' to stop");
	//Replay Moves when finished and blue color
	if(y10>=120 && x10>42
		)
	{	
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_POLYGON);
		glVertex2f(-3+x10,-65+y10);
		glVertex2f(3+x10,-65+y10);
		glVertex2f(3+x10,-55+y10);
		glVertex2f(-3+x10,-55+y10);
		glEnd();
		topy=0;topx=0;top=0;x10=0;y10=0;
		if(replay==0){replay=1;
		glutTimerFunc(1000, repla,1);}
		else{replay=0;}
	}
	//Replay Moves before finish and Red Color
	else
	{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-3+x10,-65+y10);
	glVertex2f(3+x10,-65+y10);
	glVertex2f(3+x10,-55+y10);
	glVertex2f(-3+x10,-55+y10);
	glEnd();
	}
}

//Function to Animate Light Source
void anim()
{
	if(animi==1)
	{
	
	if(xRot==360.0f)
	{
		//Change Rotation Co-Ordinate
		if(yRot==360.0f)
		{
			xRot=0.0f; yRot=0.0f;
		}
		else {yRot+=2.0f;}
	}
	else
	{xRot+=2.0f;}
	glutPostRedisplay();
	
	glutTimerFunc(25,anim,0);
	}
	
}
//Function to Animate Object
void objanim()
{	
	if(objanimi==1)
	{
	if(xspin<360)
	{
	xspin+=1;
	}
	else
	{	
		if(object<8)
		{object+=1;
		xspin=0;}
		else
		{objanimi=0;}
	}
	glutPostRedisplay();
	glutTimerFunc(25,objanim,0);
	}
}
//Function to animate color
void coloranim()
{	if(color_anim==1)
{
	if(x2==0 && y2==0 && z2==0) {x2=1.0;}
	else if(x2==1 && y2==0 && z2==0) {x2=0.0; y2=1.0;}
	else if(x2==0 && y2==1 && z2==0) {z2=1.0;y2=0;}
	else if(x2==0 && y2==0 && z2==1) {x2=0.5;y2=0.5;z2=0.5;}
	else if(x2==0.5){x2=0.1;y2=0.3;z2=0.7;}
	else if(z2==0.7){x2=0.1;y2=0.7;z2=0.3;}
	else if(y2==0.7){x2=0.7;y2=0.1;z2=0.3;}
	else {x2=0;y2=0;z2=0;}
	ambientLight[0] =  x2, ambientLight[1] =y2, ambientLight[2] =z2, ambientLight[3] =1.0f;init();
	glutPostRedisplay();
	glutTimerFunc(500,coloranim,0);
}	
}
//Individual Color Animation Functions
void blueanim()
{if(x1<0.7){ambientLight[0] =  0.0f, ambientLight[1] =0.0f, ambientLight[2] =x1, ambientLight[3] =1.0f;col=0;x1+=0.1;init();
	glutPostRedisplay();
	glutTimerFunc(1000,blueanim,0);}
}
void greenanim()
{if(x1<0.7){ambientLight[0] =  0.0f, ambientLight[1] =x1, ambientLight[2] =0.0f, ambientLight[3] =1.0f;col=2;x1+=0.1;init();
	glutPostRedisplay();
	glutTimerFunc(1000,greenanim,0);}
}
void redanim()
{if(x1<0.7){ambientLight[0] =  x1, ambientLight[1] =0.0f, ambientLight[2] =0.0f, ambientLight[3] =1.0f;col=1;x1+=0.1;init();
	glutPostRedisplay();
	glutTimerFunc(1000,redanim,0);}
}
//Display for Demo Mode
void displa(void)
{
	xspin=0;yspin=0;
	glClear(GL_COLOR_BUFFER_BIT);
	//Function for Object to be Moved
	moves();
	//Create Path for Demo Mode
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2f(40,-25);
	glVertex2f(65,-25);
	glVertex2f(65,65);
	glVertex2f(40,65);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-10,-65);
	glVertex2f(-10,-25);
	glVertex2f(10,-25);
	glVertex2f(10,-65);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-10,-25);
	glVertex2f(40,-25);
	glVertex2f(40,5);
	glVertex2f(-10,5);
	glEnd();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-65,-65);
	glVertex2f(-65,65);
	glVertex2f(65,65);
	glVertex2f(65,-65);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	
}
//Function for Menu
void ProcessMenu(int value)
{
	switch(value) {
		case 0:
			mode = FLAT_MODE;
			//Change Entry in Menu
			glutChangeToMenuEntry(1, "Smooth Shading [Y]", 1);
			break;
		case 1:
			mode = SMOOTH_MODE;
			glutChangeToMenuEntry(1, "Flat Shading [Y]", 0);
			break;
		case 2:
			wireframe = !wireframe;
			break;
		case 3:
			lighting = !lighting;
			break;
		case 4:
			object = TEAPOT;
			break;
		case 5:
			object = TORUS;
			break;
		case 6:
			object = CONE;
			break;
		case 7:
			object = SPHERE;
			break;
		case 8:
			object = CUBE;
			break;
		case 9:
			//Change Color
			if(col==0){ambientLight[0] =  1.0f, ambientLight[1] =0.5f, ambientLight[2] =0.5f, ambientLight[3] =1.0f;init();col=1;}
			else if(col==1){ambientLight[0] =  0.3f, ambientLight[1] =1.0f, ambientLight[2] =0.3f, ambientLight[3] =1.0f;init();col=2;}
			else if(col==2){ambientLight[0] =  0.3f, ambientLight[1] =0.3f, ambientLight[2] =1.0f, ambientLight[3] =1.0f;init();col=3;}
			else {ambientLight[0] =  0.5f, ambientLight[1] =0.5f, ambientLight[2] =0.5f, ambientLight[3] =1.0f;init();col=0;}
			break;
		case 10:
			//Quit
			exit(0);break;
		case 11:
			//Animate Light Source
			if(animi==0)
			{
				animi=1;
				glutTimerFunc(1000, anim,1);
			}
			else
				animi=0;
			break;
		case 12:
			//Object Animation
			if(objanimi==0)
			{
				objanimi=1;
				glutTimerFunc(1000,objanim,1);
			}
			else
				objanimi=0;
			break;
		case 13:
			//Color Animation
			if(color_anim==0)
			{
				color_anim=1;
			glutTimerFunc(1000, coloranim,1);
			}
			else
				color_anim=0;
			break;
		case 14:
			//Demo Mode
			object=27;break;

		}
	// Refresh the window
	glutPostRedisplay();
}


// Function to draw the scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if(mode == FLAT_MODE)
		glShadeModel(GL_FLAT);
	else
		glShadeModel(GL_SMOOTH);

	if(lighting)
		// Turn on lights
		glEnable(GL_LIGHTING);
	else
		// Turn off lights
		glDisable(GL_LIGHTING);

    // First place the light 
    // Save the coordinate transformation
    glPushMatrix();	
        // Rotate coordinate system
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);

        // Specify new position and direction in rotated coordinates
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);

        // Set the color to red to draw a red cone
		glColor3ub(255, 0, 0);
		// Translate origin to move the cone out to where the light is positioned
		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
		
		if(!lighting) {
			// Save the lighting state variables
			glPushAttrib(GL_LIGHTING_BIT);
				glEnable(GL_LIGHTING);
				// Draw a red cone to enclose the light source
			if(object!=27)	glutSolidCone(4.0f, 6.0f, 15, 15);
			glPopAttrib();
		}
		else {
			// Draw a red cone to enclose the light source
			if(object!=27) glutSolidCone(4.0f, 6.0f, 15, 15);
		}
        // Draw a smaller displaced sphere to denote the light bulb
        // Save the lighting state variables
        glPushAttrib(GL_LIGHTING_BIT);

            // Turn off lighting and specify a bright yellow sphere
            glDisable(GL_LIGHTING);
            if(lighting)
			glColor3ub(255, 255, 0);
			else
			glColor3f(0.75f, 0.75f, 0.75f);
		if(object!=27) glutSolidSphere(3.0f, 15, 15);

        // Restore lighting state variables
        glPopAttrib();

	// Restore coordinate transformations
	glPopMatrix();
	
	// Set material color
	if(lighting)
		glColor3ub(255, 255, 255);
	else
		glColor3f(0.25f, 0.25f, 0.25f);

	glPushMatrix();	
    // Rotate coordinate system
	if(object==27) {xspin=0;yspin=0;}
    glRotatef(xspin, 0.0f, 1.0f, 0.0f);
	glRotatef(yspin, 1.0f, 0.0f, 0.0f);

	switch (object) {
		case TEAPOT:
			// Draw Teapot
			if(wireframe) {glutWireTeapot(teasize);Sprint(-15, -65, "Wired Tea Pot"); }
			else {glutSolidTeapot(teasize);Sprint(-15, -65, "Solid Tea Pot"); }
			
			break;
		case TORUS:
			// Draw Torus
			if(wireframe) {glutWireTorus(10.0f, 40.0f, slices, stacks);Sprint(-15, -65, "Wired Torus"); }
			else {glutSolidTorus(10.0f, 40.0f, slices, stacks); Sprint(-15, -65, "Solid Torus"); }
			break;
		case CONE:
			// Draw Cone
			if(wireframe) {glutWireCone(40.0f, 70.0f, slices, stacks);Sprint(-15, -65, "Wired Cone"); }
			else {glutSolidCone(40.0f, 70.0f, slices, stacks);Sprint(-15, -65, "Solid Cone"); }
			break;
		case SPHERE:
			// Draw Sphere
			if(wireframe) {glutWireSphere(40.0f, slices, stacks);Sprint(-15, -65, "Wired Sphere"); }
			else {glutSolidSphere(40.0f, slices, stacks);Sprint(-15, -65, "Solid Sphere"); }
			break;
		case CUBE:
			//Draw Cube
			if(wireframe) {glutWireCube(cube);Sprint(-15, -65, "Wired Cube"); }
			else {glutSolidCube(cube);Sprint(-15, -65, "Solid Cube"); }
			break;
		default:
			//Draw Demo Mode
			displa();break;
			
	}		

	glPopMatrix();
	// Display the results
	glutSwapBuffers();
}
//Function for spining Object
void motion(int x, int y)
{	if(object==27)
{xspin=0;yspin=0;}
else{
	xspin = (xspin + (x - xbegin)) % 360;
	xbegin = x;
	yspin = (yspin + (y - ybegin)) % 360;
	ybegin = y;
}
	// Refresh the window
	glutPostRedisplay();
}
//Function for Rotating Light source
void SpecialKeys(int key, int x, int y)
{
    switch(key) {
		case GLUT_KEY_UP:
			xRot -= 5.0f;
			break;
		case GLUT_KEY_DOWN:
			xRot += 5.0f;
			break;
		case GLUT_KEY_LEFT:
			yRot -= 5.0f;
			break;
		case GLUT_KEY_RIGHT:
			yRot += 5.0f;
			break;
	}

	// Refresh the Window
	glutPostRedisplay();
}



void keyboard(unsigned char key, int x, int y)
{
	//Increase and Decrease Number of Slices in Object
    switch(key) {
		case ']':
			if(object==CUBE && cube<80) {cube++;}
			else{slices++;
			stacks++;}
			if(object==TEAPOT && teasize<55) {teasize++;}
			
			break;
		case '[':
			if(object==CUBE && cube>20) {cube--;}
			else{
			if(slices>3 && stacks>3) {
				slices--;
				stacks--;
			}}
			if(object==TEAPOT && teasize>25) {teasize--;}
			break;
		case '1':
			object = TEAPOT;
			break;
		case '2':
			object = TORUS;
			break;
		case '3':
			object = CONE;
			break;
		case '4':
			object = SPHERE;
			break;
		case '5':
			object = CUBE;
			break;
		case 'y':
		case 'Y':
			if(mode == SMOOTH_MODE)
				mode = FLAT_MODE;
			else
				mode = SMOOTH_MODE;
			break;
		case 'u':
		case 'U':
			wireframe = !wireframe;
			break;
		case 'l':
		case 'L':
			lighting = !lighting;
			break;
		case 'n':
		case 'N':
			if(col==0){ambientLight[0] =  1.0f, ambientLight[1] =0.4f, ambientLight[2] =0.4f, ambientLight[3] =1.0f;init();col=1;}
			else if(col==1){ambientLight[0] =  0.3f, ambientLight[1] =1.0f, ambientLight[2] =0.3f, ambientLight[3] =1.0f;init();col=2;}
			else if(col==2){ambientLight[0] =  0.3f, ambientLight[1] =0.3f, ambientLight[2] =1.0f, ambientLight[3] =1.0f;init();col=3;}
			else {ambientLight[0] =  0.5f, ambientLight[1] =0.5f, ambientLight[2] =0.5f, ambientLight[3] =1.0f;init();col=0;}
			break;
		case 'o':
		case 'O':
			if(objanimi==0)
			{
				objanimi=1;
				glutTimerFunc(1000,objanim,1);
			}
			else
				objanimi=0;
			break;
		case 'p':
		case 'P':
			if(animi==0)
			{
				animi=1;
				glutTimerFunc(1000, anim,1);
			}
			else
				animi=0;
			break;
		case 'b':
		case 'B':
			x1=0;
			glutTimerFunc(1000, blueanim,1);
			break;
		case 'r':
		case 'R':
			x1=0;
			glutTimerFunc(1000, redanim,1);
			break;
		case 'g':
		case 'G':
			x1=0;
			glutTimerFunc(1000, greenanim,1);
			break;
		case 'c':
		case 'C':
			if(color_anim==0)
			{
				color_anim=1;
			glutTimerFunc(1000, coloranim,1);
			}
			else
				color_anim=0;
			break;
		case 'w': if(replay!=1)if(y10<120){if((x10<20&&y10<60)||(x10>42 && x10<120 || y10<60)){y10++; s1[topy++]=y10;s3[top++]=0;}}break;
		case 'a': if(replay!=1) if((y10<61 && x10>-7)||(y10>65&&x10>43)){x10--;s3[top++]=1;s2[topx++]=x10;}break;
		case 's': if(replay!=1)if((y10>0 && x10<8 )|| (x10>7 && y10>40)){y10--;s3[top++]=0;s1[topy++]=y10;}break;
		case 'd': if(replay!=1)if((x10<7 && y10<39) || (x10<62 && y10>39)){x10++;s2[topx++]=x10;s3[top++]=1;}break;
		case 'z':replay=0;resume=1;break;
		case 'x':replay=1;resume=0;glutTimerFunc(100, repla,1);break;
		case 54:object=27;break;
		case 27:
			exit(0);
	}

	// Refresh the Window
	glutPostRedisplay();
}


void ChangeSize(int w, int h)
{
	GLfloat aspect;
    
	// Prevent a divide by zero
	if(h == 0)
	h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish viewing volume
	aspect = (GLfloat) w / (GLfloat) h;
	gluPerspective(35.0f, aspect, 1.0f, 500.0f);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -250.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	printf("Open GL LIGHTING\nFunctions:\n\t\'Y\' ->Toggle Shading\n\t\'U\' ->Toggle Wireframe/Solid\n\t\'L\' ->Toggle Lightening");
	printf("\n\t\'1\' ->Teapot\n\t\'2\' ->Torus\n\t\'3\' ->Cone\n\t\'4\' ->Sphere\n\t\'5\' ->Cube\n\t\'6\' ->Demo Mode\n\t\'N\' ->Change Color");
	printf("\n\t\'P\' ->Toggle Light Animation\n\t\'O\' ->Toggle Object Animation\n\t\'R\' ->Red Color\n\t\'G\' ->Green Color\n\t\'B\' ->Blue Color\n\t\'C\' ->Color Animation\n\t\'[\' and \']\' ->Increase or Decrease Size\n\n\t\'Esc\' ->Exit\n");
	printf("\nDEMO MODE:\n\t\'W\' ->UP\t\'S\' ->Down\t\'A\' ->Left\t\'D\' ->Right\n\t\'Z\' ->Pause\t\'X\' ->Resume\n");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Lighting Effects with OpenGL");
	// Create the Menu
	glutCreateMenu(ProcessMenu);
//	if(mode == SMOOTH_MODE)
	glutAddMenuEntry("Flat Shading[Y]", FLAT_MODE);
//	else
//	glutAddMenuEntry("Smooth Shading[S]", SMOOTH_MODE);
	glutAddMenuEntry("Toggle Wireframe/Solid [U]", WIREFRAME);
	glutAddMenuEntry("Toggle Lighting [L]", LIGHTING);
	glutAddMenuEntry("Teapot [1]", TEAPOT);
	glutAddMenuEntry("Torus [2]", TORUS);
	glutAddMenuEntry("Cone [3]", CONE);
	glutAddMenuEntry("Sphere [4]", SPHERE);
	glutAddMenuEntry("Cube [5]", 8);
	glutAddMenuEntry("Demo Mode [6]", 14);
	glutAddMenuEntry("Change Color [N]", 9);
	glutAddMenuEntry("Toggle Light Animation [P]", 11);
	glutAddMenuEntry("Toggle Object Animation [O]", 12);
	glutAddMenuEntry("Toggle Color Animation [C]", 13);
	glutAddMenuEntry("Exit [ESC]", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutDisplayFunc(RenderScene);
	init();
	glutMainLoop();

    return 0;
}
