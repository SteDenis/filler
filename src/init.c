/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:43:08 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 16:45:01 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "filler.h"

static int		init_player(t_filler *f)
{
	char	*player;
	char	*tmp;

	tmp = NULL;
	if ((get_next_line(0, &player) <= 0))
		return (0);
	if ((tmp = ft_strchr(player, 'p')))
		f->p = ft_atoi(&tmp[1]);
	ft_strdel(&player);
	if (f->p == 1)
	{
		f->ennemy = 'X';
		f->player = 'O';
	}
	else if (f->p == 2)
	{
		f->ennemy = 'O';
		f->player = 'X';
	}
	else
		return (0);
	return (1);
}

static int		init_map(t_filler *f)
{
	char	*map;
	char	*tmp;

	tmp = NULL;
	if ((get_next_line(0, &map) <= 0))
		return (0);
	if ((tmp = ft_strchr(map, ' ')))
		f->map_size.y = ft_atoi(&tmp[1]);
	if (tmp && (tmp = ft_strchr(tmp + 1, ' ')))
		f->map_size.x = ft_atoi(&tmp[1]);
	ft_strdel(&map);
	if ((get_next_line(0, &map) <= 0))
		return (0);
	ft_strdel(&map);
	return (1);
}

static int		create_map(t_filler *f)
{
	int		i;
	char	*line;
	char	*tmp;

	i = -1;
	line = NULL;
	if (!(f->map = (char**)malloc(sizeof(char*) * (f->map_size.y + 1))))
		return (0);
	ft_tabset(f->map, NULL, (size_t)f->map_size.y + 1);
	while (++i < f->map_size.y && (get_next_line(0, &line) > 0))
	{
		tmp = ft_strchr(line, ' ');
		if (!tmp || (ft_strlen(tmp + 1) != (size_t)f->map_size.x))
			break ;
		if (!(f->map[i] = ft_strdup(tmp + 1)))
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (i != f->map_size.y)
	{
		ft_arrdel(&f->map);
		return (0);
	}
	return (1);
}

static int		get_position(t_filler *f)
{
	int		i;
	char	*tmp;

	i = -1;
	while (f->map[++i])
	{
		if ((tmp = ft_strchr(f->map[i], f->ennemy)))
		{
			f->start_ennemy.x = tmp - f->map[i];
			f->start_ennemy.y = i;
		}
		if ((tmp = ft_strchr(f->map[i], f->player)))
		{
			f->start_player.x = tmp - f->map[i];
			f->start_player.y = i;
		}
	}
	if (f->start_player.x < 0 || f->start_player.y < 0)
		return (0);
	if (f->start_ennemy.x < 0 || f->start_ennemy.y < 0)
		return (0);
	return (1);
}

int				init_game(t_filler *f)
{
	f->piece = NULL;
	f->p = 0;
	f->map = NULL;
	f->map_size.y = -1;
	f->map_size.x = -1;
	f->piece_size.y = -1;
	f->piece_size.x = -1;
	f->start_ennemy.y = -1;
	f->start_ennemy.x = -1;
	f->start_player.y = -1;
	f->start_player.x = -1;
	if (!(init_player(f)))
		return (0);
	if (!(init_map(f)))
		return (0);
	if (f->map_size.y <= 0 || f->map_size.x <= 0 || !(create_map(f)))
		return (0);
	if (!(get_position(f)))
	{
		ft_arrdel(&f->map);
		return (0);
	}
	return (1);
}
