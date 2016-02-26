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
CND_PLATFORM=MinGW-Windows
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
	${OBJECTDIR}/Flash.o \
	${OBJECTDIR}/Game.o \
	${OBJECTDIR}/Heal.o \
	${OBJECTDIR}/Hechizo.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/WorldState.o \
	${OBJECTDIR}/hFireBasic.o \
	${OBJECTDIR}/hRayBasic.o \
	${OBJECTDIR}/hWaterBasic.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L. lib/libsfml-graphics-d.a lib/libsfml-window-d.a lib/libsfml-system-d.a lib/libsfml-audio-d.a lib/libsfml-main-d.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/elemental-revenge.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/elemental-revenge.exe: lib/libsfml-graphics-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/elemental-revenge.exe: lib/libsfml-window-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/elemental-revenge.exe: lib/libsfml-system-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/elemental-revenge.exe: lib/libsfml-audio-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/elemental-revenge.exe: lib/libsfml-main-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/elemental-revenge.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/elemental-revenge ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Flash.o: Flash.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -IHeaders -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Flash.o Flash.cpp

${OBJECTDIR}/Game.o: Game.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -IHeaders -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Game.o Game.cpp

${OBJECTDIR}/Heal.o: Heal.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -IHeaders -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Heal.o Heal.cpp

${OBJECTDIR}/Hechizo.o: Hechizo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -IHeaders -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hechizo.o Hechizo.cpp

${OBJECTDIR}/Player.o: Player.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -IHeaders -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/WorldState.o: WorldState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -IHeaders -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WorldState.o WorldState.cpp

${OBJECTDIR}/hFireBasic.o: hFireBasic.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -IHeaders -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hFireBasic.o hFireBasic.cpp

${OBJECTDIR}/hRayBasic.o: hRayBasic.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -IHeaders -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hRayBasic.o hRayBasic.cpp

${OBJECTDIR}/hWaterBasic.o: hWaterBasic.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -IHeaders -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hWaterBasic.o hWaterBasic.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -IHeaders -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/elemental-revenge.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
