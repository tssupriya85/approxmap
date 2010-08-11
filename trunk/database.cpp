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
#include "database.h"

void Database::readDBRaw(int type) {
  char fnstr[100];
  strcpy(fnstr, (fn+".data").c_str());
  char * p=strrchr(fnstr, '/');

  if (p!=NULL)
    strcpy(fnstr, p+1);

  if (type==0)
    fin.open( fnstr, fstream::in | fstream::binary ) ;
  else if (type==1)
    fin.open( fnstr, fstream::in ) ;

  if (!fin.is_open()) {
    cout<<"Error opening file "<<fnstr<<"\n";
    exit(1);
  }

  time(&start);
};

int Database::readSeqFile(vector <item> &v, int &seqid, int &nextid) {
  int i, j, item, setid=-1,e;
  multiset <int> iset;
  //DO MULTI SET & 9,9 at end
  if (seq_id.size()==0) {
    fin>>i;
    seqid=1;

    while (i!=seqid && !real) {
      seqid++;
      Indel++; // BORROW TO COUNT NULL
      NseqDB++;
    }
    if (real)
      seqid=i;
    nextid=seqid;
  } else {
    i=nextid;
    seqid=nextid;
  }

  while (!fin.eof()) {
    if (i==seqid) {
      fin>>j;
      fin>>item;
      e=corrupt(item);

      if (e>=0)
	item=e;
      if (j!=setid) {
	if (setid>-1) {
	  if (iset.size()>0)
	    v.push_back(iset);
	}
	setid=j;
	iset.clear();
      }
      
      if (iset.count(item)<1 && e>=0)
	iset.insert(item);
    } else {
      if (iset.size()>0)
	v.push_back(iset);
      NseqDB++;
      nextid++;
      while (i!=nextid && !real) {
	nextid++;
	Indel++; // BORROW TO COUNT NULL
	NseqDB++;
      }
    if (real)
      nextid=i;
      
      return FALSE;
    }

    fin>>i;
  }

  if (iset.size()>0)
    v.push_back(iset);
  NseqDB++;
  fin.close();
  return TRUE;
};

int Database::readSeqDB(vector <item> &v, int &seqid, int &nextid) {
  int i;
  seqid++;
  if (src_id<src_db->Nseq) {
    for (i=0+(int)ceil(src_db->sequence[src_id].size()*0.5)*nextid;
	 i<ceil(src_db->sequence[src_id].size()*0.5)+
	   floor(src_db->sequence[src_id].size()*0.5)*nextid;i++) {
      v.push_back(src_db->sequence[src_id][i]);
    }
    freq.push_back(src_db->freq[src_id]);
    seq_id.push_back(src_db->seq_id[src_id]);
  } 
  if (!(nextid==0 && src_db->sequence[src_id].size()==1))
    nextid = (nextid+1) % 2 ;
  if (nextid==0)
    src_id++;
  if (src_id==src_db->Nseq && i==src_db->sequence[src_id-1].size())
    return TRUE;
  else
    return FALSE;
};

void Database::readDB(int flag) {
  FILE * fp;
  char *str, string [10240];
  int i;
  fp = fopen ((fn+".seq").c_str(), "r");
  if (fp == NULL) cout<<"Error opening file "<<fn<<".seq\n";
  else {
    str=fgets (string , 5120 , fp);
    //    sscanf(str, "Nseq=%d Lseq=%d EleType=%d Indel=%d", &Nseq, &Lseq, &EleType, &Indel);
    sscanf(str, "Nseq=%d Lseq=%d EleType=%d Indel=%d", &Nseq, &Lseq, &i, &Indel);

    sequence.clear();
    sequence.resize(Nseq);
    seq_id.resize(Nseq);
    freq.resize(Nseq);
    //WHY? Indel*=1000; 

    //    for (i=0; i<Nseq; i++) 
    //      sequence[i].resize(Lseq);

    i=0;
    str=fgets (string , 10240 , fp);
    while (str != NULL) {
      readSeq(str, i++, flag);
      str=fgets (string , 10240 , fp);
    }
    fclose (fp);
    printDB(std::cout, 10);
  }
}

void Database::readSeq(char *str, int i, int flag=FALSE) {
  set <int> seen;
  int j=0, len;
  char *tok, *tmp, *ptr=strchr(str, '{'); // skip id
  multiset <int> s;

  sscanf(str, "%d :%d :%d", &seq_id[i], &freq[i], &len);
  //  sequence[i].resize(len);
  NseqDB+=freq[i];
  while (ptr != NULL) {
    tmp=ptr+1;
    ptr=strchr(tmp, '{');
    tok=strtok(tmp, "}");
    s.clear();
    readSet(tok, i, s, seen, flag);
    sequence[i].push_back(s);
  }
}

void Database::readSet(char *str, int i, multiset <int> &s, set <int> &seen, int flag=FALSE) {
  char *tok, *ptr=str;
  int e;

  tok=strtok(ptr, ",");
  while ( (tok != NULL) && (*ptr != '}') && (*ptr != ' ') ) {
    
    e=corrupt (atoi(ptr));
    if (e>=0)
      s.insert(e);
    if (flag==TRUE) {
      set <int>::iterator k=seen.find(atoi(ptr));
      if (k==seen.end()) {
	cntItem(atoi(ptr), i);
	seen.insert(atoi(ptr));
      }
    }
    ptr=ptr+strlen(tok)+1;
    tok=strtok(ptr, ",");
  }

  if (s.size()==0)
    s.insert(-1);
}

void Database::readProfile(int k) {
  FILE * fp;
  char *str, string [10240];
  int clust, sz;

  Nseq=-1;

  strcpy(string, getfn().c_str());
  //FIX to include proper order in name
  sprintf(string+strlen(string), "%d0", k);
  strcat(string, ".cprof");
  fp = fopen (string, "r");
  if (fp==NULL) {
    std::cout <<"ERROR: Can not open file "<<fn<<".cprof\n";
    exit(1);
  }

  str=fgets (string , 10240 , fp);
  while(str != NULL) {
    if (str[0]=='c') {
      sscanf(str, "cluster%d;Fsize=%d;", &clust, &sz);
//JS      profile.push_back();
      profile.resize(profile.size() + 1) ;
      NProfile.push_back(sz);
      NseqDB+=sz;
    } else {
      str=strchr(str, '{');
      readProfile(++str, clust);
    }
    str=fgets (string , 10240 , fp);
  }
  fclose (fp);
  
  reverseProfile();

  time(&start);
}

void Database::readProfile(char *str, int clust) {
  char *tok, *ptr=str;
  pair <int, int> p;
  pair <map <int, int>, set<int> > m;
  int maxN=0;
  tok=strtok(ptr, ",");

  while ( (tok != NULL) && (*ptr != '}') && (*ptr != ' ') ) {
    sscanf(ptr, "(%d:%d)", &(p.first), &(p.second));
    m.first.insert(p);
    if (p.second>maxN) 
      maxN=p.second;
    ptr=ptr+strlen(tok)+1;
    tok=strtok(ptr, ",");
  }
  
  m.second.insert(maxN);
  profile[clust].push_front(m);
}

void Database::reverseProfile() {
  list <pair <map <int, int>, set<int> > > p;
  for (int j=0; j<profile.size(); j++) {
    p.clear();
    for (list <pair <map <int, int>, set<int> > > :: iterator i=profile[j].begin();
	 i!=profile[j].end();
	 i++) {
      p.push_front( (*i) );
    }
    profile[j].clear();
    profile[j]=p;
  }
}

int Database::calcSeqProfile(vector <item> &seq, int clust, vector <vector <int> > &trace ) {
  int nprof=profile[clust].size() ,j;
  int nseq=seq.size();
  list <pair <map <int, int>,set<int> > > :: iterator s;
  //ODD SEG FAULT. can not interchange declaration order
  vector <vector <int> > editDist(nseq+1) ;//, nprof+1);
    
  // trace[i][j]=1 diagonal, 2=up, 3=left, 0=done; 
  trace.clear();
  trace.resize(nseq+1);
  //, nprof+1);
  //  vector <vector <int> > indelSum(nseq+1, nprof+1); //keeps track of indel realted cost
  for (int x = 0 ; x < nseq + 1 ; x++)
  {
	  editDist[x].resize(nprof+1) ;
	  trace[x].resize(nprof+1) ;
  }	  

  editDist[0][0]=0;
  trace[0][0]=0;
  //  indelSum[0][0]=0;

  for(int k=0; k<seq.size(); k++) {
    editDist[k+1][0]=editDist[k][0]+indelSet(seq[k], NProfile[clust]);
    trace[k+1][0]=UP;
    //indelSum[0][0]=indelSum[k][0]+1;
  }
   
  j=0;
  for(s=profile[clust].begin(); s!=profile[clust].end(); s++) {
    editDist[0][j+1]=editDist[0][j]+indelProfile( (*s) );    
    trace[0][j+1]=LEFT;
    //    indelSum[0][j+1]=indelSum[0][j]+(*s).second.size();    
    j++;
  }

  for(int i=0; i<seq.size(); i++) {
    j=0;
    for(s=profile[clust].begin(); s!=profile[clust].end(); s++) {
      editDist[i+1][j+1]=
	
	myMin( editDist[i][j]+calcProfDist(seq[i],(*s), NProfile[clust]),
	     editDist[i+1][j]+indelSet(seq[i], NProfile[clust]), 
	     editDist[i][j+1]+indelProfile( (*s) ),
	     trace[i+1][j+1]);  //[i+1][j+i]??
	
      //	myMin( editDist[i][j]+calcProfDist(seq[i],(*s)),
      //     editDist[i+1][j]+indelProfile( (*s) ), 
      //     editDist[i][j+1]+indelSet(seq[i]),
      //     trace[i+1][j+1],
      //     indelSum[i][j], indelSum[i+1][j]+(*s).second.size(), indelSum[i][j+1],
      //     indelSum[i+1][j+1]
      //     );
      j++;
    }
  }

#ifndef NOPRNT
  if (dbug != NULL) {
    if (clust==dbug->cluster && 
    	dbug->Nfrom<=NProfile[clust] && NProfile[clust]<=dbug->Nto){
      char c;
      std::cout<<"seq1="<<":prof="<<clust<<":"<<NProfile[clust]<<":len="<<nprof<<std::endl;
      std::cout<<seq;
      std::cout<<editDist;
      std::cout<<trace;
      std::cin>>c;
    }
  }
#endif //NOPRNT

  return (int)(1.0*editDist[nseq][nprof]/max0(nseq, nprof)*1.0 );
}

int Database::calcWseqDist(int clust1, int clust2) {
  int nprof1=profile[clust1].size(), i;
  int nprof2=profile[clust2].size(), j;
  list <pair <map <int, int>,set<int> > > :: iterator s1, s2;
  //ODD SEG FAULT. can not interchange declaration order
  vector <vector <int> > editDist(nprof1+1) ; //, nprof2+1);
  // trace[i][j]=1 diagonal, 2=up, 3=left, 0=done;
  vector <vector <int> > trace(nprof1+1) ; //, nprof2+1);
  //  vector <vector <int> > indelSum(nseq+1, nprof+1); //keeps track of indel realted cost
  for (int x = 0 ; x < nprof1 + 1 ; x++)
  {
	editDist[x].resize(nprof2+1) ;
	trace[x].resize(nprof2+1) ;
  }

  editDist[0][0]=0;
  trace[0][0]=0;
  //  indelSum[0][0]=0;

  i=0;
  for(s1=profile[clust1].begin(); s1!=profile[clust1].end(); s1++) {
    editDist[i+1][0]=editDist[i][0]+indelProfile( (*s1) );    
    trace[i+1][0]=UP;
    //    indelSum[0][j+1]=indelSum[0][j]+(*s).second.size();    
    i++;
  }

  j=0;
  for(s2=profile[clust2].begin(); s2!=profile[clust2].end(); s2++) {
    editDist[0][j+1]=editDist[0][j]+indelProfile( (*s2) );    
    trace[0][j+1]=LEFT;
    //    indelSum[0][j+1]=indelSum[0][j]+(*s).second.size();    
    j++;
  }

  i=0;
  for(s1=profile[clust1].begin(); s1!=profile[clust1].end(); s1++) {
    j=0;
    for(s2=profile[clust2].begin(); s2!=profile[clust2].end(); s2++) {
      editDist[i+1][j+1]=
	
	myMin( editDist[i][j]+calcProfDist((*s1), NProfile[clust1],
					 (*s2), NProfile[clust2]),
	     editDist[i+1][j]+indelProfile( (*s1) ), 
	     editDist[i][j+1]+indelProfile( (*s2) ),
	     trace[i+1][j+1]);  //[i+1][j+i]??
      j++;
    }
    i++;
  }

  return (int)(1.0*editDist[nprof1][nprof2]/max0(nprof1, nprof2)*1.0 );
}

int Database::getNoise(int n) {
  return n;
};

void Database::printProfile(int k) {
  char file[200];
  strcpy(file, getfn().c_str());
  sprintf(file+strlen(file), "%d", k);
  strcat(file, ".cprof");
  std::ofstream out(file) ;

  if (!out) {
    std::cout <<"ERROR: Can not open file "<<file<<"\n";
    exit(1);
  }

  for (int j=0; j<profile.size(); j++) {
    out<<"cluster"<<j<<";Fsize="<<NProfile[j]<<std::endl;
    for (list <pair <map <int, int>, set<int> > > :: iterator i=profile[j].begin();
	 i!=profile[j].end();
	 i++) {
      out<<"{";
      for(map<int, int>::iterator k=(*i).first.begin(); 
	  k!=(*i).first.end();
	  k++) 
	out<< "("<<(*k).first <<":"<< (*k).second <<"),";
      out<<"}:"<<getProfileSetFreq((*i).second)<<"\n";
    }
  }
}

void Database::printProfile(int clust, std::ostream& out) {
  int cnt=0, cnt2=0, tmp;
  out<<clust<<";s="<<NProfile[clust]<<";1;";
  for (list <pair <map <int, int>, set<int> > > :: iterator i=profile[clust].begin();
       i!=profile[clust].end();
       i++) {
    out<<"{";
    tmp=0;
    for(map<int, int>::iterator k=(*i).first.begin(); 
	k!=(*i).first.end();
	k++) {
      if ( ((int)((*k).second*100.0/(NProfile[clust]*1.0)) >=CutoffVar) 
	   ||((int)((*k).second*100.0/(NseqDB*1.0)) >=CutoffMaxDB) ) {
	out<< (*k).first <<",";
	cnt++;
	tmp++;
      }
    } 
    if (tmp>0)
      cnt2++;
    out<<"} ";
  }
  out<<";"<<cnt2<<";"<<cnt<<std::endl;

  int flag;
  out<<"cluster"<<clust<<";size="<<NProfile[clust]<<";1;";
  for (list <pair <map <int, int>, set<int> > > :: iterator iter=profile[clust].begin();
       iter!=profile[clust].end();
       iter++) {
    flag=0;
    out<<"{";
    for(map<int, int>::iterator p_iter=(*iter).first.begin(); 
	p_iter!=(*iter).first.end();
	p_iter++) {
      if ((int)((*p_iter).second*100.0/(NProfile[clust]*1.0)) >=CutoffVar)
	out<< (*p_iter).first<<",";
      else 
	flag++;
    } 
    out<<"} ";
  }

  out<<std::endl<<"cluster"<<clust<<";precent;1;";
  for (list <pair <map <int, int>, set<int> > > :: iterator c_iter=profile[clust].begin();
       c_iter!=profile[clust].end();
       c_iter++) {
    flag=0;
    out<<"{";
    for(map<int, int>::iterator k_iter=(*c_iter).first.begin(); 
	k_iter!=(*c_iter).first.end();
	k_iter++) {
      if ((int)((*k_iter).second*100.0/(NProfile[clust]*1.0)) >=CutoffVar)
	out<<(int)((*k_iter).second*100.0/(NProfile[clust]*1.0))<<",";
      else 
	flag++;
    } 
    if (flag>0)
      out<<"("<<flag<<")";
    out<<"} ";
  }
  out<<std::endl;
}

void Database::printPS(int k) {
  char file[200];
  set <int> s;
  int Nnull=0, Nother=0, Nfull=0, Npart=0, Nspur=0, miss=0, allmiss=0, 
    noise=0, Nnoise=0, tmp, blen=0;
  float rmiss, wrecall=0, wrecall2=0;
  vector<float> pblen, sumPblen;

  strcpy(file, getfn().c_str());
  if (CutoffPattern!=50)
    sprintf(file+strlen(file), "%dc%f", k, CutoffPattern);
  else
    sprintf(file+strlen(file), "%d", k);
  Postscript ps(file, "Helvetica-Narrow", 20);

  //FIX  readPat();
  //  findPattern();

  ps.print("Cluster Support= [Pattern=",1);
  ps.print(CutoffPattern, 1);
  ps.print("% : Variation=",1);
  ps.print(CutoffVar, 1);
  ps.print("%]; Database Support= [Min= ",1);
  ps.print(CutoffMinDB, 1);
  ps.print(" seq: Max=",1);
  ps.print(CutoffMaxDB, 1);
  ps.print("%]", 1);
  //ps.print("noise:type",1);
  ps.newline();

  consensus.resize(profile.size());
  PatternLen.resize(profile.size());
  for (int j=0; j<profile.size(); j++) {
    printPS(j, &ps);
  }
  time_t end;
  time(&end);
  cout<<"Run Time="<<difftime(end, start)<<endl;
  ps.print("TOTAL LEN=",1);
  ps.print(getPatternLen(),1);

  ps.newline();
  ps.newline();
}

int Database::genPattern(int clust, vector <item> &pat) {
  int cnt=0, len=0;
  multiset <int> iset;

  list <pair <map <int, int>, set<int> > > :: iterator temp = profile[clust].begin() ;
  for (list <pair <map <int, int>, set<int> > > :: iterator i=profile[clust].begin();
       i!=profile[clust].end();
       i++) {

    cnt=0;
    iset.clear();
    for(map<int, int>::iterator k=(*i).first.begin(); 
	k!=(*i).first.end();
	k++) {
      if ( (((*k).second*100.0/(NProfile[clust]*1.0)) >=CutoffPattern) 
	   && ((int)((*k).second >=CutoffMinDB )) ) {
	cnt++;
	iset.insert((*k).first);
      }
    } 
    if (cnt>0) 
      pat.push_back(iset);

    len+=cnt;
  }

  return len;
};

void Database::printPS(int clust, Postscript *ps) {
  char str[200];
  int cnt=0;
  //  strcpy(str, fn.c_str());
  //  sprintf(str+strlen(str), "%s%d", fn, kNN);
  //  sprintf(str, "%s%d", fn, kNN);

  sprintf(str, "cluster=%d size=%d", clust, NProfile[clust]);
  ps->print(str, .5);
  ps->print("  =<100:", 1);
  ps->print("85:", .85);
  ps->print("70:", .7);
  ps->print("50:", .5);
  ps->print("35:", .35);
  ps->print("20>", .2);
  ps->newline();
  
  ps->print("<u>PATTERN:",1);

  PatternLen[clust]=genPattern(clust, consensus[clust]);
  printPatPS(consensus[clust], ps);

  ps->print("=",1);
    //ps->newEle();

  ps->print(PatternLen[clust],1);
  ps->print("</u>",1);
  ps->newline();

  for (list <pair <map <int, int>, set<int> > > :: iterator iter =profile[clust].begin();
       iter!=profile[clust].end();
       iter++) {
    cnt=0;
    for(map<int, int>::iterator k=(*iter).first.begin(); 
	k!=(*iter).first.end();
	k++) {
      if ( ((int)((*k).second*100.0/(NProfile[clust]*1.0)) >=CutoffVar) 
	   ||((int)((*k).second*100.0/(NseqDB*1.0)) >=CutoffMaxDB) ) {
	cnt++;
	if (cnt==1)
	  ps->print("{", 1);
	ps->print( (*k).first, ((*k).second*1.0)/(NProfile[clust]*1.0) );
      }
    } 
    if (cnt>0)
      ps->print("}", 1);
    //ps->newEle();
  }
  ps->newline();
}

void Database::printAlign(int seq, int clust, std::ostream& out=std::cout) {
  int j=0;
  out<<seq<<";"<<seq_id[seq]<<";"<<freq[seq]<<";";
  for (list <pair <map <int, int>, set<int> > > :: iterator i=profile[clust].begin();
       i!=profile[clust].end();
       i++) {
    set <int> ::iterator k=(*i).second.find(seq);
    if (k!= (*i).second.end() ) {
      out<<sequence[seq][j];
      j++;
    }
    else
      out<<"{} ";
  }
  out<<std::endl;
}

void Database::debugProfile(int id, int clust) {
  char c;
  std::cout<<"seq"<<id<<":"<<sequence[id];
  std::cout<<"cluster="<<clust<<" "<<std::endl;
  std::cout<<profile[clust];
  std::cin>> c;
};

void Database::initProfile(int seq, int clust) {
  pair <map<int, int>, set <int> > pitem;
  list <pair <map<int, int>, set <int> > >l;

  pitem.second.insert(seq);
  if (profile.size()!=clust) {
    std::cout<<"ERROR: Database::initProfile-cluster id is out of range "<<clust<<"\n";
    exit(1);
  }

  // profile.push_back();
  profile.push_back(l) ;
  NProfile.push_back(freq[seq]);
  for (int i=sequence[seq].size()-1; i>=0 ;i--) {
    pitem.first.clear();
    mset2Map(sequence[seq][i], pitem.first, freq[seq]); 
    profile[clust].push_front(pitem);
  }
  //debugProfile(seq,clust);  
}

//insert seq1 to profile clust using trace 
void Database::alignSeqProfile(vector <vector <int> > &trace, int seq1 , int clust) {
  list <pair <map <int, int>, set <int> > >::iterator k=profile[clust].begin();
  pair <map <int, int>, set <int> > mset;
  int j=0;

  vector <int> op;
  traceOp(trace, op);
  for (int i=op.size()-1; i>=0 ;i--) {
    mset.first.clear();
    mset.second.clear();
    switch(op[i]) {
    case DIAGONAL:
      insertProfile (sequence[seq1][j], (*k), seq1);
      j++;
      k++;
      break;
    case LEFT:
      k++;
      break;
    case UP:
      insertProfile(sequence[seq1][j], mset, seq1);
      profile[clust].insert(k, mset);
      j++;
      break;
    default:
      std::cout<<"ERROR: setProfile trace("<<i<<","<<j<<")="<<trace[i][j]<<"\n";
      exit(1);
      break;
    }
  }
  //debugProfile(seq1,clust);  
}

void Database::genPattern(std::ostream& out=std::cout) {
  int d;

  for (int i=0; i<profile.size(); i++) {
    for (int j=0; j<profile.size(); j++) {
      d=calcWseqDist(i, j);
      out<<",("<<i<<" "<<j<<")="<<d<<" ";
    }
    out<<std::endl;
  }
};

int Database::calcProfDist(multiset <int> &mset, pair <map <int, int>, 
			   set <int> > &m, int nprof) { 
  double ret=0;
  int sum=0;
  multiset <int> :: iterator j=mset.begin();
  map <int, int>::iterator i=m.first.begin();
  if (EleType==UNIFORM_NOMINAL) { // size of set_symmetric difference
    while (j!=mset.end() && i!=m.first.end()) {
      if ( (*i).first == (*j) ) {
	ret+=(*i).second;
	sum+=(*i).second;
	i++; 
	j++;
      } else if ( (*i).first < (*j) ) {
	sum+=(*i).second;
	i++;
      } else 
	j++;
    }
    while ( i!=m.first.end()) {
      sum+=(*i).second;
      i++;
    }

    int sz=getProfileSetFreq(m.second);
    int inter=(int)ret;
    //    ret=  ( ((mset.size()+m.first.size())*sz-2*ret)*1.0/
    //	  ((mset.size()+m.first.size())*sz*1.0) );
    ret=  ( (sum+mset.size()*sz-2*ret)*1.0/
	    (sum+mset.size()*sz*1.0) );

    if (dbug != NULL) {
      if (dbug->Nfrom<=nprof && nprof<=dbug->Nto) {// && mset.size()==4) {
	std::cout<<"sum="<<sum<<":msetsize="<<mset.size()<<":inter="<<inter<<":sz="<<sz<<":nprof="<<nprof<<"ans=";
	std::cout<<(ret*sz*1.0+1.0*(nprof-sz))/(nprof*1.0) <<std::endl;
      }
    }

    ret=(ret*sz*1.0+1.0*(nprof-sz))/(nprof*1.0);
  }

  return (int) (ret*DECPOINT) ;
}

int Database::calcProfDist(pair <map <int, int>, set <int> > &m1, int nprof1,
			   pair <map <int, int>, set <int> > &m2, int nprof2) { 
  double ret1=0, ret2=0, ret=0;
  int sum1=0, sum2=0;
  map <int, int>::iterator i=m1.first.begin();
  map <int, int>::iterator j=m2.first.begin();

  if (EleType==UNIFORM_NOMINAL) { // size of set_symmetric difference

    while (i!=m1.first.end() && j!=m2.first.end()) {
      if ( (*i).first == (*j).first ) {
	ret1+=(*i).second;
	ret2+=(*j).second;

	sum1+=(*i).second;
	sum2+=(*j).second;
	i++; 
	j++;
      } else if ( (*i).first < (*j).first ) {
	sum1+=(*i).second;
	i++;
      } else {
	sum2+=(*j).second;
	j++;
      }
    }

    while ( i!=m1.first.end()) {
      sum1+=(*i).second;
      i++;
    }

    while ( j!=m2.first.end()) {
      sum2+=(*j).second;
      j++;
    }

    int sz1=getProfileSetFreq(m1.second);
    int sz2=getProfileSetFreq(m2.second);
    //    ret=  ( ((mset.size()+m.first.size())*sz-2*ret)*1.0/
    //	  ((mset.size()+m.first.size())*sz*1.0) );
    ret=  ( (sum1*sz2+sum2*sz1-ret1*sz2-ret2*sz1)*1.0/
	    ((sum1*sz2+sum2*sz1)*1.0) );
 
    int diff=(nprof1-sz1)-(nprof2-sz2);
    if (diff>0) 
      diff*=sz2;
    else 
      diff*=(-sz1);
    
    ret=(ret*sz1*sz2*1.0+1.0*diff)/((sz1*sz2+diff)*1.0);

    if (nprof1==nprof2) {
      //std::cout<<"ck="<<sum1<<"sum="<<sum2<<"ret="<<ret<<std::endl;
      //      std::cout<<"sz="<<sz1<<"sz2="<<sz2<<"nprof1="<<nprof1<<"nprof2="<<nprof2<<std::endl;
    }
  }
  return (int) (ret*DECPOINT) ;
}

// FIX =multiset not done;
int Database::calcSetDist(multiset <int> &set1, multiset <int> &set2) { 
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
    }*/
  return -1;
}

//Cnt item n, in seq i;
void Database::cntItem(int n, int i) {
  map<int,int>::iterator k=items.find(n); 
  if ( k!=items.end() )
    (*k).second=(*k).second+freq[i];
  else {
    pair <int, int> p(n,freq[i]);
    items.insert(p);
  } 
}

void Database::cntItem() {
  int flag=FALSE;
  if (freq.size()==0) {
    freq.resize(Nseq);
    flag=TRUE;
  }

  for (int i=0;i<Nseq;i++) {
    if (flag)
      freq[i]=1;
    for (int j=0;j<sequence[i].size();j++) {
      item::iterator k;
      for (k=sequence[i][j].begin();k!=sequence[i][j].end();k++) 
	cntItem(*k, freq[i]);
    }
  }
};

void Database::getLitems(vector< set <int> >&cand, vector< set <int> >&candele, int sup,  vector <set <int> > &v,  vector < set <int> > &vele, vector <int> &sv) {
  set <int> r;
  vector <int> cnt(cand.size());
  vector <int> flag(cand.size());
  int n=0, num=0;

  for (int i=0; i<Nseq;i++) {
    for (int x=0;x<cand.size() && num<cand.size();x++) {
      n=0;
      if (flag[x] !=2 )
	flag[x]=0;
    }
    for (int j=0; j<sequence[i].size() && (num+n)<cand.size() ; j++) {
      for (int k=0;k<cand.size(); k++) {
	if (flag[k]<1) {
	  r.clear();
	  set_intersection(sequence[i][j].begin(), sequence[i][j].end(),
			   cand[k].begin(), cand[k].end(),
			   inserter(r, r.begin()) );
	  if (r.size()==cand[k].size()) {
	    cnt[k]=cnt[k]+freq[i];
	    if (cnt[k]>=sup) {
	      flag[k]=2;
	      num++;
	    } else flag[k]=1;
	    n++;
	  }
	}
      }
    }
  }

  for (int y=0; y<cand.size(); y++)
    if (cnt[y]>=sup) {
      v.push_back(cand[y]);
      vele.push_back(candele[y]);
      sv.push_back(cnt[y]);
      for (set <int>::iterator j=candele[y].begin();
	   j!=candele[y].end();
	   j++)
	if (vele[*j].size()>0) {
	  set_union(vele[vele.size()-1].begin(), vele[vele.size()-1].end(),
		    vele[*j].begin(), vele[*j].end(),
		    inserter( vele[vele.size()-1], vele[vele.size()-1].begin()) );
	}
    }
};

void Database::transform(vector< set <int> >&ele, vector <vector <set <int> > > &db, vector< vector <int> >&Lseqs, vector <int> &sv, int sup ) {
  set <int> s;
  vector <set <int> > v;
  vector <vector < set <int> > > cnt(ele.size()) ; //, ele.size());
  set <int> buf;
  vector <int> seq(2);
  int c;

  for (int xx = 0 ; xx < ele.size() ; xx++)
  {
	  cnt[xx].resize(ele.size()) ;
  }

  for (int i=0;i<Nseq; i++) {
    v.clear();
    buf.clear();
    for (int j=0;j<sequence[i].size();j++) {
      s.clear();
      for (int k=0;k<ele.size();k++) {
	if (includes(sequence[i][j].begin(), sequence[i][j].end(),
		     ele[k].begin(), ele[k].end()) ) 
	  s.insert(k);
      }
      if (s.size()>0) {
	v.push_back(s);
	for(set<int>::const_iterator k=s.begin(); 
	    k!=s.end();
	    k++)
	  for(set<int>::const_iterator l=buf.begin(); 
	      l!=buf.end();
	      l++) {
	    cnt[(*l)][(*k)].insert(i);
	  }
	for(set<int>::const_iterator k_iter=s.begin(); 
	    k_iter!=s.end();
	    k_iter++)
	  buf.insert(*k_iter);
      }
    }
    //    if (v.size()>0) 
    //should not do because vector Freq have to be mapped properly
    db.push_back(v);
  }

  for (int x=0;x<cnt.size();x++)
    for (int j=0;j<cnt.size();j++) {
      c=0;
      for(set<int>::const_iterator l=cnt[x][j].begin(); 
	  l!=cnt[x][j].end();
	  l++) 
	c+=freq[(*l)];
      if (c>=sup) {
	seq[0]=x;
	seq[1]=j;
	Lseqs.push_back(seq);
	sv.push_back(c);
      }
    }
};

void Database::realign(int kNN) {
  map <int, int> idmap;
  pair <int, int> p;

  for (int i=0;i<sequence.size();i++) {
    p.first=seq_id[i];
    p.second=i;
    idmap.insert(p);
  }

  int clust=0;
  initProfile(0, clust);
  for (int i=1; i<sequence.size(); i++) 
    alignSeqProfile(i, clust);	
  clust++;

  initProfile(sequence.size()-1, clust);
  for (int i=sequence.size()-2; i>=0; i--) 
    alignSeqProfile(i, clust);	
  clust++;

  map<int, int>::const_iterator k=idmap.begin(); 
  initProfile((*k++).second, clust);
  for (; k!=idmap.end(); k++) 
    alignSeqProfile((*k).second, clust);	
  clust++;

  map<int, int>::reverse_iterator rk=idmap.rbegin(); 
  initProfile((*rk++).second, clust);
  for (; rk!=idmap.rend(); rk++) 
    alignSeqProfile((*rk).second, clust);	

  char file[200];
  strcpy(file, getfn().c_str());
  sprintf(file+strlen(file), "%d", kNN);
  //Postscript ps(file, "Arial-Narrow", 20);
  strcat(file, ".prof");
  std::ofstream fout(file) ;
  //  std::ofstream fout((fn+".nn"+kNN).c_str()) ;

  if (!fout) {
    std::cout <<"ERROR: Can not open file "<<file<<"\n";
    exit(1);
  }
 
  clust=0;
  printProfile(clust, fout);	
  for (int i=0; i<sequence.size(); i++) 
    printAlign(i, clust, fout);
  clust++;

  printProfile(clust, fout);	
  for (int i=sequence.size()-1; i>=0; i--) 
    printAlign(i, clust, fout);
  clust++;

  k=idmap.begin(); 
  printProfile(clust, fout);	
  for (; k!=idmap.end(); k++) 
    printAlign((*k).second, clust, fout);
  clust++;

  rk=idmap.rbegin(); 
  printProfile(clust, fout);	
  for (; rk!=idmap.rend(); rk++) 
    printAlign((*rk).second, clust, fout);

  printPS(kNN);
  printProfile(kNN);
}

int Database::corrupt(int ele) {
  UniformDist uni; // corrupting ele
  double prob=uni()*100;
  //  cout<<"prob="<<prob<<":"<<ele<<":"<<noiseLevel<<endl;
  if (floor(prob)<=100-noiseLevel)
    return ele;

  int res=(int)floor( (1.0*(prob-(100-noiseLevel)-0.001)/
		       (1.0*noiseLevel/Nitem) ) );
	
  return (ele==res) ? -1 : res;
}
