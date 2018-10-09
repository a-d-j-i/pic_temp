#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic_temp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic_temp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/343710134/usb_device.o ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o ${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o ${OBJECTDIR}/_ext/1472/usb_callbacks.o ${OBJECTDIR}/_ext/1472/usb_serial.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/dht.o ${OBJECTDIR}/_ext/1472/infraredSensor.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/343710134/usb_device.o.d ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d ${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o.d ${OBJECTDIR}/_ext/1472/usb_callbacks.o.d ${OBJECTDIR}/_ext/1472/usb_serial.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/dht.o.d ${OBJECTDIR}/_ext/1472/infraredSensor.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/343710134/usb_device.o ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o ${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o ${OBJECTDIR}/_ext/1472/usb_callbacks.o ${OBJECTDIR}/_ext/1472/usb_serial.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/dht.o ${OBJECTDIR}/_ext/1472/infraredSensor.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=PIC32MX220F032D
ProjectDir=/home/adji/tmp/pic_temp/pic_temp.X
ConfName=default
ImagePath=dist/default/${IMAGE_TYPE}/pic_temp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
ImageDir=dist/default/${IMAGE_TYPE}
ImageName=pic_temp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/pic_temp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [/opt/bin/pic32prog ${ImagePath}]"
	@/opt/bin/pic32prog ${ImagePath}
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=32MX220F032D
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/343710134/usb_device.o: ../Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/343710134 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/343710134/usb_device.o.d" -o ${OBJECTDIR}/_ext/343710134/usb_device.o ../Microchip/USB/usb_device.c   
	
${OBJECTDIR}/_ext/131024517/usb_function_cdc.o: ../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/131024517 
	@${RM} ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o "../Microchip/USB/CDC Device Driver/usb_function_cdc.c"   
	
${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o: ../usb_descriptors_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o.d" -o ${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o ../usb_descriptors_cdc.c   
	
${OBJECTDIR}/_ext/1472/usb_callbacks.o: ../usb_callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_callbacks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/usb_callbacks.o.d" -o ${OBJECTDIR}/_ext/1472/usb_callbacks.o ../usb_callbacks.c   
	
${OBJECTDIR}/_ext/1472/usb_serial.o: ../usb_serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_serial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/usb_serial.o.d" -o ${OBJECTDIR}/_ext/1472/usb_serial.o ../usb_serial.c   
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c   
	
${OBJECTDIR}/_ext/1472/dht.o: ../dht.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/dht.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/dht.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/dht.o.d" -o ${OBJECTDIR}/_ext/1472/dht.o ../dht.c   
	
${OBJECTDIR}/_ext/1472/infraredSensor.o: ../infraredSensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/infraredSensor.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/infraredSensor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/infraredSensor.o.d" -o ${OBJECTDIR}/_ext/1472/infraredSensor.o ../infraredSensor.c   
	
else
${OBJECTDIR}/_ext/343710134/usb_device.o: ../Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/343710134 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/343710134/usb_device.o.d" -o ${OBJECTDIR}/_ext/343710134/usb_device.o ../Microchip/USB/usb_device.c   
	
${OBJECTDIR}/_ext/131024517/usb_function_cdc.o: ../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/131024517 
	@${RM} ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o "../Microchip/USB/CDC Device Driver/usb_function_cdc.c"   
	
${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o: ../usb_descriptors_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o.d" -o ${OBJECTDIR}/_ext/1472/usb_descriptors_cdc.o ../usb_descriptors_cdc.c   
	
${OBJECTDIR}/_ext/1472/usb_callbacks.o: ../usb_callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_callbacks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/usb_callbacks.o.d" -o ${OBJECTDIR}/_ext/1472/usb_callbacks.o ../usb_callbacks.c   
	
${OBJECTDIR}/_ext/1472/usb_serial.o: ../usb_serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_serial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/usb_serial.o.d" -o ${OBJECTDIR}/_ext/1472/usb_serial.o ../usb_serial.c   
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c   
	
${OBJECTDIR}/_ext/1472/dht.o: ../dht.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/dht.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/dht.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/dht.o.d" -o ${OBJECTDIR}/_ext/1472/dht.o ../dht.c   
	
${OBJECTDIR}/_ext/1472/infraredSensor.o: ../infraredSensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/infraredSensor.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/infraredSensor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DPIC32MX220F032D_PIM -I"../" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Microchip/USB" -Os -MMD -MF "${OBJECTDIR}/_ext/1472/infraredSensor.o.d" -o ${OBJECTDIR}/_ext/1472/infraredSensor.o ../infraredSensor.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/pic_temp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION) -Os -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/pic_temp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=_min_heap_size=0,--gc-sections,-L"..",-Map="${DISTDIR}/BlinkLed.X.${IMAGE_TYPE}.map",--report-mem
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/pic_temp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -Os -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/pic_temp.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,-L"..",-Map="${DISTDIR}/BlinkLed.X.${IMAGE_TYPE}.map",--report-mem
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/pic_temp.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
