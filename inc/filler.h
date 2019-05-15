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
# define FILLER_H

# include <stdlib.h>
# define BUFF_SIZE 128

typedef struct	s_xy
{
	int		x;
	int		y;
	int		value;
}				t_xy;

typedef struct	s_filler
{
	int		p;
	char	ennemy;
	char	player;
	char	**map;
	char	**piece;
	t_xy	map_size;
	t_xy	piece_size;
	t_xy	start_ennemy;
	t_xy	start_player;
}				t_filler;

/*
** init.c
*/
int				init_game(t_filler *f);

/*
** put_piece.c
*/
int				put_piece(t_filler *f, t_xy *pos);
int				estimate_value(t_filler *f, int y, int x);

/*
** placement.c
*/
int				try_to_place_near(t_filler *f, t_xy *res);
int				try_to_place_bottom(t_filler *f, t_xy *res);
int				try_to_place_up(t_filler *f, t_xy *res);

/*
** misc.c
*/
int				get_size_piece(t_filler *f);
void			copy_txy_value(t_xy *res, t_xy tmp);
int				e_x_gt_p_x(t_filler *f);
void			free_piece(t_filler *f);
void			set_result(t_filler *f, t_xy *res, t_xy tmp);

/*
** utility
*/
void			ft_arrdel(char ***arr);
int				ft_atoi(const char *str);
void			*ft_memset(void *b, int c, size_t n);
void			ft_tabset(char **arr, void *val, size_t n);
void			ft_putchar(char c);
void			ft_putnbr(int n);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dst, const char *src);
void			ft_strdel(char **as);
char			*ft_strdup(const char *src);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *str);
char			*ft_strnew(size_t size);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
int				get_next_line(const int fd, char **line);
#endif
