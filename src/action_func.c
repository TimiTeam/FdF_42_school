/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:04:04 by tbujalo           #+#    #+#             */
/*   Updated: 2019/02/04 19:04:08 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		move_by_y(t_dot *dots, double r)
{
	float	x;
	float	z;

	x = dots->x;
	z = dots->z;
	dots->x = x * cos(r) + z * sin(r);
	dots->z = z * cos(r) - x * sin(r);
}

void		move_by_x(t_dot *dots, double r)
{
	float	y;
	float	z;

	y = dots->y;
	z = dots->z;
	dots->y = y * cos(r) + z * sin(r);
	dots->z = z * cos(r) - y * sin(r);
}

void		move_by_z(t_dot *dot, double r)
{
	float	x;
	float	y;

	x = dot->x;
	y = dot->y;
	dot->x = x * cos(r) - y * sin(r);
	dot->y = y * cos(r) + x * sin(r);
}

void		guess_rotation(int key, t_window *win, double r)
{
	mlx_destroy_image(win->mlx, win->img->p);
	change_points((win->img->center_x * -1), (win->img->center_y * -1), win);
	if (key != 69 && key != 78)
		r = M_PI / 180 * r;
	if (key == 2)
		make_rotation(win, move_by_y, -r);
	else if (key == 0)
		make_rotation(win, move_by_y, r);
	else if (key == 1)
		make_rotation(win, move_by_x, -r);
	else if (key == 13)
		make_rotation(win, move_by_x, r);
	else if (key == 86)
		make_rotation(win, move_by_z, -r);
	else if (key == 88)
		make_rotation(win, move_by_z, r);
	change_points(win->img->center_x, win->img->center_y, win);
	win->img->p = mlx_new_image(win->mlx, win->img->size_x, win->img->size_y);
	print_map(win);
	mlx_put_image_to_window(win->mlx, win->win, win->img->p, 0, 0);
}
