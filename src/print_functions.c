/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:10:38 by tbujalo           #+#    #+#             */
/*   Updated: 2019/02/05 13:43:38 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			mix_color_and_round(int *r_x_y, float *x_y, t_dot d1, t_dot d2)
{
	r_x_y[0] = round(x_y[0]);
	r_x_y[1] = round(x_y[1]);
	return (get_color(r_x_y[0], r_x_y[1], d1, d2));
}

int			print_if(t_window win, int *r_x_y)
{
	if (r_x_y[0] < win.s_x && r_x_y[0] >= 0
			&& r_x_y[1] < win.s_y && r_x_y[1] >= 0)
		return (1);
	return (0);
}

void		draw_line(t_dot d, t_dot d2, int color, t_window *win)
{
	float	x_y[2];
	int		r_x_y[2];

	x_y[0] = d.x;
	x_y[1] = d.y;
	if (fabs(d2.y - d.y) > fabs(d2.x - d.x))
	{
		while ((d.y < d2.y) ? (x_y[1] <= d2.y) : (x_y[1] >= d2.y))
		{
			x_y[0] = (((x_y[1] - d.y) / (d2.y - d.y)) * (d2.x - d.x) + d.x);
			color = mix_color_and_round(r_x_y, x_y, d, d2);
			if (print_if(*win, r_x_y))
				win->img->d[r_x_y[0] + win->img->l * r_x_y[1] / 4] = color;
			(d.y < d2.y) ? x_y[1]++ : x_y[1]--;
		}
	}
	else
		while ((d.x < d2.x) ? (x_y[0] <= d2.x) : (x_y[0] >= d2.x))
		{
			x_y[1] = (((x_y[0] - d.x) / (d2.x - d.x)) * (d2.y - d.y) + d.y);
			color = mix_color_and_round(r_x_y, x_y, d, d2);
			if (print_if(*win, r_x_y))
				win->img->d[r_x_y[0] + win->img->l * r_x_y[1] / 4] = color;
			(d.x < d2.x) ? x_y[0]++ : x_y[0]--;
		}
}

int			print_map(t_window *win)
{
	int		i;
	int		j;
	t_row	row;

	i = 0;
	while (i < win->n_rows)
	{
		row = win->rows[i];
		j = 0;
		while (j < row.num_dots)
		{
			if ((j + 1) < row.num_dots)
			{
				draw_line(row.dots[j], row.dots[j + 1], 0, win);
			}
			if ((i + 1) < win->n_rows)
			{
				draw_line(row.dots[j], win->rows[i + 1].dots[j], 0, win);
			}
			j++;
		}
		i++;
	}
	return (0);
}
