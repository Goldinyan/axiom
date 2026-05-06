# --- Compiler & Flags ---
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O3

# Homebrew Pfade
BREW_INC := /opt/homebrew/include
BREW_LIB := /opt/homebrew/lib

# Include-Pfade
INCLUDES := -Icore/include -Iapp/include -Iextern -I$(BREW_INC)

# --- Libraries für Raylib auf macOS ---
# Wir brauchen -lraylib und die macOS System-Frameworks
LIBS     := -L$(BREW_LIB) -lfmt -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

# --- Verzeichnisse ---
OBJ_DIR  := obj
BIN_DIR  := bin

# --- Dateien finden ---
CORE_SRCS := $(shell find core/src -name "*.cpp")
APP_SRCS  := $(shell find app/src -name "*.cpp")
ALL_SRCS  := $(CORE_SRCS) $(APP_SRCS)

OBJS      := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(ALL_SRCS))
TARGET    := $(BIN_DIR)/axiom

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

.PHONY: all clean run

# nur zum lexer testen::make cli

# Neues Target für CLI
DEBUG_TARGET := $(BIN_DIR)/axiom_debug
DEBUG_LIBS   := -L$(BREW_LIB) -lfmt  # KEIN raylib, KEINE Frameworks

# --- Neue Regeln ---

# Aufruf via: make debug
debug: $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking CLI Debug: $(DEBUG_TARGET)"
	$(CXX) $(OBJS) -o $(DEBUG_TARGET) $(DEBUG_LIBS)

# Spezielle Regel für das Kompilieren mit NO_UI
# Wir müssen hier aufpassen: Wenn wir zwischen UI und No-UI wechseln, 
# sollten wir die .o Dateien neu bauen oder ein zweites Verzeichnis nutzen.
cli: CXXFLAGS += -DNO_UI
cli: clean_objs debug
	./$(DEBUG_TARGET)

clean_objs:
	rm -rf $(OBJ_DIR)/app/src/main.o # Nur main muss zwingend neu für das Flag

.PHONY: debug cli clean_objs
