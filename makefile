# Makefile - Emergency Response System

CXX      = g++
CXXFLAGS = -std=c++11 -Wall -g

# All source files
SRCS = main.cpp \
       Composite.cpp \
       EmergencyTask.cpp \
       FireDepartment.cpp \
       PoliceDepartment.cpp \
       MedicalDepartment.cpp \
       Decorator.cpp \
       PriorityDecorator.cpp \
       SafetyCheckDecorator.cpp \
       ActiveTaskIterator.cpp \
       CompleteDfsIterator.cpp \
       AlertState.cpp \
       ResponseState.cpp \
       RecoveryState.cpp \
       Component.cpp

# Executable name — MinGW on Windows appends .exe automatically
TARGET = emergency_system

# Detect OS: on Windows (MinGW/MSYS) COMSPEC is set
ifdef COMSPEC
    EXE    = $(TARGET).exe
    RM     = del /f /q
    RUN    = $(EXE)
else
    EXE    = $(TARGET)
    RM     = rm -f
    RUN    = ./$(TARGET)
endif

# ── Build ──────────────────────────────────────────────────────────────────────
$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# ── Run ────────────────────────────────────────────────────────────────────────
run: $(EXE)
	$(RUN)

# ── Clean ──────────────────────────────────────────────────────────────────────
clean:
	$(RM) $(EXE)

# ── Clean and rebuild ──────────────────────────────────────────────────────────
rebuild: clean $(EXE)

.PHONY: run clean rebuild