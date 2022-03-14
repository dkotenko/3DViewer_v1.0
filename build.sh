#!/bin/bash

CC=gcc
CFLAGS="-I includes"
LDFLAGS=`pkg-config --libs glew`
LDFLAGS="$LDFLAGS -lglut"

$CC src/glut_example.c src/parser.c src/vector.c $CFLAGS $LDFLAGS -o glut