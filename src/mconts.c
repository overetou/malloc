/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mconts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:45:12 by overetou          #+#    #+#             */
/*   Updated: 2019/10/03 17:48:43 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

size_t			get_interstice_size(t_mblock *b, t_cont_mblock *cont)
{
	if (b->next == NULL)
		return ((size_t)((cont->end) - (b->end)));
	return ((size_t)(((void*)(b->next)) - (b->end)));
}

void			init_cont_mblock_info(t_cont_mblock *cont)
{
	cont->best_chunk = (size_t)((cont->end) - ((void*)(&(cont->data))));
	cont->first = NULL;
	((t_mblock*)(&(cont->data)))->end = NULL;
}

void			update_cont_mblock_info(t_cont_mblock *cont)
{
	t_mblock	*head;
	size_t		biggest;
	size_t		interstice;

	head = cont->first;
	biggest = (size_t)((void*)(head) - (void*)(&(cont->data)));
	while (head)
	{
		interstice = get_interstice_size(head, cont);
		if (interstice > biggest)
			biggest = interstice;
		head = head->next;
	}
	cont->best_chunk = biggest;
}

t_cont_mblock	*append_cont(t_track_block *root, size_t size)
{
	append_block(root, checked_map_pages(size), size);
	if (root->last == NULL)
		return (NULL);
	init_cont_mblock_info((t_cont_mblock*)root->last);
	return ((t_cont_mblock*)(root->last));
}

t_cont_mblock	*get_suitable_cont_mblock(t_track_block *root,
	size_t real_size, const int zone_type)
{
	t_cont_mblock	*head;
	size_t			zone_size;

	zone_size = pagesize_countain(
		zone_type == TINY_CONT ? TNY_ZONE : SMLL_ZONE);
	head = ((t_cont_mblock*)(root->first));
	if (head == NULL)
		return (append_cont(root, zone_size));
	while (head != (void*)(root->last))
	{
		if (real_size <= head->best_chunk)
			return (head);
		head = head->next;
	}
	if (real_size <= head->best_chunk)
		return (head);
	return (append_cont(root, zone_size));
}
