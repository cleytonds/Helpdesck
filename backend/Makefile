# ======================================================
# MAKEFILE - HELPDESK C++ REST API
# ======================================================

CXX = g++

# =====================================================
# DIRETÓRIOS
# =====================================================
SRC_DIR   = src
INC_DIR   = include
BIN_DIR   = bin
OBJ_DIR   = obj
DIST_DIR  = dist

CONTROLLERS_DIR = src/controllers
CORE_DIR        = src/core
UTILS_DIR       = src/utils
SERVICES_DIR    = src/services
REPOSITORIES_DIR = src/repositories
DATABASE_DIR    = src/database
HANDLERS_DIR    = src/handlers
ROUTES_DIR      = src/routes

TARGET = $(BIN_DIR)/servidor.exe

# =====================================================
# MODO DE BUILD
# =====================================================
MODE ?= debug

ifeq ($(MODE),debug)
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I$(INC_DIR) -MMD -MP
else
CXXFLAGS = -std=c++17 -O2 -I$(INC_DIR) -MMD -MP
endif

# =====================================================
# MYSQL / MARIADB
# =====================================================
MYSQL_INCLUDE = -I/mingw64/include/mariadb
MYSQL_LIB     = -L/mingw64/lib
MYSQL_LINK    = -lmariadb

# =====================================================
# LIBS
# =====================================================
LIBS = -lws2_32 -lssl -lcrypto -lz

# =====================================================
# FONTES
# =====================================================
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

CONTROLLER_SRCS  := $(wildcard $(CONTROLLERS_DIR)/*.cpp)
CORE_SRCS        := $(wildcard $(CORE_DIR)/server/*.cpp) \
                    $(wildcard $(CORE_DIR)/middleware/*.cpp)

UTILS_SRCS       := $(wildcard $(UTILS_DIR)/*.cpp)
SERVICES_SRCS    := $(wildcard $(SERVICES_DIR)/*.cpp)
REPOSITORY_SRCS  := $(wildcard $(REPOSITORIES_DIR)/*.cpp)
DATABASE_SRCS    := $(wildcard $(DATABASE_DIR)/*.cpp)
HANDLER_SRCS     := $(wildcard $(HANDLERS_DIR)/*.cpp)
ROUTES_SRCS      := $(wildcard $(ROUTES_DIR)/*.cpp)

ALL_SRCS := $(SRCS) \
            $(CONTROLLER_SRCS) \
            $(CORE_SRCS) \
            $(UTILS_SRCS) \
            $(SERVICES_SRCS) \
            $(REPOSITORY_SRCS) \
            $(DATABASE_SRCS) \
            $(HANDLER_SRCS) \
            $(ROUTES_SRCS)

# =====================================================
# OBJETOS
# =====================================================
OBJS := $(ALL_SRCS:%.cpp=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(SRC_DIR)/%=$(OBJ_DIR)/%)
OBJS := $(OBJS:$(CONTROLLERS_DIR)/%=$(OBJ_DIR)/controllers/%)
OBJS := $(OBJS:$(CORE_DIR)/server/%=$(OBJ_DIR)/core/server/%)
OBJS := $(OBJS:$(CORE_DIR)/middleware/%=$(OBJ_DIR)/core/middleware/%)
OBJS := $(OBJS:$(UTILS_DIR)/%=$(OBJ_DIR)/utils/%)
OBJS := $(OBJS:$(SERVICES_DIR)/%=$(OBJ_DIR)/services/%)
OBJS := $(OBJS:$(REPOSITORIES_DIR)/%=$(OBJ_DIR)/repositories/%)
OBJS := $(OBJS:$(DATABASE_DIR)/%=$(OBJ_DIR)/database/%)
OBJS := $(OBJS:$(HANDLERS_DIR)/%=$(OBJ_DIR)/handlers/%)
OBJS := $(OBJS:$(ROUTES_DIR)/%=$(OBJ_DIR)/routes/%)

DEPS := $(OBJS:.o=.d)

# =====================================================
# CORES
# =====================================================
GREEN = \033[0;32m
BLUE  = \033[0;34m
RED   = \033[0;31m
NC    = \033[0m

# =====================================================
# DEFAULT
# =====================================================
all: banner prepare $(TARGET)

# =====================================================
# PREPARAR DIRETÓRIOS
# =====================================================
prepare:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/controllers
	@mkdir -p $(OBJ_DIR)/core/server
	@mkdir -p $(OBJ_DIR)/core/middleware
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/services
	@mkdir -p $(OBJ_DIR)/repositories
	@mkdir -p $(OBJ_DIR)/database
	@mkdir -p $(OBJ_DIR)/handlers
	@mkdir -p $(OBJ_DIR)/routes
	@mkdir -p $(DIST_DIR)

# =====================================================
# LINK FINAL
# =====================================================
$(TARGET): $(OBJS)
	@echo "$(BLUE)[LINK]$(NC)"
	$(CXX) $^ -o $@ $(MYSQL_LIB) $(MYSQL_LINK) $(LIBS)
	@echo "$(GREEN)[OK] Servidor gerado -> $(TARGET)$(NC)"

# =====================================================
# COMPILAÇÃO
# =====================================================
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

$(OBJ_DIR)/controllers/%.o: $(CONTROLLERS_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/controllers
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

$(OBJ_DIR)/core/server/%.o: $(CORE_DIR)/server/%.cpp
	@mkdir -p $(OBJ_DIR)/core/server
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

$(OBJ_DIR)/core/middleware/%.o: $(CORE_DIR)/middleware/%.cpp
	@mkdir -p $(OBJ_DIR)/core/middleware
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

$(OBJ_DIR)/utils/%.o: $(UTILS_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/utils
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

$(OBJ_DIR)/services/%.o: $(SERVICES_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/services
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

$(OBJ_DIR)/repositories/%.o: $(REPOSITORIES_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/repositories
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

$(OBJ_DIR)/database/%.o: $(DATABASE_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/database
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

$(OBJ_DIR)/handlers/%.o: $(HANDLERS_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/handlers
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

$(OBJ_DIR)/routes/%.o: $(ROUTES_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/routes
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

# =====================================================
# RUN
# =====================================================
run: all
	./$(TARGET)

# =====================================================
# CLEAN
# =====================================================
clean:
	@echo "$(RED)[CLEAN]$(NC)"
	@rm -rf $(BIN_DIR) $(OBJ_DIR) $(DIST_DIR)

# =====================================================
# DEPENDÊNCIAS
# =====================================================
-include $(DEPS)

# =====================================================
# BANNER
# =====================================================
banner:
	@echo "$(GREEN)======================================$(NC)"
	@echo "$(GREEN)   HELP DESK C++ REST API           $(NC)"
	@echo "$(GREEN)   MVC + Services Architecture      $(NC)"
	@echo "$(GREEN)   Mode: $(MODE)                   $(NC)"
	@echo "$(GREEN)======================================$(NC)"