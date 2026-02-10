CXX := g++
CXXFLAGS := -std=c++17 -O3 -Wall -Wextra -Werror=return-type

ifndef TARGET
$(error TARGET is not set. Usage: make TARGET=your_target)
endif

BUILD_DIR := build
SRCS = $(wildcard $(TARGET)/*.cpp)

# Colors
RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[0;33m
BLUE   := \033[0;34m
RESET  := \033[0m

.PHONY: all run clean

all:
	@echo "$(YELLOW)Building $(TARGET)...$(RESET)"
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $(SRCS)
	@echo "$(GREEN)Build completed: $(BUILD_DIR)/$(TARGET)$(RESET)"

run: all
	@echo "$(YELLOW)Running $(TARGET)$(RESET)"
	@./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

