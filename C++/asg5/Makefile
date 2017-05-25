# $Id: Makefile,v 1.2 2015-08-13 13:55:46-07 - - $

GPP      = g++ -g -O0 -Wall -Wextra -std=gnu++11

DEPFILE  = Makefile.dep
HEADERS  = sockets.h protocol.h logstream.h
CPPLIBS  = sockets.cpp protocol.cpp 
CPPSRCS  = ${CPPLIBS} cix.cpp cixd.cpp
LIBOBJS  = ${CPPLIBS:.cpp=.o}
CIXOBJS  = cix.o ${LIBOBJS}
CIXDOBJS = cixd.o ${LIBOBJS}
OBJECTS  = ${CIXOBJS} ${CIXDOBJS}
EXECBINS = cix cixd
LISTING  = Listing.ps
SOURCES  = ${HEADERS} ${CPPSRCS} Makefile
ALLSOURCES = ${SOURCES} README

all: ${DEPFILE} ${EXECBINS}

cix: ${CIXOBJS}
	${GPP} -o $@ ${CIXOBJS}

cixd: ${CIXDOBJS}
	${GPP} -o $@ ${CIXDOBJS}

%.o: %.cpp
	${GPP} -c $<

ci:
	- checksource ${SOURCES}
	- cid + ${SOURCES}

lis: all ${SOURCES} ${DEPFILE}
	mkpspdf ${LISTING} ${SOURCES} ${DEPFILE}

clean:
	- rm ${LISTING} ${LISTING:.ps=.pdf} ${OBJECTS} Makefile.dep

spotless: clean
	- rm ${EXECBINS}

dep:
	- rm ${DEPFILE}
	make --no-print-directory ${DEPFILE}

submit: ${ALLSOURCES}
	- checksource ${ALLSOURCES}
	submit cmps109-wm.u15 asg5 ${ALLSOURCES}

${DEPFILE}:
	${GPP} -MM ${CPPSRCS} >${DEPFILE}

again: ${SOURCES}
	make --no-print-directory spotless ci all lis

include ${DEPFILE}

