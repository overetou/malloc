/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:57:36 by overetou          #+#    #+#             */
/*   Updated: 2019/09/23 11:57:38 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "malloc.h"

void	putch(const char c)
{
	write(1, &c, 1);
}

void	putstr(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

void	print_adr_interval(void *adr1, void *adr2)
{
	print_adr(adr1);
	putstr(" - ");
	print_adr(adr2);
}

void	put_size_t(const size_t s)
{
	char	buf[10];
	size_t	n;
	size_t	i;
	size_t	l;

	n = s;
	i = 0;
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	i++;
	l = i;
	n = s;
	while (i)
	{
		i--;
		buf[i] = (char)(n % 10 + '0');
		n /= 10;
	}
	write(1, buf, l);
}
