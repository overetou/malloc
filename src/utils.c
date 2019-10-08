/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:29:51 by overetou          #+#    #+#             */
/*   Updated: 2019/10/02 18:44:35 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	mcopy(char *src, char *dest, const size_t s)
{
	size_t i;

	i = 0;
	while (i != s)
	{
		dest[i] = src[i];
		i++;
	}
}

void	show_cont_allocs(const char *s, t_track_block *t)
{
	t_cont_mblock	*c;
	t_mblock		*head;

	c = (t_cont_mblock*)(t->first);
	if (c == NULL)
		return ;
	while (1)
	{
		putstr(s);
		print_adr((void*)c);
		putch('\n');
		head = c->first;
		while (head)
		{
			print_adr_interval((void*)(&(head->data)), head->end);
			putstr(" : ");
			put_size_t(get_block_size(head));
			putstr(" octets\n");
			head = head->next;
		}
		if ((t_mblock*)c == t->last)
			return ;
		c = c->next;
	}
}

void	show_alloc_mem(void)
{
	t_mblock	*head;

	show_cont_allocs("TINY : ", &(g_mmeta.conts[0]));
	show_cont_allocs("SMALL : ", &(g_mmeta.conts[1]));
	head = g_mmeta.solo_segs.first;
	if (head != NULL)
	{
		while (1)
		{
			putstr("LARGE : ");
			print_adr((void*)(&(head->data)));
			putch('\n');
			print_adr_interval((void*)(&(head->data)), head->end);
			putstr(" : ");
			put_size_t(get_block_size(head));
			putstr(" octets\n");
			if (head == g_mmeta.solo_segs.last)
				break ;
			head = head->next;
		}
	}
	putstr("Total : ");
	put_size_t(g_mmeta.total);
	putstr(" octets\n");
}
