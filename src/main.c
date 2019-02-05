/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:55:20 by tbujalo           #+#    #+#             */
/*   Updated: 2019/02/05 13:42:47 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			reset_map(t_window *win)
{
	int			i;
	int			j;

	i = 0;
	mlx_clear_window(win->mlx, win->win);
	mlx_destroy_image(win->mlx, win->img->p);
	while (i < win->n_rows)
	{
		j = 0;
		while (j < win->rows[i].num_dots)
		{
			win->rows[i].dots[j].x = win->rows[i].dots[j].o_x;
			win->rows[i].dots[j].y = win->rows[i].dots[j].o_y;
			win->rows[i].dots[j].z = win->rows[i].dots[j].o_z;
			j++;
		}
		i++;
	}
	win->img->p = mlx_new_image(win->mlx, win->img->size_x, win->img->size_y);
	print_map(win);
	win->img->center_x = win->s_x / 2;
	win->img->center_y = win->s_y / 2;
	mlx_put_image_to_window(win->mlx, win->win, win->img->p, 0, 0);
}

void			start_position(t_window *win)
{
	int			tmp_x;
	int			tmp_y;
	int			i;
	int			j;

	tmp_y = win->rows[win->n_rows - 1].dots[0].y / 2;
	tmp_x = win->rows[0].dots[win->rows[0].num_dots - 1].x / 2;
	change_points((win->s_x / 2 - tmp_x), (win->s_y / 2 - tmp_y), win);
	i = 0;
	while (i < win->n_rows)
	{
		j = 0;
		while (j < win->rows[i].num_dots)
		{
			win->rows[i].dots[j].o_x = win->rows[i].dots[j].x;
			win->rows[i].dots[j].o_y = win->rows[i].dots[j].y;
			win->rows[i].dots[j].o_z = win->rows[i].dots[j].z;
			j++;
		}
		i++;
	}
	win->img->center_x = win->s_x / 2;
	win->img->center_y = win->s_y / 2;
	print_map(win);
}

int				guess_button(int key, t_window *win)
{
	if (key == 4)
		print_help(win);
	if (key >= 123 && key <= 126)
		move_key(key, win, 10);
	if (key == 53)
		exit_x(win);
	if (key == 15)
	{
		reset_map(win);
		mlx_string_put(win->mlx, win->win, 10, 5, 16777215, win->h);
	}
	if (key == 78 || key == 69)
		make_zoom(key, win, 1.5);
	if ((key >= 0 && key <= 2) || key == 13)
		guess_rotation(key, win, 5);
	if (key == 88 || key == 86)
		guess_rotation(key, win, 5);
	return (0);
}

int				make_window(t_window *win)
{
	t_image		*i;

	win->h = ft_strdup("Press 'H' button to see help");
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->s_x, win->s_y, win->name);
	i = win->img;
	i->p = mlx_new_image(win->mlx, i->size_x, i->size_y);
	i->d = (int*)mlx_get_data_addr(i->p, &(i->b), &(i->l), &(i->en));
	start_position(win);
	mlx_put_image_to_window(win->mlx, win->win, i->p, 0, 0);
	mlx_string_put(win->mlx, win->win, 10, 5, 16777215, win->h);
	mlx_hook(win->win, 2, 2, guess_button, win);
	mlx_hook(win->win, 17, 1L << 17, exit_x, win);
	mlx_loop(win->mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	int			fd;
	t_window	*win;

	fd = 0;
	if (argc > 2)
		error_message(7);
	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 1)
			error_message(9);
		if (!(win = make_main_struct(fd)))
			error_message(5);
		close(fd);
		win->name = argv[1];
		if (!make_window(win))
			error_message(1);
	}
	else
		error_message(2);
	return (0);
}
