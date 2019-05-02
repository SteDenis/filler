/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraddline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 07:30:00 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/19 08:06:52 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**ft_arraddline(char **arr, char *line)
{
	char	**rtn;
	size_t	size;
	size_t	i;

	if (arr == NULL)
		size = 1;
	else
		size = ft_arrlen((const char *const *)arr) + 1;
	rtn = malloc(sizeof(char *) * (size + 1));
	if (rtn == NULL)
		return (NULL);
	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		rtn[i] = arr[i];
		i++;
	}
	rtn[i] = line;
	rtn[i + 1] = NULL;
	return (rtn);
}
