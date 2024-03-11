# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timo <timo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 13:57:37 by timo              #+#    #+#              #
#    Updated: 2024/03/12 00:46:24 by timo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = helper.c philo.c initialize.c print.c
OBJ = philo.o helper.o initialize.o print.o

all : $(NAME)
$(NAME) : $(OBJ) $(SRC)
	cc -Wall -Werror -Wextra -pthread -o philo $(OBJ)
$(OBJ) : $(SRC)
	cc -c -Wall -Werror -Wextra $(SRC)
clean:
	-rm -f $(OBJ)
fclean: clean
	-rm -f $(NAME)
re: fclean all