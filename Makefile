# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/08 16:51:41 by adu-pelo          #+#    #+#              #
#    Updated: 2016/03/08 17:04:12 by adu-pelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = data.c display.c format_path.c free.c get_info.c get_param.c main.c \
	  manage_opt.c option.c padding.c recursive.c size.c sort_lst.c sort_tab.c \
	  sort_tab_r.c tool.c tool2.c

OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean $(NAME)

.PHONY : all clean fclean re
