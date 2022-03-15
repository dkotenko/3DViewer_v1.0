#!/bin/bash

CC=gcc
CFLAGS="-I includes"
LDFLAGS=`pkg-config --libs glew`
LDFLAGS="$LDFLAGS -lglut"
echo $LDFLAGS
$CC src/glut.c src/parser.c src/vector.c $CFLAGS $LDFLAGS -o glut