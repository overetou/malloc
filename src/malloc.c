/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:21:15 by overetou          #+#    #+#             */
/*   Updated: 2019/10/10 17:41:54 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/resource.h>
#include "malloc.h"

t_minfo	g_mmeta = {{NULL, NULL}, {{NULL, NULL}, {NULL, NULL}}, 0, 0, 0,
	0, smart_minit, 0};

size_t	get_mmax(void)
{
	struct rlimit rlp;

	if (getrlimit(RLIMIT_AS, &rlp) != 0)
		return (0);
	else
		return (rlp.rlim_cur);
}

int		get_zone_type(size_t s)
{
	if (s <= TNY_LIM)
		return (0);
	if (s <= SMLL_LIM)
		return (1);
	return (2);
}

void	*malloc(size_t size)
{
	void *ptr;

	if (size == 0)
		return (NULL);
	ptr = g_mmeta.smart_alloc(get_zone_type(size), size);
	if ((size_t)ptr % (size_t)16)
	{
		putstr("memory not aligned.\n");
		return (NULL);
	}
	return (ptr);
}

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*s;
	size_t	i;

	if (ULONG_MAX / size < nmemb)
		return (NULL);
	size = align_size(nmemb * size);
	if (size == 0)
		size = 1;
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	s = (char*)ptr;
	i = 0;
	while (i != size)
	{
		s[i] = 0;
		i++;
	}
	return (ptr);
}

void	*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	void	*new;
	size_t	max;

	new = calloc(nmemb, size);
	if (ptr)
	{
		max = get_block_size(ptr - 4 * sizeof(void*));
		if (new)
			mcopy(ptr, new, size > max ? max : size);
		free(ptr);
	}
	return (new);
}
