INC_PATH = ./inc
SRC_PATH = ./src
TEST_PATH = ./test
BUILD_PATH = ./build
OBJ_PATH = $(BUILD_PATH)/obj
OBJ_PATH_TESTING = $(BUILD_PATH)/obj/test

PROGRAM = $(BUILD_PATH)/$(notdir $(shell pwd))
CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -g -I $(INC_PATH)
LDFLAGS = -lm

SRC_FILES = $(shell find $(SRC_PATH) -name '*.c')
OBJ_FILES = $(subst $(SRC_PATH),$(OBJ_PATH),$(SRC_FILES:.c=.o))
DEP_FILES = $(subst $(SRC_PATH),$(OBJ_PATH),$(SRC_FILES:.c=.d))

# Lista de directorios donde buscar los archivos .c y .o (https://www.gnu.org/software/make/manual/html_node/General-Search.html)
vpath %.c $(SRC_PATH):$(SRC_PATH)/utils
vpath %.o $(OBJ_PATH):$(OBJ_PATH)/utils

# Mensajes de error y decoraciones
H_BAR_YELLOW = @echo -e '\033[1;33m=============================================================================\033[0m'
H_BAR_GREEN = @echo -e '\033[1;36m=============================================================================\033[0m'
OK_MSG = [\033[1;32m OK \033[0m']
FAIL_MSG = [\033[1;31m FAIL \033[0m']

# Testing input
TEST_INPUT = $(TEST_PATH)/figuras_in.bin

#Patterns Rules (https://www.gnu.org/software/make/manual/html_node/Pattern-Rules.html)
%.o: %.c
	$(H_BAR_YELLOW)
	@echo -e '\033[1;41m --> \033[0;1;34m Compilando: \033[0m \033[1;33m $< \033[0m\033[0m'
	$(H_BAR_YELLOW)
	@mkdir -p $(dir $(OBJ_FILES))
	$(CC) $(CFLAGS) -c $< -o $(subst $(SRC_PATH),$(OBJ_PATH),$(dir $<))$@
	@echo -e '\033[0;1;36m -> Generando dependencias: \033[0m'
	$(CC) $(CFLAGS) -MM $< > $(subst $(SRC_PATH),$(OBJ_PATH),$(dir $<))$(@:.o=.d)
	$(H_BAR_YELLOW)

$(PROGRAM): $(notdir $(OBJ_FILES))
	$(H_BAR_YELLOW)
	@echo -e '\033[1;41m --> \033[0;1;34m Linkeando: \033[0m \033[1;33m $@ \033[0m\033[0m'
	$(H_BAR_YELLOW)
	$(CC) $(OBJ_FILES) -o $(PROGRAM) $(LDFLAGS)
	$(H_BAR_YELLOW)

clean:
	$(H_BAR_YELLOW)
	@echo -e '\033[1;41m --> \033[0;1;34m Limpiando el directorio... \033[0m'
	$(H_BAR_YELLOW)
	@echo -e '\033[1;41m Borrando archivos \033[0m'
	@rm -f $(PROGRAM) $(OBJ_FILES) $(DEP_FILES)
	@echo -e '\033[1;41m Borrando directorios \033[0m'
	@rm -rf $(BUILD_PATH)
	$(H_BAR_YELLOW)

run: $(PROGRAM)
	$(H_BAR_GREEN)
	@echo -e '\033[1;41m --> \033[0;1;34m Ejecutando: \033[0m \033[1;35m $(notdir $<) \033[0m\033[0m'
	$(H_BAR_GREEN)
	@$(PROGRAM) $(TEST_INPUT)
	$(H_BAR_GREEN)

test: $(PROGRAM)
	$(H_BAR_GREEN)
	@echo -e '\033[1;41m --> \033[0;1;34m Test unitarios \033[0m\033[0m'
	$(H_BAR_GREEN)
	@mkdir -p $(OBJ_PATH_TESTING)
#Test 1
	@$(CC) $(CFLAGS) -c $(TEST_PATH)/test_parser.c -o $(OBJ_PATH_TESTING)/test_parser.o
	@$(CC) $(OBJ_FILES:$(OBJ_PATH)/main.o=) $(OBJ_PATH_TESTING)/test_parser.o -o $(OBJ_PATH_TESTING)/TEST_1 $(LDFLAGS)
#Running Tests
	@$(OBJ_PATH_TESTING)/TEST_1 $(TEST_INPUT) > $(TEST_PATH)/figuras_out.txt
	@diff $(TEST_PATH)/figuras_out.txt $(TEST_PATH)/figuras_out_ref.txt\
	&& echo 'Parser test [\033[1;32m OK \033[0m'] \
	|| echo 'Parser test [\033[1;31m FAIL \033[0m']
	$(H_BAR_GREEN)


info:
	$(H_BAR_YELLOW)
	@echo -e '\033[1;41m --> \033[0;1;34m Variables: \033[0m'
	$(H_BAR_YELLOW)
	@echo -e '\033[4;32m'SRC_PATH:'\033[0m ' $(SRC_PATH)
	@echo -e '\033[4;32m'INC_PATH:'\033[0m ' $(INC_PATH)
	@echo -e '\033[4;32m'BUILD_PATH:'\033[0m ' $(BUILD_PATH)
	@echo -e '\033[4;32m'OBJ_PATH:'\033[0m ' $(OBJ_PATH)
	@echo -e '\033[4;32m'SRC_FILES:'\033[0m ' $(SRC_FILES)
	@echo -e '\033[4;32m'OBJ_FILES:'\033[0m ' $(OBJ_FILES)
	@echo -e '\033[4;32m'DEP_FILES:'\033[0m ' $(DEP_FILES)
	@echo -e '\033[4;32m'PROGRAM:'\033[0m ' $(PROGRAM)
	$(H_BAR_YELLOW)