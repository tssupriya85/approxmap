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

#include "hash2.h"

int main(int argc, char* argv[]) {
  int sz=atoi(argv[1]), x, y;
  Hash hdist(sz);
  /*
  for (int i=0; i<sz; i++)
    for (int j=0; j<sz; j++)
      hdist.puth(i,j,i*j);
  */

  for (int j=0; j<sz; j++)
    hdist.seth(j,j,j*j);

  if (sz<=10) {
    for (int i=0; i<sz; i++) {
      for (int j=0; j<sz; j++)
	cout<<hdist.geth(i,j)<<":";
      cout<<endl;
    }
  } else {
    while(1) {
      cout<<"x? ";
      cin>>x;
      cout<<"y? ";
      cin>>y;
      cout<<x*y<<"="<<hdist.geth(x,y)<<endl;
    }
  }
}  

