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
			if (f->piece[place.y][place.x] == '*'
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

static int	try_it_up(t_filler *f, t_xy pos, t_xy *tmp)
{
	t_xy	res;
	t_xy	place;

	place.y = f->piece_size.y;
	while (--place.y >= 0)
	{
		place.x = ((e_x_gt_p_x(f))) ? f->piece_size.x - 1 : 0;
		while (((e_x_gt_p_x(f))) ? place.x >= 0 : place.x < f->piece_size.x)
		{
			res.y = pos.y - place.y;
			res.x = pos.x - place.x;
			res.value = 0;
			if (f->piece[place.y][place.x] == '*'
				&& res.y < f->map_size.y && res.x < f->map_size.x)
			{
				if (put_piece(f, &res))
				{
					copy_txy_value(tmp, res);
					return (1);
				}
			}
			place.x += ((e_x_gt_p_x(f))) ? -1 : 1;
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
		place.x = ((e_x_gt_p_x(f))) ? f->map_size.x : 0;
		while (((e_x_gt_p_x(f))) ? place.x >= 0 : place.x < f->map_size.x)
		{
			if (f->map[place.y][place.x] == f->player
				&& try_it_up(f, place, &tmp))
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
			if (f->map[place.y][place.x] == f->player
				&& try_it(f, place, &tmp))
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
			if (f->map[place.y][place.x] == f->player
				&& try_it_up(f, place, &tmp))
				set_result(f, res, tmp);
			place.x--;
		}
		place.y++;
	}
	if (res->value > 0)
		return (1);
	return (0);
}
