/*	This file is part of ApproxMAP 

	Copyright (C) 2003, 2004, 2010 Hye-Chung Kum.
	You may contact Hye-Chung Kum (approxmap@unc.edu) for any further licensing inquires.

    ApproxMAP is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ApproxMAP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ApproxMAP. In the current directory gpl.txt is the GNU 
	public license file. If not, see <http://www.gnu.org/licenses/>. */


#ifndef _POSTSCRIPT_H_
#define _POSTSCRIPT_H_

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

#define YSIZE 610

class Postscript {
  char font[200];
  int size;
  char file[200];
  std::ofstream htmlout;

 public:
  Postscript(const char *fn, const char *ft, int sz) {
    char f[200];
    size=sz;
    strcpy(font, ft);
    strcpy(file, fn);

    strcpy(f, fn);
    strcat(f, ".html");
    htmlout.open(f) ;
    
    if (!htmlout) {
      std::cout <<"ERROR: Can not open file "<<file<<"\n";
      exit(1);
    }
    
    htmlout<<"<! Created by program ApproxMAP by Hye-Chung(Monica) Kum>\n";
    //htmlout<<"<HTML><table><font size=5 face='"<<font<<"'><b><TR><TD>\n";
    htmlout<<"<HTML><font size=5 face='"<<font<<"'><b>\n";
   htmlout.fill('0');
  };
  ~Postscript() {close();};
  
  void close() {
    htmlout<<"</b></font></html>";
    //htmlout<<"</TD></TR></b></font></table></html>";
    htmlout.close();
  };

  void printColor(double p) {
    int c=(int)(255.0*(log((float)log((float)2-p)/log((float)2)+1)/log((float)2) ) );
    //int c=(int)255.0*(log(log(log(2-p)/log(2)+1)/log(2)+1)/log(2) );

    htmlout<<"<font color='";
    htmlout<<hex<<std::setw(2)<<c<<std::setw(2)<<c<<std::setw(2)<<c<<"'> ";
    htmlout.unsetf(ios::hex);
  };

  void print(char* str, double p) { 
    printColor(p); 
    htmlout<<str<< "</font>\n";
  };

  void print(float i, double p) {
    printColor(p); 
    htmlout<<i<< "</font>\n";
  };

  void newline() {
    newlineColor();
  };

  void newlineColor() { 
    //htmlout<<"</TD></TR><TR><TD>\n"; 
    htmlout<<"<BR>\n"; 
  };
  void newEle() { htmlout<<"</TD><TD>\n"; }
};

#endif //_POSTSCRIPT_H_




