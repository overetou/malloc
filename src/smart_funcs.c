/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:59:07 by overetou          #+#    #+#             */
/*   Updated: 2019/10/07 18:08:52 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/resource.h>
#include "malloc.h"

void	*realloc(void *adr, size_t s)
{
	void	*ptr;
	size_t	max;

	g_mmeta.free_failed = 0;
	if (s == 0)
		s = 16;
	ptr = malloc(s);
	if (ptr && adr)
	{
		max = get_block_size(adr - 4 * sizeof(void*));
		mcopy(adr, ptr, s > max ? max : s);
		free(adr);
		if (g_mmeta.free_failed)
		{
			free(ptr);
			return (NULL);
		}
	}
	return (ptr);
}

void	*add_solo_zone(size_t size)
{
	size = find_contain(size, g_mmeta.page_size);
	append_block(&(g_mmeta.solo_segs), checked_map_pages(size), size);
	if (g_mmeta.solo_segs.last == NULL)
		return (NULL);
	g_mmeta.total += size - (4 * sizeof(void*));
	return ((void*)(&(g_mmeta.solo_segs.last->data)));
}

void	*cont_add(t_track_block *root, size_t size, const int zone_type)
{
	t_cont_mblock	*cont;

	cont = get_suitable_cont_mblock(root, size, zone_type);
	if (cont == NULL)
		return (NULL);
	g_mmeta.total += size - (4 * sizeof(void*));
	return (insert_sub_block(cont, size));
}

void	*true_malloc(const int zone_type, size_t size)
{
	if (zone_type > SMALL_CONT)
		return (add_solo_zone(size + 4 * sizeof(void*)));
	size = needed_size(size);
	return (cont_add(&(g_mmeta.conts[zone_type]), size, zone_type));
}

void	*smart_minit(int zone_type, size_t size)
{
	g_mmeta.mmax = get_mmax();
	if (!(g_mmeta.mmax))
		return (NULL);
	g_mmeta.page_size = (size_t)getpagesize();
	if (!(g_mmeta.page_size))
		return (NULL);
	g_mmeta.smart_alloc = true_malloc;
	return (true_malloc(zone_type, size));
}
