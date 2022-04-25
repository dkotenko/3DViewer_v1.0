#ifndef UTILS_H
#define UTILS_H

#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <float.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/*
** UTILS
*/
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
size_t	ft_strnlen(const char *s, size_t maxlen);
void	*ft_memalloc(size_t size);
int		handle_error(char *s);
int 	equal(double a, double b);
char	**ft_strsplit(char const *s, char c);

#endif