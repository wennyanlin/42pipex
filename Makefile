# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 22:21:23 by wlin              #+#    #+#              #
#    Updated: 2024/04/05 20:39:23 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_B = pipex_bonus

CC := gcc
CFLAGS := -Wall -Wextra -Werror -MMD -g
SRC_DIR		:=	src

SRC_FILES	:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/pipex.c \
				$(SRC_DIR)/find_path.c \
				$(SRC_DIR)/pipe.c \
				$(SRC_DIR)/split.c \
				$(SRC_DIR)/string.c \

GNL_FILES	:=	$(SRC_DIR)/gnl/get_next_line.c \
				$(SRC_DIR)/gnl/get_next_line_utils.c

OBJ_GNL		=	$(GNL_FILES:.c=.o)
DEP_GNL		=	$(OBJ_GNL:.o=.d)
OBJ_FILES	=	$(SRC_FILES:.c=.o)
DEP_FILES	=	$(OBJ_FILES:.o=.d)

SRC_B_FILES	:=	$(SRC_DIR)/main_bonus.c \
				$(SRC_DIR)/pipex.c \
				$(SRC_DIR)/find_path.c \
				$(SRC_DIR)/pipe.c \
				$(SRC_DIR)/split.c \
				$(SRC_DIR)/string.c \
				$(SRC_DIR)/here_doc.c \

OBJ_B_FILES	=	$(SRC_B_FILES:.c=.o)
DEP_B_FILES	=	$(OBJ_B_FILES:.o=.d)

%.o:%.c 	src/pipex.h Makefile
			$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME) 

-include $(DEP_FILES)
$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@

bonus: ${NAME_B}

${NAME_B}: $(OBJ_B_FILES) $(OBJ_GNL)
	$(CC) $(CFLAGS) $(OBJ_B_FILES) $(OBJ_GNL) -o $@

clean:
		rm -f $(OBJ_FILES) $(DEP_FILES) $(OBJ_B_FILES) $(DEP_B_FILES)

fclean:	clean
		rm -f $(NAME) $(NAME_B)

re:	fclean all

.PHONY: all clean fclean re
