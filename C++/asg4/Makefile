# $Id: Makefile,v 1.2 2015-07-28 21:50:51-07 - - $

MKFILE      = Makefile
DEPFILE     = ${MKFILE}.dep
NOINCL      = ci clean spotless
NEEDINCL    = ${filter ${NOINCL}, ${MAKECMDGOALS}}
GMAKE       = ${MAKE} --no-print-directory
COMPILECPP  = g++ -g -O0 -Wall -Wextra -std=gnu++11
MAKEDEPCPP  = g++ -MM -std=gnu++11

MODULES     = debug graphics interp rgbcolor shape util
CPPHEADER   = ${MODULES:=.h}
CPPSOURCE   = ${MODULES:=.cpp} main.cpp
TEMPLATES   = util.tcc
GENFILES    = colors.cppgen
OTHERS      = ${MKFILE} README mk-colors.perl
ALLSOURCES  = ${CPPHEADER} ${TEMPLATES} ${CPPSOURCE} ${OTHERS}
EXECBIN     = gdraw
OBJECTS     = ${CPPSOURCE:.cpp=.o}
LINKLIBS    = -lGL -lGLU -lglut -lm

CLASS       = cmps109-wm.u15
PROJECT     = asg4

all : ${EXECBIN}
	- checksource ${ALLSOURCES}

${EXECBIN} : ${OBJECTS}
	${COMPILECPP} -o $@ ${OBJECTS} ${LINKLIBS}

%.o : %.cpp
	${COMPILECPP} -c $<

colors.cppgen: mk-colors.perl
	mk-colors.perl >colors.cppgen

ci : ${ALLSOURCES}
	- checksource ${ALLSOURCES}
	cid + ${ALLSOURCES}

clean :
	- rm ${OBJECTS} ${DEPFILE} core ${GENFILES}

spotless : clean
	- rm ${EXECBIN}


submit : ${ALLSOURCES}
	- checksource ${ALLSOURCES}
	submit ${CLASS} ${PROJECT} ${ALLSOURCES}

dep : ${CPPSOURCE} ${CPPHEADER} ${GENFILES}
	@ echo "# ${DEPFILE} created `LC_TIME=C date`" >${DEPFILE}
	${MAKEDEPCPP} ${CPPSOURCE} >>${DEPFILE}

${DEPFILE} :
	@ touch ${DEPFILE}
	${GMAKE} dep

again :
	${GMAKE} spotless dep ci all

ifeq (${NEEDINCL}, )
include ${DEPFILE}
endif

