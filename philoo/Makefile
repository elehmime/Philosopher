# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/23 09:13:52 by ellehmim          #+#    #+#              #
#    Updated: 2024/09/15 16:12:17 by ellehmim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# Options de compilation
CFLAGS = -Wall -Wextra -Werror -g3

# Fichiers sources
SRC = main.c parsing.c init.c philo.c philo_utils.c philo_utils1.c
OBJ = $(SRC:.c=.o)

# Noms de l'exécutable
PHILO_BIN = philo

# Règle par défaut de compilaton
all: $(PHILO_BIN)

# Convertir les .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation du serveur
$(PHILO_BIN): $(OBJ)
	$(CC) $(OBJ) -o $@

# Nettoyage des fichiers compilés
clean:
	rm -f $(OBJ)

# Suppression de tout ce qui a été compilé
fclean: clean
	rm -f $(PHILO_BIN)

# Recompilation de tout
re: fclean all

# Empêcher make de confondre un fichier et une règle
.PHONY: all clean fclean re
