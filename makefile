CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -pedantic -std=c++17

SRC_DIR := src
BUILD_DIR := build
DEST_DIR := dest

SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)

EXEC := main

all: $(DEST_DIR)/$(EXEC)

$(DEST_DIR)/$(EXEC): $(OBJ_FILES)
	@mkdir -p $(DEST_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEP_FILES)

clean:
	rm -rf $(BUILD_DIR) $(DEST_DIR)/$(EXEC)

.PHONY: all clean
