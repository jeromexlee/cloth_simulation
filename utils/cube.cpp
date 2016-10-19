#include "OpenGL/gl.h"
#include "cube.h"

static GLfloat vertices[][3] = { {1.0f, 1.0f, 1.0f},  {-1.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f},
			  {1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f},
                          {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}
                        };

static GLfloat normals[][3] = { {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f},
			 {1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
			 {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}
			};

void Cube::polygon(int a, int b, int c, int d, int facenum)
{
  glPushMatrix();

  glTranslated(trans_.val[0], trans_.val[1], trans_.val[2]);
  glRotated(rotAngle_, rotAxis_.val[0], rotAxis_.val[1], rotAxis_.val[2]);
  glScaled(scale_.val[0], scale_.val[1], scale_.val[2]);

  glBegin(GL_POLYGON);
    glNormal3fv(normals[facenum]);
    glVertex3fv(vertices[a]);

    glNormal3fv(normals[facenum]);
    glVertex3fv(vertices[b]);

    glNormal3fv(normals[facenum]);
    glVertex3fv(vertices[c]);

    glNormal3fv(normals[facenum]);
    glVertex3fv(vertices[d]);
  glEnd();

  glPopMatrix();
}

void Cube::draw()
{
  polygon(0,1,2,3,0);
  polygon(5,4,7,6,1);
  polygon(4,0,3,7,2);
  polygon(1,5,6,2,3);
  polygon(1,0,4,5,4);
  polygon(3,2,6,7,5);
}
