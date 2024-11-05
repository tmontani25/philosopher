# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 17:33:19 by tmontani          #+#    #+#              #
#    Updated: 2024/11/04 18:15:02 by tmontani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
C_FLAGS= -Wall -Wextra -Werror
NAME=philo


all: philo

$(NAME): philo.c
	$(CC) $(C_FLAGS) -o $(NAME) philo.c -lpthread

fclean:
	rm -rf $(NAME)