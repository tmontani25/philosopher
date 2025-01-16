# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 17:33:19 by tmontani          #+#    #+#              #
#    Updated: 2025/01/15 14:39:03 by tmontani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = gcc
C_FLAGS = -Wall -Wextra -Werror
NAME = philo

# Liste des fichiers source
SRC = philo.c start.c utils.c free_and_destroy.c # Ajoute ici tous tes fichiers .c

# Liste des fichiers objets, générés automatiquement à partir des fichiers source
OBJ = $(SRC:.c=.o)

# Règle par défaut
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJ)
	$(CC) $(C_FLAGS) -o $(NAME) $(OBJ) -lpthread

# Règle de compilation des fichiers .o
%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

# Recompilation complète
re: fclean all
