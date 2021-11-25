# Makefile for ft_containers, updated Fri Nov 26 06:16:37 JST 2021

SRC := main.cpp
OBJ := main.o

# DO NOT ADD OR MODIFY ANY LINES ABOVE THIS -- run 'make source' to add files

NAME     := a.out

UNAME_S  := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CC   := g++
endif
ifeq ($(UNAME_S),Darwin)
	CC   := clang++
endif
CFLAGS   := -Wall -Wextra -Werror -std=c++98 --pedantic
RM       := rm -fr

SRC_DIR  := .
OBJ_DIR  := obj
SRCS     := $(addprefix $(SRC_DIR)/, $(SRC))
OBJS     := $(addprefix $(OBJ_DIR)/, $(OBJ))
HEADERS  := $(shell find . -not -path "./.ccls-cache/*" -type f -name '*.hpp' -print)
CPPLINT_FILTERS := #--filter=-runtime/references,-runtime/threadsafe_fn
COVERAGE := coverage
EXE_ARG  := 100

.PHONY:	all
all: $(NAME)

# Linking
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: lint
lint:
	cpplint $(CPPLINT_FILTERS) $(SRC) $(HEADERS)

.PHONY: leak
leak: CFLAGS += -g -fsanitize=leak
leak: test

.PHONY: address
address: CFLAGS += -g -fsanitize=address
address: test

.PHONY: thread
thread: CFLAGS += -g -fsanitize=thread
thread: test

.PHONY: memory
memory: CFLAGS += -g -fsanitize=memory
memory: test

.PHONY: gcov
gcov: CFLAGS   += -fPIC -fprofile-arcs -ftest-coverage
gcov: re
	./$(NAME) $(EXE_ARG)
	gcov -o $(OBJ_DIR) $(SRCS)

.PHONY: lcov
lcov: gcov
	mkdir -p ./$(COVERAGE)
	lcov --capture --directory . --output-file ./$(COVERAGE)/lcov.info

.PHONY: report
report : lcov
	genhtml ./$(COVERAGE)/lcov.info --output-directory ./$(COVERAGE)

.PHONY: clean
clean:
	$(RM) Makefile.bak $(NAME).dSYM $(OBJ_DIR)
	$(RM) *.so *.gcno *.gcda *.gcov *.info $(COVERAGE)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: valgrind
valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(EXE_ARG)

.PHONY: test
test: re
	./$(NAME) $(EXE_ARG)

.PHONY: test-coverage
test-coverage:
	@echo "Hello world"

.PHONY: source
source:
	@mv Makefile Makefile.bak
	@echo "# Makefile for ft_containers, updated `date`" >> Makefile
	@echo '' >> Makefile
	@echo SRC := `ls *.cpp` >> Makefile
	@echo OBJ := `ls *.cpp | sed s/cpp$$/o/` >> Makefile
	@echo '' >> Makefile
	@sed -n -e '/^# DO NOT ADD OR MODIFY/,$$p' < Makefile.bak >> Makefile
