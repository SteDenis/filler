/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:38:38 by stdenis           #+#    #+#             */
/*   Updated: 2018/11/13 18:28:07 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"

char	*ft_strnew(size_t size)
{
	char	*new;

	if (!(new = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memset(new, '\0', size + 1);
	return (new);
}
