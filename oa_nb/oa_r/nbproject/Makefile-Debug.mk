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
	${OBJECTDIR}/oa_r.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64 -mtune=core2 -Wall -pedantic
CXXFLAGS=-m64 -mtune=core2 -Wall -pedantic

# Fortran Compiler Flags
FFLAGS=-m64

# Assembler Flags
ASFLAGS=--64

# Link Libraries and Options
LDLIBSOPTIONS=-L/C/Program\ Files/R/R-3.0.2/bin/x64 -L/C/Program\ Files/R/R-3.0.2/library/Rcpp/libs/x64 ../oalib/dist/Debug/RTools-Windows/liboalib.a -lRcpp -lR

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f1

${TESTDIR}/TestFiles/f1: ../oalib/dist/Debug/RTools-Windows/liboalib.a

${TESTDIR}/TestFiles/f1: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	g++ -o ${TESTDIR}/TestFiles/f1 ${OBJECTFILES} ${LDLIBSOPTIONS} -m64 -s -static-libgcc -shared

${OBJECTDIR}/oa_r.o: oa_r.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DRCOMPILE -I/C/Program\ Files/R/R-3.0.2/library/Rcpp/include -I/C/Program\ Files/R/R-3.0.2/include -I../oalib -I. -std=c++98  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/oa_r.o oa_r.cpp

# Subprojects
.build-subprojects:
	cd ../oalib && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${TESTDIR}/TestFiles/f1

# Subprojects
.clean-subprojects:
	cd ../oalib && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
