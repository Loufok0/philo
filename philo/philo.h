/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:06:52 by malapoug          #+#    #+#             */
/*   Updated: 2025/01/28 15:59:20 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "colors.h"

//====================(STRUCTS)=============================//

typedef struct s_philosopher
{
	int	id;
	pthread_t	thread;
	pthread_mutex_t		fork;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
	long long int	times_eaten;
	unsigned long long int	last_t_eat;
} 	t_philosopher;

typedef struct s_philo
{
	t_philosopher	*philosophers;
	unsigned int	n_philo;
	unsigned long long int	t_die;
	unsigned long long int	t_eat;
	unsigned long long int	t_sleep;
	unsigned long long int	n_eat;
} 	t_philo;

//====================(DECLARATIONS)========================//
//utils
long long int	ft_atolli(const char *str);
int	count_occ(char *str, int c);
int	total_occ(char **split, int c);

//philo_init
int	init_philo(t_philo *philos, char **av);
int	init_philosophers(t_philo *philo);

//debug
void	show_philo(t_philo philo);

#endif
