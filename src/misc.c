/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:43:08 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 16:45:01 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			get_size_piece(t_filler *f)
{
	char	*piece;
	char	*tmp;

	piece = NULL;
	if ((get_next_line(0, &piece)) <= 0)
		return (0);
	if ((tmp = ft_strchr(piece, ' ')))
		f->piece_size.y = ft_atoi(&tmp[1]);
	if (tmp && (tmp = ft_strchr(tmp + 1, ' ')))
		f->piece_size.x = ft_atoi(&tmp[1]);
	ft_strdel(&piece);
	if (f->piece_size.x < 0 || f->piece_size.y < 0)
		return (0);
	return (1);
}

void		copy_txy_value(t_xy *res, t_xy tmp)
{
	res->x = tmp.x;
	res->y = tmp.y;
	res->value = tmp.value;
}

int			e_x_gt_p_x(t_filler *f)
{
	if ((f->start_ennemy.x > f->start_player.x))
		return (1);
	return (0);
}

void		free_piece(t_filler *f)
{
	f->piece_size.x = -1;
	f->piece_size.y = -1;
	if (f->piece)
		ft_arrdel(&f->piece);
	f->piece = NULL;
}

void		set_result(t_filler *f, t_xy *res, t_xy tmp)
{
	if (tmp.value >= res->value)
	{
		if (tmp.value == res->value)
		{
			if (f->start_ennemy.y > f->start_player.y)
				copy_txy_value(res, tmp);
			else if (((e_x_gt_p_x(f))))
				copy_txy_value(res, tmp);
		}
		else
			copy_txy_value(res, tmp);
	}
}
