/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:06:52 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/12 15:39:19 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include "colors.h"

//====================(STRUCTS)=============================//

typedef struct s_philo
{
	pthread_t	monitor;
	void	*head;
	unsigned int	n_philo;
	unsigned long long int	t_die;
	unsigned long long int	t_eat;
	unsigned long long int	t_sleep;
	unsigned long long int	n_eat;
	pthread_mutex_t		stop_m;
	int			stop;
	pthread_mutex_t		printf;
	unsigned long long int	t_start;
} 	t_philo;

typedef struct s_philosopher
{
	t_philo *philo;
	int	id;
	pthread_t	thread;
	pthread_mutex_t		data_m;
	pthread_mutex_t		fork;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
	long long int	times_eaten;
	unsigned long long int	last_t_eat;
} 	t_philosopher;

//====================(DECLARATIONS)========================//
//utils
long long int	ft_atolli(const char *str);
int	count_occ(char *str, int c);
int	total_occ(char **split, int c);
int	is_number(char *str);
long	get_timestamp(t_philo *philo);

//process
int	process(t_philo *philo);
void	*routine(void *arg);
long	get_time(void);

//philo_init
int	init_philo(t_philo *philos, char **av);
int	init_philosophers(t_philo *philo);

//debug
void	show_philo(t_philo philo);
void	print_philosophers(t_philosopher *head);

#endif
