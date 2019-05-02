# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 17:23:35 by fstadelw          #+#    #+#              #
#    Updated: 2018/12/31 23:46:37 by fstadelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################
#         VARIABLES         #
#############################
#### FILE STRUCTURE ####
include include.mk
NAME	:=	$(LIBFT)

SRC		:=	\
	arr/ft_arraddline.c	\
	arr/ft_arrdel.c		\
	arr/ft_arrdelline.c	\
	arr/ft_arrdup.c		\
	arr/ft_arrlen.c		\
	\
	ascii/ft_isalnum.c		\
	ascii/ft_isalpha.c		\
	ascii/ft_isascii.c		\
	ascii/ft_isdigit.c		\
	ascii/ft_islower.c		\
	ascii/ft_isprint.c		\
	ascii/ft_isspace.c		\
	ascii/ft_isstralnum.c	\
	ascii/ft_isupper.c		\
	ascii/ft_tolower.c		\
	ascii/ft_toupper.c		\
	\
	gnl/get_next_line.c	\
	\
	math/ft_abs.c	\
	math/ft_atoi.c	\
	math/ft_itoa.c	\
	math/ft_max.c	\
	math/ft_min.c	\
	math/ft_pow.c	\
	\
	mem/ft_bzero.c		\
	mem/ft_memalloc.c	\
	mem/ft_memccpy.c	\
	mem/ft_memchr.c		\
	mem/ft_memcmp.c		\
	mem/ft_memcpy.c		\
	mem/ft_memdel.c		\
	mem/ft_memmove.c	\
	mem/ft_memset.c		\
	\
	put/ft_putarr_fd.c	\
	put/ft_putarr.c		\
	put/ft_putchar.c	\
	put/ft_putchar_fd.c	\
	put/ft_putendl.c	\
	put/ft_putendl_fd.c	\
	put/ft_putnbr.c		\
	put/ft_putnbr_fd.c	\
	put/ft_putstr.c		\
	put/ft_putstr_fd.c	\
	\
	str/ft_strappend.c		\
	str/ft_strcat.c			\
	str/ft_strchr.c			\
	str/ft_strclr.c			\
	str/ft_strcmp.c			\
	str/ft_strcpy.c			\
	str/ft_strdel.c			\
	str/ft_strdup.c			\
	str/ft_strequ.c			\
	str/ft_strfindchar.c	\
	str/ft_striter.c		\
	str/ft_striteri.c		\
	str/ft_strjoin.c		\
	str/ft_strlcat.c		\
	str/ft_strlen.c			\
	str/ft_strmap.c			\
	str/ft_strmapi.c		\
	str/ft_strnappend.c		\
	str/ft_strncat.c		\
	str/ft_strncmp.c		\
	str/ft_strncpy.c		\
	str/ft_strnequ.c		\
	str/ft_strnew.c			\
	str/ft_strnstr.c		\
	str/ft_strrchr.c		\
	str/ft_strsplit.c		\
	str/ft_strstr.c			\
	str/ft_strsub.c			\
	str/ft_strtrim.c

SRCDIR	:=	src
INCDIR	:=	inc
LIBDIR	:=	lib

BUILDDIR	:=	build
OBJDIR		:=	$(BUILDDIR)/obj
DBGDIR		:=	$(BUILDDIR)/debug
DEPDIR		:=	$(BUILDDIR)/dep

# File used as a command output buffer
TMP		:=	build/tmp.txt

#### COMPILER ####
CC		?=	cc

INCFLAG	:= -I $(INCDIR)
STDFLAG	?=	-ansi
WFLAGS	?=	-Wall -Wextra -Werror -pedantic
CFLAGS	=	$(WFLAGS) $(INCFLAG) $(STDFLAG)

DEPGEN	:=	$(CC)
DEPFLAG	:=	-MM $(INCFLAG)

LD		:=	ar
LDFLAG	:=	rcs

#############################
#    MAKEFILE VARIABLES     #
#############################
#### FILE STRUCTURE ####
# *LOCA is the list of all subdirectory in a directory
SRCLOCA	:=	$(shell find $(SRCDIR) -type d)
OBJLOCA	:=	$(subst $(SRCDIR), $(OBJDIR), $(SRCLOCA))
DBGLOCA	:=	$(subst $(SRCDIR), $(DBGDIR), $(SRCLOCA))
DEPLOCA	:=	$(subst $(SRCDIR), $(DEPDIR), $(SRCLOCA))

OBJ		:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DBG		:=	$(addprefix $(DBGDIR)/, $(SRC:.c=.o))
DEP		:=	$(addprefix $(DEPDIR)/, $(SRC:.c=.d))
SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))

#### COLORS ####
ifdef TERM
# Ansi excape color sequences
RED			:=	"\033[1;31m"
GREEN		:=	"\033[0;32m"
BGREEN		:=	"\033[1;32m"
BLUE		:=	"\033[0;34m"
YELLOW		:=	"\033[0;33m"
PURPLE		:=	"\033[0;35m"
CYAN		:=	"\033[0;36m"
GREY		:=	"\033[0;37m"

# When printed reset the color
COLRESET	:=	"\033[0m"

# Move the cursor at the begining of the line
MOVELINE	:=	"\033[1A"
# Erase current line
CLEARLINE	:=	"\033[K"

COMPCOLOR	:=	$(GREEN)
LINKCOLOR	:=	$(PURPLE)
ONGOINGCOL	:=	$(YELLOW)
KOCOLOR		:=	$(RED)
RMCOLOR		:=	$(GREY)
DEBUGCOLOR	:=	$(YELLOW)
endif

#############################
#           RULES           #
#############################
#### COMPILE ####
# Standard rule used when just calling $> make
all:		$(NAME)

# Program linkage
$(NAME):	$(OBJ)
ifdef TERM
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
endif
	@ $(LD) $(LDFLAG) $(NAME) $(OBJ) 1> $(TMP) 2> $(TMP) \
		&& (echo $(CLEARLINE)$(LINKCOLOR)[libft]$(COLRESET)"	: created" \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP)) \
		|| (echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: linkage fail" \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP) \
			; exit 1)

# Compilation and .d generation
$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
ifdef TERM
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
endif
	@ $(CC) -c $< $(CFLAGS) -o  $@ 1> $(TMP) 2> $(TMP) \
		&& (echo $(CLEARLINE)$(COMPCOLOR)[OK]$(COLRESET)"	: "$@ \
			; cat $(TMP) \
			| sed -e "s/^/    /g") \
		|| (echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: "$@ \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP) \
			; exit 1)
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
		> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

# Dir created to store build cache
$(OBJDIR):
	@ mkdir -p $(OBJLOCA)
$(DBGDIR):
	@ mkdir -p $(DBGLOCA)
$(DEPDIR):
	@ mkdir -p $(DEPLOCA)
$(BUILDDIR):
	@ mkdir -p $(BUILDDIR)

# Recompile with as much warning as possible
warn:	WFLAGS := -Wall -Wextra -ansi -Wpedantic -Wno-vla
# If clang is installed also add this exclusive warning
ifdef CLANG_INSTALLED
warn:	CC := clang
warn:	WFLAGS += -Weverything
endif
warn:	lre

#### FORBIDEN FUNCTION ####
# Check forbiden funcion call
# All functions listed in .function_whitelist.txt are authorised
ffcheck:	$(NAME)
	@ nm -u $(NAME) \
		| sed -e 's/^\s*U\s//g' \
		| grep -Ev '^\s*w\s|^__|dyld_stub_binder' \
		| grep -Ev 1> $(TMP) 2> $(TMP) \
			`cat .function_whitelist.txt \
			| sed -e 's/^/\^_?/g' \
			| sed -e 's/$$/|/g' \
			| tr -d '\n' \
			| sed 's/|$$//g'` \
		; wc -l < $(TMP) \
		| grep -e '^\s*\0$$' 1> /dev/null 2> /dev/null \
	&& echo $(BGREEN)[func]$(COLRESET)"	: no forbiden functions found" \
	|| (echo $(RED)[func]$(COLRESET)"	: forbiden functions found" \
		; cat $(TMP) \
		| sed -e "s/^/    /g" \
		; rm $(TMP))

#### NORM ####
norm:	| $(BUILDDIR)
ifdef TERM
	@ echo $(ONGOINGCOL)[norm]$(COLRESET)"	: "Will it pass ?$(MOVELINE)
endif
	@ norminette $(SRC) $(INCDIR) \
		| (! grep -E -B 1 "(^Warning|^Error)" 1> $(TMP) 2> $(TMP)) \
		&& echo $(CLEARLINE)$(CYAN)[NORM]$(COLRESET)"	:" \
				"pass, it's ok for now" \
		|| (echo $(CLEARLINE)$(RED)[NORM]$(COLRESET)"	:" \
				"you failed miserably !" \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP))

sure: warn ffcheck norm

#### DEBUGING ####
$(DBGDIR)/%.o:		$(SRCDIR)/%.c | $(DBGDIR) $(DEPDIR)
ifdef TERM
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
endif
	@ $(CC) -c $< $(CFLAGS) -o  $@ 1> $(TMP) 2> $(TMP) \
		&& (echo $(CLEARLINE)$(COMPCOLOR)[OK]$(COLRESET)"	: "$@ \
			; cat $(TMP) \
			| sed -e "s/^/    /g") \
		|| (echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: "$@ \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP) \
			; exit 1)
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
		> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

debug:	WFLAGS		:= -g -ggdb
debug:	COMPCOLOR	:=	$(DEBUGCOLOR)
debug:	LINKCOLOR	:=	$(DEBUGCOLOR)
debug:	$(DBG)
ifdef TERM
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
endif
	@ $(LD) $(LDFLAG) -o $(NAME) $(DBG) 1> $(TMP) 2> $(TMP) \
		&& (echo $(CLEARLINE)$(LINKCOLOR)[libft]$(COLRESET)"	:"\
				"ready to be beaten" \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP)) \
		|| (echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: linkage fail" \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP) \
			; exit 1)

debugclean:
	@ rm -r $(DBGDIR) 1> /dev/null 2> /dev/null \
		&& echo $(DEBUGCOLOR)[CLR]$(COLRESET)"	:" debug obj \
		; (exit 0)

rdebug: debugclean debug

#### TESTS ####
# Use when you have some error and just want to rest
test:	WFLAGS := -Wall -Wextra
test:	all

# Test with everything recompile
rtest:	WFLAGS := -Wall -Wextra
rtest:	lre

#### LOCAL (Don't recompile lib) ####
lclean:
	@ rm -r $(BUILDDIR) 1> /dev/null 2> /dev/null \
		&& echo $(RMCOLOR)[CLR]$(COLRESET)"	:" obj \
		; (exit 0)

lfclean: lclean
	@ rm -Rf *.dSYM 1> /dev/null 2> /dev/null
	@ rm $(NAME) 1> /dev/null 2> /dev/null \
		&& echo $(RMCOLOR)[CLR]$(COLRESET)"	:" $(NAME) \
		; (exit 0)

lre: lfclean all

#### MANDATORY ####
clean: lclean
	@ rm -f $(TMP)

fclean:	lfclean

re:		fclean all

#############################
#          SETTING          #
#############################
# Add rule to phony if they are not based on actual files.
.PHONY: all clean fclean re
.PHONY: ffcheck norm sure
.PHONY: debug rdebug debugclean
.PHONY: warn test rtest
.PHONY: lclean lfclean lre

#############################
#         DEPENDENCY        #
#############################
# Include all custom dependency rules created in .d's
# the '-' prevent error in case of non existing files
-include $(DEP)
