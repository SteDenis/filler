/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:43:08 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 16:45:01 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		put_piece(t_filler *f, t_xy *pos)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	count = 0;
	if ((pos->x == 0 && pos->y == 0) || pos->x < 0 || pos->y < 0)
		return (0);
	while (++i < f->piece_size.y)
	{
		j = -1;
		while (++j < f->piece_size.x)
			if (f->piece[i][j] == '*')
			{
				if (pos->y + i >= f->map_size.y || pos->x + j >= f->map_size.x)
					return (0);
				if (f->map[pos->y + i][pos->x + j] == f->player && ++count > 1)
					return (0);
				if (f->map[pos->y + i][pos->x + j] == f->ennemy)
					return (0);
				pos->value += estimate_value(f, pos->y + i, pos->x + j);
			}
	}
	return (count < 1 ? 0 : 1);
}

int		estimate_value(t_filler *f, int y, int x)
{
	int		i;
	int		j;
	t_xy	count;

	count.x = 0;
	count.y = 0;
	i = y + 2;
	while (--i >= y - 1)
	{
		j = x + 2;
		while (--j >= x - 1)
		{
			if (i >= 0 && j >= 0 && j < f->map_size.x && i < f->map_size.y)
			{
				if (f->map[i][j] == f->ennemy)
					count.x++;
				else if (f->map[i][j] == f->player)
					count.y++;
			}
		}
	}
	if (count.x > 0 && count.y > count.x)
		count.x = 1;
	return (count.x);
}
