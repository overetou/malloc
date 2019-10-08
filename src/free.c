/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:19:57 by overetou          #+#    #+#             */
/*   Updated: 2019/10/02 17:52:34 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

char	free_cont_sb(void *adr, t_mblock *b, t_cont_mblock *c, t_track_block *t)
{
	while (b)
	{
		if ((void*)(&(b->data)) == adr)
		{
			remove_sub_block(b, c, t);
			return (1);
		}
		b = b->next;
	}
	return (0);
}

char	free_tracked_sb(void *adr, t_track_block *t)
{
	t_cont_mblock	*cont;

	cont = (t_cont_mblock*)(t->first);
	if (cont == NULL)
		return (0);
	while (((t_mblock*)cont) != t->last)
	{
		if ((void*)cont < adr && adr < cont->end)
			return (free_cont_sb(adr, cont->first, cont, t));
		cont = cont->next;
	}
	if ((void*)cont < adr && adr < cont->end)
		return (free_cont_sb(adr, cont->first, cont, t));
	return (0);
}

char	free_tracked_sseg(void *adr, t_track_block *t)
{
	t_mblock *head;

	head = t->first;
	if (head == NULL)
		return (0);
	while (head != t->last)
	{
		if ((void*)(&(head->data)) == adr)
		{
			remove_block(head, t);
			return (1);
		}
		head = head->next;
	}
	if ((void*)(&(head->data)) == adr)
	{
		remove_block(head, t);
		return (1);
	}
	return (0);
}

void	free_dive(void *adr)
{
	if (!free_tracked_sb(adr, &(g_mmeta.conts[TINY_CONT])))
	{
		if (!free_tracked_sb(adr, &(g_mmeta.conts[SMALL_CONT])))
		{
			if (!free_tracked_sseg(adr, &(g_mmeta.solo_segs)))
			{
				g_mmeta.free_failed = 1;
			}
		}
	}
}

void	free(void *adr)
{
	if (adr == NULL)
		return ;
	free_dive(adr);
}
