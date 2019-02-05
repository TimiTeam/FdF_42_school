/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_worker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 22:33:10 by tbujalo           #+#    #+#             */
/*   Updated: 2019/02/05 13:43:29 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot			*make_dot(t_list *elem, int step, int *dot_count)
{
	char		**arr;
	char		**he;
	int			size;
	int			d;
	t_dot		*dots;

	arr = ft_strsplit(elem->content, ' ');
	size = 0;
	while (arr[size])
		size++;
	d = 0;
	dots = (t_dot*)malloc(sizeof(t_dot) * size + 1);
	while (d < size)
	{
		he = ft_strsplit(arr[d], ',');
		dots[d].y = *dot_count * step;
		dots[d].z = ft_atoi(he[0]) * -step;
		dots[d].color = make_color(arr[d]);
		dots[d].x = d * step;
		free_map(he);
		d++;
	}
	*dot_count = d;
	free_map(arr);
	return (dots);
}

t_row			*make_rows(t_list *all, t_window *win)
{
	t_row		*rows;
	t_list		*cp;
	int			p;
	int			do_co;

	rows = (t_row*)malloc(sizeof(t_row) * win->n_rows);
	p = 0;
	cp = all;
	while (p < win->n_rows)
	{
		do_co = p;
		rows[p].dots = make_dot(cp, win->img->dot_step, &do_co);
		rows[p].num_dots = do_co;
		cp = cp->next;
		p++;
	}
	return (rows);
}

t_image			*make_image(int screen_x, int screen_y, int n_cols)
{
	t_image		*img;

	img = (t_image*)malloc(sizeof(t_image));
	img->size_x = screen_x;
	img->size_y = screen_y;
	img->dot_step = 20;
	if (n_cols > 150)
		img->dot_step = 4;
	else if (n_cols > 90)
		img->dot_step = 6;
	return (img);
}

t_list			*read_and_save(int fd, int *num_rows)
{
	t_list		*all;
	t_list		*elem;
	char		*line;

	*num_rows = 0;
	line = NULL;
	if (!get_next_line(fd, &line))
		return (NULL);
	all = ft_lstnew(line, (*num_rows)++);
	ft_strdel(&line);
	while (get_next_line(fd, &line) > 0)
	{
		if (!validate_map(line))
		{
			ft_lstdel(&all, free_list);
			ft_strdel(&line);
			return (NULL);
		}
		elem = ft_lstnew(line, *num_rows);
		elem->content_size = (*num_rows)++;
		ft_strdel(&line);
		add_to_end(&all, elem);
	}
	ft_strdel(&line);
	return (all);
}

t_window		*make_main_struct(int fd)
{
	t_list		*all;
	t_window	*win;
	int			num_rows;

	if (!(all = read_and_save(fd, &num_rows)))
		return (NULL);
	if (num_rows <= 1)
	{
		ft_lstdel(&all, free_list);
		return (NULL);
	}
	win = (t_window*)malloc(sizeof(t_window));
	win->n_rows = num_rows;
	win->s_x = (num_rows > 220 ? 2200 : num_rows * 10);
	if (win->s_x < 840)
		win->s_x = 840;
	win->s_y = (win->s_x < 1800 ? win->s_x - (win->s_x / 4) : 1250);
	win->img = make_image(win->s_x, win->s_y, num_rows);
	win->rows = make_rows(all, win);
	ft_lstdel(&all, free_list);
	return (win);
}
