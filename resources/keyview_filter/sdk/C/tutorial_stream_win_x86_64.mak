# BEGIN COPYRIGHT NOTICE
# (c) Copyright 2022-2023 Open Text.
# 
# The only warranties for products and services of Open Text and its
# affiliates and licensors ("Open Text") are as may be set forth in the
# express warranty statements accompanying such products and services. Nothing
# herein should be construed as constituting an additional warranty. Open
# Text shall not be liable for technical or editorial errors or omissions
# contained herein. The information contained herein is subject to change
# without notice.
# 
# Except as specifically indicated otherwise, this document contains
# confidential information and a valid license is required for possession, use
# or copying. If this work is provided to the U.S. Government, consistent with
# FAR 12.211 and 12.212, Commercial Computer Software, Computer Software
# Documentation, and Technical Data for Commercial Items are licensed to the
# U.S. Government under vendor's standard commercial license.

# END COPYRIGHT NOTICE

# Ensure that you have run vcvars64.bat and the path is set to find the necessary files
# usage: nmake /f "filter_win_x86_64.mak"

PROGRAM_NAME=tutorial_stream
OBJ_DIR=obj
OUT_DIR=bin

CC=cl.exe
INC_FLAGS = /I"." /I"..\..\include"
LIB_DIR = ..\..\WINDOWS_X86_64\lib

CFLAGS = /nologo /MD /D"_WINDOWS" /D"WIN64" /D"_WIN64" /D"_WIN64_INTEL" /D"KVFILTER" $(INC_FLAGS)
LFLAGS = /RELEASE kernel32.lib user32.lib $(LIB_DIR)\kvfilter.lib
OBJ_FILES = $(OBJ_DIR)\tutorial_file.obj

!include ..\win64x_makefiles\makefile.inc

all: directories $(OUT_DIR)\$(PROGRAM_NAME).exe

directories: $(OBJ_DIR) $(OUT_DIR)

$(OBJ_DIR) $(OUT_DIR):
	mkdir $@

.c{$(OBJ_DIR)}.obj:
	$(CC) $(CFLAGS) /c $< /Fo:$@

$(OUT_DIR)\$(PROGRAM_NAME).exe: $(OBJ_FILES)
	link $(LFLAGS) /OUT:$@ $**
	$(_VC_MANIFEST_EMBED_EXE)

clean:
	rmdir /q /s $(OBJ_DIR)
	rmdir /q /s $(OUT_DIR)
	$(_VC_MANIFEST_CLEAN)

!include ..\win64x_makefiles\makefile.targ.inc

