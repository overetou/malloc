/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mblocks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:40:24 by overetou          #+#    #+#             */
/*   Updated: 2019/10/03 17:31:20 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

size_t	get_block_size(t_mblock *b)
{
	return ((size_t)(b->end - (void*)(&(b->data))));
}

void	append_block(t_track_block *root, void *mapped_space, size_t size)
{
	if (root->first == NULL)
	{
		root->first = mapped_space;
		root->last = mapped_space;
	}
	else
	{
		root->last->next = mapped_space;
		root->last->next->prev = root->last;
		root->last = mapped_space;
	}
	root->last->end = (void*)(((size_t)mapped_space) + size);
}

void	remove_first_block(const t_mblock *b, t_track_block *root)
{
	if (b != root->last)
		root->first = b->next;
	else
		root->first = NULL;
}

void	remove_block(t_mblock *b, t_track_block *root)
{
	if (b == root->first)
		remove_first_block(b, root);
	else
	{
		if (b != root->last)
		{
			b->prev->next = b->next;
			b->next->prev = b->prev;
		}
		else
			root->last = b->prev;
	}
	updating_munmap((void*)b, (size_t)(b->end - (void*)b));
}
