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

#include <stdlib.h>
#include "utility.h"
#include "database.h"
#include "distance.h"

int main(int argc, char* argv[]) {
  int cmd, n=0;

  if (argc < 2 ) {
    std::cout<<"usage: "<<argv[0]<<" fn -data kNN [-noise noise(%) Nitem]\n";
    std::cout<<"usage2: "<<argv[0]<<" fn -sample/-hash kNN [sample(%)]\n";
    std::cout<<"usage2: "<<argv[0]<<" fn -order kNN 0-3(order) 0=dense 1=reverse 2=id 3=reverse id\n";
    std::cout<<"usage2: "<<argv[0]<<" fn -f(.seq)/-S(.data) kNN [-noise noise(%) Nitem]\n";
    /*
    std::cout<<"================\n";
    std::cout<<"usage2: "<<argv[0]<<" fn -local kNN [-noise noise (%) Nitem Nseq (real data)]\n";
    std::cout<<"usage2: "<<argv[0]<<" fn -version kNN [-noise noise (%) Nitem Nseq (real data)]\n";
    std::cout<<"usage2: "<<argv[0]<<" fn [-cut kNN CutoffPattern(=50%) CutoffMinDB(=10) CutoffMaxDB(=100) CutoffVariation(=20%)] Nseq (real data)\n";
    std::cout<<"usage4: "<<argv[0]<<" fn [-auto kNN 0(I/O) 0(binary) noise Nitem ]\n";
    std::cout<<"usage4: "<<argv[0]<<" fn [-auto kNN 0(I/O) 0(binary) 0-4(order)]\n";
    std::cout<<"usage4: "<<argv[0]<<" fn [-noise kNN 0(I/O) 0(binary) noise Nitem ]\n";
    std::cout<<"usage4: "<<argv[0]<<" fn [-reorder kNN NseqDB raw/seq]\n";
    std::cout<<"usage3: "<<argv[0]<<" fn [-debug kNN cluster Nfrom Nto\n";
    std::cout<<"usage3: "<<argv[0]<<" fn - outfn\n";
    std::cout<<"Alphabet Type: UNIFORM_NOMINAL="<<UNIFORM_NOMINAL;
    std::cout<<" WEIGHTED_NOMINAL="<<WEIGHTED_NOMINAL;
    std::cout<<" INTERVAL="<<INTERVAL<<" RATIO="<<RATIO<<"\n" ;
    */
    exit(1);
  } 

  Debug *bug=NULL;
  Database *db=new Database(argv[1], bug);
  Distance *dist=new Distance(NULL);
  dist->setDB(db);
  dist->setkNN(atoi(argv[3]));

  if (argc>5) {
    if (argv[4][1]=='n') {
      db->setNoiseLevel(argv[5], argv[2][1]);
      db->setNitem(atoi(argv[6]));
    }
  };
    
  if (argv[2][1]=='d' || argv[2][1]=='o' 
      || argv[2][1]=='l' || argv[2][1]=='f' || argv[2][1]=='S' ) { //data
    if (argv[2][1]=='o')
      dist->setOrder(atoi(argv[4]));

    db->readDBRaw(1);
    db->setReal(TRUE);
    
    // TODO: to make it work with tiny example;
    if (db->getNseq()<=10) {
      db->setCutoffMinDB(1);
      db->setCutoffMaxDB(50);
    }

    dist->calcDistStream(argv[1]);
    if (argv[2][1]=='f') {
      db->saveDB();
      exit(1);
    } else if (argv[2][1]=='S') {
      db->printDB();
      exit(1);
    }

    dist->kNNCluster();
    dist->profileCluster();
    if (argv[2][1]=='d' || argv[2][1]=='o' )
      exit(1);
  }

  else if (argv[2][1]=='s' || argv[2][1]=='h' ) { //sample hash
    db->readDBRaw(1);
    db->setReal(TRUE);
    if (argc>4) {
      dist->setSample(atoi(argv[4]));
      db->chgFile(argv[2][1], argv[4]);
    }
    if (argv[2][1]=='h')  //hash
      dist->setHash(TRUE);
    dist->calcDistStreamSample(argv[1]);
    dist->profileCluster();
    exit(1);
  }

  else if (argv[2][1]=='v') { //old version
    db->readDBRaw(1);
    db->setReal(TRUE);

    dist->calcDistStream1(argv[1]);
    dist->kNNCluster();
    dist->profileCluster();
    exit(1);
  }

  if (argv[2][1]=='l') { //local
    Database *db_orig=db;
    Database *db_new=NULL;
    int i=1;
    char fn[100], fn_orig[100];
    

    if (argc>5) {
      if (argv[4][1]=='n') 
	sprintf(fn_orig, "%c%s/", argv[2][1], argv[5]);
    } else 
      fn_orig[0]='\0';

    while (db_orig->getMaxL()<90) {
      sprintf(fn, "%s%s%d", fn_orig, argv[1],i++);
      db_new=new Database(fn, bug);
      dist=NULL;
      dist=new Distance(db_new);
      dist->setkNN(atoi(argv[3]));
      
      db_new->readDBRaw(db_orig);
      db_new->setReal(TRUE);
      dist->calcDistStream(argv[1]);
      dist->kNNCluster();
      dist->profileCluster();

      db_orig=db_new;
      db_new=NULL;
    }
    exit(1);
  }

  /*
  else  if (argc<4) {
      db->readDB();
      db->printDB(argv[3]);
    } else if (argv[2][1]=='r') {
      if (argv[5][1]=='r')
	db->readDBRaw();
      else {
	db->readDB();
	dist->calcDist(argv[1]);
      }
      db->setNseqDB(atoi(argv[4]));
      db->realign(atoi(argv[3]));
    } else if (argc<10) {
      if (argc>=5) {
	db->setIO(atoi(argv[4]));
	if (argc==7)
	  dist->setOrder(atoi(argv[6]));
	else if(argc>7) {
	  db->setNoiseLevel(argv[6], argv[2][1]);
	  db->setNitem(atoi(argv[7]));
	  //	  db->readDBRaw(atoi(argv[5]));
	  //	  db->printStream();
	  //	  exit(1);
	}

      }
      if (argv[2][1]=='c') {
	db->readProfile(atoi(argv[3]));
	if (argc>=5) 
	  db->setCutoffPattern(atoi(argv[4]));
	if (argc>=6) 
	  db->setCutoffMinDB(atoi(argv[5]));
	if (argc>=7) 
	  db->setCutoffMaxDB(atoi(argv[6]));
	if (argc>=8)  
	  db->setCutoffVar(atoi(argv[7]));
	if (argc>=9) 
	  dist->setOrder(atoi(argv[8]));
	
	db->printPS(atoi(argv[3]));
	exit(1);
      } else if (argc>=6 && argv[2][1]=='a') {
	db->readDBRaw(atoi(argv[5]));
	dist->calcDistStream(argv[1]);
      }	else {
	if(argc>5) {
	  db->setNoiseLevel(argv[4], argv[2][1]);
	  db->setNitem(atoi(argv[5]));
	  //	  db->readDB();
	  //	  db->printDB();
	  //	  exit(1);
	}
	db->readDB();
	dist->calcDist(argv[1]);
      }

      dist->kNNCluster();
      dist->profileCluster();
      exit(1);
    } 
  */
  return 0;
}

