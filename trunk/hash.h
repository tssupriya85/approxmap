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

#ifndef _HASH_H_
#define _HASH_H_

#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define MAXS 10000000

class Hash {
  vector < map <int, int> > htable;
  int hsize;
 public:
  Hash(int sz) { 
    if (sz <= MAXS) {
      htable.resize(sz);
      hsize=sz;
    } else {
      htable.resize(MAXS);
      hsize=MAXS;
    }
  };

  ~Hash() { htable.clear(); };
  
  int geth(int x, int y) { 
    if (x>=hsize)
      return -2;

    map<int, int>::iterator iter=htable[x].find(y);
    if (iter==htable[x].end())
      return -1;
    else
      return (*iter).second;
  };

  int seth(int x, int y, int val) {
    pair <int, int> p;
    p.first=y;
    p.second=val;

    if (x>=hsize)
      return -2;

    map<int, int>::iterator iter=htable[x].find(y);
    if (iter==htable[x].end())
      htable[x].insert(p);
    else
      (*iter).second=val;
    return 0;
  };
};

#endif //_HASH_H_
