#	This file is part of ApproxMAP 
#
#	Copyright (C) 2003, 2004, 2010 Hye-Chung Kum.
#	You may contact Hye-Chung Kum (approxmap@unc.edu) for any further licensing inquires.
#
#    ApproxMAP is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    ApproxMAP is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with ApproxMAP. In the current directory gpl.txt is the GNU 
#	public license file. If not, see <http://www.gnu.org/licenses/>. 


# remove command
RM	= /bin/rm -f

# Compilation variables
CC      = g++

CFLAGS  = -LANG:std -O

PROGS   = approx
#PROGS   = approx evaluate
#PROGS   = approx apriori 
OBJS1 = database.o distance.o approx.o distribution.o
OBJS2 = database.o apriori.o distribution.o
OBJS3 = database.o apriori.o evaluate.o distribution.o distance.o

.SUFFIXES: .o .cpp

default: $(PROGS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE) -g -c $<

approx: $(OBJS1)
	$(CC) $(CFLAGS) $(OBJS1) -g -o $@

apriori: $(OBJS2)
	$(CC) $(CFLAGS) $(OBJS2) -g -o $@

evaluate: $(OBJS3)
	$(CC) $(CFLAGS) $(OBJS3) -g -o $@

clean: 
	$(RM) *.o $(PROGS)

cleanall: clean
	$(RM) -R ii_files

distribution.o: distribution.h distribution.cpp
database.o: utility.h postscript.h database.h database.cpp
distance.o: utility.h database.h postscript.h distance.h distance.cpp
postscript.o: postscript.h postscript.cpp
approx.o: database.h distance.h approx.cpp
apriori.o: utility.h postscript.h database.h apriori.cpp apriori.h
evaluate.o: evaluate.cpp evaluate.h apriori.cpp apriori.h utility.h postscript.h database.h 
