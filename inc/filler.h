/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:43:08 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 16:45:01 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
#define FILLER_H

typedef struct		s_xy
{
	int		x;
	int		y;
}					t_xy;

typedef struct		s_xy_res
{
	int		x;
	int		y;
	int		value;
}					t_xy_res;

typedef struct		s_filler
{
	int		player;
	char	ennemy[3];
	char 	our[3];
	char	**map;
	char	**piece;
	int		fd;
	t_xy	map_size;
	t_xy	piece_size;
	t_xy	last_ennemy;
	t_xy	last_player;
}					t_filler;

int				init_game(t_filler *f);
int				get_position(t_filler *f);
#endif
