# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 00:28:46 by malapoug          #+#    #+#              #
#    Updated: 2025/01/28 16:05:12 by malapoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

DEBUGA = -fsanitize=address
DEBUGP = -fsanitize=pthread

CFLAGS = -Wall -Wextra -Werror

SRCS =	main.c\
	philo_init.c\
	utils/ft_atoi.c\
	utils/count_occ.c\
	debug.c\

OBJS = $(SRCS:.c=.o)

RM = rm -f


all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo $(NAME)" compiled!\n"

debug: $(OBJS)
	@$(CC) $(CFLAGS) $(DEBUGA) $(OBJS) -o debugAddress
	@$(CC) $(CFLAGS) $(DEBUGP) $(OBJS) -o debugPthread
	@echo $(NAME)" compiled debug with address and pthread!\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) debugAddress
	@$(RM) debugPthread
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

