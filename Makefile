# Makefile for ft_containers, updated Tue Nov 30 06:50:22 JST 2021

SRC := main.cpp
OBJ := main.o
DEP := main.d

# DO NOT ADD OR MODIFY ANY LINES ABOVE THIS -- run 'make source' to add files

NAME_FT   := ft.out
NAME_STD  := std.out
RES_FT    := ft.txt
RES_STD   := std.txt

CXX        = clang++
CFLAGS    := -Wall -Wextra -Werror -std=c++98 -pedantic-errors
RM        := rm -fr
DFLAGS	   = -MMD -MP

SRC_DIR   := .
OBJ_DIR   := ./obj
SRCS      := $(addprefix $(SRC_DIR)/, $(SRC))
OBJS_STD  := $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=_std.o))
DEPS_STD  := $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=_std.d))
OBJS_FT  := $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=_ft.o))
DEPS_FT  := $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=_ft.d))
HEADERS   := $(shell find . -not -path "./.ccls-cache/*" -type f -name '*.hpp' -print)
CPPLINT_FILTERS := --filter=-legal/copyright,-runtime/references,-build/include_what_you_use,-runtime/int
COVERAGE  := coverage
EXE_ARG   := 100
UNIT_TEST := unit_test

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -D LINUX
endif

-include $(DEPS_FT) $(DEPS_STD)

.PHONY:	all
all: $(NAME_FT) $(NAME_STD)

# Linking
$(NAME_STD): $(OBJS_STD)
	$(CXX) $(CFLAGS) -o $@ $^

$(NAME_FT): $(OBJS_FT)
	$(CXX) $(CFLAGS) -o $@ $^

# Compiling
$(OBJ_DIR)/%_std.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -o $@ -c $< $(DFLAGS)

$(OBJ_DIR)/%_ft.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -D NAMESPACE_FT=1 -o $@ -c $< $(DFLAGS)

.PHONY: lint
lint:
	cpplint --recursive $(CPPLINT_FILTERS) $(SRC) $(HEADERS)

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
gcov: CXX = g++
gcov: CFLAGS   += -fPIC -fprofile-arcs -ftest-coverage
gcov: re
	./$(NAME_FT)
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
	$(RM) Makefile.bak $(NAME_STD).dSYM $(NAME_FT).dSYM $(OBJ_DIR)
	$(RM) *.so *.gcno *.gcda *.gcov *.info $(COVERAGE)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME_STD) $(NAME_FT)

.PHONY: re
re: fclean all

.PHONY: valgrind
valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME_FT)

.PHONY: test
test: re
	./$(NAME_FT)

.PHONY: std
std: re
	./$(NAME_STD)

.PHONY: diff
diff: re
	./$(NAME_FT) > $(RES_FT)
	./$(NAME_STD) > $(RES_STD)
	diff -a $(RES_FT) $(RES_STD)
	$(RM) $(RES_FT) $(RES_STD)

.PHONY: unit
unit:
	$(CXX) -std=c++11 -Wall -I$(UNIT_TEST) ./$(UNIT_TEST)/vector.cpp ./$(UNIT_TEST)/CatchMain.cpp -o ./$(UNIT_TEST)/$(NAME_FT)
	./$(UNIT_TEST)/$(NAME_FT) --success

.PHONY: unit-compact
unit-compact:
	$(CXX) -std=c++11 -Wall -I$(UNIT_TEST) ./$(UNIT_TEST)/vector.cpp ./$(UNIT_TEST)/CatchMain.cpp -o ./$(UNIT_TEST)/$(NAME_FT)
	./$(UNIT_TEST)/$(NAME_FT) --reporter compact --success

.PHONY: unit-val
unit-val: fclean
	$(CXX) -std=c++11 -Wall -I$(UNIT_TEST) ./$(UNIT_TEST)/vector.cpp ./$(UNIT_TEST)/CatchMain.cpp -o ./$(UNIT_TEST)/$(NAME_FT)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(UNIT_TEST)/$(NAME_FT) --reporter compact --success

.PHONY: source
source:
	@mv Makefile Makefile.bak
	@echo "# Makefile for ft_containers, updated `date`" >> Makefile
	@echo '' >> Makefile
	@echo SRC := `ls *.cpp` >> Makefile
	@echo OBJ := `ls *.cpp | sed s/cpp$$/o/` >> Makefile
	@echo DEP := `ls *.cpp | sed s/cpp$$/d/` >> Makefile
	@echo '' >> Makefile
	@sed -n -e '/^# DO NOT ADD OR MODIFY/,$$p' < Makefile.bak >> Makefile
