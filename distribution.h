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

#ifndef _DISTRIBUTION_H_
#define _DISTRIBUTION_H_

#define INIT_SEED -1
//KUM insert;
#define MAXLONG 2147483647L

float ran0(long &idum);

//=============================  Distributions  =============================

class UniformDist;

class RandSeed
{
private:
  static UniformDist *ran1;
public:
  static void set_seed(long new_seed);
  static long new_seed(void);
	// Returns a random seed between 0 and MAXLONG, using
	// INIT_SEED to initialize the random sequence.
};


// Returns a random deviate between 0.0 and 1.0 (exclusive of
// the endpoint values). Call with a negative integer to
// initialize.
//
#define NTAB 32
class UniformDist
{
private:
  long idum;
  long iy;
  long iv[NTAB];
  
  float ran1(void);
public:
  UniformDist(void)
    : iy(0) { idum = RandSeed::new_seed(); };
  UniformDist(long seed)
    : iy(0), idum(seed) {};
  float operator()(void)	// returns a random number between 0 and 1
    { return ran1(); };
};


class PoissonDist
{
private:
  float lambda;
  float sq,alxm,g,oldm;
  UniformDist *ran1;

  float poidev(float xm);
  	// Returns as a floating-point number an integer value that is
	// a random deviate drawn from a Poisson distribution of mean xm.
public:
  PoissonDist(float mean)	// 
    : lambda(mean), oldm(-1.0) { ran1 = new UniformDist(); };
  int operator()()	// returns a random variable with Poisson dist.
    { return int( poidev(lambda) ); };
};


class NormalDist
{
private:
  float mu;	// mean
  float sigma;	// (std. deviation)^2
  int iset;
  float gset;
  UniformDist *ran1;

  float gasdev(void);
	// Returns a normally distributed deviate with zero mean and
	// unit variance.
public:
  NormalDist(float m, float s)	// mu, sigma
    : mu(m), sigma(s), iset(0) { ran1 = new UniformDist(); };
  float operator()()	// returns a random variable with Normal dist.
    { return gasdev() * sigma + mu; };
};


class ExpDist
{
private:
  float lambda;
  UniformDist *ran1;

  float expdev(void);
	// Returns an exponentially distributed, positive, random
	// deviate of unit mean.
public:
  ExpDist(float mean = 1.0)
    : lambda(mean) { ran1 = new UniformDist(); };
  float operator()()	// returns a random variable with an exp. distribution
    { return lambda * expdev(); };
};


// Used to choose k random numbers in the range [1..n]
//
class Choose
{
private:
  int *num;	// list of the positions
  float *rval;	// random value (used to get random ordering of the items)
public:
  Choose(int n, int k);
  ~Choose(void);
  int pos(int i) { return num[i]; };	// returns the i-th position
};

#endif //_DISTRIBUTION_H_
