#!/usr/bin/make -f

######### COLOR #############
COLOR_RED="\033[0;31m"
COLOR_GREEN="\033[0;32m"
COLOR_YELLOW="\033[0;33m"
COLOR_RESET="\033[0m"
#############################

######### APP ###############
NAME=3DViewer
VERSION=V1.0
ARCHIVE_NAME=$(NAME)-$(VERSION).tar.gz
#############################

######### MATRIX LIB ########
MATRIX_LIB_NAME = s21_matrix.a
MATRIX_LIB_DIR = ./matrix_lib/
MATRIX_LIB_FILE = $(MATRIX_LIB_DIR)$(MATRIX_LIB_NAME)
MATRIX_LIB = -L $(MATRIX_LIB_DIR) -l:s21_matrix.a
MATRIX_HEADERS_FILES=\
	s21_matrix.h
#############################

######### INCLUDES ##########
HEADERS_MATRIX_LIB_DIR = $(MATRIX_LIB_DIR)includes
HEADERS_DIR = includes
HEADERS_FILES=\
	parser.h \
	cvector.h \
	scop.h \
	vector.h \
	utils.h \
	stb_image_write.h \
	stb_image.h
#############################



######### SRCS ##############
SRCS_DIR=src
SRCS_FILES_FOR_TEST=
SRCS_NOT_TEST = \
	glarea-example.c \
	parser.c \
	vector.c \
	camera.c \
	math.c \
	pipeline.c \
	shader.c \
	mesh.c \
	print.c \
	init.c \
	utils.c \
	texture.c # \
	run.c \

SRCS_FILES=$(SRCS_FOR_TEST) $(SRCS_NOT_TEST)
#############################


SRCS_FOR_TEST=$(addprefix $(SRCS_DIR)/, $(SRCS_FILES_FOR_TEST))
SRCS=$(SRCS_FOR_TEST) $(addprefix $(SRCS_DIR)/, $(SRCS_NOT_TEST))

HEADERS = $(addprefix $(HEADERS_DIR)/, $(HEADERS_FILES))
MATRIX_LIB_HEADERS = $(addprefix $(HEADERS_MATRIX_LIB_DIR)/, $(MATRIX_HEADERS_FILES))
OBJ=$(SRCS:.c=.o)
OBJ_FOR_TEST=$(SRCS_FOR_TEST:.c=.o)
INCLUDES=-I./includes
MATRIX_LIB_INCLUDES=-I.$(MATRIX_LIB_DIR)includes
TEST_INCLUDES_DIR=tests/includes
TEST_INCLUDES=$(TEST_INCLUDES_DIR)/tests.h

TEST_DIR=tests
TEST_NAME=test.out
TEST_LIB_LINKS =  -lcheck -lm -lpthread -lrt -lsubunit
TEST_FILES= \
		test_main.c
TEST_SRCS=$(addprefix $(TEST_DIR)/$(SRCS_DIR)/, $(TEST_FILES))
TEST_OBJS=$(TEST_SRCS:%.c=%.o)

REPORT_NAME=report.html


FLAGS:=-lGLEW -lGLU -lGL -lglut
FLAGS:=$(FLAGS) -pedantic -lGL -lm -O3 -g 

CC=gcc -std=c11 -Wall -Wextra -Werror
CC_GCOV=gcc -Wall -Wextra -Werror -std=c11 \
-fcf-protection=full -static-libgcc --coverage -lgcov
THREADS = 8

PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0 epoxy)
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0 epoxy)

export MESA_GL_VERSION_OVERRIDE=3.3

all:
	$(MAKE) -sC $(MATRIX_LIB_DIR)
	$(MAKE) -j$(THREADS) $(NAME)
	
gcov_report: CC=$(CC_GCOV)
gcov_report: fclean test
	./$(TEST_NAME)
	gcovr -r . -f src --html-details -o $(REPORT_NAME)

multi:
	$(MAKE) -j$(THREADS) all

test: $(TEST_NAME)

install: all
	install -m 755 -d includes $(path)
	install -m 755 -d microui $(path)
	install -m 755 -d scripts $(path)
	install -m 755 -d src $(path)
	install -m 755 -d tests $(path)
	install -m 755 * $(path)

uninstall:
	make -c $(path) fclean
	rm -rf $(path)/Makefile
	rm -rf $(path)/includes
	rm -rf $(path)/microui
	rm -rf $(path)/scripts
	rm -rf $(path)/src
	rm -rf $(path)/test

dist:
	touch $(ARCHIVE_NAME)
	tar -czf $(ARCHIVE_NAME) --exclude=$(ARCHIVE_NAME) .

dvi:
	./scripts/make_dvi.sh

$(TEST_NAME): $(NAME) $(TEST_OBJS)
	$(CC) $(MATRIX_LIB_FILE) $(TEST_OBJS) $(OBJ_FOR_TEST) -o $@ $(TEST_LIB_LINKS) $(MATRIX_LIB)

$(TEST_DIR)/%.o:$(TEST_DIR)/%.c $(TEST_INCLUDES)
	$(CC) -I./$(TEST_DIR)/includes -I./includes -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(MATRIX_LIB_FILE) $(OBJ) $(FLAGS) -o $@ $(MATRIX_LIB) $(LIBS)
	
	@echo -n $(COLOR_GREEN)
	@echo =================================
	@echo $(NAME) HAS BEEN MADE       
	@echo =================================	
	@echo -n $(COLOR_RESET)

%.o:%.c $(HEADERS) $(MATRIX_LIB_HEADERS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(MATRIX_LIB_INCLUDES) -c $< -o $@
	@echo $<


		
clean:
	$(MAKE) -sC $(MATRIX_LIB_DIR) clean
	/bin/rm -f $(OBJ)
	/bin/rm -f $(TEST_OBJS)
	find . -name "*.gcda" -type f -delete
	find . -name "*.gcno" -type f -delete
	/bin/rm -f $(REPORT_NAME)
	/bin/rm -f report.* plot.txt
fclean: clean
	$(MAKE) -sC $(MATRIX_LIB_DIR) fclean
	/bin/rm -f $(NAME)
	/bin/rm -f $(TEST_NAME)
distclean: fclean
	/bin/rm -f $(ARCHIVE_NAME)
re: fclean all



.PHONY: lib clean fclean all re multi

INSTALLATION_DIRECTORY=/opt/smartcalc/v1.0

PHONY: all, install, uninstall, clean, distclean, mostyclean, realclean, TAGS, info, dvi, dist, test, gcov_report
#all, clean, test, s21_matrix.a, gcov_report