/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 14:33:09 by fstadelw          #+#    #+#             */
/*   Updated: 2019/01/28 18:02:47 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char **str, const char *end)
{
	char	*rtn;

	rtn = ft_strjoin(*str, end);
	ft_strdel(str);
	*str = rtn;
	return (rtn);
}
