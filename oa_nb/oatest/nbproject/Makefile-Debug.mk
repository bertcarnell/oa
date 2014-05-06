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
	${OBJECTDIR}/_ext/879778936/OATestClass.o \
	${OBJECTDIR}/COrthogonalArrayTest.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/matrixTest.o \
	${OBJECTDIR}/primesTest.o \
	${OBJECTDIR}/runifTest.o \
	${OBJECTDIR}/rutilsTest.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64 -std=c++0x
CXXFLAGS=-m64 -std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=--64

# Link Libraries and Options
LDLIBSOPTIONS=-L../oalib/dist/Debug/RTools-Windows -loalib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/oatest.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/oatest.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/oatest ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/879778936/OATestClass.o: /C/Users/Rob/Documents/Repositories/oa/oa_nb/oatest/OATestClass.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/879778936
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../oalib -I../bclib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/879778936/OATestClass.o /C/Users/Rob/Documents/Repositories/oa/oa_nb/oatest/OATestClass.cpp

${OBJECTDIR}/COrthogonalArrayTest.o: COrthogonalArrayTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../oalib -I../bclib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/COrthogonalArrayTest.o COrthogonalArrayTest.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../oalib -I../bclib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/matrixTest.o: matrixTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../oalib -I../bclib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/matrixTest.o matrixTest.cpp

${OBJECTDIR}/primesTest.o: primesTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../oalib -I../bclib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/primesTest.o primesTest.cpp

${OBJECTDIR}/runifTest.o: runifTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../oalib -I../bclib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/runifTest.o runifTest.cpp

${OBJECTDIR}/rutilsTest.o: rutilsTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../oalib -I../bclib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rutilsTest.o rutilsTest.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/oatest.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
