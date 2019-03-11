EXE = run_the_game
OBJ_DIR = Debug/bin/Src
SRC_DIR = Code/Src

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS), Windows)
	external_include_dirs := external_dependencies/SDL2-2.0.9/32bit/include \
		external_dependencies/SDL2_image-2.0.4/32bit/include \
		external_dependencies/DevIL_Windows_SDK/include
	external_lib_dirs := external_dependencies/SDL2-2.0.9/32bit/lib \
		external_dependencies/SDL2_image-2.0.4/32bit/lib \
		external_dependencies/DevIL_Windows_SDK/lib/x86/minGW
	external_libraries_flags := mingw32 SDL2main SDL2 SDL2_image DevIL ILU ILUT
else
	external_include_dirs := /usr/local/include/SDL2 \
		/usr/local/include/IL
	external_lib_dirs := /usr/local/lib
	LD_LIB_PATH := -Wl,-rpath=/usr/local/lib
	external_libraries_flags := SDL2main SDL2 SDL2_image IL ILU ILUT
endif

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
CXX = g++
CPPFLAGS = -std=c++14
HIDE_CONSOLE_WINDOW = #-Wl,-subsystem,windows# uncomment to work
CFLAGS = -g -Wall -pedantic $(HIDE_CONSOLE_WINDOW)
INCLUDE_PATHS = $(foreach includeDir, $(external_include_dirs),-I$(includeDir))
LIBRARY_PATHS = $(foreach libDir, $(external_lib_dirs),-L$(libDir))
LINKER_FLAGS = $(foreach lib, $(external_libraries_flags),-l$(lib))

# é preciso ter o CygWin para o clean funcionar corretamente,
# pois ele simula os comandos de linux no windows

.PHONY: all clean tests

all: build tests

build: $(EXE)

$(EXE): $(OBJ)
ifeq ($(detected_OS), Windows)
	$(CXX) $^ $(CPPFLAGS) $(CFLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $@
else
	$(CXX) $^ $(CPPFLAGS) $(CFLAGS) $(LD_LIB_PATH) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $@
endif
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
ifeq ($(detected_OS), Windows)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -c $< -o $@
else
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LD_LIB_PATH) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -c $< -o $@ 
endif

TEST_EXECUTABLE = run_all_tests
TEST_OBJ_DIR = Debug/bin/Tests
TEST_SRC_DIR = Code/Tests

Tests_src = $(wildcard $(TEST_SRC_DIR)/*.cpp)
Tests_obj = $(Tests_src:$(TEST_SRC_DIR)/%.cpp=$(TEST_OBJ_DIR)/%.o)

tests: $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(Tests_obj)
ifeq ($(detected_OS), Windows)
	$(CXX) $^ $(CPPFLAGS) $(CFLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $@
else
	$(CXX) $^ $(CPPFLAGS) $(CFLAGS) $(LD_LIB_PATH) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $@
endif

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
ifeq ($(detected_OS), Windows)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -c $< -o $@
else
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LD_LIB_PATH) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -c $< -o $@ 
endif

install: install_SDL2 install_SDL2_image install_IL

install_SDL2:
ifneq ($(detected_OS), Windows)
	apt-cache search libsdl2
	sudo apt-get install libsdl2-dev
endif

install_SDL2_image:
ifneq ($(detected_OS), Windows)
	apt-cache search libsdl2-image
	sudo apt-get install libsdl2-image-dev
endif

install_IL:
ifneq ($(detected_OS), Windows)
	@mkdir -p temp
	@cd ./temp && sudo wget 'http://downloads.sourceforge.net/openil/DevIL-1.8.0.tar.gz' \
		&& tar -xvzf DevIL-1.8.0.tar.gz && cd DevIL/DevIL && mkdir -p build \
		&& cd build && cmake .. && make && sudo make install
	$(RM) -rf temp
endif

clean:
	$(RM) *~ $(OBJ) $(Tests_obj) $(EXE) $(TEST_EXECUTABLE)