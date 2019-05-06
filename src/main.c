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
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int			get_piece(t_filler *f)
{
	char	*piece;
	char	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	if ((get_next_line(0, &piece)) <= 0)
		return (0);
	if ((tmp = ft_strchr(piece, ' ')))
		f->piece_size.y = ft_atoi(&tmp[1]);
	if (tmp && (tmp = ft_strchr(tmp + 1, ' ')))
		f->piece_size.x = ft_atoi(&tmp[1]);
	ft_strdel(&piece);
	if (f->piece_size.x < 0 || f->piece_size.y < 0)
		return (0);
	if (!(f->piece = (char**)malloc(sizeof(char*) * f->piece_size.y + 1)))
		return (0);
	ft_tabset(f->piece, NULL, f->piece_size.y + 1);
	while (++i < f->piece_size.y && (get_next_line(0, &piece)) > 0)
	{
		if (ft_strlen(piece) != (size_t)f->piece_size.x)
			return (0);
		f->piece[i] = piece;
	}
	if (i != f->piece_size.y)
		return (0);
	return (1);
}

int		read_map(t_filler *f)
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
		{
			ft_strdel(&tmp);
			return (0);
		}
		f->map[i] = ft_strcpy(f->map[i], line + 1);
		ft_strdel(&tmp);
	}
	if (i != f->map_size.y)
		return (0);
	return (1);
}

void 	test2(t_filler *f, t_xy_res place)
{
	(void)f;
	ft_putnbr(place.y);
	ft_putchar(' ');
	ft_putnbr(place.x);
	ft_putchar('\n');
}

int			estimate_value(t_filler *f, int y, int x)
{
	int		i;
	int		j;
	int		count;
	t_xy	coord;

	count = 0;
	i = y + 1;
	while (i >= y - 1)
	{
		j = x + 1;
		while (j >= x - 1)
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

int			put_piece(t_filler *f, t_xy pos, int *value)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	while (i < f->piece_size.y)
	{
		j = 0;
		while (j < f->piece_size.x)
		{
			if (f->piece[i][j] == '*')
			{
				if (pos.y + i >= f->map_size.y || pos.x + j >= f->map_size.x)
					return (0);
				if (f->map[pos.y + i][pos.x + j] == f->our && ++count > 1)
					return (0);
				if (f->map[pos.y + i][pos.x + j] == f->ennemy)
					return (0);
				*value += estimate_value(f, pos.y + i, pos.x + j);
			}
			j++;
		}
		i++;
	}
	if (count < 1)
		return (0);
	return (1);
}

t_xy_res			try_it(t_filler *f, t_xy pos)
{
	t_xy res;
	t_xy_res res2;
	int	value;
	int i;
	int j;

	i = 0;
	while (i < f->piece_size.y)
	{
		j = 0;
		while (j < f->piece_size.x)
		{
			res.y = pos.y - i;
			res.x = pos.x - j;
			value = 0;
			if (res.x >= 0 && res.y >= 0 && f->piece[i][j] == '*'
				&& res.y < f->map_size.y && res.x < f->map_size.x)
			{
				if (put_piece(f, res, &value))
				{
					res2.y = res.y;
					res2.x = res.x;
					res2.value = value;
					return (res2);
				}
			}
			j++;
		}
		i++;
	}
	res2.x = -1;
	res2.y = -1;
	res2.value = -1;
	return (res2);
}

int			try_to_place_up(t_filler *f)
{
	t_xy	place;
	t_xy_res	tmp;

	place.y = 0;
	while (place.y < f->map_size.y)
	{
		place.x = (f->last_ennemy.x > f->last_player.x) ? f->map_size.x - 1 : 0;
		if (place.x > 0)
		{
			while(place.x >= 0)
			{
				if (f->map[place.y][place.x] == f->our)
				{
					tmp = try_it(f, place);
					if (tmp.x >= 0 && tmp.y >= 0)
					{
						test2(f, tmp);
						return (1);
					}
				}
				place.x--;
			}
		}
		else
		{
			while(place.x < f->map_size.x)
			{
				if (f->map[place.y][place.x] == f->our)
				{
					tmp = try_it(f, place);
					if (tmp.x >= 0 && tmp.y >= 0)
					{
						test2(f, tmp);
						return (1);
					}
				}
				place.x++;
			}
		}
		place.y++;
	}
	write(1, "0 0\n", 4);
	dprintf(f->fd, "up place %d %d\n", 0, 0);
	exit(1);
	return (0);
}

int			try_to_place_bottom(t_filler *f)
{
	t_xy	place;
	t_xy_res	tmp;

	place.y = f->map_size.y - 1;
	while (place.y >= 0)
	{
		place.x = (f->last_ennemy.x > f->last_player.x) ? f->map_size.x - 1 : 0;
		if (place.x > 0)
		{
			while(place.x >= 0)
			{
				if (f->map[place.y][place.x] == f->our)
				{
					tmp = try_it(f, place);
					if (tmp.x >= 0 && tmp.y >= 0)
					{
						test2(f, tmp);
						return (1);
					}
				}
				place.x--;
			}
		}
		else
		{
			while(place.x < f->map_size.x)
			{
				if (f->map[place.y][place.x] == f->our)
				{
					tmp = try_it(f, place);
					if (tmp.x >= 0 && tmp.y >= 0)
					{
						test2(f, tmp);
						return (1);
					}
				}
				place.x++;
			}
		}
		place.y--;
	}
	write(1, "0 0\n", 4);
	dprintf(f->fd, "bot place %d %d\n", 0, 0);
	exit(1);
	return (0);
}

int			try_to_place_near(t_filler *f)
{
	t_xy	place;
	t_xy_res	tmp;
	t_xy_res	res;

	place.y = 0;
	res.value = -1;
	res.x = 0;
	res.y = 0;
	while (place.y < f->map_size.y)
	{
			place.x = f->map_size.x - 1;
			while(place.x >= 0)
			{
				if (f->map[place.y][place.x] == f->our)
				{
					tmp = try_it(f, place);
					if (tmp.x >= 0 && tmp.y >= 0)
					{
						if (tmp.value >= res.value)
						{
							if (tmp.value == res.value)
							{
								if (f->last_ennemy.y > f->last_player.y)
									res = tmp;
								else if (f->last_ennemy.x < f->last_player.x)
									res = tmp;
							}
							else
								res = tmp;
						}
					}
				}
				place.x--;
			}
		place.y++;
	}
	if (res.value > 0)
		test2(f, res);
	else if (f->last_ennemy.y > f->last_player.y)
		try_to_place_bottom(f);
	else
		try_to_place_up(f);
	return (0);
}

void		free_piece(t_filler *f)
{
	f->piece_size.x = -1;
	f->piece_size.y = -1;
	ft_arrdel(&f->piece);
}

int			main(void)
{
	t_filler	f;

	f.fd = open("./log", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (!(init_game(&f)))
		return (1);
	if (!(get_piece(&f)))
		return (1);
	try_to_place_near(&f);
	while (1)
	{
		if (!(read_map(&f)))
			break ;
		free_piece(&f);
		if (!(get_piece(&f)))
			break ;
		try_to_place_near(&f);
	}
	free_piece(&f);
	ft_arrdel(&f.map);
	return (0);
}
