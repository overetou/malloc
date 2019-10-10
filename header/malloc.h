/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:31:57 by overetou          #+#    #+#             */
/*   Updated: 2019/10/10 17:37:54 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <unistd.h>

# define TNY_LIM 128
# define SMLL_LIM 1024
# define TNY_ZONE 4 * 4096
# define SMLL_ZONE 30 * 4096
# define TINY_CONT 0
# define SMALL_CONT 1
# define SOLO_ZONE 2

typedef struct				s_mblock
{
	void					*leave_blank;
	struct s_mblock			*next;
	struct s_mblock			*prev;
	void					*end;
	void					*data;
}							t_mblock;

typedef struct				s_cont_mblock
{
	void					*leave_blank;
	struct s_cont_mblock	*next;
	struct s_cont_mblock	*prev;
	void					*end;
	size_t					best_chunk;
	t_mblock				*first;
	void					*data;
}							t_cont_mblock;

typedef struct				s_track_block
{
	t_mblock				*first;
	t_mblock				*last;
}							t_track_block;

typedef struct				s_minfo
{
	t_track_block			solo_segs;
	t_track_block			conts[2];
	size_t					mmax;
	size_t					page_size;
	size_t					total;
	size_t					total_mapped;
	void					*(*smart_alloc)(int zone_type, size_t size);
	char					free_failed;
}							t_minfo;

extern t_minfo				g_mmeta;

void						*malloc(size_t size);
void						free(void *adr);
void						*realloc(void *adr, size_t s);
void						show_alloc_mem(void);
void						*reallocarray(void *ptr, size_t nmemb, size_t size);
void						*calloc(size_t nmemb, size_t size);
void						*add_solo_zone(size_t size);
void						append_block(t_track_block *root,
void *mapped_space, size_t size);
void						remove_first_block(const t_mblock *b,
t_track_block *root);
void						remove_block(t_mblock *b, t_track_block *root);
void						*smart_minit(int zone_type, size_t size);
void						*checked_map_pages(size_t s);
void						*map_pages(size_t s);
long unsigned int			get_mmax(void);
size_t						pagesize_countain(size_t to_contain);
size_t						find_contain(size_t to_contain, const size_t mult);
void						print_status(void);
void						*cont_add(t_track_block *root,
size_t size, const int zone_type);
t_cont_mblock				*get_suitable_cont_mblock(t_track_block *root,
size_t real_size, int zone_type);
size_t						get_interstice_size(t_mblock *b,
t_cont_mblock *cont);
void						update_cont_mblock_info(t_cont_mblock *cont);
void						*insert_sub_block(t_cont_mblock *cont,
size_t real_size);
void						remove_sub_block(t_mblock *b,
t_cont_mblock *cont, t_track_block *t);
size_t						get_block_size(t_mblock	*b);
void						mcopy(char *src, char *dest, const size_t s);
void						print_adr(void *p0);
void						put_size_t(const size_t s);
void						putstr(const char *str);
void						putch(const char c);
void						print_adr_interval(void *adr1, void *adr2);
void						updating_munmap(void *adr, size_t s);
size_t						needed_size(size_t size);
size_t						align_size(size_t size);
#endif
