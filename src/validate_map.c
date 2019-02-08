/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:22:56 by tbujalo           #+#    #+#             */
/*   Updated: 2019/02/08 16:27:29 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			check_char(char c)
{
	if (c == ',' || c == 'x')
		return (1);
	if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}

int			validate_map(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] < '0' && line[i] > '9' && line[i] != ' ')
			if (!check_char(line[i]))
				return (0);
		i++;
	}
	return (1);
}

int			get_decimal(char a)
{
	if (a == 'A' || a == 'a')
		return (10);
	else if (a == 'B' || a == 'b')
		return (11);
	else if (a == 'C' || a == 'c')
		return (12);
	else if (a == 'D' || a == 'd')
		return (13);
	else if (a == 'E' || a == 'e')
		return (14);
	else if (a == 'F' || a == 'f')
		return (15);
	return (0);
}
