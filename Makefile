#!/usr/bin/make -f

NAME=scop

######### COLOR #############
COLOR_RED="\033[0;31m"
COLOR_GREEN="\033[0;32m"
COLOR_YELLOW="\033[0;33m"
COLOR_RESET="\033[0m"

######### MATRIX LIB ########
MATRIX_LIB_NAME = s21_matrix.a
MATRIX_LIB_DIR = ./matrix_lib/
MATRIX_LIB_FILE = $(MATRIX_LIB_DIR)$(MATRIX_LIB_NAME)
MATRIX_LIB = -L $(MATRIX_LIB_DIR) -l:s21_matrix.a
MATRIX_HEADERS_FILES=\
	s21_matrix.h

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

######### SRCS ##############
SRCS_DIR=src
SRCS = \
	main.c \
	parser.c \
	vector.c \
	config.c \
	camera.c \
	math.c \
	pipeline.c \
	shader.c \
	mesh.c \
	print.c \
	run.c \
	init.c \
	utils.c \
	texture.c

######### OBJS ##############
OBJS_DIR = ./obj
ALL_OBJS=$(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_DIR)/, $(ALL_OBJS))

HEADERS = $(addprefix $(HEADERS_DIR)/, $(HEADERS_FILES))
MATRIX_LIB_HEADERS = $(addprefix $(HEADERS_MATRIX_LIB_DIR)/, $(MATRIX_HEADERS_FILES))
INCLUDES=-I./includes
MATRIX_LIB_INCLUDES=-I.$(MATRIX_LIB_DIR)includes

FLAGS:=-lGLEW -lGLU -lGL -lglut
FLAGS:=$(FLAGS) -pedantic `sdl2-config --libs` -lGL -lm -O3 -g 

CC=gcc -std=c11 -Wall -Wextra -Werror
THREADS = 8

export MESA_GL_VERSION_OVERRIDE=3.3

all: $(OBJS_DIR)
	$(MAKE) -sC $(MATRIX_LIB_DIR)
	$(MAKE) -j$(THREADS) $(NAME)

multi:
	$(MAKE) -j$(THREADS) all

$(OBJS_DIR):
	/bin/mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
	$(CC) $(MATRIX_LIB_FILE) $(OBJS) $(FLAGS) -o $@ $(MATRIX_LIB)
	
	@echo -n $(COLOR_GREEN)
	@echo =================================
	@echo $(NAME) HAS BEEN MADE       
	@echo =================================	
	@echo -n $(COLOR_RESET)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS) $(MATRIX_LIB_HEADERS) | $(OBJS_DIR)
	$(CC) $(FLAGS) $(INCLUDES) $(MATRIX_LIB_INCLUDES) -c $< -o $@
		
clean:
	$(MAKE) -sC $(MATRIX_LIB_DIR) clean
	/bin/rm -rf $(OBJS_DIR)
fclean: clean
	$(MAKE) -sC $(MATRIX_LIB_DIR) fclean
	/bin/rm -f $(NAME)
re: fclean all

.PHONY: all, install, uninstall, clean, multi, fclean