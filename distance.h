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

#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#include "utility.h"
#include "database.h"
#include "postscript.h"
#include "hash.h"

#include <algorithm>
#include <stdio.h>
#include <cmath>

#define MIN_CNT 1
#define NUM 0
#define CLUST 2
#define DEN 0
#define I 1
#define J 2
#define MAX_kNN 10

class Distance {
  Database *db;
  int num, Nclust;
  vector <vector <vector <int> > > Cprofile;

  vector <int> sampleIDs; // seqids in the sample
  vector <int> center; // center for sample clusters

  Hash *hdist;

  vector <vector <int> >  savecalc; // [0]=index [1]=total, [2]=save
  int hash_flag;
  int sample; // sampled in sample based or hash mode as %
  vector <vector <int> > dist;
  vector <vector <int> > dist_min; 
  int kNN; //parameter = # of NN to use for clustering 
  vector <multimap <int, int, less<int> > > neighbor;  //key=dist, val=id
  vector <int> Nknn;

  vector <multimap <int, int, greater<int> > > cluster;  //key=density, val=id

  vector <int> clust_id;
  vector <vector <int> > head; //ID=head of each cluster NUM=size of each cluster;
  vector <int> next;  // pointer to next element id in same clust. -1 end;
  int order; //0=dense 1=reverse 3=id 4=reverse id

  // ODD CHECK LATER
  std::ofstream debug_fout;

#ifndef NOPRNT
#endif //NOPRNT
  
  //  vector <vector <set <int> > > clust;
  //  vector <vector <vector <int> > > Mclust;
  //  vector <int> Mclust_id;

  void calcDistS();

  void setMinList(int d, int x, int y) {
    updateNeighbor(d, x, y);
    updateNeighbor(d, y, x);
  };

  int updateNeighbor(int d, int x, int y);
  void genNeighbor();
  void printNeighbor(string fn);

  void calcDistL();

  /*
  int getDensity(int i) 
    { return (int) ( (1.0*DECPOINT*Nknn[i]/
      (pow( (*neighbor[i].rbegin()).first*1.0/DECPOINT, 3)*1.0)  ) ); };
  */      

  int getDensity(int i) 
    { return (int) (DECPOINT*(1.0*DECPOINT*Nknn[i]/
			    (*neighbor[i].rbegin()).first*1.0) ); };
  
  void incSave(int i, int n) {
    savecalc[0][0]++;
    savecalc[i][savecalc[0][0]]+=n;
  };

  void printSave() { 
    cout<<"SAVE=";
    for (int i=0;i<NSAVE;i++) 
      cout<<savecalc[2][i]<<"+";
    cout<<"\nSAVE OVER=";
    for (int i=0;i<NSAVE;i++) 
      cout<<savecalc[1][i]<<"+";
    cout<<endl;
  };

  int getClustDensity(int i) { return ( *cluster[i].begin() ).first; };
  int isMerged(int x) { return ((* cluster[x].begin() ).first<0); };
  int mergedID(int x) { return ((* cluster[x].begin() ).second ); };
  int findCluster(int x);
  int findCluster(int x, vector <int> &clust);
  int findMaxNNClust(int src, multimap<int,int>::const_iterator &start);  
  int findMaxNN(int src, multimap<int,int>::const_iterator &start);  
  void mergeCluster(int to, int from);
  void initCluster();
  void buildCluster();
  void buildCluster2();
  void initClust();

  int findMin();
  int findMin(int k, int prev_chg);
  void setMin(int i);
public:
  Distance(Database *d, int xorder=0) {
    db=d;
    num=0;
    kNN=3;
    order=xorder;
    hash_flag=FALSE;
    sample=20;
    /*
    savecalc.resize(3);
    savecalc[0].resize(1);
    savecalc[1].resize(NSAVE);
    savecalc[2].resize(NSAVE);
    savecalc[0][0]=-1;
    for (int i=0;i<NSAVE;i++) {
      savecalc[1][i]=0;
      savecalc[2][i]=0;
    }
    */
  };

  ~Distance() {};

  void setDB(Database *d) { db=d; };
  void setkNN(int k) { kNN=k; };
  void setOrder(int o) { order=o; };
  void setHash(int h) { hash_flag=h;};
  void setSample(int s) { sample=s; };
  int getID(int id) { return (sampleIDs.size()>0)? sampleIDs[id]: id; }
  //  int getDist(int i, int j) { return (i<j)? dist[j-1][i]:dist[i-1][j]; }
  int getDist(int i, int j) { return calcCenterDist(i,j); }
  int calcCenterDist(int i, int j) { 
    if (i==j) 
      return 0;

    int x=(i<j)? j-1: i-1;
    int y=(i<j)? i: j;    
    
    if (hash_flag==FALSE)
      return calcCenterDistX(x,y);
    else 
      return calcCenterDistH(x,y);
  }

  int calcCenterDistX(int x, int y) { 
    if (dist[x].size()==0) {
      dist[x].resize(x+1);
      for (int n=0;n<x+1;n++)
	dist[x][n]=-1;
    }
    if (dist[x][y]<0)
      dist[x][y]=db->calcSeqDist(x+1, y);
    return dist[x][y];
  }

  int calcCenterDistH(int x, int y) { 
    int val=hdist->geth(x,y);
    if (val==-1) {
      val=db->calcSeqDist(x+1, y);
      hdist->seth(x,y,val);
    }

    return val;
  }

  int distance(int i, int j) { return ( (i==j)? 0 : ((i<j)? dist[j-1][i]:dist[i-1][j]) ); };
  void calcDistStream(string fn);
  void calcDistStream1(string fn);
  void calcDistStreamSample(string fn);
  void testInsert(vector <item> &seqi, int id);
  void reCluster();
  int findCenter(int n=0);
  int calcDist(vector <item> &seqi, int i, vector <int>& min_dist);
  void calcDist(string fn, bool type=true);
  void readDist(string fn);
  void printDist(std::ostream& out=std::cout) { out<<num<<"\n"<<dist; };
  void printSas(string fn);

  void kNNCluster();
  void printCluster (string fn);
  void printClusterID (string fn, int n);
  void printCluster(std::ostream& out=std::cout);
  void profileCluster();
  void printProfile();
  void printCenterDist(std::ostream& out=std::cout);  
  void readClust(string fn, int Nseq);
  void printClust(string fn);
  void printClust(std::ostream& out=std::cout);
  /*
  void calcDendro(string fn);
  void readDendro(string fn);
  void printDendro(std::ostream& out=std::cout) {out<<dendro;};
  void printDendro(string fn);
  */
};

inline void Distance::initCluster() {
  cluster.clear();
  cluster.resize(num);
  clust_id.resize(num);
  Nclust=num;

  for (int i=0;i<num;i++) {
    clust_id[i]=0;
    cluster[i].insert( pair <int, int> (getDensity(i), i) );
  }
};

inline int Distance::findCluster(int x) {
  while (isMerged(x) ) 
    x=mergedID(x); 
  return x;
}

inline int Distance::findCluster(int x, vector <int> &clust) {
  for (int i=0; i<Nclust;i++) 
    if (clust[i]==x)
      return i;

  int ret = 0 ;
  int d = dist[myMax(x, clust[ret])-1][myMin(x, clust[ret])];
  for(int j=1; j<Nclust;j++)
    if (d>dist[myMax(x, clust[j])-1][myMin(x, clust[j])]) {
      ret=j;
      d=dist[myMax(x, clust[ret])-1][myMin(x, clust[ret])];
    }

  return ret;
}

inline void Distance::printCluster(string fn) {
  char file[200];
  strcpy(file, fn.c_str());
  sprintf(file+strlen(file), "%d", kNN);
  strcat(file, ".clust");
  std::ofstream to(file) ;

  if (!to) {
    std::cout <<"ERROR: Can not open file "<<fn<<".clust\n";
    exit(1);
  }
  printCluster(to);
}

inline void Distance::printClusterID(string fn, int n) {
  char file[200];

  strcpy(file, fn.c_str());
  sprintf(file+strlen(file), "%d", kNN);
  strcat(file, ".clustID");
  sprintf(file+strlen(file), "%d", n);
  std::ofstream to1(file) ;
  
  for (int i=0;i<num;i++)
    to1<<i<<":"<<clust_id[i]<<"\n";
}

inline void Distance::initClust() {
  head.resize(num);
  next.resize(num);
  clust_id.resize(num);
  Nclust=num;

  for (int i=0;i<num;i++) {
    head[i].resize(2);
    head[i][NUM]=1;
    head[i][ID]=i;
    next[i]=-1;
    clust_id[i]=i;
  }
}

inline int Distance::updateNeighbor(int d, int x, int y) {
  pair <int, int> m;
  int i=0;

  if (neighbor[x].size()<kNN || (*neighbor[x].rbegin()).first==0 )
    i=1;
  else if (d<=(*neighbor[x].rbegin()).first )
    i=2;

  if (i>0) {
    if (i==2) {
      if (d<(*neighbor[x].rbegin()).first &&
	  (1 + neighbor[x].size()
	   - neighbor[x].count( (*neighbor[x].rbegin()).first) )>=kNN )
      neighbor[x].erase( (*neighbor[x].rbegin()).first );
    }

    m.first=d;
    m.second=y;
    neighbor[x].insert(m);
  }

#ifndef NOOPL
  return (neighbor[x].size()<kNN) ? MAX_DIST:(*neighbor[x].rbegin()).first;
#else
  return MAX_DIST;
#endif //NOOPL

};

#endif //_DISTANCE_H_
