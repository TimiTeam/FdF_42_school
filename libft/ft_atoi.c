/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 14:43:26 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/29 14:21:14 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nbr)
{
	int		m;
	int		c;
	int		res;
	char	*chek;

	m = 1;
	res = 0;
	c = 0;
	while (*nbr == ' ' || *nbr == '\t' || *nbr == '\f' ||
			*nbr == '\r' || *nbr == '\n' || *nbr == '\v')
		nbr++;
	if (*nbr == '-' || *nbr == '+')
	{
		if (*nbr == '-')
			m = -1;
		nbr++;
	}
	chek = (char*)nbr;
	while (*nbr >= '0' && *nbr <= '9' && c++ < 19)
		res = (res * 10) + (*nbr++ - '0');
	if (c >= 19)
		res = -1;
	if (c >= 19 && m == -1)
		res = 0;
	return (res * m);
}
