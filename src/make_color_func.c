/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_color_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:27:54 by tbujalo           #+#    #+#             */
/*   Updated: 2019/02/04 22:29:28 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			atoi_base(char *s, int i)
{
	int		l;
	int		num;
	int		sum;

	l = ft_strlen(s);
	while (s[--l] <= 32)
		;
	num = 0;
	sum = 0;
	while (l >= 0 && s[l] > 32)
	{
		if (s[l] >= '0' && s[l] <= '9')
			num = s[l] - '0';
		else if ((s[l] >= 'A' && s[l] <= 'F') || (s[l] >= 'a' && s[l] <= 'f'))
			num = get_decimal(s[l]);
		if (i > 0)
			num *= i;
		if (i != 0)
			i *= 16;
		else
			i = 16;
		sum += num;
		l--;
	}
	return (sum);
}

int			make_color(char *str)
{
	char	**arr;
	int		i;
	int		ret;
	int		p;

	p = 0;
	arr = ft_strsplit(str, ',');
	i = 0;
	ret = 16777215;
	while (arr[i])
		i++;
	if (i > 1)
		ret = atoi_base(arr[1], p);
	free_map(arr);
	return (ret);
}

double		percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int			get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int			get_color(int x, int y, t_dot start, t_dot end)
{
	int		r;
	int		g;
	int		b;
	double	pro;

	if (end.x - start.x > end.y - start.y)
		pro = percent(start.x, end.x, x);
	else
		pro = percent(start.y, end.y, y);
	r = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, pro);
	g = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, pro);
	b = get_light(start.color & 0xFF, end.color & 0xFF, pro);
	return ((r << 16) | (g << 8) | b);
}
