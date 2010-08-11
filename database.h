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

#ifndef _DATABASE_H_
#define _DATABASE_H_
#include <string.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <time.h>
#include <iomanip>
using namespace std;

#include "utility.h"
#include "postscript.h"
#include "distribution.h"

class Debug {
 public:
  int cluster;
  int Nfrom;
  int Nto;

  Debug(int c, int f, int t) : cluster(c), Nfrom(f), Nto(t) {};
  ~Debug();
};

class Database {
  map <int, int> items;
  int real;
  int maxL;

  vector <vector <item> > sequence;  //actually seq of sets
  vector <int> seq_id;  //actually seq of sets
  vector <int> freq; // frequencies of each sequences of sets
  vector <int> cluster_id; // cluster id for each seq of sets

  Database *src_db;
  int src_id;

  //  vector <list <pair <map <int, int>, int> > > profile;  // flipped
  vector <list <pair <map <int, int>, set<int> > > > profile;  // flipped
  vector <int> NProfile; // total size of each profile
  vector <vector <item> > consensus;
  int Nseq; // total # of sequences
  int NseqDB; // total # of sequences in whole DB including the freqs
  int Lseq; // length of seq
  int Nitem; // # of unique items
  int noiseLevel;
  //  int EleType; // set element type
  int Indel; // INDEL cost 
  int Wsize; // weight of size of set on indel
  int CutoffVar;  //cutoff for variations in percent
  float CutoffPattern; //cutoff for pattern in percent of cluster
  int CutoffMinDB; //cutoff for pattern in # (not percent) of whole DB
  int CutoffMaxDB; //cutoff for pattern in percent of whole DB

  int io;
  time_t start;

  vector <int> PatternLen; // total pattern length
  // if EleType=NOMINAL_UNIFORM, INDEL=normalization factor (to compare w/ other data types
  std::ifstream fin;
  string fn;
  Debug *dbug;

  int calcSetDist(multiset <int> &set1, multiset <int> &set2);
  int calcProfDist(multiset <int> &mset, pair <map <int, int>, set <int> > &m, int nprof);
  int calcProfDist(pair <map <int, int>, set <int> > &m1, int nprof1, 
		   pair <map <int, int>, set <int> > &m2, int nprof2);
  int calcSetDistOld(multiset <int> &set1, multiset <int> &set2); 
  int indelSet(multiset <int> &set, int nprof);
  int indelProfile(pair <map <int, int>, set <int> > &m);
  void mset2Map(multiset <int>& mset, map<int, int>& m, int i);
  
  void insertProfile(item& mset, pair<map <int, int>, set <int> > &m, int seq);
  void alignSeqProfile(vector <vector <int> > &trace, int seq1, int clust) ;
  void inProfile(item& mset, pair<map <int, int>, set <int> > &m, int cutoff, vector<int> &ret);

  void debugProfile(int id, int clust); 

  void cleanup() {
    for (int i=0; i<Nseq; i++) 
      for (int j=0; j<Lseq; j++)
	sequence[i][j].erase(NULL_ELE);
  };

public:
  Database(char *f=NULL, Debug *d=NULL) :
    fn(f), dbug(d)    {
    NseqDB=0;
    Nseq=0;
    CutoffVar=20;
    CutoffPattern=50;
    CutoffMinDB=10;
    Nitem=0;
    noiseLevel=1;
    real=FALSE;
    src_db=NULL;
    src_id=0;
    maxL=0;
    //    CutoffMaxDB=numeric_limits<int>::max() ;
    CutoffMaxDB=10;
    io=TRUE;
  };

  ~Database() {};

  void readDBRaw(int type=1);
  void readDBRaw(Database *src) {src_db=src; }; 
  int readSeq(vector <item> &v, int& seqid, int& nextid) {
    if (src_db==NULL)
      return readSeqFile(v, seqid, nextid);
    else 
      return readSeqDB(v, seqid, nextid);
  };
  int readSeqFile(vector <item> &v, int& seqid, int& nextid);
  int readSeqDB(vector <item> &v, int& seqid, int& nextid);
  void insertSeq(vector <item> &v, int id) {
    sequence.push_back(v);
    if (src_db==NULL) {
      freq.push_back(1);
      seq_id.push_back(id);
    }

    Nseq++;
    if (v.size()==1)
      maxL++;
  };

  int postSeq() {
    /*    if (Indel>0) {
      vector <item> v;
      sequence.push_back(v);
      freq.push_back(Indel);
      seq_id.push_back(-1);
      Nseq++;
    }
    */
    Lseq=0;
    //    EleType=0;
    Indel=1;
    
    cout<<sequence.size()<<"=";
    printDB(std::cout, 10);
    return Nseq;
  };

  void incFreq(int i) { freq[i]++; };
  void rmSeq(int i) {//NOT NEEDED
    seq_id[Nseq-1]=seq_id[Nseq];
    Nseq--;
    freq[i]++;
  };

  void readDB(int flag=FALSE);
  void readSeq(char *str, int i, int flag);
  void readSet(char *str, int i, multiset <int> &s, set <int> & seen, int flag);
  int corrupt(int ele);
  void readProfile(int k);
  void readProfile(char *str, int clust);
  void reverseProfile();
  int calcSeqDist(int seq1, int seq2, int clust=-1) {
    return seqDist(sequence[seq1], sequence[seq2]);
  }

  int calcSeqDist(vector <item> &seq1, int seq2, int min, 
		  vector <vector <int> > &save, int clust=-1) {
    return seqDist2(seq1, sequence[seq2], save, min);
  }

  int calcSeqProfile (vector <item> &seq, int clust, vector <vector <int> > &trace );
  void alignSeqProfile (int seq1, int clust) {
    vector <vector <int> > trace;
    calcSeqProfile(sequence[seq1], clust, trace);
    NProfile[clust]+=freq[seq1];
    alignSeqProfile(trace, seq1, clust);
  } ;
  int calcWseqDist (int clust1, int clust2);
  int getNseq() { return Nseq; };
  int getMaxL() { return (int) (100.0*maxL/Nseq); };
  int getNseqDB() { return NseqDB; };
  int getSeqID(int i) { return seq_id[i]; };
  string getfn() { return fn; };
  int getFreq(int i) { return freq[i]; };

  void cntItem(int n, int i);
  void cntItem(); // cnt all Items in DB;
  void getLitems(int sup, vector <set <int> > &v, vector <int> &sv);
  void getLitems(vector< set <int> > &cand);
  void getLitems(vector< set <int> > &cand, vector< set <int> > &candele, int sup,  vector <set <int> > &v,  vector <set <int> > &vele, vector <int> &sv);
  void transform(vector< set <int> >&ele, vector <vector <set <int> > > &db, vector< vector <int> >&Lseqs, vector <int> &sv, int sup );

  void setIO(int i) { io=i; };
  int getIO() { return io; };
  void setReal(int n) { real=n; };
  void setNseqDB(int n) { NseqDB=n; };
  void setDB(vector <vector <item> > &d) { sequence=d; Nseq=sequence.size(); };
  void setNitem(int n) { Nitem=n; };
  void chgFile(char c, char *n) {
      string s;
      fn=s+c+n+"/"+fn;
  };
  void setNoiseLevel (char *n, char c='x') { 
    noiseLevel=atoi(n); 
    if (c!='x') 
      chgFile(c, n);
  };

  void setCutoffPattern(float c) { CutoffPattern=c; };
  void setCutoffMinDB(int c) { CutoffMinDB=c; };
  void setCutoffMaxDB(int c) { CutoffMaxDB=c; };
  void setCutoffVar(int c) { CutoffVar=c; };
  void initProfile(int seq, int clust);
  void printProfile(int clust, std::ostream& out);
  void printProfile(int k);
  void printPS(int k);
  void printPS(int clust, Postscript *ps);
  int getPatternLen();
  int genPattern(int clust, vector <item> & pat);
  void genPattern(vector <vector <item> > & pat, vector <int> &len , vector <int> &sz) {
    pat.resize(profile.size());
    len.resize(profile.size());
    sz.resize(profile.size());
    for (int i=0;i<pat.size(); i++) {
      sz[i]=NProfile[i];
      len[i]=genPattern(i, pat[i]);
    }
  };

  void genPattern(std::ostream& out);
  int getNProfile(int i) { return NProfile[i];};
  int getProfileSetFreq(set <int> s);
  int getNoise(int n);
  void realign(int kNN);

  void printAlign(int seq, int clust, std::ostream& out);
  void printDB(std::ostream& out) { printDB(out, Nseq); } ; 

  void printDB() {
    std::ofstream fout((fn+".data").c_str()) ;
    for (int i=0;i<sequence.size();i++)
      for (int l=0;l<freq[i];l++)
	for (int j=0;j<sequence[i].size();j++)
	  for (multiset <int>::iterator k=sequence[i][j].begin();
	       k!=sequence[i][j].end();
	       k++) 
	    fout<<i<<l<<" "<<j<<" "<<(*k)<<std::endl;
  }

  void saveDB() {
    std::ofstream fout((fn+".seq").c_str()) ;
    printDB(fout);
  };

  void printDB(std::ostream& out, int num) {
    out<<"N="<<num<<" (Nseq="<<Nseq<<")\n";
    for (int i=0; i<num && i<Nseq; i++) {
      out<<i<<":"<<seq_id[i]<<":"<<freq[i]<<":";
      printSeq(out, i);
    }
  }; 

  void printPatPS(vector <item> &pat, Postscript *ps) {
    char str[5120];
    std::ostringstream sout ;

    sout<<pat;;
    strcpy(str, sout.str().c_str());
    ps->print(str, 1);
  };

  void printSeq(std::ostream& out, int i) {
      out<<sequence[i];
  }

  void printItems(std::ostream& out) { out<<items<<std::endl ;};
};

inline void Database::mset2Map(multiset <int>& mset, map<int, int>& m, int i) {
  pair <int, int> p;
  int item;
  for(multiset<int>::iterator k=mset.begin(); 
      k!=mset.end();
      k++) {
    item=(*k);
    map<int, int>::iterator j=m.find( item );
    while (j!=m.end() ) {
      item=MAX_NITEM+item;
      j=m.find(item);
    }

    p.first=(item);
    p.second=i;
    m.insert(p);
  }
}

inline int Database::getProfileSetFreq(set <int> s){
  int ret=0;
  if (Nseq==-1)
    return (*s.begin());

  for(set<int>::iterator k=s.begin(); 
      k!=s.end();
      k++) 
    ret+=freq[*k];
  return ret;
};

inline void Database::insertProfile(item& mset, pair<map <int, int>, set<int> > &m, int seq) {
  pair <int, int> p;
  int item, cnt;

  m.second.insert(seq);
  for(multiset<int>::iterator k=mset.begin(); 
      k!=mset.end();
      k++) {
    cnt=mset.count( (*k) );
    for (int j=0; j< cnt; j++) {
      item=(*k)+MAX_NITEM*j;
      map<int, int>::iterator it=m.first.find( item );
      if (it!=m.first.end() ) 
	(*it).second+=freq[seq];
      else {
	p.first=item;
	p.second=freq[seq];
	m.first.insert(p);
      }
      if (j>0)
	k++;
    }
  }
  //std::cout<<"insert: "<<mset;
  //std::cout<<"into : "<<m<<std::endl;
}

inline void Database::inProfile(item& mset, pair<map <int, int>, set<int> > &m, int cutoff, vector <int> &ret) {
  pair <int, int> p;
  int item, cnt;

  for(multiset<int>::iterator k=mset.begin(); 
      k!=mset.end();
      k++) {
    cnt=mset.count( (*k) );
    for (int j=0; j< cnt; j++) {
      item=(*k)+MAX_NITEM*j;
      map<int, int>::iterator it=m.first.find( item );
      if (it!=m.first.end()) {
	ret[0]++;
	if ((*it).second>= cutoff &&(*it).second>= CutoffMinDB) 
	  ret[1]++;
      }
      //else 
      if (j>0)
	k++;
    }
  }

  for(map<int, int>::iterator k=m.first.begin(); 
      k!=m.first.end();
      k++) {
    if ((*k).second>=cutoff && (*k).second>=CutoffMinDB){
      multiset<int>::iterator it=mset.find( (*k).first );
      if (it==mset.end())
	ret[2]++;
    }
  }
  //std::cout<<"insert: "<<mset;
  //std::cout<<"into : "<<m<<std::endl;
}

inline int Database::indelProfile(pair<map <int, int>, set<int> > &m) {
  int ret=0;
  if (EleType==UNIFORM_NOMINAL) // size of set_symmetric difference
    ret=1*DECPOINT;
  return ret;
}

inline int Database::indelSet(multiset<int> &mset, int nprof=1) { 
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
      }*/

  return -1;

}

inline int Database::getPatternLen() { 
  int ret=0; 
  for (int i=0; i<PatternLen.size(); i++) 
    ret+=PatternLen[i]; 
  return ret; 
};

inline void Database::getLitems(int sup, vector <set <int> > &v, vector <int> &sv) {
  set <int> s;
  for (map<int,int> ::iterator i=items.begin();
       i!= items.end();
       i++) {
    if ((*i).second>=sup) {
      s.clear();
      s.insert( (*i).first) ;
      v.push_back(s);
      sv.push_back((*i).second);      
    }
  }
};

#endif //_DATABASE_H_

















