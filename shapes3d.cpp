#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <cmath>

const float vel = .1f;
const float rotVel = .01f;
const float PI = 3.14159f;
float screenx = 0.0f;
float screenz = 0.0f;
float screeny = 0.0f;
float d = -2.0f;
float theta = 1.57f;
float xVel = 0.0f;
float yVel = 0.0f;
float zVel = 0.0f;
float thetaVel = 0.0f;
float vertical = 0.0f;
float horizontal = 0.0f;

struct vertex;
struct polygon;

struct vertex {
   float v_x;
   float v_y;
   float v_z;
   vertex* v_next = NULL;
};

struct polygon {
   float p_red;
   float p_green;
   float p_blue;
   int p_numVertices;
   vertex* p_vertexRoot;
};

void addVertex(polygon* poly, float x, float y, float z) {
   if (poly->p_vertexRoot == NULL) {
      poly->p_vertexRoot = new vertex;
      poly->p_vertexRoot->v_x = x;
      poly->p_vertexRoot->v_y = y;
      poly->p_vertexRoot->v_z = z;
   } else {
      vertex* lastVertex = poly->p_vertexRoot;
      while (lastVertex->v_next != NULL) {
         lastVertex = lastVertex->v_next;
      }
      lastVertex->v_next = new vertex;
      lastVertex = lastVertex->v_next;
      lastVertex->v_x = x;
      lastVertex->v_y = y;
      lastVertex->v_z = z;
   }
   poly->p_numVertices++;
}

void polygonColor(polygon* poly, float red, float green, float blue) {
   poly->p_red = red;
   poly->p_green = green;
   poly->p_blue = blue;
}

void drawPolygon(polygon* poly) {
   vertex* currentVertex = poly->p_vertexRoot;
   glBegin(GL_POLYGON);
   glColor3f(poly->p_red, poly->p_green, poly->p_blue);
   while (currentVertex != NULL) {
      float deltaX = currentVertex->v_x - screenx;
      float deltaY = currentVertex->v_y - screeny;
      float deltaZ = currentVertex->v_z - screenz;
      float phi = deltaY == 0
            ? deltaX >= 0
               ? 0
               : PI
            : atan(deltaX / deltaY);

      if (deltaY > 0) phi = (PI / 2.0f) - phi;
      else if (deltaY < 0) phi = (3.0f * PI / 2.0f) - phi;
      // phi is the vertex's angle to the camera coords (lower left hand corner)
      float angle = phi - theta;
      if ((theta >= phi && (angle >= -PI / 2.0f || angle <= -3.0f * PI / 2.0f)) || (theta < phi && (angle <= PI
          / 2.0f || angle >= 3.0f * PI / 2.0f))) {
         float deltaX2 = sqrt((deltaX * deltaX) + (deltaY * deltaY)) * cos((PI / 2.0f) + theta - phi);
         float deltaY2 = sqrt((deltaX * deltaX) + (deltaY * deltaY)) * sin((PI / 2.0f) + theta - phi);
         glVertex2f(d * deltaX2 / (d - deltaY2), d * deltaZ / (d - deltaY2));
      }
      std::cout<< "PHI " << phi << " THETA " << theta << std::endl;
      currentVertex = currentVertex->v_next;
   }
   glEnd();
}

void listVertices(polygon* poly) {
   vertex* currentVertex = poly->p_vertexRoot;
   while (currentVertex != NULL) {
      std::cout << currentVertex->v_x << " " << currentVertex->v_y << " " << currentVertex->v_z << " " << std::endl;
      currentVertex = currentVertex->v_next;
   }
}

void destroyVertex(vertex* vert) {
   if (vert->v_next != NULL) destroyVertex(vert->v_next);
   delete vert;
}

void destroyPolygon(polygon* poly) {
   if (poly->p_vertexRoot != NULL) destroyVertex(poly->p_vertexRoot);
   delete poly;
}
