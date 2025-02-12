# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 00:28:46 by malapoug          #+#    #+#              #
#    Updated: 2025/02/12 15:13:40 by malapoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

DEBUGA = -fsanitize=address
DEBUGP = -fsanitize=thread

CFLAGS = -Wall -Wextra -Werror

SRCS =	main.c\
	process.c\
	philo_init.c\
	utils/ft_atoi.c\
	utils/is_number.c\
	utils/count_occ.c\
	debug.c\

OBJS = $(SRCS:.c=.o)

RM = rm -f


all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread
	@echo $(NAME)" compiled!\n"

debug: $(OBJS)
	@$(CC) $(CFLAGS) $(DEBUGA) $(OBJS) -o debugAddress -lpthread
	@$(CC) $(CFLAGS) $(DEBUGP) $(OBJS) -o debugPthread -lpthread
	@echo $(NAME)" compiled debug with address and pthread!\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -lpthread


clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) debugAddress
	@$(RM) debugPthread
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

