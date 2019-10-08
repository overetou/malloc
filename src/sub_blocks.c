/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_blocks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:21:36 by overetou          #+#    #+#             */
/*   Updated: 2019/10/02 18:00:11 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_mblock	*find_optimal_sub_block_space(t_mblock *head,
	size_t real_size, t_cont_mblock *cont)
{
	size_t		curr_ok_min;
	size_t		inter;
	t_mblock	*min_prev_block_adr;

	if (real_size <= (size_t)((void*)(cont->first) - (void*)(&(cont->data))))
	{
		curr_ok_min = (void*)(cont->first) - (void*)(&(cont->data));
		min_prev_block_adr = (void*)(&(cont->data));
	}
	else
	{
		curr_ok_min = 0;
		min_prev_block_adr = NULL;
	}
	while (head)
	{
		inter = get_interstice_size(head, cont);
		if (inter >= real_size && (inter < curr_ok_min || !min_prev_block_adr))
		{
			curr_ok_min = inter;
			min_prev_block_adr = head;
		}
		head = head->next;
	}
	return (min_prev_block_adr);
}

t_mblock	*insert_nonfirst_sub_block(t_mblock *preceding_block,
t_cont_mblock *cont)
{
	t_mblock	*new_sub_block;

	if (preceding_block == (t_mblock*)(&(cont->data)) &&
	preceding_block != cont->first)
	{
		new_sub_block = preceding_block;
		new_sub_block->next = cont->first;
		new_sub_block->prev = NULL;
		cont->first = new_sub_block;
		(new_sub_block->next)->prev = new_sub_block;
	}
	else
	{
		new_sub_block = preceding_block->end;
		new_sub_block->next = preceding_block->next;
		new_sub_block->prev = preceding_block;
		preceding_block->next = new_sub_block;
		if (new_sub_block->next != NULL)
			new_sub_block->next->prev = new_sub_block;
	}
	return (new_sub_block);
}

void		*insert_sub_block(t_cont_mblock *cont, size_t real_size)
{
	t_mblock	*new_sub_block;
	t_mblock	*preceding_block;

	if (cont->first == NULL)
	{
		new_sub_block = (t_mblock*)(&(cont->data));
		new_sub_block->prev = NULL;
		new_sub_block->next = NULL;
		(cont->first) = new_sub_block;
	}
	else
	{
		preceding_block = find_optimal_sub_block_space(cont->first,
		real_size, cont);
		new_sub_block = insert_nonfirst_sub_block(preceding_block,
		cont);
	}
	new_sub_block->end = (void*)(((void*)(new_sub_block)) + real_size);
	update_cont_mblock_info(cont);
	return ((void*)(&(new_sub_block->data)));
}

size_t		rm_first_sub_block(t_mblock *b, t_cont_mblock *cont,
t_track_block *t)
{
	if (b->next == NULL)
	{
		remove_block((t_mblock*)cont, t);
		return (0);
	}
	b->next->prev = NULL;
	cont->first = b->next;
	return ((size_t)((void*)(cont->first) - (void*)(&(cont->data))));
}

void		remove_sub_block(t_mblock *b, t_cont_mblock *cont, t_track_block *t)
{
	size_t		free_space;

	if (b->prev == NULL)
		free_space = rm_first_sub_block(b, cont, t);
	else
	{
		if (b->next)
		{
			free_space = (void*)(b->next) - b->prev->end;
			b->next->prev = b->prev;
		}
		else
			free_space = cont->end - (void*)b;
		b->prev->next = b->next;
	}
	if (free_space && cont->best_chunk < free_space)
		cont->best_chunk = free_space;
}
