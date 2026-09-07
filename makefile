# Makefile - Emergency Response System

CXX = g++
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

# Executable name
TARGET = emergency_system

# Build
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean
clean:
	rm -f $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)

# Clean and rebuild
rebuild: clean $(TARGET)

.PHONY: clean run rebuild