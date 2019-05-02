/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:43:08 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 16:45:01 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int			get_piece(t_filler *f)
{
	char	*piece;
	char	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	if ((get_next_line(0, &piece) <= 0))
		return (0);
	if ((tmp = ft_strchr(piece, ' ')))
		f->piece_size.y = ft_atoi(&tmp[1]);
	if (tmp && (tmp = ft_strchr(tmp, ' ')))
		f->piece_size.x = ft_atoi(&tmp[1]);
	ft_strdel(&piece);
	if (f->piece_size.x < 0 || f->piece_size.y < 0)
		return (0);
	if (!(f->piece = (char**)malloc(sizeof(char*) * f->piece_size.y)))
		return (0);
	while (++i < f->piece_size.y && (get_next_line(0, &piece) > 0))
		f->piece[i] = piece;
	f->piece[i] = NULL;
	return (1);
}

void		place_piece(t_filler *f)
{
	ft_putnbr(f->last_player.y);
	ft_putchar(' ');
	ft_putnbr(f->last_player.x - 1);
	ft_putchar('\n');
}

void		read_map(t_filler *f)
{
	char	*tmp;
	int		i;

	i = 0;
	get_next_line(0, &tmp);
	ft_strdel(&tmp);
	get_next_line(0, &tmp);
	ft_strdel(&tmp);
	while (i < f->map_size.y && (get_next_line(0, &tmp) > 0))
	{
		ft_strdel(&f->map[i]);
		f->map[i++] = ft_strchr(tmp, ' ');
	}
	get_position(f, 0);
}

int			main(void)
{
	t_filler	f;

	if (!(init_game(&f)))
		return (1);
	if (!(get_piece(&f)))
		return (1);
	place_piece(&f);
	while (1)
	{
		read_map(&f);
		get_piece(&f);
		place_piece(&f);
	}
	return (0);
}
