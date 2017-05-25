// $Id: graphics.cpp,v 1.11 2014-05-15 16:42:55-07 - - $

#include <iostream>
using namespace std;

#include <GL/freeglut.h>

#include "graphics.h"
#include "util.h"

int window::width = 640; // in pixels
int window::height = 480; // in pixels
int window::border_width = 4;
string window::border_color = "red";
vector<object> window::objects;
size_t window::selected_obj = 0;
bool window::selected = false;
int window::delta = 4;
mouse window::mus;

object::object (const shared_ptr<shape>& sha, vertex& cen, 
        rgbcolor& col) : pshape(sha), center(cen), color(col) {
}

void object::move(GLfloat delta_x, GLfloat delta_y) {
    GLfloat x = delta_x + center.xpos;
    GLfloat y = delta_y + center.ypos;
    if (x < 0)
        x += window::get_width();
    else if (x > window::get_width())
        x -= window::get_width();

    if (y < 0)
        y += window::get_height();
    else if (y > window::get_height())
        y -= window::get_height();

    center.xpos = x;
    center.ypos = y;
}

// Executed when window system signals to shut down.
void window::close() {
   DEBUGF ('g', sys_info::execname() << ": exit ("
           << sys_info::exit_status() << ")");
   exit (sys_info::exit_status());
}

// Executed when mouse enters or leaves window.
void window::entry (int mouse_entered) {
   DEBUGF ('g', "mouse_entered=" << mouse_entered);
   window::mus.entered = mouse_entered;
   if (window::mus.entered == GLUT_ENTERED) {
      DEBUGF ('g', sys_info::execname() << ": width=" << window::width
           << ", height=" << window::height);
   }
   glutPostRedisplay();
}

// Called to display the objects in the window.
void window::display() {
   glClear (GL_COLOR_BUFFER_BIT);
   for (size_t i = 0; i < window::objects.size(); i++) {
       if (i == window::selected_obj) 
           window::selected = true;
       objects.at(i).draw();
       if (i < 13) {
           int w = glutBitmapWidth(GLUT_BITMAP_8_BY_13, 'c'); 
           if (i > 9) w *= 2;
           vertex center = objects.at(i).get_center();
           glEnable(GL_COLOR_LOGIC_OP);
           glLogicOp(GL_XOR);
           //glColor3ubv(rgbcolor("white").ubvec);
           glRasterPos2f(center.xpos - w/2, center.ypos - 4);
           glutBitmapString(GLUT_BITMAP_8_BY_13, 
        reinterpret_cast<const unsigned char*>(to_string(i).c_str()));
           glDisable(GL_COLOR_LOGIC_OP);
       }
       window::selected = false;
   }
   mus.draw();
   glutSwapBuffers();
}

// Called when window is opened and when resized.
void window::reshape (int width, int height) {
   DEBUGF ('g', "width=" << width << ", height=" << height);
   window::width = width;
   window::height = height;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (0, window::width, 0, window::height);
   glMatrixMode (GL_MODELVIEW);
   glViewport (0, 0, window::width, window::height);
   glClearColor (0.25, 0.25, 0.25, 1.0);
   glutPostRedisplay();
}

// Executed when a regular keyboard key is pressed.
enum {BS=8, TAB=9, ESC=27, SPACE=32, DEL=127};
void window::keyboard (GLubyte key, int x, int y) {
   DEBUGF ('g', "key=" << (unsigned)key << ", x=" << x << ", y=" << y);
   window::mus.set (x, y);
   switch (key) {
      case 'Q': case 'q': case ESC:
         window::close();
         break;
      case 'H': case 'h':
         window::move_selected_object(-1, 0);
         break;
      case 'J': case 'j':
         window::move_selected_object(0, -1);
         break;
      case 'K': case 'k':
         window::move_selected_object(0, 1);
         break;
      case 'L': case 'l':
         window::move_selected_object(1, 0);
         break;
      case 'N': case 'n': case SPACE: case TAB:
         next_object();
         break;
      case 'P': case 'p': case BS:
         prev_object();
         break;
      case '0'...'9':
         select_object (key - '0');
         break;
      default:
         cerr << (unsigned)key << ": invalid keystroke" << endl;
         break;
   }
   glutPostRedisplay();
}


// Executed when a special function key is pressed.
void window::special (int key, int x, int y) {
   DEBUGF ('g', "key=" << key << ", x=" << x << ", y=" << y);
   window::mus.set (x, y);
   switch (key) {
      case GLUT_KEY_LEFT: move_selected_object (-1, 0); break;
         break;
      case GLUT_KEY_DOWN: move_selected_object (0, -1); break;
         break;
      case GLUT_KEY_UP: move_selected_object (0, +1); break;
      case GLUT_KEY_RIGHT: move_selected_object (+1, 0); break;
      case GLUT_KEY_F1: select_object (1); break;
      case GLUT_KEY_F2: select_object (2); break;
      case GLUT_KEY_F3: select_object (3); break;
      case GLUT_KEY_F4: select_object (4); break;
      case GLUT_KEY_F5: select_object (5); break;
      case GLUT_KEY_F6: select_object (6); break;
      case GLUT_KEY_F7: select_object (7); break;
      case GLUT_KEY_F8: select_object (8); break;
      case GLUT_KEY_F9: select_object (9); break;
      case GLUT_KEY_F10: select_object (10); break;
      case GLUT_KEY_F11: select_object (11); break;
      case GLUT_KEY_F12: select_object (12); break;
      default:
         cerr << (unsigned)key << ": invalid function key" << endl;
         break;
   }
   glutPostRedisplay();
}


void window::motion (int x, int y) {
   DEBUGF ('g', "x=" << x << ", y=" << y);
   window::mus.set (x, y);
   glutPostRedisplay();
}

void window::passivemotion (int x, int y) {
   DEBUGF ('g', "x=" << x << ", y=" << y);
   window::mus.set (x, y);
   glutPostRedisplay();
}

void window::mousefn (int button, int state, int x, int y) {
   DEBUGF ('g', "button=" << button << ", state=" << state
           << ", x=" << x << ", y=" << y);
   window::mus.state (button, state);
   window::mus.set (x, y);
   glutPostRedisplay();
}

void window::move_selected_object(int xdir, int ydir) {
    if (objects.size() > 0) {
        objects.at(selected_obj).move(xdir * window::delta,
                                      ydir * window::delta);
    }
}

void window::next_object() {
    if (window::selected_obj == window::objects.size() - 1)
        selected_obj = 0;
    else
        window::selected_obj = window::selected_obj + 1;
}

void window::prev_object() {
    if (window::selected_obj == 0)
        selected_obj = window::objects.size() - 1;
    else
        window::selected_obj = window::selected_obj - 1;
}

void window::select_object(size_t obj) {
    if (obj <  window::objects.size())
        window::selected_obj = obj;
}

void window::main () {
   static int argc = 0;
   glutInit (&argc, nullptr);
   glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize (window::width, window::height);
   glutInitWindowPosition (128, 128);
   glutCreateWindow (sys_info::execname().c_str());
   glutCloseFunc (window::close);
   glutEntryFunc (window::entry);
   glutDisplayFunc (window::display);
   glutReshapeFunc (window::reshape);
   glutKeyboardFunc (window::keyboard);
   glutSpecialFunc (window::special);
   glutMotionFunc (window::motion);
   glutPassiveMotionFunc (window::passivemotion);
   glutMouseFunc (window::mousefn);
   DEBUGF ('g', "Calling glutMainLoop()");
   glutMainLoop();
}


void mouse::state (int button, int state) {
   switch (button) {
      case GLUT_LEFT_BUTTON: left_state = state; break;
      case GLUT_MIDDLE_BUTTON: middle_state = state; break;
      case GLUT_RIGHT_BUTTON: right_state = state; break;
   }
}

void mouse::draw() {
   static rgbcolor color ("green");
   ostringstream text;
   text << "(" << xpos << "," << window::height - ypos << ")";
   if (left_state == GLUT_DOWN) text << "L"; 
   if (middle_state == GLUT_DOWN) text << "M"; 
   if (right_state == GLUT_DOWN) text << "R"; 
   if (entered == GLUT_ENTERED) {
      void* font = GLUT_BITMAP_HELVETICA_18;
      glColor3ubv (color.ubvec);
      glRasterPos2i (10, 10);
      glutBitmapString (font, (GLubyte*) text.str().c_str());
   }
}

