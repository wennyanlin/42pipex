# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 22:21:23 by wlin              #+#    #+#              #
#    Updated: 2024/04/04 11:39:53 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_B = pipex_bonus

CC := gcc
CFLAGS := -Wall -Wextra -Werror -MMD -g
EXTRAFLAGS = -Iinclude -I$(SRC_DIR)/$(GNL_DIR)
LDFLAGS = -L$(SRC_DIR)/mlx -L$(SRC_DIR)/gnl
LDLIBS := -framework OpenGL -framework AppKit -lget_next_line
GNL_DIR		:=	gnl

SRC_FILES	:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/pipex.c \
				$(SRC_DIR)/find_path.c \
				$(SRC_DIR)/pipe.c \
				$(SRC_DIR)/split.c \
				$(SRC_DIR)/string.c \

OBJ_FILES	=	$(SRC_FILES:.c=.o)
DEP_FILES	=	$(OBJ_FILES:.o=.d)

SRC_B_FILES	:=	$(SRC_DIR)/main_bonus.c \
				$(SRC_DIR)/pipex.c \
				$(SRC_DIR)/find_path.c \
				$(SRC_DIR)/pipe.c \
				$(SRC_DIR)/split.c \
				$(SRC_DIR)/string.c \
				$(SRC_DIR)/$(GNL_DIR)/*.c

OBJ_B_FILES	=	$(SRC_B_FILES:.c=.o)
DEP_B_FILES	=	$(OBJ_B_FILES:.o=.d)

# Regla/metodo implicito
%.o:%.c 	src/pipex.h Makefile
			$(CC) $(CFLAGS) -c $< -o $@

# Mis reglas mis metodos
all: GNL $(NAME) 

-include $(DEP_FILES)
$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@

bonus: ${NAME_B}

${NAME_B}: $(OBJ_B_FILES)
	$(CC) $(CFLAGS) $(OBJ_B_FILES) -o $@

clean:
		rm -f $(OBJ_FILES) $(DEP_FILES) $(OBJ_B_FILES) $(DEP_B_FILES) 
		make -C $(SRC_DIR)/gnl clean

fclean:	clean
		rm -f $(NAME) $(NAME_B)

re:	fclean all

.PHONY: all clean fclean re GNL

GNL:
	make -C $(SRC_DIR)/gnl --no-print-directory

# NAME = pipex

# INCLUDES = pipex.h

# SRCS = pipex.c split.c string.c\

# OBJS = $(SRCS:.c=.o)

# COMPILER = gcc

# CFLAGS = -g -Wall -Werror -Wextra

# $(NAME): $(OBJS) $(INCLUDES) Makefile
# 		$(COMPILER) $(SRCS) -g -fsanitize=address -o $(NAME)

# all:
# 	$(MAKE)

# clean:
# 		rm -f $(OBJS)
# 		$(MAKE) fclean

# fclean:	clean
# 		rm -f $(NAME)

# re:		fclean all

# .PHONY: all clean fclean re
