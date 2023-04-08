TARGET := gcaster
CC := clang++

SRC_DIR   = src
OBJ_DIR   = obj
BIN_DIR   = bin

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
SOURCES := $(filter-out $(wildcard $(SRC_DIR)/test*.cpp), $(SOURCES))
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

INCLUDE_DIR = -Iinclude -I/usr/local/include -I/opt/homebrew/Cellar/fftw/3.3.10_1/include -I/opt/homebrew/Cellar/sdl2/2.26.5/include
LIBRARY_DIR = -Llib -L/usr/local/lib -L/opt/homebrew/Cellar/fftw/3.3.10_1/lib -L/opt/homebrew/Cellar/sdl2/2.26.5/lib
LIBRARIES = -lfftw3 -lsdl2
DEFINITIONS = -DFFTWPP_SINGLE_THREAD
LD_FLAGS = -O2 -Wall -stdlib=libc++ -std=c++11 -Wno-reorder -Wno-uninitialized
# LD_FLAGS = -g -O2 -Wall -stdlib=libc++ -std=c++11 -Wno-reorder -Wno-uninitialized

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@$(CC) -o $@ $(LD_FLAGS) $(LD_FLAGS) $(LIBRARY_DIR) $(LIBRARIES)  $(OBJECTS)
	@echo "Linked OK"

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIR) $(LD_FLAGS) $(DEFINITIONS)
	@echo "Compiled " $<

.PHONEY: clean
clean:
	rm -f $(OBJECTS)
	
.PHONEY: remove
remove: clean
	@$(rm) $(BIN_DIR)/$(TARGET)

.PHONEY: list
list:
	@echo $(SOURCES)
