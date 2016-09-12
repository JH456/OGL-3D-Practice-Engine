#include "shaped3d.cpp"

void MyKeyboardFunc(unsigned char key, int x, int y);
//void MySpecialFunc(int key, int x, int y);
void MyUpFunc(unsigned char key, int x, int y);
//void MySpecialUpFunc(int key, int x, int y);
void paintAgain(int i);
void display();
void drawPolygon(polygon* poly);

polygon* square;
polygon* square2;

/* Initialize OpenGL Graphics */
void initGL() {
   glutCreateWindow("Vertex, Primitive & Color");
   glutInitWindowSize(320, 320);
   glutInitWindowPosition(50, 50);
   glutDisplayFunc(display);
   glutIgnoreKeyRepeat(1);
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glutKeyboardFunc(MyKeyboardFunc);
   //glutSpecialFunc(MySpecialFunc);
   glutKeyboardUpFunc(MyUpFunc);
   //glutSpecialUpFunc(MySpecialUpFunc);
   //glutIdleFunc(update) // IMPLEMENT THIS ONCE WE ARE NETWORKING
}

void MyKeyboardFunc(unsigned char key, int x, int y)
{
   switch(key) {
      case 'w':
      vertical += 1.0f;
      break;
      case 's':
      vertical -= 1.0f;
      break;
      case 'a':
      thetaVel += -rotVel;
      break;
      case 'd':
      thetaVel += rotVel;
      break;
      case 'q':
      horizontal -= 1.0f;
      break;
      case 'e':
      horizontal += 1.0f;
      break;
   };
}

void MyUpFunc(unsigned char key, int x, int y) {
   switch(key) {
      case 'w':
      vertical -= 1.0f;
      break;
      case 's':
      vertical += 1.0f;
      break;
      case 'a':
      thetaVel -= -rotVel;
      break;
      case 'd':
      thetaVel -= rotVel;
      break;
      case 'q':
      horizontal += 1.0f;
      break;
      case 'e':
      horizontal -= 1.0f;
      break;
   };
}

void paintAgain(int i) {
   glutPostRedisplay();
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   // Clear the color buffer with current clearing color
   glClear(GL_COLOR_BUFFER_BIT);

   //Move these to some other thread once we get networking
   if (vertical != 0 || horizontal != 0) {
      float movementAngle = horizontal == 0
            ? vertical >= 0
               ? 0
               : PI
            : atan(vertical / horizontal);
      if (horizontal > 0) movementAngle = (PI / 2.0f) - movementAngle;
      else if (horizontal < 0) movementAngle = (3.0f * PI / 2.0f) - movementAngle;
      movementAngle += theta;
      screeny += vel * sin(movementAngle);
      screenx += vel * cos(movementAngle);
   }
   theta += thetaVel;
   if (theta < 0) {
      theta += (PI * 2.0);
   }
   theta = std::fmod(theta, 2.0 * PI);

   drawPolygon(square);
   drawPolygon(square2);

   // Render now
   glFlush();
   glutTimerFunc(1000.0 / 60.0, paintAgain, 0);
}
