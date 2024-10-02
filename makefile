ifeq ($(OS),Windows_NT) #Handles Windows systems
CUR_DIR:= $(shell cd)
SRC_DIR:=$(CUR_DIR)\src
TARGETCPUS:=$(SRC_DIR)\CPUSched
TARGETPC:=$(SRC_DIR)\Producer-Consumer
PCSOURCES:= $(shell where /r $(TARGETPC) *.cpp)
CPUSSOURCES:= $(shell where /r $(TARGETCPUS) *.cpp)

PCHEADERS:= $(shell where /r $(TARGETPC) *.h)
CPUSHEADERS:= $(shell where /r $(TARGETCPUS) *.h)

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
TARGETCPUS:=$(SRC_DIR)\CPUSched
TARGETPC:=$(SRC_DIR)\Producer-Consumer
SOURCES:= $(shell find src -name "*.cpp")
HEADERS:= $(shell find src -name "*.h")
Junk:=find src -name "*.o"
RM = rm -rf
CP = cp -f
endif

#Compilier to be used
CXX := g++


#Information for compiling
PCOBJECTS:= $(patsubst %.cpp,%.o,$(PCSOURCES))
PCHEADERSDIRS:= $(sort $(dir $(PCHEADERS)))
PCINCLUDEFLAGS:=$(addprefix -I, $(PCHEADERSDIRS))

CPUSOBJECTS:= $(patsubst %.cpp,%.o,$(CPUSSOURCES))
CPUSHEADERSDIRS:= $(sort $(dir $(CPUSHEADERS)))
CPUSINCLUDEFLAGS:=$(addprefix -I, $(CPUSHEADERSDIRS))

#Name for the compiled object
ProjectName:= Program

all: CPUSched ProducerConsumer

CPUSched: $(TARGETCPUS) RMJunk

ProducerConsumer: $(TARGETPC) RMJunk

$(TARGETCPUS):$(CPUSOBJECTS)
	$(CXX) $^ -o CPUSched.exe

$(TARGETPC):$(PCOBJECTS)
	$(CXX) $^ -o ProducerConsumer.exe

$(TARGETCPUS)/%.o: $(TARGETCPUS)/%.cpp
	$(CXX) $< -c $(CPUSINCLUDEFLAGS) -o $@

$(TARGETPC)/%.o: $(TARGETPC)/%.cpp
	$(CXX) $< -c $(PCINCLUDEFLAGS) -o $@

RMJunk: #Removes the extra information left behind after compiling
	$(RM) $(shell $(Junk))
clean:  #Removes the compiled program
	$(RM) *.out *.exe