/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 09:40:21 by overetou          #+#    #+#             */
/*   Updated: 2019/09/25 17:40:28 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "malloc.h"

char	hex_digit(char v)
{
	if (v >= 0 && v < 10)
		return ('0' + v);
	else
		return ('a' + v - 10);
}

size_t	rec_put_hex(size_t n)
{
	if (n >= 16)
		n = n - rec_put_hex(n / 16) * 16;
	putch(hex_digit((char)n));
	return (n);
}

void	print_adr(void *p0)
{
	putstr("0x");
	rec_put_hex((size_t)p0);
}
