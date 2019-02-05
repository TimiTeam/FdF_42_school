/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:29:33 by tbujalo           #+#    #+#             */
/*   Updated: 2019/02/05 13:41:32 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H
# define __FDF_H

# include "../libft/libft.h"
# include "mlx.h"
# include "get_next_line.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct	s_dot
{
	double		x;
	double		y;
	double		z;
	int			color;
	double		o_x;
	double		o_y;
	double		o_z;
}				t_dot;

typedef struct	s_row
{
	t_dot		*dots;
	int			num_dots;
}				t_row;

typedef struct	s_image
{
	void		*p;
	int			b;
	int			l;
	int			en;
	int			size_x;
	int			size_y;
	int			dot_step;
	int			*d;
	double		center_x;
	double		center_y;
}				t_image;

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	t_image		*img;
	t_row		*rows;
	int			n_rows;
	char		*name;
	int			s_x;
	char		*h;
	int			s_y;
}				t_window;

t_window		*make_main_struct(int fd);
void			error_message(int code);
void			free_list(void *content, size_t content_size);
void			add_to_end(t_list **alst, t_list *new);
void			free_map(char **str);
int				make_color(char *str);
int				exit_x(void *par);
void			change_points(int x, int y, t_window *win);
void			guess_rotation(int key, t_window *win, double r);
int				print_map(t_window *win);
void			move_key(int key, t_window *win, int step);
int				get_color(int x, int y, t_dot start, t_dot end);
int				get_decimal(char a);
int				validate_map(char *line);
void			print_help(t_window *win);
void			make_rotation(t_window *win, void f(t_dot*, double), double r);
void			make_zoom(int key, t_window *win, double r);

#endif
