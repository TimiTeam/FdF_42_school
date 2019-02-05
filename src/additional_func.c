/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:06:24 by tbujalo           #+#    #+#             */
/*   Updated: 2019/02/04 19:22:59 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		error_message(int code)
{
	ft_putendl(strerror(code));
	exit(1);
}

void		add_to_end(t_list **alst, t_list *new)
{
	t_list	*elem;

	elem = *alst;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
}

void		free_list(void *content, size_t content_size)
{
	content_size = 0;
	free(content);
}

void		free_map(char **str)
{
	int		i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
