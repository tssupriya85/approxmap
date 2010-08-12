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

#include "utility.h"
#include "distance.h"

#define MAX_LOOP 10000

//Memory Save NO CLUSTERING
void Distance::calcDistS() {
  /*  vector <int> dist;

  for(int i=1; i<num; i++) {
    dist.resize(i);
    for(int j=0; j<i; j++) 
      dist[j]=db->calcSeqDist(i,j);
  if (db->getIO()==2)
    fout<<dist; 
  } */
  cout<<"NOT IMPLEMENTED YET\n";
}

void Distance::genNeighbor() {
  int d;

  Nknn.resize(num);
  for (int i=0; i<num;i++) {
    //    Nknn[i]=db->getFreq(i)-1;
    Nknn[i]=0;
    multimap<int, int>::iterator j=neighbor[i].begin();
    //    for (; j!=neighbor[i].end() && Nknn[i]<kNN; j++)
    for (; j!=neighbor[i].end(); j++)
      Nknn[i]+=db->getFreq((*j).second);

    //    neighbor[i].erase(j, neighbor[i].end());
  }

#ifndef NOPRNT
//  if (db->getIO()==2) 
    printNeighbor(db->getfn());
#endif //NOPRNT
}

void Distance::printNeighbor(string fn) {
  char file[200];
  strcpy(file, fn.c_str());
  sprintf(file+strlen(file), "%d", kNN);
  strcat(file, ".nn");
  std::ofstream fout(file) ;

  //  std::ofstream fout((fn+".nn"+kNN).c_str()) ;

  if (!fout) {
    std::cout <<"ERROR: Can not open file "<<fn<<".nn\n";
    exit(1);
  }

    fout<<neighbor.size()<<"ID=Num points, Max Dist, Density [NN list=dist:id]\n";
    for (int i=0;i<num;i++) {
      fout<<i<<"="<<Nknn[i]<<","
	  <<(*neighbor[i].rbegin()).first<<","<<getDensity(i)<<", ";
      fout<<neighbor[i]<<"\n";
    }
}

// No memory save
void Distance::calcDistL() {
  neighbor.resize(num);
  if (hash_flag==FALSE)
    dist.resize(db->getNseq());
  else
    hdist=new Hash(db->getNseq());

  for(int i=1; i<num; i++) {
    for(int j=0; j<i; j++) {
      setMinList( calcCenterDist(getID(i), getID(j)), i, j);
    }

#ifndef NOPRNT
    debug_fout<<dist[i-1]; 
#endif //NOPRNT
  } 
  genNeighbor();
}

int Distance::calcDist(vector <item> &seqi, int i, vector <int> &min_dist) {
  vector <int> dd;
  vector <int> v;
  multimap <int, int> m;
  int cur_min=MAX_DIST;

  if (i>dist.size()) {
    //    dist.push_back(v);
    //    dist_min.push_back(v);
    neighbor.push_back(m);
  }
  neighbor[i].clear();
  dd.resize(i);

  for(int j=0; j<i; j++) {
    dd[j]=db->calcSeqDist(seqi,j, max(cur_min, min_dist[j]), savecalc);
#ifndef NOPRNT
      if (db->getIO()==FALSE)
        debug_fout<<i<<":"<<j<<"=";

      debug_fout<<dd[j]<<" ";
#endif //NOPRNT

    if (dd[j]==0) {
      db->incFreq(j);
      return FALSE;
    } else if (kNN==0)
      return TRUE;
    else 
      cur_min=updateNeighbor(dd[j], i, j); 
  }
#ifndef NOPRNT
  debug_fout<<endl;
#endif //NOPRNT
  min_dist.push_back(cur_min);
  for(int j=0; j<i; j++)
    min_dist[j]=updateNeighbor(dd[j], j, i); 

  return TRUE;
};
    
void Distance::calcDistStream(string fn) {
#ifndef NOPRNT
  cout<<"PRINT on for dist\n";
  debug_fout.open((fn+".dist").c_str()) ;

  if (!debug_fout.is_open()) {
    std::cout <<"ERROR: Can not open file "<<fn<<".dist\n";
    exit(1);
  }
#endif //NOPRNT

  vector <int> v;
  vector <item> seqi;
  vector <int> min_dist;

  int i=1, j, done, id=-1, nextid=0;
  //  dist.resize(num-1);
  //  dist_min.resize(num-1);

  neighbor.resize(1);
  done=db->readSeq(seqi, id, nextid);
  db->insertSeq(seqi, id);
  min_dist.push_back(MAX_DIST);
  while (!done) {
    seqi.clear();
    done=db->readSeq(seqi, id, nextid);
    if (calcDist(seqi, i, min_dist)) {
      db->insertSeq(seqi, id);
      i++;
#ifndef NOPRNT
      if (db->getIO()==FALSE)
	debug_fout<<i-1<<"; ";  
#endif //NOPRNT
    }
  } 

  num=db->getNseq();
  if (num!=db->postSeq()) {
    seqi.clear();
    calcDist(seqi,num, min_dist);
  }

#ifndef NOPRNT
  debug_fout<<"TOTAL NUM="<<num<<"\n";
  debug_fout.close();
#endif //NOPRNT
  if (kNN>0) {
    num=db->getNseq();
    genNeighbor();
    //  cout<<num<<"=="<<dist.size()<<"="<<dist[0].size()<<"\n";
    dist.clear();
  }
  //  printSave();
}

void Distance::calcDistStream1(string fn) {
#ifndef NOPRNT
  debug_fout.open((fn+".dist").c_str()) ;
#endif //NOPRNT
  vector <int> v;
  vector <item> seqi;
  vector <int> min_dist;

  int i=1, j, done, id, nextid;
  //  dist.resize(num-1);
  //  dist_min.resize(num-1);

#ifndef NOPRNT
  if (!debug_fout.is_open()) {
    std::cout <<"ERROR: Can not open file "<<fn<<".dist\n";
    exit(1);
  }
#endif //NOPRNT

  neighbor.resize(1);

  done=db->readSeq(seqi, id, nextid);
  db->insertSeq(seqi, id);
  min_dist.push_back(MAX_DIST);
  while (!done) {
    seqi.clear();
    done=db->readSeq(seqi, id, nextid);
    db->insertSeq(seqi, id);

#ifndef NOPRNT
      if (db->getIO()==1)
	debug_fout<<i-1<<"; ";  
#endif //NOPRNT

  } 

  num=db->getNseq();
  if (num!=db->postSeq()) {
    seqi.clear();
    calcDist(seqi,num, min_dist);
  }

#ifndef NOPRNT
  debug_fout<<"TOTAL NUM="<<num<<"\n";
  debug_fout.close();
#endif //NOPRNT
  num=db->getNseq();
  calcDistL();
  //  cout<<num<<"=="<<dist.size()<<"="<<dist[0].size()<<"\n";
  dist.clear();
}

void Distance::testInsert(vector <item> &seqi, int id) {
  vector <item> seq;
  for (int k=1;k<5;k++) {
    seq.clear();
    seq.resize(seqi.size());
    for (int i=0;i<seqi.size();i++) 
      for (item::iterator j=seqi[i].begin(); j!=seqi[i].end();j++)
	seq[i].insert((*j)+k*100);
    db->insertSeq(seq, id+k*100);
  }
}

void Distance::calcDistStreamSample(string fn) {
#ifndef NOPRNT
  debug_fout.open((fn+".dist").c_str()) ;
  if (!debug_fout.is_open()) {
    std::cout <<"ERROR: Can not open file "<<fn<<".dist\n";
    exit(1);
  }
#endif //NOPRNT
  vector <int> v;
  vector <item> seqi;
  vector <int> min_dist;

  int i=1, j, done, id, nextid;
  //  dist.resize(num-1);
  //  dist_min.resize(num-1);

  done=db->readSeq(seqi, id, nextid);
  db->insertSeq(seqi, id);
  while (!done) {
    seqi.clear();
    done=db->readSeq(seqi, id, nextid);
    db->insertSeq(seqi, id);
    //testInsert(seqi,id);
  } 

  num=db->getNseq();
  if (num!=db->postSeq()) {
    seqi.clear();
    calcDist(seqi,num, min_dist);
  }

  UniformDist uf=UniformDist();

  min_dist.push_back(MAX_DIST);
  for (i=0; i<num; i++) {
    if (uf()*100<= sample ) 
      sampleIDs.push_back(i);
  }  

  num=sampleIDs.size();
  calcDistL();
#ifndef NOPRNT
  debug_fout<<"TOTAL NUM="<<num<<"\n";
  debug_fout<<sampleIDs;
#endif //NOPRNT
  //  cout<<num<<"=="<<dist.size()<<"="<<dist[0].size()<<"\n";
  kNNCluster();
  findCenter();
  /*
  center[0]=0;
  center[1]=10;
  center[2]=20;
  center[3]=30;
  center[4]=40;
  */
  int loop;
  num=db->getNseq();
  dist.clear();
  sampleIDs.clear();
  dist_min.clear();
  neighbor.clear();
  Nknn.clear();

  if (hash_flag==FALSE)
    dist.resize(num-1);
  for (int n=1;n<MAX_LOOP;n++) {
    reCluster();
#ifndef NOPRNT
    debug_fout<<"Iterate: "<<n<<endl;
    printCluster(debug_fout);
#endif //NOPRNT
    loop=n;
    n=findCenter(n);
  }
  cout<<"Converged Time: "<<loop<<endl;
#ifndef NOPRNT
  debug_fout.close();
#endif //NOPRNT
}

void Distance::calcDist(string fn, bool type) {
  num=db->getNseq();
  if (type)
    calcDistL();
  else
    calcDistS();
  std::cout<< "Distance calculation done.\n";
}

void Distance::readDist(string fn) {
  std::ifstream from((fn+".dist").c_str()) ;
  if (!from) {
    std::cout <<"ERROR: Can not open file "<<fn<<".dist\n";
    exit(1);
  }

  from>>num;
  dist.clear();
  dist_min.clear();
  dist.resize(num-1);
  dist_min.resize(num-1);
  neighbor.resize(num);

  for(int i=1; i<num; i++) {
    dist[i-1].resize(i);
    dist_min[i-1].resize(2);
    dist_min[i-1][VALUE]=MAX_DIST;
    for(int j=0; j<i; j++) {
      from>>dist[i-1][j];

      if (dist[i-1][j]<dist_min[i-1][VALUE]) {
	dist_min[i-1][VALUE]=dist[i-1][j];
	dist_min[i-1][INDEX]=j;
      }

      setMinList(dist[i-1][j], getID(i), getID(j));
    }      
  }
  genNeighbor();
  std::cout<< "Distance Matrix read:"<<num<<"\n";
};

void Distance::printSas(string fn) {
  int n=dist.size()+1;
  if (n==1)
    std::cout<<"CAN NOT SAVE: used memory saving algorithm.  No data remains.\n";
  else {
    std::ofstream fout((fn+".dat").c_str()) ;
    
    if (!fout) {
      std::cout <<"ERROR: Can not open file "<<fn<<".dist\n";
      exit(1);
    }
    for (int i=0;i<n;i++) {
      fout<<"SEQ"<<i<<"\n";
      for (int j=0;j<n;j++) {
	if (i==j)
	  fout<<"0\n";
	else if (i<j)
	  fout<<dist[j-1][i]<<"\n";
	else
	  fout<<dist[i-1][j]<<"\n";
      }
    }
  }
}

int Distance::findMaxNNClust(int src, multimap<int,int>::const_iterator &start) {
  int tid, pid, cid=findCluster( (*start).second );

  multimap<int,int>::const_iterator ptr=start; 
  ptr++;
  while (ptr!=neighbor[src].end() && (*ptr).first==(*start).first)
    ptr++;
  
  if ( ptr!=neighbor[src].end() && ((*ptr).first == (*start).first ) ) { // same distance exist    
    tid=(*ptr).second;    // find myMax
    ptr=start;
    while ( tid != (*ptr).second ) {
      ptr++;
      pid=findCluster( (*ptr).second );
      if ( getClustDensity(cid) < getClustDensity(pid) )
	cid=pid;
    }
  } 

  if (getClustDensity(findCluster(src))>getClustDensity(cid) 
      || (getClustDensity(findCluster(src))==getClustDensity(cid)
	  && src<cid) )
    return src;  // find cluster to merge

  return cid;
};

int Distance::findMaxNN(int src, multimap<int,int>::const_iterator &start) {
  int tid;

  multimap<int,int>::const_iterator ptr=start; 
  ptr++;
  while (ptr!=neighbor[src].end() && (*ptr).first==(*start).first)
    ptr++;
  
  if ( ptr!=neighbor[src].end() && ((*ptr).first == (*start).first ) ) { // same distance exist    
    tid=(*ptr).second;    // find myMax
    ptr=start;
    while ( tid != (*ptr).second ) {
      ptr++;
      if ( (*start).first < (*ptr). first ) 
	start=ptr;
    }
  } 
  //      std::cout<<"to"<<(*k)<<"\n";      
  return (*start).second;  // find cluster to merge
}

void Distance::mergeCluster(int to, int from) {
  to=findCluster(to);

  //std::cout<< "merging "<<from<<"+"<<to<<"\n";
  if (to != from) {
    Nclust=Nclust-1;
//	cluster[to].insert< multimap<int, int, greater< int > >::iterator >(cluster[from].begin(), cluster[from].end());
    for( multimap<int, int, greater<int> >::iterator m=cluster[from].begin();
	 m!=cluster[from].end();
	 m++)
      cluster[to].insert(*m);

	cluster[from].clear();
	pair <int, int> p;
	p.first=-1;
	p.second=to;
    cluster[from].insert( p );
  } 
  //    else std::cout<< "ERROR: recursive. id="<<from<<"\n";
}

void Distance::kNNCluster() {
  multimap<int,int>::const_iterator k;

  initCluster();

  for (int i=0;i<num;i++) { // find myMax dense NN and merge
    k=neighbor[i].begin(); 
    while (k!=neighbor[i].end() && getDensity(i)>=getDensity( (*k).second ) )
      k++;
    if (k!=neighbor[i].end() )  //merge clusters;
      mergeCluster(findMaxNN(i, k), i);
  }

  for (int j=0;j<num;j++) { // if myMax but have NN with same desity
    if ( !isMerged(j) ) {
      k=neighbor[j].begin(); 
      while (k!=neighbor[j].end() && getDensity(j)!=getDensity((*k).second) )
	k++;
      if (k!=neighbor[j].end())  //merge clusters;
	mergeCluster(findMaxNNClust(j, k), j);
    }
  }

  std::cout<< "kNN="<<kNN<<" Nclust="<<Nclust<<"\n";

  buildCluster();
  //  buildCluster2();
  //printCluster();
#ifndef NOPRNT
    printCluster(db->getfn());
#endif //NOPRNT
}

void Distance::printCluster(std::ostream& out) {
  out<<"kNN="<<kNN<<" Nclust="<<Nclust<<"\n";
  for (int i=0; i<cluster.size(); i++) {
    if ( !isMerged(i) ) {
      out<<i<<"="<<cluster[i]<<"\n";
      out<<"SEQ:"<<i<<":print proper size"<<cluster[i].size()<<":";
      db->printSeq( out, (* (cluster[i].begin()) ).second);
    }
  }
}

// clust_id[seq#]= cluster id;
// cluster as kNN was merged;
void Distance::buildCluster() {
  int j=0;

  for (int i=0; i<cluster.size(); i++) {
    if ( !isMerged(i) ) {
      vector <int> h(2);
      j++;
      h[ID]=(*cluster[i].begin()).second;
      h[NUM]=0;
      for(multimap<int,int, greater<int> >::const_iterator k=cluster[i].begin(); 
	  k!=cluster[i].end();
	  k++) { 
	clust_id[(*k).second]=j;
	h[NUM]++;
      }
      head.push_back(h);
    }
  }
  Nclust=j;

  //mergeCluster();
  if (db->getIO()==2)
    printClusterID(db->getfn(), 1);
}

// clust_id[seq#]= cluster id;
// use kNN to find the most dense point in each cluster
// then, re-cluster all points with the nearest of the centers
void Distance::buildCluster2() {
  int j=0;
  vector <int> real(Nclust);
  for (int i=0; i<cluster.size(); i++) {
    if ( !isMerged(i) ) {
      real[j]=(*(cluster[i].begin()) ).second;
      j++;
    }
  }
  std::cout<<"TEST"<<real;
  Nclust=j;
  for(int x=0;x<num;x++)
    clust_id[x]=findCluster(x, real);

  if (db->getIO()==2)
    printClusterID(db->getfn(), 2);
}

void Distance::reCluster() {
  int d;
  pair <int, int> p;
  clust_id.clear();
  clust_id.resize(num);
  cluster.clear();
  cluster.resize(center.size());
  next.clear();
  next.resize(num);

  for(int i=0; i<num; i++) {
    clust_id[i]=0;
    next[i]=calcCenterDist(i, center[0]);
    for (int j=1; j<center.size();j++) {
      d=calcCenterDist(i, center[j]);
      if (d<next[i]) {
	clust_id[i]=j;
	next[i]=d;
      }
    }
    p.first=i;
    p.second=i;
    cluster[clust_id[i]].insert(p);
  }
}

int Distance::findCenter(int n) {
  int clust=0, d, diff=0, orig;
  vector<int> sum;
  
  sum.resize(num);
  for (int i=0; i<cluster.size(); i++) {
    if ( !isMerged(i) ) {
      multimap<int,int, greater<int> >::iterator j = cluster[i].begin(); 
      multimap<int,int, greater<int> >::iterator k;
      for (;j!=cluster[i].end();j++) {
	k=j;
	k++;
	for (;k!=cluster[i].end();k++) {
	  d=(getDist((*j).second, (*k).second))/100;
	  sum[(*j).second]+=d;
	  sum[(*k).second]+=d;
	}
      }

      if (n>0)
	orig=center[clust];
      j = cluster[i].begin(); 
      if (n==0) 
	center.push_back(sampleIDs[(*j).second]);
      else
	center[clust]=((*j).second);

      d=sum[(*j).second];
      j++;
      for (;j!=cluster[i].end();j++) {
	if (d>sum[(*j).second]) {
	  if (n==0)
	    center[clust]=sampleIDs[(*j).second];
	  else
	    center[clust]=(*j).second;

	  d=sum[(*j).second];
	}
      }
      if (center[clust]!= orig)
	diff++;
      clust++;
    }
  }
#ifndef NOPRNT
  debug_fout<<sum;
  debug_fout<<"Center="<<center;
#endif //NOPRNT
  return ( diff==0 && n>0) ? MAX_LOOP:n;
}

void Distance::profileCluster() {
  int clust=0;
  for (int i=0; i<cluster.size(); i++) {
    if ( !isMerged(i) ) {
      if (order==0) {
	multimap<int,int, greater<int> >::const_iterator k = cluster[i].begin(); 
	db->initProfile((*k).second, clust);
	k++;
	while (k!=cluster[i].end()) {
	  db->alignSeqProfile((*k).second, clust);	
	  k++;
	}
      } else if (order==1) {
	multimap<int,int, greater<int> >::reverse_iterator k = cluster[i].rbegin(); 
	db->initProfile((*k).second, clust);
	k++;
	while (k!=cluster[i].rend()) {
	  db->alignSeqProfile((*k).second, clust);	
	  k++;
	}
      } else if (order==2) {
	map <int, int> idmap;
	pair <int, int> p;

	multimap<int,int, greater<int> >::reverse_iterator k = cluster[i].rbegin(); 
	while (k!=cluster[i].rend()) {
	  p.first=db->getSeqID((*k).second);
	  p.second=(*k).second;
	  idmap.insert(p);
	  k++;
	}

	map<int, int>::const_iterator kk=idmap.begin(); 
	db->initProfile((*kk++).second, clust);
	for (; kk!=idmap.end(); kk++) 
	  db->alignSeqProfile((*kk).second, clust);	
      } else {
	map <int, int, greater<int> > idmap;
	pair <int, int> p;

	multimap<int,int, greater<int> >::reverse_iterator k = cluster[i].rbegin(); 
	while (k!=cluster[i].rend()) {
	  p.first=db->getSeqID((*k).second);
	  p.second=(*k).second;
	  idmap.insert(p);
	  k++;
	}

	map<int, int>::const_iterator kk=idmap.begin(); 
	db->initProfile((*kk++).second, clust);
	for (; kk!=idmap.end(); kk++) 
	  db->alignSeqProfile((*kk).second, clust);	
      }
      clust++;
}
  }

#ifndef NOPRNT
  char file[200];
  strcpy(file, db->getfn().c_str());
  sprintf(file+strlen(file), "%d", kNN);
  std::ofstream fout( strcat(file, ".end") ) ;

  if (db->getIO()==2) {
    db->genPattern(fout);
    printCenterDist(fout);
  }

  fout.close();
#endif //NOPRNT
  printProfile();
}

void Distance::printProfile() {
#ifndef NOPROF
  char file[200];
  strcpy(file, db->getfn().c_str());
  sprintf(file+strlen(file), "%d%d", kNN,order);
  //Postscript ps(file, "Arial-Narrow", 20);
  strcat(file, ".prof");
  std::ofstream fout(file) ;
  //  std::ofstream fout((fn+".nn"+kNN).c_str()) ;

  if (!fout) {
    std::cout <<"ERROR: Can not open file "<<file<<"\n";
    exit(1);
  }
 
  int clust=0;
  for (int i=0; i<cluster.size(); i++) {
    if ( !isMerged(i) ) {
      db->printProfile(clust, fout);	
      multimap<int,int, greater< int > >::const_iterator k=cluster[i].begin(); 
      db->printAlign((*k).second, clust, fout);
      k++;
      while (k!=cluster[i].end()) {
	db->printAlign((*k).second, clust, fout);	
	k++;
      }
      clust++;
    }
  }

#endif //NOPROF
  db->printPS(kNN*10+order);
  db->printProfile(kNN*10+order);
}

void Distance::readClust(string fn, int Nseq) {
  int id, tid, j=0, k=0, freq=1;
  std::ifstream from((fn+".clust").c_str()) ;

  if (!from) {
    std::cout <<"ERROR: Can not open file "<<fn<<".clust\n";
    exit(1);
  }

  num=Nseq;
  clust_id.resize(num);
  from>>Nclust;
  head.resize(Nclust);
  next.resize(num);
  for (int x=0; x<Nclust; x++)
    head[x].resize(2);
  std::cout<<num<<" "<<Nclust<<"\n";
  from>>tid;
  for(int i=0; i<num; i++) {
    from>>clust_id[tid];
    from>>freq;
    id=tid;
    from>>tid;

    if (j==0) {
      head[clust_id[id]][ID]=id;
      head[clust_id[id]][NUM]=freq;      
    }

    if (head[clust_id[id]][NUM]>++j)
      next[id]=tid;
    else {
      next[id]=-1;
      j=0;
    }
  }
}

void Distance::printClust(string fn) {
  std::ofstream to((fn+".clust").c_str()) ;

  if (!to) {
    std::cout <<"ERROR: Can not open file "<<fn<<".clust\n";
    exit(1);
  }
  printClust(to);
}

void Distance::printClust(std::ostream& out) {
  int id;
  out<<Nclust;
  
  for (int i=0;i<Nclust;i++) {
    out<<"\nCluster "<<i<<" : "<<head[i][NUM]<<" : ";
    id=head[i][ID];
    while (id != -1) {
      out<<id<<" ";
      id=next[id];
    }
  }
  out<<"\n";
}

//void Distance::mergeCluster() {
  //  for (int i=0;i<Nclust;i++) {
  // out<<"clust"<<i<<":";
  // for (int j=i+1;j<Nclust;j++) {
  //  if (distance(head[i][ID],head[j][ID])<x
  //  out<<",("<<i<<":"<<head[i][ID]<<" "<<j<<":"<<head[j][ID]<<")="<<distance(head[i][ID],head[j][ID]);
  // }
  // out<<std::endl;
  //}
//}

void Distance::printCenterDist(std::ostream& out) {
  for (int i=0;i<Nclust;i++) {
    out<<"clust"<<i<<":";
    for (int j=0;j<Nclust;j++) {
      out<<",("<<i<<":"<<head[i][ID]<<" "<<j<<":"<<head[j][ID]<<")="<<distance(head[i][ID],head[j][ID]);
    }
    out<<std::endl;
  }
}

