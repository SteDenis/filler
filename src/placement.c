/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:43:08 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 16:45:01 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	put_piece(t_filler *f, t_xy *pos)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	count = 0;
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
	if (count < 1)
		return (0);
	return (1);
}

static int	try_it(t_filler *f, t_xy pos, t_xy *tmp)
{
	t_xy	res;
	t_xy	place;

	place.y = -1;
	while (++place.y < f->piece_size.y)
	{
		place.x = -1;
		while (++place.x < f->piece_size.x)
		{
			res.y = pos.y - place.y;
			res.x = pos.x - place.x;
			res.value = 0;
			if (res.x >= 0 && res.y >= 0 && f->piece[place.y][place.x] == '*'
				&& res.y < f->map_size.y && res.x < f->map_size.x)
			{
				if (put_piece(f, &res))
				{
					copy_txy_value(tmp, res);
					return (1);
				}
			}
		}
	}
	return (0);
}

int			try_to_place_up(t_filler *f, t_xy *res)
{
	t_xy	place;
	t_xy	tmp;

	place.y = 0;
	while (place.y < f->map_size.y)
	{
		place.x = ((e_x_gt_p_x(f))) ? f->map_size.x - 1 : 0;
		while (((e_x_gt_p_x(f))) ? place.x >= 0 : place.x < f->map_size.x)
		{
			if (f->map[place.y][place.x] == f->player && try_it(f, place, &tmp))
			{
				copy_txy_value(res, tmp);
				return (1);
			}
			place.x += ((e_x_gt_p_x(f))) ? -1 : 1;
		}
		place.y++;
	}
	return (0);
}

int			try_to_place_bottom(t_filler *f, t_xy *res)
{
	t_xy	place;
	t_xy	tmp;

	place.y = f->map_size.y - 1;
	tmp.value = -1;
	while (place.y >= 0)
	{
		place.x = (e_x_gt_p_x(f)) ? f->map_size.x - 1 : 0;
		while ((e_x_gt_p_x(f)) ? place.x >= 0 : place.x < f->map_size.x)
		{
			if (f->map[place.y][place.x] == f->player && try_it(f, place, &tmp))
			{
				copy_txy_value(res, tmp);
				return (1);
			}
			place.x += (e_x_gt_p_x(f)) ? -1 : 1;
		}
		place.y--;
	}
	return (0);
}

int			try_to_place_near(t_filler *f, t_xy *res)
{
	t_xy	place;
	t_xy	tmp;

	place.y = 0;
	tmp.value = -1;
	while (place.y < f->map_size.y)
	{
		place.x = f->map_size.x - 1;
		while (place.x >= 0)
		{
			if (f->map[place.y][place.x] == f->player && try_it(f, place, &tmp))
				set_result(f, res, tmp);
			place.x--;
		}
		place.y++;
	}
	if (res->value > 0)
		return (1);
	return (0);
}
