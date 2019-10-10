/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alignment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:39:21 by overetou          #+#    #+#             */
/*   Updated: 2019/10/10 17:39:26 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align_size(size_t size)
{
	return ((size + 15) & ~15);
}

size_t	needed_size(size_t size)
{
	return (4 * sizeof(void*) + align_size(size));
}
