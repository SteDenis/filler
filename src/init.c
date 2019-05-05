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
#include "libft.h"
#include "filler.h"

int			init_player(t_filler *f)
{
	char	*player;
	char	*tmp;

	tmp = NULL;
	if ((get_next_line(0, &player) < 0))
		return (0);
	if ((tmp = ft_strchr(player, 'p')))
		f->player = ft_atoi(&tmp[1]);
	ft_strdel(&player);
	if (f->player == 1)
	{
		ft_strcpy(f->ennemy, "xX");
		ft_strcpy(f->our, "oO");
	}
	else if (f->player == 2)
	{
		ft_strcpy(f->ennemy, "oO");
		ft_strcpy(f->our, "xX");
	}
	else
		return (0);
	return (1);
}

int			init_map(t_filler *f)
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

void		init_struct(t_filler *f)
{
	f->map_size.y = -1;
	f->map_size.x = -1;
	f->piece_size.y = -1;
	f->piece_size.x = -1;
	f->last_ennemy.y = -1;
	f->last_ennemy.x = -1;
	f->last_player.y = -1;
	f->last_player.x = -1;
}

int			create_map(t_filler *f)
{
	int		i;
	char	*line;

	i = -1;
	line = NULL;
	if (!(f->map = (char**)malloc(sizeof(char*) * f->map_size.y)))
		return (0);
	while (++i < f->map_size.y && (get_next_line(0, &line) > 0))
	{
		f->map[i] = ft_strdup(ft_strchr(line, ' ') + 1);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	f->map[i] = NULL;
	if (i != f->map_size.y)
	{
		ft_arrdel(&f->map);
		return (0);
	}
	return (1);
}

int			get_position(t_filler *f)
{
	int		i;
	char	*tmp;

	i = -1;
	while (f->map[++i])
	{
		if ((tmp = ft_strchr(f->map[i], f->ennemy[1])))
		{
			f->last_ennemy.x = tmp - f->map[i];
			f->last_ennemy.y = i;
		}
		if ((tmp = ft_strchr(f->map[i], f->our[1])))
		{
			f->last_player.x = tmp - f->map[i];
			f->last_player.y = i;
		}
	}
	if (f->last_player.x < 0 || f->last_player.y < 0)
		return (0);
	if (f->last_ennemy.x < 0 || f->last_ennemy.y < 0)
		return (0);
	return (1);
}

int			init_game(t_filler *f)
{
	init_struct(f);
	if (!(init_player(f)))
		return (0);
	if (!(init_map(f)))
		return (0);
	if (f->map_size.y < 0 || f->map_size.x < 0 || !(create_map(f)))
		return (0);
	if (!(get_position(f)))
		return (0);
	return (1);
}
