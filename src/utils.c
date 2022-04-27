#include "utils.h"

#define _GNU_SOURCE


#define ERR_MALLOC "MALLOC FAILED"
#define ERR_MALLOC_SIZE "INVALID MALLOC SIZE"
#define EPSILON 0.0000001

static void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)destination;
	while (n > 0)
	{
		*(s++) = (unsigned char)c;
		n--;
	}
	return (destination);
}

void	*ft_memalloc(size_t size)
{
	void	*a;

	if (size + 1 < size)
		handle_error(ERR_MALLOC_SIZE);
	a = malloc(size);
	if (!a)
		handle_error(ERR_MALLOC);
	ft_memset(a, 0, size);
	return (a);
}

char	*ft_strdup(const char *src)
{
	char			*dupl;
	unsigned int	len;

	len = strlen(src);
	dupl = (char *)ft_memalloc((len + 1) * sizeof(char));
	
	len = 0;
	while (src[len])
	{
		dupl[len] = src[len];
		len++;
	}
	return (dupl);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*dst;
	size_t	i;

	dst = (char *)ft_memalloc((ft_strnlen(src, n) + 1) * sizeof(char));
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && s[i])
		++i;
	return (i);
}

int	handle_error(char *s)
{
	printf("ERROR:\t%s\n", s);
	exit(0);
}

int equal(double a, double b)
{
	return a - b < EPSILON;
}
