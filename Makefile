CXX = g++
CXXFLAGS =               \
		   -std=c++17    \
		   -Wall -Wextra \
		   -g            \
		   -I$(SRC_DIR)
LDFLAGS =

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

EXECUTABLE = $(BUILD_DIR)/zenith
TEST_EXECUTABLE = $(BUILD_DIR)/run_tests

OBJ_DIR = $(BUILD_DIR)/obj
TEST_OBJ_DIR = $(BUILD_DIR)/test_obj

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(TEST_OBJ_DIR)/%.o, $(TEST_SOURCES))

.PHONY: all test clean

# --- Main Rules ---

all: $(EXECUTABLE)

test: $(TEST_EXECUTABLE)

# --- Build Executable Rules ---

$(EXECUTABLE): $(OBJECTS) | $(BUILD_DIR)
	@echo "Linking main executable..."
	$(CXX) $(LDFLAGS) $^ -o $@

$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(OBJECTS) | $(BUILD_DIR)
	@echo "Linking test executable..."
	$(CXX) $(LDFLAGS) $^ -o $@

# --- Compile Object File Rules ---

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(TEST_OBJ_DIR)
	@echo "Compiling test $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Directory Creation Rules ---

$(OBJ_DIR):
	@mkdir -p $@

$(TEST_OBJ_DIR):
	@mkdir -p $@

$(BUILD_DIR):
	@mkdir -p $@

# --- Clean Rule ---

clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_D)

