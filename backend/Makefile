# =====================================================
# COMPILADOR
# =====================================================
CXX = g++

# =====================================================
# DIRETÓRIOS PADRÃO (nível empresa)
# =====================================================
SRC_DIR   = src
INC_DIR   = include
BUILD_DIR = build
BIN_DIR   = bin
OBJ_DIR   = obj
DIST_DIR  = dist
TEST_DIR  = tests

TARGET    = $(BIN_DIR)/servidor.exe
TEST_BIN  = $(BIN_DIR)/tests.exe

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
# MYSQL (mantido do seu projeto)
# =====================================================
MYSQL_INCLUDE = -I"/c/mysql-connector-c++-9.7.0-winx64/mysql-connector-c++-9.7.0-winx64/include/jdbc"
MYSQL_LIB     = -L"/c/mysql-connector-c++-9.7.0-winx64/mysql-connector-c++-9.7.0-winx64/lib64/vs14"
MYSQL_LINK    = -lmysqlcppconn
LIBS          = -lws2_32

# =====================================================
# SOURCES
# =====================================================
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# TESTES (opcional)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/tests_%.o)

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
	@mkdir -p $(DIST_DIR)

# =====================================================
# LINK PRINCIPAL
# =====================================================
$(TARGET): $(OBJS)
	@echo "$(BLUE)[LINK APP]$(NC)"
	$(CXX) $^ -o $@ $(MYSQL_LIB) $(MYSQL_LINK) $(LIBS)
	@echo "$(GREEN)[OK] App gerado -> $(TARGET)$(NC)"

# =====================================================
# COMPILAÇÃO APP
# =====================================================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)[COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) $(MYSQL_INCLUDE) -c $< -o $@

# =====================================================
# TESTES
# =====================================================
tests: prepare $(TEST_BIN)
	@echo "$(GREEN)[OK] Testes prontos$(NC)"

$(TEST_BIN): $(TEST_OBJS) $(OBJS)
	@echo "$(BLUE)[LINK TESTS]$(NC)"
	$(CXX) $^ -o $@ \
	$(MYSQL_LIB) $(MYSQL_LINK) $(LIBS)

$(OBJ_DIR)/tests_%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)[TEST COMP]$(NC) $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =====================================================
# EXECUTAR APP
# =====================================================
run: all
	./$(TARGET)

# =====================================================
# EXECUTAR TESTES
# =====================================================
run-tests: tests
	./$(TEST_BIN)

# =====================================================
# CLEAN
# =====================================================
clean:
	@echo "$(RED)[CLEAN] removendo builds...$(NC)"
	@rm -rf $(BUILD_DIR) $(BIN_DIR) $(OBJ_DIR) $(DIST_DIR)

# =====================================================
# RELEASE PACKAGE (deploy local)
# =====================================================
dist: all
	@echo "$(BLUE)[DIST] criando pacote...$(NC)"
	@mkdir -p $(DIST_DIR)
	@cp $(TARGET) $(DIST_DIR)/
	@cp -r $(INC_DIR) $(DIST_DIR)/
	@echo "$(GREEN)[OK] pacote criado em $(DIST_DIR)$(NC)"

# =====================================================
# DEPLOY SIMULADO (produção local)
# =====================================================
deploy: dist
	@echo "$(BLUE)[DEPLOY] enviando para produção (simulado)...$(NC)"
	@mkdir -p deploy
	@cp -r $(DIST_DIR)/* deploy/
	@echo "$(GREEN)[OK] Deploy concluído (simulado)$(NC)"

# =====================================================
# DEPENDÊNCIAS AUTOMÁTICAS
# =====================================================
-include $(DEPS)

# =====================================================
# BANNER
# =====================================================
banner:
	@echo "$(GREEN)======================================$(NC)"
	@echo "$(GREEN)   HELP DESK BACKEND (C++ SERVER)     $(NC)"
	@echo "$(GREEN)   MODE: $(MODE)                       $(NC)"
	@echo "$(GREEN)======================================$(NC)"