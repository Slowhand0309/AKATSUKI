###############################################################################
#                                                                             #
# File-name   : Makefile                                                      #
# Author      : Slowhand0309                                                  #
# Function    : Makefile for AKATSUKI                                         #
#                                                                             #
###############################################################################

# Home directory
HOME = .

# Common directory
BUILDDIR  = $(HOME)/build
SRCDIR = $(HOME)/src/projects
INCDIR = $(HOME)/src/include
LIBDIR = $(HOME)/lib

# env
PLATFORM = $(shell uname)

# Project's src dir
ATBATSRCDIR = $(SRCDIR)/ATbat
ATGAESRCDIR = $(SRCDIR)/ATgae
ATLIBSRCDIR = $(SRCDIR)/ATlib
ATUTLSRCDIR = $(SRCDIR)/ATutl

# Project's target declare
#TARGET_ATBAT  =	$(LIBDIR)/ATlib.a
TARGET_ATLIB  =	$(LIBDIR)/ATlib.a
#TARGET_ATGAE  =	$(LIBDIR)/ATlib.a
#TARGET_ATUTL  =	$(LIBDIR)/ATutl.a

# Command

# C++
CXX = g++
CFLAGS = -Wall -O2

##############################################################
#
# Build ATlib
#
##############################################################
#SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
SRC_ATLIB = $(wildcard $(ATLIBSRCDIR)/*.cpp) $(wildcard $(ATLIBSRCDIR)/*/*.cpp)
OBJ_ATLIB = $(addprefix $(BUILDDIR)/,$(notdir $(SRC_ATLIB:.cpp=.o)))

atlib: $(TARGET_ATLIB)

# Compile
$(TARGET_ATLIB) : $(OBJ_ATLIB)
	@echo "compile..."
	ar rcs $(TARGET_ATLIB) $^
	@echo "done"

# Dependency
$(BUILDDIR)/%.o: $(ATLIBSRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(BUILDDIR)/%.o: $(ATLIBSRCDIR)/*/%.cpp
	$(CXX) $(CFLAGS) -I$(INCDIR) -c $< -o $@

##############################################################
#
# Build ATutl
#
##############################################################

# Phony
.PHONY: all
all :


.PHONY: clean
clean :
	@rm -f $(BUILDDIR)/*.o
	@rm -f $(TARGET_ATLIB)

.PHONY: echo
echo :
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(PLATFORM)
