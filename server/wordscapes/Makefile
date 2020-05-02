TEST_EXE = Wordscapes-test
DICTIONARY = myDictionary

M_DIR = $(shell pwd)
M_BUILD_DIR = $(M_DIR)/build

vpath %.o $(M_BUILD_DIR)

OBJ = wordscapes.o

all: $(OBJ) $(BUILD_DIR)/$(DICTIONARY)
	cp $(addprefix $(M_BUILD_DIR)/, $(OBJ)) $(BUILD_DIR)/

$(M_BUILD_DIR)/$(TEST_EXE): $(OBJ) test.o
	g++ -g $(addprefix $(M_BUILD_DIR)/, $(notdir $^)) -o $@

$(BUILD_DIR)/$(DICTIONARY): $(M_DIR)/$(DICTIONARY)
	cp $< $@

$(M_BUILD_DIR)/$(DICTIONARY): $(M_DIR)/$(DICTIONARY)
	cp $< $@

%.o:%.cc
	mkdir -p $(M_BUILD_DIR)
	$(CXX) $(OPTIONS) -c $< -o $(M_BUILD_DIR)/$@

.PHONY: test
test: $(M_BUILD_DIR)/$(TEST_EXE) $(M_BUILD_DIR)/$(DICTIONARY)

clean:
	@rm -rf $(M_BUILD_DIR)
	@echo "Wordscapes clean finished!"
