/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_in_zoom_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:24:27 by tbujalo           #+#    #+#             */
/*   Updated: 2019/02/05 13:24:34 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		zoo_minus(t_dot *dot, double z)
{
	dot->x /= z;
	dot->y /= z;
	dot->z /= z;
}

void		zoo_plus(t_dot *dot, double z)
{
	dot->x *= z;
	dot->y *= z;
	dot->z *= z;
}

void		make_zoom(int key, t_window *win, double r)
{
	mlx_destroy_image(win->mlx, win->img->p);
	change_points((win->img->center_x * -1), (win->img->center_y * -1), win);
	if (key == 69)
		make_rotation(win, zoo_plus, r);
	else if (key == 78)
		make_rotation(win, zoo_minus, r);
	change_points(win->img->center_x, win->img->center_y, win);
	win->img->p = mlx_new_image(win->mlx, win->img->size_x, win->img->size_y);
	print_map(win);
	mlx_put_image_to_window(win->mlx, win->win, win->img->p, 0, 0);
}
