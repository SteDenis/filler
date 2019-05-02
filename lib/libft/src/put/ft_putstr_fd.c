/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:22:01 by fstadelw          #+#    #+#             */
/*   Updated: 2018/11/09 21:56:51 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void		ft_putstr_fd(char const *s, int fd)
{
	size_t	i;

	if (s == (char *)NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
		i++;
	write(fd, s, i);
}
