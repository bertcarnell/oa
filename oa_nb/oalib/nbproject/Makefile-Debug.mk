#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=RTools-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/COrthogonalArray.o \
	${OBJECTDIR}/ak3.o \
	${OBJECTDIR}/akconst.o \
	${OBJECTDIR}/akn.o \
	${OBJECTDIR}/construct.o \
	${OBJECTDIR}/galois.o \
	${OBJECTDIR}/gfields.o \
	${OBJECTDIR}/oa.o \
	${OBJECTDIR}/primes.o \
	${OBJECTDIR}/runif.o \
	${OBJECTDIR}/rutils.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64 -pedantic -Wall -Wno-long-long -mtune=core2
CXXFLAGS=-m64 -pedantic -Wall -Wno-long-long -mtune=core2

# Fortran Compiler Flags
FFLAGS=-m64

# Assembler Flags
ASFLAGS=--64

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboalib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboalib.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboalib.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboalib.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboalib.a

${OBJECTDIR}/COrthogonalArray.o: COrthogonalArray.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/COrthogonalArray.o COrthogonalArray.cpp

${OBJECTDIR}/ak3.o: ak3.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ak3.o ak3.cpp

${OBJECTDIR}/akconst.o: akconst.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/akconst.o akconst.cpp

${OBJECTDIR}/akn.o: akn.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/akn.o akn.cpp

${OBJECTDIR}/construct.o: construct.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/construct.o construct.cpp

${OBJECTDIR}/galois.o: galois.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/galois.o galois.cpp

${OBJECTDIR}/gfields.o: gfields.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gfields.o gfields.cpp

${OBJECTDIR}/oa.o: oa.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/oa.o oa.cpp

${OBJECTDIR}/primes.o: primes.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/primes.o primes.cpp

${OBJECTDIR}/runif.o: runif.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/runif.o runif.cpp

${OBJECTDIR}/rutils.o: rutils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../bclib -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rutils.o rutils.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboalib.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
