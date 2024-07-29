#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# Add any compiled dispatch library entrypoint here!
DISPATCHES = 

# Module directories with whitespace seperation
MODULE = app/modules

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags with whitespace seperation
CXXFLAGS	:= -std=c++17 -Wall -Wreturn-type -Wextra -g

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -pthread -lcrypto -lssl -lrt -loatpp-websocket -loatpp -ldbus-cxx

# define output directory
OUTPUT	:= output

# define source directories with whitespace seperation
SRC		:= app/src

# define include directories with whitespace seperation
INCLUDE	:= include include/* app/modules app/modules/* wasp wasp/* /usr/local/include/dbus-cxx-2.0 /usr/local/include/sigc++-3.0 /usr/local/lib/sigc++-3.0/*

# define local lib directories with whitespace seperation
LIB		:= lib /usr/local/lib /usr/local/lib/oatpp 

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
MODULEDIRS := $(MODULE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
MODULEDIRS := $(shell find $(MODULE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS))) $(wildcard $(patsubst %,%/*.cpp, $(MODULEDIRS))) $(DISPATCHES)

# define the C object files 
OBJECTS		:= $(SOURCES:.cpp=.o)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!