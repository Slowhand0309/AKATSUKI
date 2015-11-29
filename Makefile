###############################################################################
#                                                                             #
# File-name   : Makefile                                                      #
# Author      : Slowhand0309                                                  #
# Function    : Makefile for AKATSUKI                                         #
#                                                                             #
###############################################################################

# Home directory
HOME = .

# Directory
BUILDDIR  = $(HOME)/build
SRCDIR = $(HOME)/src/projects
INCDIR = $(HOME)/src/include

ATLIBSRCDIR = $(SRCDIR)/ATlib

# Target declare
TARGET_LIB  =	$(BUILDDIR)/AKATSUKI.a

# Command
MAKE	=	/usr/bin/make
MV		=	/usr/bin/mv
CHMOD	=	/usr/bin/chmod
CP	=	/usr/bin/cp

# C++
CXX = g++

CFLAGS = -Wall -O2

# Object's
#SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
SRC = $(wildcard $(ATLIBSRCDIR)/io/*.cpp) $(wildcard $(ATLIBSRCDIR)/io/*/*.cpp)
OBJ = $(addprefix $(BUILDDIR)/,$(notdir $(SRC:.cpp=.o)))

# env
PLATFORM = $(shell uname)

# Compile
$(TARGET_LIB) : $(OBJ)
	@echo "compile..."
	ar rcs $(TARGET_LIB) $^
	@echo "done"

# Dependency
$(BUILDDIR)/%.o: $(ATLIBSRCDIR)/io/%.cpp
	$(CXX) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(BUILDDIR)/%.o: $(ATLIBSRCDIR)/io/*/%.cpp
	$(CXX) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Phony
.PHONY: all
all :
	@$(MAKE) clean
	@$(MAKE)

.PHONY: clean
clean :
	@rm -f $(BUILDDIR)/*.o
	@rm -f $(TARGET_LIB)

.PHONY: echo
echo :
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(PLATFORM)
