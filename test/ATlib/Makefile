###############################################################################
#                                                                             #
# File-name   : Makefile                                                      #
# Author      : Slowhand0309                                                  #
# Function    : Makefile for ATlib Test                                       #
#                                                                             #
###############################################################################

# Root directory
ROOT = ../../

# Home directory
HOME = .

# Common directory
BUILDDIR  = $(HOME)/build
SRCDIR = $(HOME)/src

# Header and Library
INCDIR = $(ROOT)/src/include
LIBDIR = $(ROOT)/lib

# Env
PLATFORM = $(shell uname)

# Target module
TARGET_MODULE  = $(HOME)/bin/ATlibTest

# Command

# C++
CXX = g++
CFLAGS = -Wall -O2

##############################################################
#
# Build ATlib Test
#
##############################################################
#SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
SRC_ATLIB = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
OBJ_ATLIB = $(addprefix $(BUILDDIR)/,$(notdir $(SRC_ATLIB:.cpp=.o)))

testatlib : $(TARGET_MODULE)

# Compile
$(TARGET_MODULE) : $(OBJ_ATLIB)
	@echo "compile..."
	ar rcs $(TARGET_ATLIB) $^
	@echo "done"

# Dependency
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/*/%.cpp
	$(CXX) $(CFLAGS) -I$(INCDIR) -c $< -o $@


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
