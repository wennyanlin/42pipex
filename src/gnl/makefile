# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 22:21:23 by wlin              #+#    #+#              #
#    Updated: 2024/04/04 11:32:07 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl
CC := gcc
CFLAGS := -Wall -Wextra -Werror -MMD -g

SRC_FILES	:=	get_next_line.c \
				get_next_line_utils.c

OBJ_FILES	=	$(SRC_FILES:.c=.o)
DEP_FILES	=	$(OBJ_FILES:.o=.d)

# Regla/metodo implicito
%.o:%.c 	get_next_line.h Makefile
			$(CC) $(CFLAGS) -c $< -o $@

# Mis reglas mis metodos
all: $(NAME) 

-include $(DEP_FILES)
$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@

clean:
		rm -f $(OBJ_FILES) $(DEP_FILES)

fclean:	clean
		rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
