// Author: Bradley Bernard, bmbernar@ucsc.edu
// $Id: rgbcolor.cpp,v 1.3 2015-08-03 22:00:53-07 - - $

#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
using namespace std;

#include "rgbcolor.h"
#include "colors.cppgen"

rgbcolor::rgbcolor (const string& name) {
   auto entry = color_names.find (name);
   if (entry != color_names.end()) {
      *this = entry->second;
   }else {
      string err {"rgbcolor::rgbcolor(" + name + ")"};
      if (name.size() != 8) throw runtime_error{err};
      string prefix = name.substr (0, 2);
      if (not (prefix == "0x" or prefix == "0X")) 
         throw runtime_error{err};
      for (size_t index = 0; index < 3; ++index) {
         string hex = name.substr (index * 2 + 2, 2);
         for (char digit: hex) if (not isxdigit(digit)) 
                                  throw runtime_error{err};
         ubvec[index] = stoul (hex, nullptr, 16);
      }
   }
}

rgbcolor::operator string() const {
   ostringstream result;
   result << "0x"
          << hex << setiosflags (ios::uppercase) << setfill ('0')
          << setw(2) << static_cast<unsigned> (red)
          << setw(2) << static_cast<unsigned> (green)
          << setw(2) << static_cast<unsigned> (blue);
   return result.str();
}

ostream& operator<< (ostream& out, const rgbcolor& color) {
   out << string (color);
   return out;
}

