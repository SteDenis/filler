/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdelline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 07:30:26 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/19 09:05:15 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**ft_arrdelline(char **arr, size_t line)
{
	size_t	i;

	if (line > ft_arrlen((const char *const *)arr))
		return (arr);
	if (line == ft_arrlen((const char *const *)arr) && line == 0)
	{
		ft_arrdel(&arr);
		return (NULL);
	}
	ft_strdel(&arr[line]);
	i = line;
	while (arr[i + 1] != NULL)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
