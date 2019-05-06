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

# include <stdlib.h>

# define BUFF_SIZE 128

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
	char	ennemy;
	char 	our;
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
