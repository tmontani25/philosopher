# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 17:33:19 by tmontani          #+#    #+#              #
#    Updated: 2024/11/02 19:00:00 by tmontani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
C_FLAGS= -Wall -Wextra -Werror
NAME=philosophers


all: philosophers

$(NAME): philosophers.c
	$(CC) $(C_FLAGS) -o $(NAME) philosophers.c

fclean:
	rm -rf $(NAME)