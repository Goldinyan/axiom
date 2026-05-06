# --- Compiler & Flags ---
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O3

BREW_INC := /opt/homebrew/include
BREW_LIB := /opt/homebrew/lib
INCLUDES := -Icore/include -Iapp/include -Iextern -I$(BREW_INC)

# Standard Libraries (mit Raylib)
LIBS     := -L$(BREW_LIB) -lfmt -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

# CLI Libraries (ohne Raylib)
DEBUG_LIBS := -L$(BREW_LIB) -lfmt

OBJ_DIR  := obj
BIN_DIR  := bin

# Dateien finden
CORE_SRCS := $(shell find core/src -name "*.cpp")
APP_SRCS  := $(shell find app/src -name "*.cpp")
ALL_SRCS  := $(CORE_SRCS) $(APP_SRCS)

# Alle Objekt-Dateien
OBJS      := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(ALL_SRCS))

TARGET       := $(BIN_DIR)/axiom
DEBUG_TARGET := $(BIN_DIR)/axiom_debug

# --- Regeln ---
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking: $@"
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	./$(TARGET)

# --- CLI DEBUG REGELN ---

# Wir definieren cli_run so, dass es das Flag setzt und ALLES neu baut oder 
# zumindest die kritischen Dateien bereinigt.
cli: CXXFLAGS += -DNO_UI
cli: clean_main_and_ui debug
	./$(DEBUG_TARGET)

debug: $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking CLI Debug: $(DEBUG_TARGET)"
	$(CXX) $(OBJS) -o $(DEBUG_TARGET) $(DEBUG_LIBS)

clean_main_and_ui:
	@echo "Cleaning UI-dependent objects for CLI mode..."
	@rm -f $(OBJ_DIR)/app/src/main.o
	@rm -f $(OBJ_DIR)/app/src/camera.o
	@rm -f $(OBJ_DIR)/app/src/input_handler.o

.PHONY: all clean run debug cli clean_main_and_ui
