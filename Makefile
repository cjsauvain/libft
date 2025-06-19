# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 15:21:43 by jsauvain          #+#    #+#              #
#    Updated: 2022/09/07 10:50:13 by jsauvain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#####################
#   Library Name	#
#####################
NAME = libft.a

#####################
#    Directories	#
#####################
SRCS_DIR = srcs
OBJS_DIR = obj
INC_DIR  = inc

#####################
# Sources / Headers #
#####################
SRCS_CHAR =		ft_isalnum.c ft_isalpha.c ft_isascii.c \
			 	ft_isdigit.c ft_isprint.c ft_toupper.c \
			 	ft_tolower.c 

SRCS_STRING =	ft_strlcpy.c ft_strlcat.c ft_strlen.c		\
				ft_strlen_double.c ft_strchr.c ft_strrchr.c	\
				ft_strncmp.c ft_strcmp.c ft_strnstr.c		\
				ft_atoi.c ft_strdup.c ft_substr.c			\
				ft_strjoin.c ft_strtrim.c ft_strmapi.c		\
				ft_striteri.c ft_itoa.c ft_split.c

SRCS_MEMORY =	ft_bzero.c ft_memcpy.c ft_memmove.c \
			  	ft_memset.c ft_memchr.c ft_memcmp.c \
			  	ft_calloc.c 

SRCS_IO =		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c 

SRCS_LST =		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
				ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
				ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCS_PARSING =	ft_getopt.c

SRCS =	$(addprefix $(SRCS_DIR)/char/, $(SRCS_CHAR))		\
		$(addprefix $(SRCS_DIR)/string/, $(SRCS_STRING))	\
		$(addprefix $(SRCS_DIR)/memory/, $(SRCS_MEMORY))	\
		$(addprefix $(SRCS_DIR)/io/, $(SRCS_IO))			\
		$(addprefix $(SRCS_DIR)/lst/, $(SRCS_LST))			\
		$(addprefix $(SRCS_DIR)/parsing/, $(SRCS_PARSING))	\

HEADER = $(INC_DIR)/libft.h

#####################
#      Objects      #
#####################
OBJS = $(subst $(SRCS_DIR)/,,$(SRCS:%.c=$(OBJS_DIR)/%.o))

#####################
#    Compilation	#
#####################
CC = clang
CFLAGS = -Wall -Wextra -Werror --std=c23
INCLUDE = -I $(INC_DIR)
AR = ar rcs

ifeq ($(DEV), 1)
CFLAGS += -g3
USE_WARNINGS := 1
EXTRA_DEPS += compile_commands.json
endif

#####################
#       Rules       #
#####################
all: $(EXTRA_DEPS) $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
		$(AR) $(NAME) $(OBJS)

compile_commands.json: clean
		@bear -- make --no-print-directory -s USE_WARNINGS=1 $(NAME) -j$(shell nproc)	

clean:
		@rm -rf $(OBJS_DIR)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
