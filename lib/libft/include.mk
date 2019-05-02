# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 17:23:35 by fstadelw          #+#    #+#              #
#    Updated: 2018/11/21 17:31:33 by fstadelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT		:=	libft.a

LIBFT_PATH	?=	.

LIBFT_LINK	:= -L $(LIBFT_PATH) -l ft
LIBFT_INC	:= -I $(LIBFT_PATH)/inc

ifndef LIB_LINK
LIB_LINK	:=
LIB_INC		:=
endif

LIB_LINK	+= $(LIBFT_LINK)
LIB_INC		+= $(LIBFT_INC)
