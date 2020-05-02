EXE        = CheaterHub

export DIR        = $(shell pwd)
export BUILD_DIR  = $(DIR)/build

WORDSCAPES_DIR = wordscapes

vpath %.o $(BUILD_DIR)

export MAKE := make
export CXX := g++
export OPTIONS = -std=c++11
MODE ?= debug

OBJ = cheaterHub.o
OBJ_ADDITION = wordscapes.o

ifeq ($(strip $(MODE)), release)
	OPTIONS += -O2
	TARGET = $(EXE)
else
	OPTIONS += -g
	TARGET = $(EXE)-staging
endif

all: build_wordscapes $(TARGET)

build_wordscapes:
	@mkdir -p $(BUILD_DIR)
	$(MAKE) -C $(WORDSCAPES_DIR)

$(TARGET): $(OBJ)
	$(CXX) $(OPTIONS) -pthread \
		$(addprefix $(BUILD_DIR)/, $(OBJ)) \
		$(addprefix $(BUILD_DIR)/, $(OBJ_ADDITION)) \
		-o $(BUILD_DIR)/$@

$(OBJ):%.o:%.cc
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OPTIONS) -c $< -o $(BUILD_DIR)/$@

clean:
	$(MAKE) -C $(WORDSCAPES_DIR) clean
	rm -rf $(BUILD_DIR)
