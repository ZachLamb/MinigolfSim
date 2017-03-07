/*
*  Zach Lamb
*  Final Project
*
*  Based off of previous homeworks
*
*/
#include "CSCIx229.h"

int mode=1;       //  Projection mode
int move=1;       //  Move light
int th=0;         //  Azimuth of view angle
int ph=10;        //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1;     //  Aspect ratio
double dim=3.0;   //  Size of world
// Light values
int one       =   1;     // Unit value
int distance  =   5;     // Light distance
int inc       =  10;     // Ball increment
int smooth    =   1;     // Smooth/Flat shading
int local     =   0;     // Local Viewer Model
int emission  =   0;     // Emission intensity (%)
int ambient   =  30;     // Ambient intensity (%)
int diffuse   = 100;     // Diffuse intensity (%)
int specular  =   0;     // Specular intensity (%)
int shininess =   0;     // Shininess (power of two)
float shinyvec[1];       // Shininess (value)
int zh        =  90;     // Light azimuth
float ylight  =   0;     // Elevation of light
unsigned int texture[9]; // Texture names
int frameNumber = 0; //rotate windmill

/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);

      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transformations
   glPopMatrix();
}

/*
 * Draw a brick, given position x, y, z and scaling factors
 * dx, dy, dz and rotation about the z-axis th
 *
 */
static void brick(double x, double y, double z,
		      double dx, double dy, double dz,
		      double th,GLuint  textureOf){


  // Set specular color to white
  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

  glPushMatrix();

  // Translations
  glTranslated(x, y, z);
  glRotated(th, 0, 1, 0);
  glScaled(dx, dy, dz);

  // Enable Textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

  // Body of brick
  glBindTexture(GL_TEXTURE_2D,textureOf); // Stone
  glBegin(GL_QUADS);
  //Front
  glNormal3f( 0, 0, 1);
  glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1, 1);
  glTexCoord2f(5.0, 0.0); glVertex3f(+1,-1, 1);
  glTexCoord2f(5.0, 5.0); glVertex3f(+1,+1, 1);
  glTexCoord2f(0.0, 5.0); glVertex3f(-1,+1, 1);
  //  Back
  glNormal3f( 0, 0,-1);
  glTexCoord2f(0.0, 0.0); glVertex3f(+1,-1,-1);
  glTexCoord2f(5.0, 0.0); glVertex3f(-1,-1,-1);
  glTexCoord2f(5.0, 5.0); glVertex3f(-1,+1,-1);
  glTexCoord2f(0.0, 5.0); glVertex3f(+1,+1,-1);
  //  Right
  glNormal3f(+1, 0, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(+1,-1,+1);
  glTexCoord2f(5.0, 0.0); glVertex3f(+1,-1,-1);
  glTexCoord2f(5.0, 5.0); glVertex3f(+1,+1,-1);
  glTexCoord2f(0.0, 5.0); glVertex3f(+1,+1,+1);
  //  Left
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1,-1);
  glTexCoord2f(5.0, 0.0); glVertex3f(-1,-1,+1);
  glTexCoord2f(5.0, 5.0); glVertex3f(-1,+1,+1);
  glTexCoord2f(0.0, 5.0); glVertex3f(-1,+1,-1);
  //  Top
  glNormal3f( 0,+1, 0);
  glVertex3f(-1,+1,+1);
  glVertex3f(+1,+1,+1);
  glVertex3f(+1,+1,-1);
  glVertex3f(-1,+1,-1);
  //  Bottom
  glNormal3f( 0,-1, 0);
  glVertex3f(-1,-1,-1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,-1,+1);
  glVertex3f(-1,-1,+1);
  glEnd();
  glDisable(GL_POLYGON_OFFSET_FILL);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}
//creates a tower from brick,a roof with the bricks as well,and finally the wings
static void windmill(double radius,double centralX,double centralY,double height){

  //main tower
   for(double j=0.05; j<2.50 ; j=j+0.05){

       double rotate = 0.0;
        double angle = 0.1;
     if(j<.15){;
       for (double i=0; i<50; i=i+10) {
           float x = radius*cos(i) + centralX + rotate;
           float y = radius*sin(i) + centralY + rotate;
           brick(x,j,y,.05,.05,angle,90,texture[1]);
       }
     }
     else{
        for (double i=0; i<360; i=i+5) {
            float x = radius*cos(i) + centralX + rotate;
            float y = radius*sin(i) + centralY + rotate;
            brick(x,j,y,.05,.05,angle,90,texture[1]);
        }
     }
   }
   //start roof at the top of the main tower
   double topY = radius*sin(360) + centralY+.25;
  //Top
  double topRadius = radius+.08;
  for(double j=0.05; j<0.75 ;j=j+0.05){
     double angle = 0.1;
     topRadius = topRadius-.05;
     for (double i=0; i<360; i=i+5) {
         float x = topRadius*cos(i);
         float y = topRadius*sin(i);
         brick(x,j+topY*3.5,y,.05,.05,angle,45,texture[2]);
     }
     angle=angle+.1;
  }
    //wings
    glPushMatrix();
    glRotated(0, 0, 0, 1);
    glTranslated(0,2.5,0.65);
    // Enable Textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[3]); // Stone

  	for (int  i=0; i<4; i++) {
  		glRotated(90, 0, 0, 1);
  		glBegin(GL_POLYGON);
  		glVertex2f(0,0);
  		glVertex2f(0.5f, 0.2f);
  		glVertex2f(2.1f,0.2f);
      glVertex2f(2.1f,-0.2f);
  		glVertex2f(0.5f, -0.2f);
  		glEnd();
  	}
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
//creates a ring of bricks ,but it cuts out some of them depending on what angle you want to put in for the 'cut' variable
void fencedObstacles(double cut,int angle,double radius,double centralX,double centralY){
  glPushMatrix();
  glRotated(angle, 0, 1, 0);
  for (double i=0; i<360; i++) {
      float rad  = -3.14*i/cut;
      float x = radius*cos(rad) + centralX;
      float y = radius*sin(rad) + centralY;
      brick(x,0,y,.05,.05,.1,90,texture[3]);

  }
  glPopMatrix();
}
/*
 * This function is set as the glutTimerFunc to drive the animation
 */
void doFrame(int v) {
    frameNumber++;
    glutPostRedisplay();
    glutTimerFunc(30,doFrame,0);
}
//used for golf hole
void drawCircle(float x, float y, float radius)
{
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle


    //draw hole
     glPushMatrix();
     glRotatef(90, 1, 0, 0);
     glTranslated(0,0,-.05);
    //radius
    float twicePi = 5.0f * M_PI;
    glColor3f(0,0,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for(i = 0; i <= triangleAmount;i++)
    {
        glVertex2f(
                   x + (radius * cos(i *  twicePi / triangleAmount)),
                   y + (radius * sin(i * twicePi / triangleAmount)));

    }
    glEnd();

    glPopMatrix();

}

static void drawScene(){

  windmill(0.5,0.0,0.0,25);
  fencedObstacles(-3.14,0,4,0.0,0.0);
  fencedObstacles(270,50,3,0.0,0.0);
  fencedObstacles(270,120,2,0.0,0.0);
  // castle(0.5,3.0,3.0,10);


  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);


  // Draw Ground
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);
  glTexCoord2f(0.0,  0.0);   glVertex3f(-5,0,-5);
  glTexCoord2f(10.0,0.0);   glVertex3f(-5,0,5);
  glTexCoord2f(10.0,10.0); glVertex3f(5,0,5);
  glTexCoord2f(0.0,  10.0); glVertex3f(5,0,-5);
  glEnd();

   drawCircle(0,-1,.1);
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1,1,1);
        ball(Position[0],Position[1],Position[2] , 0.1);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
     glDisable(GL_LIGHTING);
   // Draw scene
   drawScene();

   //  no lighting from here on
   glDisable(GL_LIGHTING);

   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
     th,ph,dim,fov,mode?"Perspective":"Orthogonal",light?"On":"Off");
   if (light)
   {
      glWindowPos2i(5,45);
      Print("Model=%s LocalViewer=%s Distance=%d Elevation=%.1f",smooth?"Smooth":"Flat",local?"On":"Off",distance,ylight);
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shinyvec[0]);
   }

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   frameNumber=frameNumber+.7;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
   glutTimerFunc(30,doFrame,0);
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th -= 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th += 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;

   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Switch projection mode
   else if (ch == 'p' || ch == 'P')
      mode = 1-mode;
   //  Toggle light movement
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Translate shininess power to value (-1 => 0)
   shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(mode?fov:0,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Final Project: Zach Lamb");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("ground.bmp");
   texture[1] = LoadTexBMP("wall.bmp");
   texture[2] = LoadTexBMP("roof.bmp");
   texture[3] = LoadTexBMP("castle.bmp");
   texture[4] = LoadTexBMP("door.bmp");
   texture[5] = LoadTexBMP("window.bmp");
   texture[6] = LoadTexBMP("dark.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
