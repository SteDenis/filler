/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:34:02 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/19 05:17:45 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**ft_arrdup(const char *const *arr)
{
	char	**rtn;
	size_t	i;

	rtn = malloc(sizeof(char *) * (ft_arrlen(arr) + 1));
	if (rtn != NULL)
	{
		i = 0;
		while (arr[i] != NULL)
		{
			rtn[i] = ft_strdup(arr[i]);
			if (rtn[i] == NULL)
			{
				ft_arrdel(&rtn);
				return (rtn);
			}
			i++;
		}
		rtn[i] = NULL;
	}
	return (rtn);
}
