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

#ifndef _HEADER_H_
#define _HEADER_H_

/** Disable some common warnings in MS VC++ */
#if defined(_MSC_VER)

// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning ( disable : 4244 )

// 'identifier' : truncation from 'type1' to 'type2'
#pragma warning ( disable : 4305 )

// 'conversion' : truncation of constant value
#pragma warning ( disable : 4309 )

// 'identifier' : identifier was truncated to 'number' characters in the
// debug information
#pragma warning ( disable : 4786 )

// 'type' : forcing value to bool 'true' or 'false' (performance warning)
#pragma warning ( disable : 4800 )

#endif

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

#include <functional>
#include <queue>
#include <list>

#include <iostream>
#include <vector>
#include <set>
#include <map>

#include "distribution.h"
/*
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iomanip.h>
#include <multimap>
*/

using namespace std;

//#define NOPROF 1
#define NOPRNT  1 
//#define DEBUG 1
//#define NOOPL 1
//#define RANDMIN 1
#define NSAVE 50

#define TRUE    1
#define FALSE   0

#define UNIFORM 1
#define GIVEN   0

#define NULL_ELE -1

#define VALUE 0
#define INDEX 1
#define ID 1

#define DIAGONAL 1
#define LEFT 2
#define UP 3

typedef multiset<int> item;
//typedef set<int> item;

#define UNIFORM_NOMINAL 0
#define WEIGHTED_NOMINAL 1
#define ORDINAL 2
#define INTERVAL 3
#define RATIO 4
#define INTER_DIST 5

#define EleType UNIFORM_NOMINAL // set element type

#define DECPOINT 10000
#define MAX_NITEM 10000
#define MAX_DIST 1000000

struct ValComp  {
  bool operator() (vector<int> &v1, vector<int> &v2) const {
    return v1[1] < v2[1];
  }
};

inline int set2multiset(multiset<int> & ms, set<int>& s) {
  for(set<int>::const_iterator k=s.begin(); 
      k!=s.end();
      k++) 
    ms.insert(*k);
  return ms.size();
};

inline std::ostream& operator <<(std::ostream& out, const vector<string>& v) {
  for (int i=0; i<v.size(); i++) 
    out<<v[i]<<" ";
  out<<"\n";
  return out;
};

inline void printVD(std::ostream& out, const vector<double>& v, int start, int end) {
  out.precision(4);
  for (int i=start; i<end; i++) 
    out<<v[i]<<" ";
};

inline std::ostream& operator <<(std::ostream& out, const vector<double>& v) {
  out.precision(4);
  for (int i=0; i<v.size(); i++) 
    out<<v[i]<<" ";
  out<<"\n";
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const vector< vector <double> >& matrix) {
  for (int i=0; i<matrix.size(); i++)
    out<<matrix[i];
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const vector<int>& v) {
  for (int i=0; i<v.size(); i++) 
    out<<v[i]<<" ";
  out<<"\n";
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const vector< vector <int> >& matrix) {
  for (int i=0; i<matrix.size(); i++) 
    out<<matrix[i];
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const vector< vector <vector <int> > >& matrix) {
  for (int i=0; i<matrix.size(); i++) {
    out<<i<<":\n";
    out<<matrix[i];
  }
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const set<int>& s) {
  out<<"{";
  for(set<int>::const_iterator k=s.begin(); 
      k!=s.end();
      k++) 
    out<< *k <<",";
  out<<"} ";
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const vector<set <int> >& v) {
  for (int i=0; i<v.size(); i++)
    out<<v[i];
  out<<"\n";
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const vector <vector<set <int> > >& v) {
  for (int i=0; i<v.size(); i++)
    out<<v[i];
  return out;
};

inline std::ostream& operator <<(std::ostream& out, list<vector <set <int> > >& s) {
  for(list<vector <set <int> > >::iterator k=s.begin(); 
      k!=s.end();
      k++) 
    out<< (*k);
  out<<"\n";
  return out;
}

inline std::ostream& operator <<(std::ostream& out, const multiset<int>& s) {
  out<<"{";
  for(multiset<int>::const_iterator k=s.begin(); 
      k!=s.end();
      k++) 
    out<< *k <<",";
  out<<"} ";
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const vector<multiset <int> >& v) {
  for (int i=0; i<v.size(); i++)
    out<<v[i];
  out<<"\n";
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const multimap<int, int>& s) {
  out<<"[";
  for(multimap<int,int>::const_iterator k=s.begin(); 
      k!=s.end();
      k++) 
    out<< (*k).first <<":"<<(*k).second<<",";
  out<<"] ";
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const vector<multimap <int, int> >& v) {
  for (int i=0; i<v.size(); i++)
    out<<v[i];
  out<<"\n";
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const multimap<int, int, greater<int> >& s) {
  out<<"[";
  for(multimap<int,int, greater<int> >::const_iterator k=s.begin(); 
      k!=s.end();
      k++) 
    out<< (*k).first <<":"<<(*k).second<<",";
  out<<"] ";
  return out;
};

inline std::ostream& operator <<(std::ostream& out, const vector<multimap <int, int, greater<int> > >& v) {
  for (int i=0; i<v.size(); i++)
    out<<v[i];
  out<<"\n";
  return out;
};

inline std::ostream& operator <<(std::ostream& out, map <int,int> &m) {
  for(map<int, int>::iterator k=m.begin(); 
      k!=m.end();
      k++) 
    out<< "("<<(*k).first <<":"<<(*k).second <<"),";
  return out;
}

inline std::ostream& operator <<(std::ostream& out, pair<map <int,int>,  set<int> > &m) {
  out<< m.first <<"="<<m.second;
  return out;
}

inline std::ostream& operator <<(std::ostream& out, list<pair <map <int, int>, set <int> > >& s) {
  for(list<pair <map <int, int>, set <int> > >::iterator k=s.begin(); 
      k!=s.end();
      k++) 
    out<< (*k);
  return out;
}

inline std::ostream& operator <<(std::ostream& out, list<int>& s) {
  for(list<int>::iterator k=s.begin(); 
      k!=s.end();
      k++) 
    out<< (*k) <<",";
  out<<"\n";
  return out;
}

inline std::ostream& operator <<(std::ostream& out, vector <list <int> > & v) {
  for (int j=0;j<v.size();j++) {
    std::cout<<"   "<<j<<" list: ";
    out<<v[j];
  }
  return out;
}

inline std::ostream& operator <<(std::ostream& out, vector <vector <list <int> > > & v) {
  for(int i=0;i<v.size();i++) {
    out<<i<<" vector:\n";
    out<<v[i];
  }
  return out;
}

/*
inline std::ostream& operator <<(std::ostream& out, pair <int, int> &p) {
  out<<p.first<<":"<<p.second;
};
*/

inline std::istream& operator >>(std::istream& in, vector<vector <int> >& v) {
  for (int i=0; i<v.size(); i++) 
    for (int j=0; j<v.size(); j++) 
      in>>v[i][j];
  return in;
};

inline int myMin(int x1, int x2) {
  return (x1 < x2) ? x1 : x2;
};

inline int myMax(int x1, int x2) {
  return (x1 > x2) ? x1 : x2;
};

inline int myMin(int x1, int x2, int x3) {
  int m=(x1 < x2) ? x1 : x2; // myMin(x1, x2)
  return (m < x3) ? m : x3;
};

inline int max0(int x1, int x2) {
  int m=(x1 > x2) ? x1 : x2; 
  return (m !=0 ) ? m : 1;
};

inline int diff(multiset <int> &set1, multiset <int> &set2) {
  multiset <int> res;
  insert_iterator<multiset<int> > ii(res, res.begin());
  set_symmetric_difference(set1.begin(), set1.end(),
			   set2.begin(), set2.end(),
			   ii);
  return res.size();
};
/*
inline void merge (multimap <int,int> &to, multimap <int, int> from) {
  for(multimap<int,int>::insert_iterator k=s.beg(); 
      k!=s.end();
      k++) 
  insert_iterator<multimap<int, int> > ii(res, res.begin());
  set_symmetric_difference(set1.begin(), set1.end(),
			   set2.begin(), set2.end(),
			   ii);
  return res.size();
};
*/

//If set size is 0, return 1;
inline int size0(int x) {
  return (x==0) ? 1 : x;
}

inline bool isSimilar(set <int> &set1, set <int> &set2) {
  set <int> res;
  insert_iterator<set<int> > ii(res, res.begin());
  set_intersection(set1.begin(), set1.end(),
	    set2.begin(), set2.end(),
	    ii);
  return res.size()>=1.5*((set1.size()+set2.size()-2*res.size()));
};

inline void swap(int &x, int &y) {
  int tmp=y;
  y=x;
  x=tmp;
};

inline void traceOp(vector <vector <int> > &trace, vector <int> &ret) {
  int i=trace.size()-1, j=trace[0].size()-1;
  while (trace[i][j]!=0) {
    ret.push_back(trace[i][j]);
    switch(trace[i][j]) {
    case DIAGONAL:
      i--;
      j--;
      break;
    case UP:
      i--;
      break;
    case LEFT:
      j--;
      break;
    default:
      std::cout<<"ERROR: setProfile trace("<<i<<","<<j<<")="<<trace[i][j]<<"\n";
      exit(1);
      break;
    }
  }
};

inline int indelSet(multiset<int> &mset, int nprof=1) { 
  int ret=0;

  if (EleType==UNIFORM_NOMINAL) // size of set_symmetric difference
    //return Indel+(Wsize*mset.size());
    return 1*DECPOINT;
  /*
  else if (EleType==WEIGHTED_NOMINAL) {
    for (multiset<int>::iterator i=mset.begin(); i!=mset.end() ;i++)
      ret+=cfg->getWalpha(*i);
    return ret;
  } else if (EleType==INTERVAL) {
    if (mset.size()==0)
      return 0;
    else
      return Indel;
  } else if (EleType==RATIO) {
      for(multiset<int>::iterator i=mset.begin(); i!=mset.end() ; i++) 
	ret+=(*i);
      return ret;
  }
  */
  return -1;

}

inline int calcSetDist(multiset <int> &set1, multiset <int> &set2) { 
  int ret=0;
  multiset <int> res;

  if ((set1.size()+set2.size())==0) {
    std::cout<<"ERROR: calcSetDist. divide by zero.";
    exit(1);
  }

  if (EleType==UNIFORM_NOMINAL) { // size of set_symmetric difference
    set_intersection(set1.begin(), set1.end(), //div by myMax set size
		     set2.begin(), set2.end(), // if not=0 
		     inserter(res, res.begin()));
    // int tt=ret;
    //std::cout<<"TEST="<<tt<<" Set"<<set1<<"set2"<<set2<<"sim="<<res.size();
    //  std::cin>>tt;
    ret= (int) ( ( ((set1.size()+set2.size())-2*res.size() )*1.0/
		   (set1.size()+set2.size())*1.0)*DECPOINT );
    return ret;

  } 
  /*
else if (EleType==WEIGHTED_NOMINAL) {
    set_symmetric_difference(set1.begin(), set1.end(),
			     set2.begin(), set2.end(),
			     inserter(res, res.begin()));
    for (multiset<int>::iterator i=res.begin(); i!=res.end() ;i++)
      ret+=cfg->getWalpha(*i);
    return ret;
  } else if ((EleType==INTERVAL) && (set1.size()==0 || set2.size()==0)) {
    if (set1.size() + set2.size()==0) 
      return 0;
    else
      return Indel;
  } else if ((EleType==INTERVAL) || (EleType==RATIO)) {
    for(multiset<int>::iterator i=set1.begin(); i!=set1.end() ; i++) 
      ret+=(*i);
    for(multiset<int>::iterator iter=set2.begin(); iter!=set2.end() ; iter++) 
      ret-=(*iter);
    return abs(ret);
  }
  */
  return -1;
}

inline int myMinSet(int x1, int x2, int x3, int &index) {
  int ret;
  if (x1<=x2) {
    ret=x1;
    index=DIAGONAL;
  } else {
    ret=x2;
    index=LEFT;
  }

  if (x3<ret) {
    ret=x3;
    index=UP;
  }
  return ret;
};

//align seq to seq
inline int myMinRand(int x1, int x2, int x3, int &index) {
  UniformDist uni;
  int ret;
  if (x1<x2 || (x1==x2 && (uni()<0.5) ) ) {
    ret=x1;
    index=DIAGONAL;
  } else {
    ret=x2;
    index=LEFT;
  }

  if (x3<ret || (x3==ret && (uni()<0.5) ) ) {
    ret=x3;
    index=UP;
  }

  return ret;
};

inline int myMin(int x1, int x2, int x3, int &index) {
#ifdef RANDMIN
  return myMinRand(x1,x2,x3,index);
#else
  return myMinSet(x1,x2,x3,index);
#endif //RANDMIN
}

inline int seqDistPrivate(vector <item> &seq1, vector <item> &seq2, vector <vector <int> >&trace, vector < vector<int> > &save, int min=MAX_DIST) {
  save[0][0]++;
  if (save[0][0]==NSAVE)
    save[0][0]=0;
  if (save[0][0]!=-10)
    save[1][save[0][0]]+=seq1.size()*seq2.size();

  //ODD SEG FAULT. can not interchange declaration order
  vector <vector <int> > editDist(seq1.size()+1) ;
  //, seq2.size()+1);
  // trace[i][j]=1 diagonal, 2=up, 3=left, 0=done;
  trace.resize(seq1.size()+1) ;
  //  , seq2.size()+1);
  int min_line;

  for (int x = 0 ; x < seq1.size() + 1 ; x++)
  {
	editDist[x].resize(seq2.size() + 1) ;
	trace[x].resize(seq2.size() + 1) ;
  }
  editDist[0][0]=0;
  trace[0][0]=0;

  for(int i=0; i<seq1.size(); i++) {
    editDist[i+1][0]=editDist[i][0]+indelSet(seq1[i]);
    trace[i+1][0]=UP;
  }
    
  for(int j=0; j<seq2.size(); j++) {
    editDist[0][j+1]=editDist[0][j]+indelSet(seq2[j]);    
    trace[0][j+1]=LEFT;
  }
  
  for(int k=0; k<seq1.size(); k++) {
    min_line=editDist[k+1][0];
    for(int l=0; l<seq2.size(); l++) {
      editDist[k+1][l+1]=
	myMin( editDist[k][l]+calcSetDist(seq1[k],seq2[l]),
	     editDist[k+1][l]+indelSet(seq2[k]), 
	     editDist[k][l+1]+indelSet(seq1[l]),
	     trace[k+1][l+1]); //[i+1][j+i]??

#ifndef NOOPL
      if (editDist[k+1][l+1]<min_line)
	min_line=editDist[k+1][l+1];
#endif //NOOPL
    }
#ifndef NOOPL
    if ((min_line/max0(seq1.size(), seq2.size()) ) > min+1) {
      //cout<<"HE:"<<min_line/max0(seq1.size(), seq2.size())<<"="<< min<<"\n";
      //cout<<endl<<editDist<<endl<<seq1<<endl<<seq2;
	//	char ch;
	//	cin>>ch;
      if (k<seq1.size()-1) {
	//cout<<"Stopped "<<k<<" ("<<seq1.size()<<","<<seq2.size()<<")\n";
	if (save[0][0]!=-10)
	  save[2][save[0][0]]+=(seq1.size()-k-1)*seq2.size();
      }
      return MAX_DIST;
    }
#endif //NOOPL
  };

  return (int)(1.0*editDist[seq1.size()][seq2.size()]/
	       max0(seq1.size(), seq2.size())*1.0 );
}

inline int seqDist(vector <item> &seq1, vector <item> &seq2, 
		   int min=MAX_DIST ) {
  vector <vector <int> > trace;
  vector <vector <int> > save;
  return (seq1.size() >= seq2.size())? 
    seqDistPrivate(seq1, seq2, trace, save, min): 
    seqDistPrivate(seq2, seq1, trace, save, min);
}

inline int seqDist2(vector <item> &seq1, vector <item> &seq2, 
		   vector <vector <int> > &save, int min=MAX_DIST ) {
  vector <vector <int> > trace;
  return (seq1.size() >= seq2.size())? 
    seqDistPrivate(seq1, seq2, trace, save, min): 
    seqDistPrivate(seq2, seq1, trace, save, min);
}

//FIX LATER same as above function
inline int seqDist(vector <item> &seq1, vector <item> &seq2, vector <vector <int> >&trace) {
  vector <vector <int> > save;
  save.resize(1);
  save[0].resize(1);
  save[0][0]=-10;
  return seqDistPrivate(seq1, seq2, trace, save);
}

#endif //_HEADER_H_
 
