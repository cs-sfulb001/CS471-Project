ifeq ($(OS),Windows_NT) #Handles Windows systems
CUR_DIR:= $(shell cd)
SRC_DIR:=$(CUR_DIR)\src
SOURCES:= $(shell where /r $(SRC_DIR) *.cpp)
HEADERS:= $(shell where /r $(SRC_DIR) *.h)
Junk:=where /r $(SRC_DIR) *.o
RM = del /Q /F
CP = copy /Y
ifdef ComSpec #Unknow OS only handles clean theoreticly
SHELL := $(ComSpec)
endif
ifdef COMSPEC #Unknow OS only handles clean theoreticly
SHELL := $(COMSPEC)
endif
else #Handles Linux systems (Untested)
CUR_DIR:= $(shell pwd)
SRC_DIR:=$(CUR_DIR)\src
SOURCES:= $(shell find src -name "*.cpp")
HEADERS:= $(shell find src -name "*.h")
Junk:=find src -name "*.o"
RM = rm -rf
CP = cp -f
endif

#Compilier to be used
CXX := g++

#Targets to be compilied
TARGETS:=$(SRC_DIR)

#Information for compiling
OBJECTS:= $(patsubst %.cpp,%.o,$(SOURCES))
HEADERSDIRS:= $(sort $(dir $(HEADERS)))
INCLUDEFLAGS:=$(addprefix -I, $(HEADERSDIRS))

#Name for the compiled object
ProjectName:= Program

all: $(TARGETS) RMJunk

$(TARGETS):$(OBJECTS)
	$(CXX) $^ -o $(ProjectName).exe

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $< -c $(INCLUDEFLAGS) -o $@

RMJunk: #Removes the extra information left behind after compiling
	$(RM) $(shell $(Junk))
clean:  #Removes the compiled program
	$(RM) *.out *.exe