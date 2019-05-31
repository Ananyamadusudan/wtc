#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include "image_loader.h"
#include<math.h>
GLuint _texwall,texfront,texfire,texsky,texnight,texbn,texid;
GLfloat theta=0;
float fx,fy,fz;
float ny=0;
int menuid,num=2,nextframe=0,window;
int xcount=0;
int angle=0,angle2=0;
GLfloat xt=0,yt=0,zt=0,zt1=0,xs=0,ys=0,zs=0,xs1=0,ys1=0,zs1=0,difparam;
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0,2.0,-2.0,2.0,-10.0,10.0);
	Image* image=loadBMP("C://Users/Ananya/Downloads/texture.bmp");
	_texwall=loadTexture(image);
	image=loadBMP("E://opengl/Middle-view.bmp");
	texfront=loadTexture(image);
	image=loadBMP("C://Users/Ananya/Downloads/frf.bmp");
	texfire=loadTexture(image);
	image=loadBMP("E://opengl/Bangalore-Institute-of-Technology-3d-Model-master/sky.bmp");
	texsky=loadTexture(image);
	image=loadBMP("C://Users/Ananya/Downloads/nsky.bmp");
	texnight=loadTexture(image);
	image=loadBMP("C://Users/Ananya/Downloads/skyscraper14.bmp");
	texbn=loadTexture(image);
	delete image;
	gluLookAt(2.0,1.0,4.0,0.0,0.2,0.2,0.0,1.0,0.0);

}

void myresize(int w, int h){
	//double ar=(double)w/h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2,2,-6,6,1,125);
	glMatrixMode(GL_MODELVIEW);
}
void drawbuilding()
{

	const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	 const GLfloat light_diffuse[]={1.0,1.0,1.0,1.0};
		const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
		 glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
			    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
			    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
			    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			    glEnable(GL_TEXTURE_2D);
			    if(num==1)
			    	{texid=texbn;
			    	glColor3f(0.8,0.498039,0.196078);
			    	}
			    else texid=texfront;
			    glPushMatrix();
	        glBindTexture(GL_TEXTURE_2D,texid);
	        //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	       	        glBegin(GL_QUADS);
	        	glTexCoord2f(0.0,0.0); glVertex3f(-0.5+xs,-2+ys,0.1);
	        	glTexCoord2f(1.0,0.0); glVertex3f(0.0+xs,-2+ys,0.1);
	        	glTexCoord2f(1.0,1.0); glVertex3f(0.0+xs,2+ys,0.1);
	        	glTexCoord2f(0.0,1.0); glVertex3f(-0.5+xs,2+ys,0.1);
	        glEnd();
	        glPopMatrix();

	        //back face
	        glPushMatrix();
	        glBindTexture(GL_TEXTURE_2D,texid);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	        	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	        	       	        	        glBegin(GL_QUADS);
	        	        	glTexCoord2f(0.0,0.0); glVertex3f(-0.5+xs,-2+ys,-0.1);
	        	        	glTexCoord2f(1.0,0.0); glVertex3f(0.0+xs,-2+ys,-0.1);
	        	        	glTexCoord2f(1.0,1.0); glVertex3f(0.0+xs,2+ys,-0.1);
	        	        	glTexCoord2f(0.0,1.0); glVertex3f(-0.5+xs,2+ys,-0.1);
	        	        glEnd();
	        glPopMatrix();


	        glPushMatrix();
	        glBindTexture(GL_TEXTURE_2D,_texwall);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	        glBegin(GL_QUADS);
	        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0+xs, -2+ys, -0.1f);
	        			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f+xs,  2+ys, -0.1f);
	        			glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f+xs,  2+ys,  0.1f);
	        			glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f+xs, -2+ys,  0.1f);
	       	glEnd();
	       	glPopMatrix();



	        glPushMatrix();
	        glBindTexture(GL_TEXTURE_2D,_texwall);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	        glBegin(GL_QUADS);
	       		glTexCoord2f(0.0,0.0); glVertex3f(-0.5+xs,-2+ys,-0.1);
	       		glTexCoord2f(1.0,0.0); glVertex3f(-0.5+xs,-2+ys,0.1);
	       		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5+xs,2+ys,0.1);
	       		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5+xs,2+ys,-0.1);
	       	glEnd();
	       	glPopMatrix();



	       	glPushMatrix();
	        glBindTexture(GL_TEXTURE_2D,_texwall);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	       	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	       	glBegin(GL_QUADS);
	       		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5+xs,  2+ys, -0.1);
	       		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5+xs,  2+ys,  0.1);
	       		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0+xs,  2+ys,  0.1);
	       		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0+xs,  2+ys, -0.1);
	       	glEnd();
	       	glPopMatrix();

	       	glPushMatrix();
	        glBindTexture(GL_TEXTURE_2D,_texwall);
	      	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	      	       	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	      	       	glBegin(GL_QUADS);
	      	      glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5+xs, -2+ys, -0.1);
	      	      			glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0+xs, -2+ys, -0.1);
	      	      			glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0+xs, -2+ys,  0.1);
	      	      			glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5+xs, -2+ys,  0.1);
	      	      	glEnd();
	      	      glPopMatrix();
	      	    glDisable(GL_TEXTURE_2D);
}
void drawbuilding2()
{

	const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
		const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
		const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
		 glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
			    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
			    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
			    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			    if(num==1)
			    {    	texid=texbn;
			    	glColor3f(0.8,0.498039,0.196078);
			    }
			    			    else texid=texfront;
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		        glBindTexture(GL_TEXTURE_2D,texid);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		       	        glBegin(GL_QUADS);
		        	glTexCoord2f(0.0,0.0); glVertex3f(0.5,-2.0+ys1,0.1);
		        	glTexCoord2f(1.0,0.0); glVertex3f(1.0,-2.0+ys1,0.1);
		        	glTexCoord2f(1.0,1.0); glVertex3f(1.0,2.0+ys1,0.1);
		        	glTexCoord2f(0.0,1.0); glVertex3f(0.5,2+ys1,0.1);
		        glEnd();
		        glPopMatrix();

		        glPushMatrix();
		        glBindTexture(GL_TEXTURE_2D,texid);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		        	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		        	       	        	        glBegin(GL_QUADS);
		        	        	glTexCoord2f(0.0,0.0); glVertex3f(0.5,-2+ys1,-0.1);
		        	        	glTexCoord2f(1.0,0.0); glVertex3f(1.0,-2+ys1,-0.1);
		        	        	glTexCoord2f(1.0,1.0); glVertex3f(1.0,2+ys1,-0.1);
		        	        	glTexCoord2f(0.0,1.0); glVertex3f(0.5,2+ys1,-0.1);
		        	        glEnd();
		        glPopMatrix();



		        glPushMatrix();
		        glBindTexture(GL_TEXTURE_2D,_texwall);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		        glBegin(GL_QUADS);
		        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -2+ys1, -0.1f);
		        			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  2+ys1, -0.1f);
		        			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  2+ys1,  0.1f);
		        			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -2+ys1,  0.1f);
		       	glEnd();
		       	glPopMatrix();



		        glPushMatrix();
		        glBindTexture(GL_TEXTURE_2D,_texwall);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		        glBegin(GL_QUADS);
		       		glTexCoord2f(0.0,0.0); glVertex3f(0.5,-2+ys1,-0.1);
		       		glTexCoord2f(1.0,0.0); glVertex3f(0.5,-2+ys1,0.1);
		       		glTexCoord2f(1.0, 1.0); glVertex3f(0.5,2+ys1,0.1);
		       		glTexCoord2f(0.0, 1.0); glVertex3f(0.5,2+ys1,-0.1);
		       	glEnd();
		       	glPopMatrix();



		       	glPushMatrix();
		        glBindTexture(GL_TEXTURE_2D,_texwall);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		       	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		       	glBegin(GL_QUADS);
		       		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5,  2+ys1, -0.1);
		       		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5,  2+ys1,  0.1);
		       		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0,  2+ys1,  0.1);
		       		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0,  2+ys1, -0.1);
		       	glEnd();
		       	glPopMatrix();


		       	glPushMatrix();
		        glBindTexture(GL_TEXTURE_2D,_texwall);
		      	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		      	       	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		      	       	glBegin(GL_QUADS);
		      	      glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, -2+ys1, -0.1);
		      	      			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0, -2+ys1, -0.1);
		      	      			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0, -2+ys1,  0.1);
		      	      			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5, -2+ys1,  0.1);
		      	      	glEnd();
		      	      glPopMatrix();
		      	    glDisable(GL_TEXTURE_2D);
}

void drawplane()
{
	const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
			const GLfloat light_diffuse[]  = { 0.8f, 0.8f, 0.8f, 1.0f };
			const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
			 glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
				    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
				    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
				    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
		    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
		    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
		    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glColor3d(1.0,1.0,1.0);
		    glPushMatrix();
		        glTranslated(-1.7+xt,1.5+yt+ny,0+zt);
		        glScaled(2,0.4,0.5);
		        glutSolidSphere(0.25,30,30);
		    glPopMatrix();

		    glColor3d(0,0,0);
		    	    glPushMatrix();
		    	        glTranslated(-1.4+xt,1.55+yt+ny,0+zt);
		    	        glScaled(1.5,0.7,0.8);
		    	        glRotated(40,0,1,0);
		    	        glutSolidSphere(0.1,30,30);
		    	    glPopMatrix();

		    	    glColor3d(0.0,0.0,0.0);
		    	    glPushMatrix();
		    	    glTranslated(-1.2+xt,1.5+yt+ny,0+zt);
		    	    glScaled(0.1,0.3,0.1);
		    	    glutSolidSphere(0.1,30,30);
		    	    glPopMatrix();

		    	    			    	    	 glColor3d(0.3,0.3,0.3);
		    	   		    	   		 glPushMatrix();
		    	   		    	   		 glTranslated(-1.2+xt,1.4+yt+ny,0);
		    	   		    	   		glScaled(0.05,1.2,0.1);
		    	   		    	   	glTranslated(-1.2+xt,0.1,0);
		    	   		    	   	glRotated(angle2,1,0,0);
		    	   		    	   	angle2+=10;
		    	   		    	   	if(angle2>360)
		    	   		    	   			   angle2-=360;
		    	   		    	   		glTranslated(-(-1.2+xt),-(0.1),0);
		    	   		    	   		glutSolidSphere(0.1,30,30);
		    	   		    	   		glPopMatrix();
		    	   		    	   		glutPostRedisplay();

		    	    glColor3d(0.5,0.5,0.5);
		    	   	    glPushMatrix();
		    	   	        glTranslated(-1.2+xt,1.65+yt+ny,1.2+zt+zt1);
		    	   	        glRotated(-20,0,1,0);
		    	   	        glScaled(0.7,0.1,2);
		    	   	        glRotated(25,0,1,0);
		    	   	        glRotated(10,0,0,1);
		    	   	        glutSolidCube(0.3);
		    	   	    glPopMatrix();
		    	   	 glColor3d(0.8,0.8,0.8);
		    	   		    glPushMatrix();
		    	   		        glTranslated(-1.25+xt,1.6+yt+ny,1.15+zt+zt1);
		    	   		        glRotated(70,0,1,0);
		    	   		        glScaled(0.1,0.1,0.9);
		    	   		        glutSolidTorus(0.2,0.2,50,50);
		    	   		    glPopMatrix();

		    	   		 glColor3d(0.8,0.8,0.8);
		    	   		 	    glPushMatrix();
		    	   		 	        glTranslated(-1.35+xt,1.57+yt+ny,0.9+zt+zt1);
		    	   		 	        glRotated(90,0,1,0);
		    	   		 	    glScaled(0.1,0.1,0.9);
		    	   		 	   	        glutSolidTorus(0.2,0.2,50,50);
		    	   		 	   	    glPopMatrix();

		    	   		 	    glColor3d(0.5,0.5,0.5);
		    	   		 	   	    glPushMatrix();
		    	   		 	   	        glTranslated(-2.3+xt,1.35+yt+ny,-1.2+zt);
		    	   		 	   	        glRotated(20,1,0,0);
		    	   		 	   	        glScaled(0.7,0.1,1.5);
		    	   		 	   	        glRotated(45,0,1,0);
		    	   		 	   	        glutSolidCube(0.3);
		    	   		 	   	    glPopMatrix();

		    	   		 	    glColor3d(0.5,0.5,0.5);
		    	   		 	   	        glPushMatrix();
		    	   		 	   	            glTranslated(-1.4+xt,1.8+yt+ny,1.5+zt+zt1);
		    	   		 	   	            glRotated(-30,0,1,0);
		    	   		 	   	            glScaled(0.7,0.1,1);
		    	   		 	   	            glRotated(10,0,1,0);
		    	   		 	   	            glutSolidCube(0.2);
		    	   		 	   	        glPopMatrix();

		    	   		 	   	 glColor3d(0.5,0.5,0.5);
		    	   		 	   	 	        glPushMatrix();
		    	   		 	   	 	            glTranslated(-2.9+xt,1.25+yt+ny,-1.5+zt);
		    	   		 	   	 	            glRotated(50,0,1,0);
		    	   		 	   	 	            glScaled(0.7,0.1,1);
		    	   		 	   	 	            glRotated(-10,0,1,0);
		    	   		 	   	 	            glutSolidCube(0.2);
		    	   		 	   	 	        glPopMatrix();

		    	   		 	   	 glColor3d(0.5,0.5,0.5);
		    	   		 	   	 	    glPushMatrix();
		    	   		 	   	 	        glTranslated(-2.05+xt,1.65+yt+ny,0.3+zt);
		    	   		 	   	 	        glRotated(30,1,0,0);
		    	   		 	   	 	        glScaled(0.8,2,0.1);
		    	   		 	   	 	        glutSolidCube(0.1);
		    	   		 	   	 	    glPopMatrix();

}
void drawfire()
{
	const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
				const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
				const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
				 glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
					    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
					    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
					    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
					    glEnable(GL_TEXTURE_2D);
					    glPushMatrix();
					    glBindTexture(GL_TEXTURE_2D,texfire);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	const float partof1=0.6f;
	glColor4f(1.0,1.0,1.0,partof1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex3f(-0.5,1.5,0.1);
	glTexCoord2f(0.0,1.0);glVertex3f(-0.5,2.3,0.1);
	glTexCoord2f(1.0,1.0);glVertex3f(0.0,2.3,0.1);
	glTexCoord2f(1.0,0.0);glVertex3f(0.0,1.5,0.1);

	glTexCoord2f(0.0,0.0);glVertex3f(0.0,1.5,0.1);
	glTexCoord2f(0.0,1.0);glVertex3f(0.0,2.0,0.1);
	glTexCoord2f(1.0,1.0);glVertex3f(0.0,2.0,-0.1);
	glTexCoord2f(1.0,0.0);glVertex3f(0.0,1.5,-0.1);

	glTexCoord2f(0.0,0.0);glVertex3f(-0.5,1.5,0.1);
	glTexCoord2f(0.0,1.0);glVertex3f(-0.5,2.3,0.1);
	glTexCoord2f(1.0,1.0);glVertex3f(-0.5,2.3,-0.1);
	glTexCoord2f(1.0,0.0);glVertex3f(-0.5,1.5,-0.1);

	glTexCoord2f(0.0,0.0);glVertex3f(-0.5,1.5,-0.1);
	glTexCoord2f(0.0,1.0);glVertex3f(-0.5,2.3,-0.1);
	glTexCoord2f(1.0,1.0);glVertex3f(0.0,2.3,-0.1);
	glTexCoord2f(1.0,0.0);glVertex3f(0.0,1.5,-0.1);
    glEnd();
    glDisable(GL_BLEND);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawfire2()
{
	const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
					const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
					const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
					const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
					 glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
						    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
						    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
						    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
						    glEnable(GL_TEXTURE_2D);
						    glPushMatrix();
						    glBindTexture(GL_TEXTURE_2D,texfire);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			const float partof1=0.6f;
			glColor4f(1.0,1.0,1.0,partof1);
	    glBegin(GL_POLYGON);
	    glTexCoord2f(0.0,0.0);glVertex3f(0.5,1.5,0.1);
	    glTexCoord2f(0.0,1.0);glVertex3f(0.5,2.4,0.1);
	    glTexCoord2f(1.0,1.0);glVertex3f(1.0,2.4,0.1);
	    glTexCoord2f(1.0,0.0);glVertex3f(1.0,1.5,0.1);

	    glTexCoord2f(0.0,0.0);glVertex3f(1.0,1.5,0.1);
	    glTexCoord2f(0.0,1.0);glVertex3f(1.0,2.4,0.1);
	    glTexCoord2f(1.0,1.0);glVertex3f(1.0,2.4,-0.1);
	    glTexCoord2f(1.0,0.0);glVertex3f(1.0,1.5,-0.1);

	    glTexCoord2f(0.0,0.0);glVertex3f(0.5,1.5,-0.1);
	    glTexCoord2f(0.0,1.0);glVertex3f(0.5,2.4,-0.1);
	    glTexCoord2f(1.0,1.0);glVertex3f(1.0,2.4,-0.1);
	    glTexCoord2f(1.0,0.0);glVertex3f(1.0,1.5,-0.1);
	    glEnd();
	    glPopMatrix();
	    glDisable(GL_TEXTURE_2D);
	    glDisable(GL_BLEND);
}
void drawmoon()
{
	const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
							const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
							const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
							const GLfloat light_position[] = { 0.7f, 0.5f, 3.0f, 0.0f };
							 glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
								    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
								    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
								    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
								    glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,1.5);
								    glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.75);
								    glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.4);
								    GLUquadricObj *dis;
								    glPushMatrix();
								    		dis=gluNewQuadric();
								    						glColor3f(1.0,1.0,1.0);
								    						glTranslated(-1.5,1.9,0.5);
								    						gluDisk(dis,0,0.1,64,1);
								    glPopMatrix();
}
void drawnightsky()
{

	const GLfloat light_ambient[]  = { 0.0f, 0.0f, 1.0f, 1.0f };
			const GLfloat light_diffuse[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
			const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
			 glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
				    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
				    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
				    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D,texnight);
									    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
									    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);glVertex3f(-3.5,-2.5,-2.0);
				glTexCoord2f(1.0,0.0);glVertex3f(2.9,-2.5,-2.0);
				glTexCoord2f(1.0,1.0);glVertex3f(2.9,2.3,-2.0);
				glTexCoord2f(0.0,1.0);glVertex3f(-3.5,2.3,-2.0);
				glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

}
void drawsky()
{

	const GLfloat light_ambient[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
					const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
					const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
					const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
					 glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
						    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
						    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
						    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_TEXTURE_2D);
			glPushMatrix();
	 glBindTexture(GL_TEXTURE_2D,texsky);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);glVertex3f(-3.5,-2.5,-2.0);
		glTexCoord2f(1.0,0.0);glVertex3f(2.9,-2.5,-2.0);
		glTexCoord2f(1.0,1.0);glVertex3f(2.9,2.3,-2.0);
		glTexCoord2f(0.0,1.0);glVertex3f(-3.5,2.3,-2.0);
		glEnd();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(num==1)
		{drawnightsky();
		drawmoon();
		drawbuilding();
			drawbuilding2();
	}
	else if(num==2)
		{
		drawsky();

	drawbuilding();
	drawbuilding2();
	drawplane();
	if(xcount==7)
		drawfire();
	if(xcount>7)
	{
		ys=-2.4;}

	if(xcount==17)
		drawfire2();
	if(xcount>17)
		ys1=-2.5;}
	glFlush();
	glutSwapBuffers();
}
void keys(unsigned char k,int x,int y)
{

	if(k=='r')

	{
		xt+=0.1;
		xcount++;
	}

	if(k=='u')
		yt+=0.1;
	if(k=='d')
		yt-=0.1;

	if(k=='e')
		exit(0);
	display();
}
void menu(int value)
{
	num=value;
	if(num==1)
		ny=-0.5;
	if(num==2)
		ny=0;
	display();
}
void bitmap_output(float x, float y, float z,const char* string, void *font){
  int len, i;
  glRasterPos3f(x, y, z);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

void front(){
    glClearColor(0.9, 0.9, 0.9, 1.0);
	glColor3f(0.0,0.0,0.5);
	bitmap_output(-1.0, 1.75, 0, "BANGALORE INSTITUTE OF TECHNOLOGY",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-1.3, 1.5, 0, "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-1.1, 1.3, 0, "COMPUTER GRAPHICS AND VISUALIZATION(15CSL68) ",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-.5, 1.1, 0, "MINI PROJECT",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-0.9, .8, 0, "ATTACK ON WORLD TRADE CENTER",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-1.8, 0.1, 0, "SUBMITTED BY-",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-2.0, -.2, 0,"NAME- ANANYA B M",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-2.0, -.4, 0,"USN- 1BI16CS012",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(1.1, 0.0, 0,"NAME- AKSHAY KUMAR K",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(1.1, -.2, 0,"USN- 1BI16CS009",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.5,0.0,0.5);
	bitmap_output(-1.8, -0.6, 0, "Under the guidance of",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(-2.0, -0.8, 0, "Dr.Kempanna M",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(1.1, -0.5, 0, "Prof Mahalakshmi C V",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1.0,0.0,0.0);
	glColor3f(0.0,0.5,0.0);
	bitmap_output(1.3, -.9, 0, "Press Enter to continue.......",GLUT_BITMAP_HELVETICA_18);
}
void keypress(unsigned char key, int x, int y){
    if(key == 13){
        glutDestroyWindow(window);
    }
}
void display1(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    front();
    glutSwapBuffers();
}
void initfront(void){
		glClearColor(1.0,1.0,1.0,1.0);
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(-100,500.0,-100,500.0);
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutCreateWindow("cube");
	init();
	glutFullScreen();
	glutDisplayFunc(display);
	//glutReshapeFunc(myresize);
	glutKeyboardFunc(keys);
	menuid=glutCreateMenu(menu);
	glutAddMenuEntry("night",1);
	glutAddMenuEntry("day",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glEnable(GL_DEPTH_TEST);
	 glEnable(GL_LIGHT0);
	    glEnable(GL_NORMALIZE);
	    glEnable(GL_COLOR_MATERIAL);
	    glEnable(GL_LIGHTING);
	    //glutInitWindowSize(1960,1280);
	 window=glutCreateWindow("first page");
	  glutFullScreen();
	  glutDisplayFunc(display1);
	  glutKeyboardFunc(keypress);
	  init();
	glutMainLoop();
	return 0;
}
