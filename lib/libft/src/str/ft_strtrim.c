/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:22:01 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/30 18:49:28 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*rtn;
	size_t	beg;
	size_t	end;

	if (s == (char *)NULL)
		return ((char *)NULL);
	beg = 0;
	while (s[beg] == ' ' || s[beg] == '\t' || s[beg] == '\n')
		beg++;
	end = ft_strlen(s);
	while (end > 1
		&& (s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\n'))
		end--;
	if (beg == 0 && end == ft_strlen(s))
		return (ft_strdup(s));
	if (beg >= end)
		return (ft_strdup(""));
	rtn = ft_strnew(end - beg);
	if (rtn == (char *)NULL)
		return ((char *)NULL);
	ft_strncpy(rtn, &s[beg], end - beg);
	return (rtn);
}
