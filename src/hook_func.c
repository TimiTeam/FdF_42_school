/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:18:42 by tbujalo           #+#    #+#             */
/*   Updated: 2019/02/04 19:19:17 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

void		print_help(t_window *win)
{
	int		h;
	int		c;

	c = 16777215;
	h = 20;
	mlx_string_put(win->mlx, win->win, 10, h, c, "To move: use 'arrows'");
	h += 20;
	mlx_string_put(win->mlx, win->win, 10, h, c, "Rotate by z, y and x");
	h += 20;
	mlx_string_put(win->mlx, win->win, 10, h, c, " to z: 4 and 6");
	h += 20;
	mlx_string_put(win->mlx, win->win, 10, h, c, " to y: 'A' and 'D'");
	h += 20;
	mlx_string_put(win->mlx, win->win, 10, h, c, " to x: 'S' and 'W'");
	h += 20;
	mlx_string_put(win->mlx, win->win, 10, h, c, "To zoom: '+' and '-'");
	h += 20;
	mlx_string_put(win->mlx, win->win, 10, h, c, "Reset: 'R' button");
}

void		move_key(int key, t_window *win, int step)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	mlx_destroy_image(win->mlx, win->img->p);
	change_points((win->img->center_x * -1), (win->img->center_y * -1), win);
	if (key == 126)
		y = step;
	else if (key == 125)
		y = -step;
	else if (key == 123)
		x = step;
	else if (key == 124)
		x = -step;
	change_points(x, y, win);
	change_points(win->img->center_x, win->img->center_y, win);
	win->img->p = mlx_new_image(win->mlx, win->img->size_x, win->img->size_y);
	print_map(win);
	mlx_put_image_to_window(win->mlx, win->win, win->img->p, 0, 0);
	win->img->center_x += x;
	win->img->center_y += y;
}

void		make_rotation(t_window *win, void f(t_dot*, double), double r)
{
	int		i;
	int		j;
	t_row	row;

	i = 0;
	while (i < win->n_rows)
	{
		j = 0;
		row = win->rows[i];
		while (j < row.num_dots)
		{
			f(&row.dots[j], r);
			j++;
		}
		i++;
	}
}

void		change_points(int x, int y, t_window *win)
{
	int		i;
	int		j;

	i = 0;
	while (i < win->n_rows)
	{
		j = 0;
		while (j < win->rows[i].num_dots)
		{
			win->rows[i].dots[j].x += x;
			win->rows[i].dots[j].y += y;
			j++;
		}
		i++;
	}
}
