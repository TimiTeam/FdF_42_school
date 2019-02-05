/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:36:16 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/05 17:40:01 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_word_count(char *str, char s)
{
	while (*str == s && *str)
		str++;
	if (*str != '\0' && *str != s)
	{
		while (*str != s && *str)
			str++;
		return (1 + ft_word_count(str, s));
	}
	return (0);
}
