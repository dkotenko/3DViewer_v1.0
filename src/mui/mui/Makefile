LIB=mui
NAME=$(LIB).a
HEADERS_DIR = includes
HEADERS_FILES=$(LIB).h browser.h  displaylist.h  gizmo.h  hslider.h  textlist.h  uicolor.h  vslider.h
SRCS_DIR=src

SRCS_FILES=gizmo.c glutmui.c displaylist.c uicolor.c miscui.c mui.c vslider.c textlist.c button.c pulldown.c hslider.c

SRCS=$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
HEADERS = $(addprefix $(HEADERS_DIR)/, $(HEADERS_FILES))
OBJ=$(SRCS:.c=.o)
INCLUDES=-I./includes
TEST_INCLUDES_DIR=tests/includes
TEST_INCLUDES=$(TEST_INCLUDES_DIR)/tests.h

TEST_DIR=tests
TEST_NAME=test.bin
TEST_SRCS=$(addprefix $(TEST_DIR)/$(SRCS_DIR)/test_, $(SRCS_FILES))
TEST_SRCS+= tests/$(SRCS_DIR)/test_main.c
TEST_OBJS=$(TEST_SRCS:%.c=%.o)

REPORT_NAME=report.html

CC=gcc -Wall -Wextra -std=c11 -lGLEW -lGLU -lGL -lglut # -Werror -
CC_GCOV=gcc -Wall -Wextra -Werror -std=c11 \
-fcf-protection=full -static-libgcc --coverage -lgcov
THREADS = 8

all: CC=$(CC_GCOV)
all:
	$(MAKE) -j$(THREADS) $(NAME)

gcov_report: CC=$(CC_GCOV)
gcov_report: fclean test
	./$(TEST_NAME)
	gcovr -r . -f src --html -o $(REPORT_NAME)

multi:
	$(MAKE) -j$(THREADS) all

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ) 
	@echo =================================
	@echo $(NAME) HAS BEEN MADE          
	@echo =================================	

%.o:%.c $(HEADERS)
	@$(CC) $(INCLUDES) -c $< -o $@
	@echo $<


		
clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f $(TEST_OBJS)
	find . -name "*.gcda" -type f -delete
	find . -name "*.gcno" -type f -delete
	/bin/rm -f $(REPORT_NAME)
fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(TEST_NAME)
re: fclean all



.PHONY: lib clean fclean all re multi
#all, clean, test, s21_matrix.a, gcov_report