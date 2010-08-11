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

#include "distribution.h"
//#include <values.h>

//------------------------------- RandSeed -------------------------------

UniformDist *RandSeed::ran1 = new UniformDist(INIT_SEED);

void RandSeed::set_seed(long new_seed)
{
  delete ran1;
  ran1 = new UniformDist(new_seed);
}

long RandSeed::new_seed(void)
{
  float ans;

  ans = (*ran1)();
  ans *= (*ran1)();
//  cout << "rand_seed : " << idum << " " << long(-MAXLONG * ans) << endl;
  return long(-MAXLONG * ans);
}


#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

// "Minimal" random number generator of Park and Miller with
// Bays-Durham shuffle and added safeguards. Returns a uniform random
// deviate between 0.0 and 1.0 (exclusive of the endpoint values).
// Call with idum a negative integer to initialize; thereafter, do not
// alter idum between successive deviates in a sequence. RNMX should
// approximate the largest flating value that is less than 1.
float UniformDist::ran1(void)
{
  int j;
  long k;
  float temp;
  
  if (idum <= 0 || !iy) {	// Initialize
    if (-idum < 1)		// Be sure to prevent idum = 0
      idum = 1;
    else
      idum = -idum;
    for (j = NTAB+7; j >= 0; j-- )  // Load the shuffle table (after 8 warmups)
      {
	k = idum/IQ;
	idum = IA * (idum-k*IQ) - IR*k;
	if (idum < 0) idum += IM;
	if (j < NTAB) iv[j] = idum;
      }
    iy = iv[0];
  }
  k = idum/IQ;			  // Start here when not initializing.
  idum = IA * (idum-k*IQ) - IR*k; // Compute idum = (IA*idum) % IM without
  if (idum < 0) idum += IM;	  //     overflows by Schrage's method.
  j = iy/NDIV;			  // Will be in the range 0..NTAB-1
  iy = iv[j];			  // Output previously stored value and
  iv[j] = idum;			  //      and refull the shuffle table.
  if ((temp = AM*iy) > RNMX) 	  // Because users don't expect endpoint values
    return RNMX;
  else
    return temp;

}


//------------------------------- Choose -------------------------------


// allows selection of k random items from the string
// 
Choose::Choose(int n, int k)
{
  UniformDist ud;
  int i, j, ival;
  float fval;

  num = new int [n];
  rval = new float [n];

  // associate a random value with each item
  // also copy item into num
  for (i = 0; i < n; i++)
    {
      rval[i] = ud();
      num[i] = i;
    }
  
  // sort num according to the values in rval
  for (i = 0; i < n; i++ )
    {
      ival = num[i]; fval = rval[i];
      for ( j = i; j > 0 && rval[j-1] > fval; j-- ) {
	  num[j] = num[j-1];
	  rval[j] = rval[j-1];
	}
      num[j] = ival;
      rval[j] = fval;
    }

  // resort first k num according to position
  for (i = 0; i < k; i++ )
    {
      ival = num[i]; 
      for ( j = i; j > 0 && num[j-1] > ival; j-- )
	num[j] = num[j-1];
      num[j] = ival;
    }
}


Choose::~Choose(void)
{
  delete [] num;
  delete [] rval;
}


