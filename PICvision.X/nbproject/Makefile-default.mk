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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PICvision.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PICvision.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=audio/sound.c games/2048/gc_2048.c games/snake/snake.c graphics/graphics.c Hardware/controllers/SNES/snes_paddle.c Hardware/hardwareProfile.c system/timers.c text_console/font.c text_console/text_console.c TVout/TVout.c PICvision.c PICvision_banner.c menus.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/audio/sound.o ${OBJECTDIR}/games/2048/gc_2048.o ${OBJECTDIR}/games/snake/snake.o ${OBJECTDIR}/graphics/graphics.o ${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o ${OBJECTDIR}/Hardware/hardwareProfile.o ${OBJECTDIR}/system/timers.o ${OBJECTDIR}/text_console/font.o ${OBJECTDIR}/text_console/text_console.o ${OBJECTDIR}/TVout/TVout.o ${OBJECTDIR}/PICvision.o ${OBJECTDIR}/PICvision_banner.o ${OBJECTDIR}/menus.o
POSSIBLE_DEPFILES=${OBJECTDIR}/audio/sound.o.d ${OBJECTDIR}/games/2048/gc_2048.o.d ${OBJECTDIR}/games/snake/snake.o.d ${OBJECTDIR}/graphics/graphics.o.d ${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o.d ${OBJECTDIR}/Hardware/hardwareProfile.o.d ${OBJECTDIR}/system/timers.o.d ${OBJECTDIR}/text_console/font.o.d ${OBJECTDIR}/text_console/text_console.o.d ${OBJECTDIR}/TVout/TVout.o.d ${OBJECTDIR}/PICvision.o.d ${OBJECTDIR}/PICvision_banner.o.d ${OBJECTDIR}/menus.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/audio/sound.o ${OBJECTDIR}/games/2048/gc_2048.o ${OBJECTDIR}/games/snake/snake.o ${OBJECTDIR}/graphics/graphics.o ${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o ${OBJECTDIR}/Hardware/hardwareProfile.o ${OBJECTDIR}/system/timers.o ${OBJECTDIR}/text_console/font.o ${OBJECTDIR}/text_console/text_console.o ${OBJECTDIR}/TVout/TVout.o ${OBJECTDIR}/PICvision.o ${OBJECTDIR}/PICvision_banner.o ${OBJECTDIR}/menus.o

# Source Files
SOURCEFILES=audio/sound.c games/2048/gc_2048.c games/snake/snake.c graphics/graphics.c Hardware/controllers/SNES/snes_paddle.c Hardware/hardwareProfile.c system/timers.c text_console/font.c text_console/text_console.c TVout/TVout.c PICvision.c PICvision_banner.c menus.c


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

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PICvision.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/audio/sound.o: audio/sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/audio 
	@${RM} ${OBJECTDIR}/audio/sound.o.d 
	@${RM} ${OBJECTDIR}/audio/sound.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  audio/sound.c  -o ${OBJECTDIR}/audio/sound.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/audio/sound.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/audio/sound.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/games/2048/gc_2048.o: games/2048/gc_2048.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/games/2048 
	@${RM} ${OBJECTDIR}/games/2048/gc_2048.o.d 
	@${RM} ${OBJECTDIR}/games/2048/gc_2048.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  games/2048/gc_2048.c  -o ${OBJECTDIR}/games/2048/gc_2048.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/games/2048/gc_2048.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/games/2048/gc_2048.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/games/snake/snake.o: games/snake/snake.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/games/snake 
	@${RM} ${OBJECTDIR}/games/snake/snake.o.d 
	@${RM} ${OBJECTDIR}/games/snake/snake.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  games/snake/snake.c  -o ${OBJECTDIR}/games/snake/snake.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/games/snake/snake.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/games/snake/snake.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/graphics/graphics.o: graphics/graphics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/graphics 
	@${RM} ${OBJECTDIR}/graphics/graphics.o.d 
	@${RM} ${OBJECTDIR}/graphics/graphics.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  graphics/graphics.c  -o ${OBJECTDIR}/graphics/graphics.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/graphics/graphics.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/graphics/graphics.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o: Hardware/controllers/SNES/snes_paddle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware/controllers/SNES 
	@${RM} ${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o.d 
	@${RM} ${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Hardware/controllers/SNES/snes_paddle.c  -o ${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Hardware/hardwareProfile.o: Hardware/hardwareProfile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware 
	@${RM} ${OBJECTDIR}/Hardware/hardwareProfile.o.d 
	@${RM} ${OBJECTDIR}/Hardware/hardwareProfile.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Hardware/hardwareProfile.c  -o ${OBJECTDIR}/Hardware/hardwareProfile.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Hardware/hardwareProfile.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Hardware/hardwareProfile.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/system/timers.o: system/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system 
	@${RM} ${OBJECTDIR}/system/timers.o.d 
	@${RM} ${OBJECTDIR}/system/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system/timers.c  -o ${OBJECTDIR}/system/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system/timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/system/timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/text_console/font.o: text_console/font.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/text_console 
	@${RM} ${OBJECTDIR}/text_console/font.o.d 
	@${RM} ${OBJECTDIR}/text_console/font.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  text_console/font.c  -o ${OBJECTDIR}/text_console/font.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/text_console/font.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/text_console/font.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/text_console/text_console.o: text_console/text_console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/text_console 
	@${RM} ${OBJECTDIR}/text_console/text_console.o.d 
	@${RM} ${OBJECTDIR}/text_console/text_console.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  text_console/text_console.c  -o ${OBJECTDIR}/text_console/text_console.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/text_console/text_console.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/text_console/text_console.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/TVout/TVout.o: TVout/TVout.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TVout 
	@${RM} ${OBJECTDIR}/TVout/TVout.o.d 
	@${RM} ${OBJECTDIR}/TVout/TVout.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  TVout/TVout.c  -o ${OBJECTDIR}/TVout/TVout.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TVout/TVout.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/TVout/TVout.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PICvision.o: PICvision.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/PICvision.o.d 
	@${RM} ${OBJECTDIR}/PICvision.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PICvision.c  -o ${OBJECTDIR}/PICvision.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PICvision.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PICvision.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PICvision_banner.o: PICvision_banner.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/PICvision_banner.o.d 
	@${RM} ${OBJECTDIR}/PICvision_banner.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PICvision_banner.c  -o ${OBJECTDIR}/PICvision_banner.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PICvision_banner.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PICvision_banner.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/menus.o: menus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/menus.o.d 
	@${RM} ${OBJECTDIR}/menus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  menus.c  -o ${OBJECTDIR}/menus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/menus.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/menus.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/audio/sound.o: audio/sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/audio 
	@${RM} ${OBJECTDIR}/audio/sound.o.d 
	@${RM} ${OBJECTDIR}/audio/sound.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  audio/sound.c  -o ${OBJECTDIR}/audio/sound.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/audio/sound.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/audio/sound.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/games/2048/gc_2048.o: games/2048/gc_2048.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/games/2048 
	@${RM} ${OBJECTDIR}/games/2048/gc_2048.o.d 
	@${RM} ${OBJECTDIR}/games/2048/gc_2048.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  games/2048/gc_2048.c  -o ${OBJECTDIR}/games/2048/gc_2048.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/games/2048/gc_2048.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/games/2048/gc_2048.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/games/snake/snake.o: games/snake/snake.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/games/snake 
	@${RM} ${OBJECTDIR}/games/snake/snake.o.d 
	@${RM} ${OBJECTDIR}/games/snake/snake.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  games/snake/snake.c  -o ${OBJECTDIR}/games/snake/snake.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/games/snake/snake.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/games/snake/snake.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/graphics/graphics.o: graphics/graphics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/graphics 
	@${RM} ${OBJECTDIR}/graphics/graphics.o.d 
	@${RM} ${OBJECTDIR}/graphics/graphics.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  graphics/graphics.c  -o ${OBJECTDIR}/graphics/graphics.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/graphics/graphics.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/graphics/graphics.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o: Hardware/controllers/SNES/snes_paddle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware/controllers/SNES 
	@${RM} ${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o.d 
	@${RM} ${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Hardware/controllers/SNES/snes_paddle.c  -o ${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Hardware/controllers/SNES/snes_paddle.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Hardware/hardwareProfile.o: Hardware/hardwareProfile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Hardware 
	@${RM} ${OBJECTDIR}/Hardware/hardwareProfile.o.d 
	@${RM} ${OBJECTDIR}/Hardware/hardwareProfile.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Hardware/hardwareProfile.c  -o ${OBJECTDIR}/Hardware/hardwareProfile.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Hardware/hardwareProfile.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Hardware/hardwareProfile.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/system/timers.o: system/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system 
	@${RM} ${OBJECTDIR}/system/timers.o.d 
	@${RM} ${OBJECTDIR}/system/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system/timers.c  -o ${OBJECTDIR}/system/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system/timers.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/system/timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/text_console/font.o: text_console/font.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/text_console 
	@${RM} ${OBJECTDIR}/text_console/font.o.d 
	@${RM} ${OBJECTDIR}/text_console/font.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  text_console/font.c  -o ${OBJECTDIR}/text_console/font.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/text_console/font.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/text_console/font.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/text_console/text_console.o: text_console/text_console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/text_console 
	@${RM} ${OBJECTDIR}/text_console/text_console.o.d 
	@${RM} ${OBJECTDIR}/text_console/text_console.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  text_console/text_console.c  -o ${OBJECTDIR}/text_console/text_console.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/text_console/text_console.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/text_console/text_console.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/TVout/TVout.o: TVout/TVout.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TVout 
	@${RM} ${OBJECTDIR}/TVout/TVout.o.d 
	@${RM} ${OBJECTDIR}/TVout/TVout.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  TVout/TVout.c  -o ${OBJECTDIR}/TVout/TVout.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TVout/TVout.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/TVout/TVout.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PICvision.o: PICvision.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/PICvision.o.d 
	@${RM} ${OBJECTDIR}/PICvision.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PICvision.c  -o ${OBJECTDIR}/PICvision.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PICvision.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PICvision.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PICvision_banner.o: PICvision_banner.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/PICvision_banner.o.d 
	@${RM} ${OBJECTDIR}/PICvision_banner.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PICvision_banner.c  -o ${OBJECTDIR}/PICvision_banner.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PICvision_banner.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PICvision_banner.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/menus.o: menus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/menus.o.d 
	@${RM} ${OBJECTDIR}/menus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  menus.c  -o ${OBJECTDIR}/menus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/menus.o.d"      -g -omf=elf -O1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/menus.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PICvision.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PICvision.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf  -mreserve=data@0x800:0x822   -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PICKIT2=1,$(MP_LINKER_FILE_OPTION),--heap=1024,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PICvision.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PICvision.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=1024,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PICvision.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
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
