#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @
CPPUTEST_HOME=$(HOME)/cpputest

#---- Outputs ----#
COMPONENT_NAME = TddExamples

#--- Inputs ----#
CPP_PLATFORM = g++
PROJECT_HOME_DIR = $(HOME)/tdd/linkedlistv2

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/source\

TEST_SRC_DIRS = \
	$(PROJECT_HOME_DIR)/tests\
	
INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include\
  $(PROJECT_HOME_DIR)/include\
	
CPPUTEST_WARNINGFLAGS = -Wall -Wswitch-default -Werror 
#CPPUTEST_CFLAGS = -std=c89 
CPPUTEST_CFLAGS += -Wall -Wstrict-prototypes -pedantic
LD_LIBRARIES = -lpthread
	
  
ifeq ($(CPPUTEST_HOME),)
$(info CPPUTEST_HOME not set! See README.txt)
else  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
endif
