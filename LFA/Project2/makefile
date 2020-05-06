# MakeFile - Linux
# Needs working g++

$(info - - - - - - - - - - - - - -)
# DO NOT Comment inline, like below
# some makefile instruction  # some comment
# Don't know if '+=' can break stuff if Makefile is called recursively

# Do you want make to run in parralel?
# if not, just comment the MAKEFLAGS line
NPROCS = $(shell grep -c 'processor' /proc/cpuinfo)
MAKEFLAGS += -j$(NPROCS)

# Project Name (executable)
PROJECT = a.out
# Run Options      (For when running: make run) 
COMMANDLINE_OPTIONS += 

# Compiler
CPP = cpp
CXX = g++
CSTD = c++17

# ======== Project options  =====================
# THE folder to search for cpp files
SRC_FO += src
# search for include paths in these folders (includes just specified folder)
HDR_FO +=
# folders to Recursively search for includes (includes All subfolders)
REC_HDR_FO += inc

# ========= !!!!!!!!! =====================
# WATCH OUT THESE TWO FOLDERS. 'cleanAll' calls RM -RF on them !!
# where the *.d and *.o files will be stored
DEP_FO += .dep
# used for useful information storage
STAT_FO += .stats

# ======== Libraries for linking
LIBS += 

# we use <filesystem> which is a new thing, oh well
ifneq ($(filter $(shell g++ -dumpversion),1 2 3 4 5 6 7),)
	CXX = g++-8
	LIBS += -lstdc++fs
else ifeq ($(shell g++ -dumpversion),8)
	LIBS += -lstdc++fs
endif

# =============== Miscellaneous Compiler arguments
# Sanitizer options
SANITIZER += -fsanitize=address,undefined,signed-integer-overflow

# Always use this at compile / linking
GLOBAL_FLAGS += -std=$(CSTD) -g -O0 -Wall -Wextra

# Compiler options during compilation
COMPILE_OPTIONS += $(GLOBAL_FLAGS) $(SANITIZER) $(HEADERS) 

# Compiler options during linking the whole project
LINKING_OPTIONS += $(GLOBAL_FLAGS) $(SANITIZER) $(LIBS)

# Dependency options
DEPENDENCY_OPTIONS += -MM $(HEADERS)


# Creating stats folder
# Stats part, kinda useless but hey
# Print how many files recalculated dependencies and how many recompiled
RESET_COMPILE_CNT = mkdir -p $(STAT_FO); \
    rm -f $(STAT_FO)/bash_count.txt; \
	touch $(STAT_FO)/bash_count.txt
ADD_COMPILE_CNT = echo "X" >> $(STAT_FO)/bash_count.txt
SHOW_COMPILE_CNT = echo ""; echo Recompiled: \
	$$(cat $(STAT_FO)/bash_count.txt)  ---  \
	$$(cat $(STAT_FO)/bash_count.txt | wc -l)

SHELL_OUT := $(shell $(RESET_COMPILE_CNT))

#-- Do not edit below this line --
SUBDIRS_H := $(foreach d, $(REC_HDR_FO), $(shell find $(d) -type d) )
DIRS_H := $(sort $(HDR_FO) $(SUBDIRS_H))
HEADERS := $(foreach d, $(DIRS_H),-I$(d))

SUBDIRS_C := $(shell find $(SRC_FO) -type d)
DIRS_C := $(SUBDIRS_C)
SOURCE_FILES := $(foreach d, $(DIRS_C), $(wildcard $(d)/*.cpp))


# $(info DIRS = $(DIRS))
#  $(info SRC = $(HEADERS))
# $(info SHOW = $(SHOW_HOW_MANY))

# Create an object file of every cpp file
OBJECTS = $(patsubst $(SRC_FO)/%.cpp, $(DEP_FO)/%.o, $(SOURCE_FILES))

# Dependencies
DEPENDENCIES = $(patsubst $(SRC_FO)/%.cpp, $(DEP_FO)/%.d, $(SOURCE_FILES))

# Pretty print a path
noop=
space = $(noop) $(noop)
PRETTY_PATH = $(subst $(space),/,$(filter-out $(lastword $(subst /, ,$(1))),$(subst /, ,$(1))))\
 $(noop) $(lastword $(subst /, ,$(1)))

# Create .d files
$(DEP_FO)/%.d: $(SRC_FO)/%.cpp | createDepFolder
	@echo Preprocess: "$(subst $(DEP_FO),,$(call PRETTY_PATH,$@))"
	@$(CPP) $(DEPENDENCY_OPTIONS) $< -MT "$(DEP_FO)/$*.o $(DEP_FO)/$*.d" -MF $(DEP_FO)/$*.d

# Make $(PROJECT) the default target
all: $(DEPENDENCIES) $(PROJECT)

$(PROJECT): $(OBJECTS)
	@printf "\nLinking $(PROJECT)\n"
	@$(CXX) -o $(PROJECT) $(OBJECTS) $(LINKING_OPTIONS)
	@$(SHOW_COMPILE_CNT)

# Include dependencies (if there are any) and if i dont have to just clean
ifneq "$(strip $(DEPENDENCIES))" ""
#  if some argument contains 'clean' then i don't need to remake *.d files
 ifneq (clean,$(findstring clean,$(MAKECMDGOALS)))
#    $(info Am adaugat DEPS)
   -include $(DEPENDENCIES)
  endif
endif

# Compile every cpp file to an object
$(DEP_FO)/%.o: $(SRC_FO)/%.cpp | createDepFolder # | resetCompile
	@echo Compile: "$(subst $(SRC_FO),,$(call PRETTY_PATH,$<))"
	@$(CXX) -c $(COMPILE_OPTIONS) -o $@ $< 
	@$(ADD_COMPILE_CNT)

# Build & Run Project
run: $(PROJECT)
	./$(PROJECT) $(COMMANDLINE_OPTIONS)

createDepFolder:
#	@echo Creating dependency folders
	@$(foreach folder,$(patsubst src/%,$(DEP_FO)/%,$(SOURCE_FILES)),\
 mkdir -p $(dir $(folder));)

# Clean & Debug
.PHONY: makefile-debug
makefile-debug:

.PHONY: clean cleanDep cleanFiles cleanAll
clean:
	rm -f $(PROJECT) $(OBJECTS)
cleanDep:
	rm -f $(DEPENDENCIES)
cleanFiles: clean cleanDep

cleanAll:
	rm -rf $(DEP_FO)
	rm -rf $(STAT_FO)

# don't delete these, maybe will help for debugging
.PHONY: resetCompile addCompile showCompile
resetCompile:
	$(RESET_COMPILE_CNT)

addCompile:
	$(ADD_COMPILE_CNT)

showCompile:
	@$(SHOW_COMPILE_CNT)