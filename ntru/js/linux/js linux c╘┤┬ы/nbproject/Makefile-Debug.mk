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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/DGS.o \
	${OBJECTDIR}/NTT.o \
	${OBJECTDIR}/crypto_sha3_512.o \
	${OBJECTDIR}/crypto_stream.o \
	${OBJECTDIR}/fastrandombytes.o \
	${OBJECTDIR}/helloworld.o \
	${OBJECTDIR}/misc.o \
	${OBJECTDIR}/packing.o \
	${OBJECTDIR}/param.o \
	${OBJECTDIR}/poly.o \
	${OBJECTDIR}/pqNTRUSign.o \
	${OBJECTDIR}/rng.o \
	${OBJECTDIR}/sha3.o \
	${OBJECTDIR}/shred.o \
	${OBJECTDIR}/sign.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk dist/libntrusign.so

dist/libntrusign.so: ${OBJECTFILES}
	${MKDIR} -p dist
	${LINK.c} -o dist/libntrusign.so ${OBJECTFILES} ${LDLIBSOPTIONS} -lm -lcrypto -shared -fPIC

${OBJECTDIR}/DGS.o: DGS.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DGS.o DGS.c

${OBJECTDIR}/NTT.o: NTT.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NTT.o NTT.c

${OBJECTDIR}/crypto_sha3_512.o: crypto_sha3_512.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/crypto_sha3_512.o crypto_sha3_512.c

${OBJECTDIR}/crypto_stream.o: crypto_stream.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/crypto_stream.o crypto_stream.c

${OBJECTDIR}/fastrandombytes.o: fastrandombytes.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fastrandombytes.o fastrandombytes.c

${OBJECTDIR}/helloworld.o: helloworld.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/helloworld.o helloworld.c

${OBJECTDIR}/misc.o: misc.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/misc.o misc.c

${OBJECTDIR}/packing.o: packing.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/packing.o packing.c

${OBJECTDIR}/param.o: param.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/param.o param.c

${OBJECTDIR}/poly.o: poly.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/poly.o poly.c

${OBJECTDIR}/pqNTRUSign.o: pqNTRUSign.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pqNTRUSign.o pqNTRUSign.c

${OBJECTDIR}/rng.o: rng.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rng.o rng.c

${OBJECTDIR}/sha3.o: sha3.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sha3.o sha3.c

${OBJECTDIR}/shred.o: shred.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/shred.o shred.c

${OBJECTDIR}/sign.o: sign.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/lib/jdk/jdk1.8/include -I/usr/lib/jdk/jdk1.8/include/linux -include /usr/lib/jdk/jdk1.8/include/jni.h -include /usr/local/include/openssl/evp.h -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sign.o sign.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
