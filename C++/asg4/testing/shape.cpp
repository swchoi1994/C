// $Id: shape.cpp,v 1.7 2014-05-08 18:32:56-07 - - $

#include <typeinfo>
#include <unordered_map>
using namespace std;

#include "shape.h"
#include "graphics.h"
#include "util.h"

static unordered_map<void*,string> fontname {
   {GLUT_BITMAP_8_BY_13       , "Fixed-8x13"    },
   {GLUT_BITMAP_9_BY_15       , "Fixed-9x15"    },
   {GLUT_BITMAP_HELVETICA_10  , "Helvetica-10"  },
   {GLUT_BITMAP_HELVETICA_12  , "Helvetica-12"  },
   {GLUT_BITMAP_HELVETICA_18  , "Helvetica-18"  },
   {GLUT_BITMAP_TIMES_ROMAN_10, "Times-Roman-10"},
   {GLUT_BITMAP_TIMES_ROMAN_24, "Times-Roman-24"},
};

ostream& operator<< (ostream& out, const vertex& where) {
   out << "(" << where.xpos << "," << where.ypos << ")";
   return out;
}

shape::shape() {
   DEBUGF ('c', this);
}

text::text (void* glut_bitmap_font, const string& textdata):
      glut_bitmap_font(glut_bitmap_font), textdata(textdata) {
   DEBUGF ('c', this);
}

ellipse::ellipse (GLfloat width, GLfloat height):
dimension ({width, height}) {
   DEBUGF ('c', this);
}

circle::circle (GLfloat diameter): ellipse (diameter, diameter) {
   DEBUGF ('c', this);
}

polygon::polygon (const vertex_list& vertices): vertices(vertices) {
   DEBUGF ('c', this);
}

rectangle::rectangle (GLfloat width, GLfloat height):
            polygon({{0, 0}, {width, 0}, 
                     {width, height}, {0, height}}) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

square::square (GLfloat width): rectangle (width, width) {
   DEBUGF ('c', this);
}

diamond::diamond (const GLfloat width, const GLfloat height):
            polygon({{0, 0}, {-width / 2, height / 2},
                     {0, height}, {width / 2, height / 2}}) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

triangle::triangle (const vertex_list& vertices): polygon(vertices) {
   DEBUGF ('c', this);
}

right_triangle::right_triangle (const GLfloat width, 
                                const GLfloat height):
    triangle({{0,0}, {0, height}, {width, 0}}) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

isosceles::isosceles (const GLfloat width, const GLfloat height):
    triangle({{-width/2,0}, {width/2, 0}, {0, height}}) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

equilateral::equilateral (const GLfloat width):
    isosceles(width, sqrt(3) * width / 2) {
   DEBUGF ('c', this << "(" << width << ")");
}


void text::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   rgbcolor textcolor;
   if (window::selected == true)
       textcolor = rgbcolor(window::border_color);
   else
       textcolor = color;
   glColor3ubv(textcolor.ubvec);
   glRasterPos2f(center.xpos, center.ypos);
   glutBitmapString(glut_bitmap_font, 
           reinterpret_cast<const unsigned char*>(textdata.c_str())); 
}

void ellipse::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   DEBUGF ('d', "dimension: " << dimension);
   // dimension has the width and height GLfloats
   // center has the position GLfloats
   glBegin(GL_POLYGON);
   glEnable (GL_LINE_SMOOTH);
   glColor3ubv(color.ubvec);
   const float delta = 2 * M_PI / 32;
   for (float theta = 0; theta < 2 * M_PI; theta += delta) {
       float xpos = dimension.xpos/2 * cos(theta) + center.xpos;
       float ypos = dimension.ypos/2 * sin(theta) + center.ypos;
       glVertex2f(xpos, ypos);
   }
   glEnd();

   if (window::selected == true) {
       glLineWidth(window::border_width);
       glBegin (GL_LINE_LOOP);
       glEnable (GL_LINE_SMOOTH);
       glColor3ubv(rgbcolor(window::border_color).ubvec);
       const float delta = 2 * M_PI / 32;
       for (float theta = 0; theta < 2 * M_PI; theta += delta) {
           float xpos = dimension.xpos/2 * cos(theta) + center.xpos;
           float ypos = dimension.ypos/2 * sin(theta) + center.ypos;
           glVertex2f(xpos, ypos);
       }
       glEnd();
   }
}

void polygon::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   GLfloat xbar;
   GLfloat ybar;
   int i = 0;
   for (vertex v : vertices) {
       xbar = (xbar * i + v.xpos)/(i + 1);
       ybar = (ybar * i + v.ypos)/(i + 1);
       i++;
   }
   DEBUGF ('d', "xbar: " << xbar << ", ybar: " << ybar );
   glBegin(GL_POLYGON);
   glColor3ubv(color.ubvec);
   for (vertex v : vertices) {
       GLfloat x = center.xpos + v.xpos - xbar;
       GLfloat y = center.ypos + v.ypos - ybar;
       glVertex2f(x,y);
   }
   glEnd();

   if (window::selected == true) {
       glLineWidth(window::border_width);
       glBegin (GL_LINE_LOOP);
       glColor3ubv(rgbcolor(window::border_color).ubvec);
       glLineWidth(window::border_width);
       for (vertex v : vertices) {
           GLfloat x = center.xpos + v.xpos - xbar;
           GLfloat y = center.ypos + v.ypos - ybar;
           glVertex2f(x,y);
       }
       glEnd();
   }
}

void shape::show (ostream& out) const {
   out << this << "->" << demangle (*this) << ": ";
}

void text::show (ostream& out) const {
   shape::show (out);
   out << glut_bitmap_font << "(" << fontname[glut_bitmap_font]
       << ") \"" << textdata << "\"";
}

void ellipse::show (ostream& out) const {
   shape::show (out);
   out << "{" << dimension << "}";
}

void polygon::show (ostream& out) const {
   shape::show (out);
   out << "{" << vertices << "}";
}

ostream& operator<< (ostream& out, const shape& obj) {
   obj.show (out);
   return out;
}

