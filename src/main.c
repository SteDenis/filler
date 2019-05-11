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

#include "filler.h"
#include <stdlib.h>

static int	get_piece(t_filler *f)
{
	char	*piece;
	int		i;

	piece = NULL;
	i = -1;
	if (!(get_size_piece(f)))
		return (0);
	if (!(f->piece = (char**)malloc(sizeof(char*) * (f->piece_size.y + 1))))
		return (0);
	ft_tabset(f->piece, NULL, f->piece_size.y + 1);
	while (++i < f->piece_size.y && (get_next_line(0, &piece)) > 0)
	{
		f->piece[i] = piece;
		if (ft_strlen(f->piece[i]) != (size_t)f->piece_size.x)
			return (0);
	}
	if (i != f->piece_size.y)
		return (0);
	return (1);
}

static int	read_map(t_filler *f)
{
	char	*tmp;
	char	*line;
	int		i;

	i = -1;
	tmp = NULL;
	if ((get_next_line(0, &tmp)) <= 0)
		return (0);
	ft_strdel(&tmp);
	if ((get_next_line(0, &tmp)) <= 0)
		return (0);
	ft_strdel(&tmp);
	while (++i < f->map_size.y && (get_next_line(0, &tmp) > 0))
	{
		line = ft_strchr(tmp, ' ');
		if (!line || (ft_strlen(line + 1) != (size_t)f->map_size.x))
			break ;
		f->map[i] = ft_strcpy(f->map[i], line + 1);
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp);
	if (i != f->map_size.y)
		return (0);
	return (1);
}

static int	get_result(t_filler *f)
{
	t_xy	res;

	res.value = -1;
	res.x = 0;
	res.y = 0;
	if (!(try_to_place_near(f, &res)))
	{
		if (f->start_ennemy.y > f->start_player.y)
			try_to_place_bottom(f, &res);
		else
			try_to_place_up(f, &res);
	}
	ft_putnbr(res.y);
	ft_putchar(' ');
	ft_putnbr(res.x);
	ft_putchar('\n');
	if (res.x == 0 && res.y == 0)
		return (0);
	return (1);
}

int			estimate_value(t_filler *f, int y, int x)
{
	int		i;
	int		j;
	int		count;
	t_xy	coord;

	count = 0;
	i = y + (f->map_size.y / 10);
	while (i >= y - (f->map_size.y / 10))
	{
		j = x + (f->map_size.y / 10);
		while (j >= x - (f->map_size.y / 10))
		{
			coord.y = i;
			coord.x = j;
			if (coord.x >= 0 && coord.y >= 0
				&& coord.x <= f->map_size.x && coord.y < f->map_size.y)
			{
				if (f->map[coord.y][coord.x] == f->ennemy)
					count++;
			}
			j--;
		}
		i--;
	}
	return (count);
}

int			main(void)
{
	t_filler	f;

	if (!(init_game(&f)))
		return (1);
	if (get_piece(&f) && get_result(&f))
	{
		while (1)
		{
			if (!(read_map(&f)))
				break ;
			free_piece(&f);
			if (!(get_piece(&f)))
				break ;
			if (!(get_result(&f)))
				break ;
		}
	}
	free_piece(&f);
	ft_arrdel(&f.map);
	return (0);
}
