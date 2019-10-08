/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:37:53 by overetou          #+#    #+#             */
/*   Updated: 2019/10/03 17:50:07 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <sys/mman.h>

size_t	find_contain(size_t to_contain, const size_t mult)
{
	size_t	container;

	container = to_contain / mult * mult;
	if (to_contain % mult)
		container += mult;
	return (container);
}

size_t	pagesize_countain(size_t to_contain)
{
	return (find_contain(to_contain, g_mmeta.page_size));
}

void	*map_pages(size_t s)
{
	void	*pages;

	pages = mmap(NULL, s, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
	0, 0);
	if (pages == MAP_FAILED)
	{
		write(2, "Page allocation failed.\n", 23);
		return (NULL);
	}
	return (pages);
}

void	updating_munmap(void *adr, size_t s)
{
	g_mmeta.total_mapped -= s;
	munmap(adr, s);
}

void	*checked_map_pages(size_t s)
{
	g_mmeta.total_mapped += s;
	if (g_mmeta.total_mapped > g_mmeta.mmax)
		return (NULL);
	return (map_pages(s));
}
