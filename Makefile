# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/01 11:16:13 by stdenis           #+#    #+#              #
#    Updated: 2019/05/02 03:39:12 by stdenis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= std.filler

SRC		:=	\
	main.c				\
	init.c				\

SRCDIR	:=	src
INCDIR	:=	inc
LIBDIR	:=	lib
TESTDIR	:=	test

BUILDDIR	:=	bin
OBJDIR		:=	$(BUILDDIR)/obj
DBGDIR		:=	$(BUILDDIR)/debug
DEPDIR		:=	$(BUILDDIR)/dep

#### LIBRARY ####
# Printf
LIBFT_PRTF		:=	libftprintf.a
LIBFT_PRTF_PATH :=  $(LIBDIR)/ft_printf
LIB_LINK		:= -L $(LIBFT_PRTF_PATH) -l ftprintf
LIB_INC			:= -I $(LIBFT_PRTF_PATH)/inc

# Libft
LIBFT		:=	libft.a
LIBFT_PATH	:= $(LIBDIR)/libft
LIB_LINK	+= -L $(LIBFT_PATH) -l ft
LIB_INC		+= -I $(LIBFT_PATH)/inc

#### COMPILER ####
CC			?=	cc

INCFLAG		:=	-I $(INCDIR) $(LIB_INC)

STDFLAG		?=	-ansi
WFLAGS		?=	-Wall -Wextra -Werror -pedantic
CFLAGS		=	$(WFLAGS) $(INCFLAG) $(STDFLAG)

DEPGEN		:=	$(CC)
DEPFLAG		:=	-MM $(INCFLAG)

LD			:=	$(CC)
LDFLAG		=	$(LIB_LINK)
LDFLAG		+=	-Wno-unused-command-line-argument $(WFLAGS)

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

COLOR		= 		\033[01;34m
NO_COLOR	= 		\033[00m
OP_COLOR	= 		\033[1;31m
DONE 		= 		$(NO_COLOR)[\033[1;32mOK$(NO_COLOR)]
KO			= 		$(NO_COLOR)[\033[00;31mKO$(NO_COLOR)]


#############################
#           RULES           #
#############################
#### COMPILE ####
all: $(NAME)

$(NAME):	$(OBJ)| $(LIBFT_PATH)/$(LIBFT) $(LIBFT_PRTF_PATH)/$(LIBFT_PRTF)
	@ echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@ $(LD) -o $(NAME) $(OBJ) $(LDFLAG)
	@ printf "$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)\n"


$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@ $(CC) -c $< $(CFLAGS) -o $@ \
		&& printf "$(DONE)	: $(COLOR)$<$(NO_COLOR)\n" \
		|| (printf "$(KO)	<-  $(COLOR)$<$(NO_COLOR)\n" ; false)
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
			> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

$(LIBFT_PATH)/$(LIBFT):
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory

$(LIBFT_PRTF_PATH)/$(LIBFT_PRTF):
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory

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
warn:	WFLAGS += -Wstrict-prototypes -Wunreachable-code  -Wwrite-strings
warn:	WFLAGS += -Wpointer-arith -Wbad-function-cast -Wcast-align -Wcast-qual
CLANG_INSTALLED	:= $(shell which clang > /dev/null 2> /dev/null && echo yes)
# If clang is installed also add this exclusive warning
ifdef CLANG_INSTALLED
warn:	CC := clang
warn:	WFLAGS += -Weverything -Wno-padded -Wno-missing-noreturn
endif
warn:	lre

#### DEBUGING ####
$(DBGDIR)/%.o:		$(SRCDIR)/%.c | $(DBGDIR) $(DEPDIR)
	@printf "$(COLOR)$<$(NO_COLOR) -> "
	@touch $<
	@ $(CC) -c $< $(CFLAGS) -o  $@ && printf "$(DONE)\n" || printf "$(KO)\n"
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
		> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

debug:	WFLAGS		:= -g
debug:	$(DBG) | $(LIBFT_PATH)/$(LIBFT) $(LIBFT_PRTF_PATH)/$(LIBFT_PRTF)
	@echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@$ $(LD) -o $(NAME) $(DBG) $(LDFLAG)
	@printf "$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)  \n"

debugclean:
	@ rm -r $(DBGDIR) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)"	:" debug obj" \
		; (exit 0)

rdebug: debugclean debug

clear:
	@clear

sclean:
	@rm -rf $(OBJ) $(NAME)

#### LOCAL (Don't recompile lib) ####
lclean:
	@ rm -r $(BUILDDIR) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)	: obj\n" \
		; (exit 0)

lfclean: lclean
	@ rm -Rf *.dSYM 1> /dev/null 2> /dev/null
	@ rm $(NAME) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)	: $(NAME)\n" \
		; (exit 0)

lre: lfclean all

#### MANDATORY ####
clean: lclean
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory clean
	@ $(MAKE) -C $(TESTDIR) --no-print-directory clean
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory clean

fclean:	lfclean
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory fclean
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory fclean

re:		fclean all

fre: clear sclean all

test:
	@ $(MAKE) -C $(TESTDIR) --no-print-directory fast

full-test:
	@ $(MAKE) -C $(TESTDIR) --no-print-directory

#############################
#          SETTING          #
#############################
# Add rule to phony if they are not based on actual files.
.PHONY: all re
.PHONY: debug rdebug debugclean
.PHONY: warn
.PHONY: lclean lfclean lre val exe fre
.PHONY: clear sclean clean fclean save
.PHONY: full-test test save val exe fre

#############################
#         DEPENDENCY        #
#############################
# Include all custom dependency rules created in .d's
# the '-' prevent error in case of non existing files
-include $(DEP)
