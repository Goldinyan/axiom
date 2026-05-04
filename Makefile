# --- Compiler & Flags ---
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O3

BREW_INC := /opt/homebrew/include
BREW_LIB := /opt/homebrew/lib

# Include-Pfade, damit der Compiler die .hpp Dateien findet
INCLUDES := -Icore/include -Iapp/include -Iextern -I$(BREW_INC)

# --- Libraries (Hier später GLFW, GL, etc. hinzufügen) ---
LIBS     := -lGL -lglfw -lglew -L$(BREW_LIB)

# --- Verzeichnisse ---
SRC_DIR  := .
OBJ_DIR  := obj
BIN_DIR  := bin

# --- Dateien finden ---
# Sucht alle .cpp Dateien im Core und App Verzeichnis
CORE_SRCS := $(shell find core/src -name "*.cpp")
APP_SRCS  := $(shell find app/src -name "*.cpp")
ALL_SRCS  := $(CORE_SRCS) $(APP_SRCS)

# Erzeugt die Liste der .o Dateien im obj/ Ordner
OBJS      := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(ALL_SRCS))

# Name des fertigen Programms
TARGET    := $(BIN_DIR)/axiom


# --- Regeln ---

# 1. Hauptziel: Das Programm bauen
all: $(TARGET)

# 2. Linken: Aus den .o Dateien die ausführbare Datei machen
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking: $@"
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# 3. Kompilieren: Aus jeder .cpp eine .o Datei machen
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 4. Aufräumen
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Hilfsregel zum Ausführen
run: all
	./$(TARGET)

.PHONY: all clean run
