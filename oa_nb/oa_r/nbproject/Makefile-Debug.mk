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

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

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
LDLIBSOPTIONS=-L/C/Program\ Files/R/R-3.0.1/bin/x64 ../oalib/dist/Debug/RTools-Windows/liboalib.a ../Rcpp/dist/Debug/RTools-Windows/librcpp.a -lR

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboa_r.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboa_r.${CND_DLIB_EXT}: ../oalib/dist/Debug/RTools-Windows/liboalib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboa_r.${CND_DLIB_EXT}: ../Rcpp/dist/Debug/RTools-Windows/librcpp.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboa_r.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboa_r.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -m64 -s -static-libgcc -shared

${OBJECTDIR}/oa_r.o: oa_r.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../../../../../../Program\ Files/R/R-3.0.1/library/Rcpp/include -I../../../../../../../Program\ Files/R/R-3.0.1/include -I../oalib -I../../../boost -std=c++98 -mtune=core2 -Wall -pedantic  -MMD -MP -MF $@.d -o ${OBJECTDIR}/oa_r.o oa_r.cpp

# Subprojects
.build-subprojects:
	cd ../oalib && ${MAKE}  -f Makefile CONF=Debug
	cd ../Rcpp && ${MAKE}  -f Makefile CONF=Debug

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/oa_rTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/oa_rTest.o: tests/oa_rTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../../../../../../Program\ Files/R/R-3.0.1/library/Rcpp/include -I../../../../../../../Program\ Files/R/R-3.0.1/include -I../oalib -I../../../boost -I. -std=c++98 -mtune=core2 -Wall -pedantic -MMD -MP -MF $@.d -o ${TESTDIR}/tests/oa_rTest.o tests/oa_rTest.cpp


${OBJECTDIR}/oa_r_nomain.o: ${OBJECTDIR}/oa_r.o oa_r.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/oa_r.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Werror -I../../../../../../../Program\ Files/R/R-3.0.1/library/Rcpp/include -I../../../../../../../Program\ Files/R/R-3.0.1/include -I../oalib -I../../../boost -std=c++98 -mtune=core2 -Wall -pedantic  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/oa_r_nomain.o oa_r.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/oa_r.o ${OBJECTDIR}/oa_r_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liboa_r.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../oalib && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Rcpp && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
