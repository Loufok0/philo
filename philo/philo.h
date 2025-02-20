/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:06:52 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/20 01:03:21 by malapoug         ###   ########.fr       */
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

typedef struct s_philosopher	t_philosopher;

typedef struct s_philo
{
	pthread_t				monitor;
	t_philosopher			*head;
	unsigned int			n_philo;
	unsigned long long int	t_die;
	unsigned long long int	t_eat;
	unsigned long long int	t_sleep;
	unsigned long long int	n_eat;
	pthread_mutex_t			stop_m;
	int						stop;
	pthread_mutex_t			printf;
	unsigned long long int	t_start;
}	t_philo;

typedef struct s_philosopher
{
	t_philo					*philo;
	int						id;
	pthread_t				thread;
	pthread_mutex_t			data_m;
	pthread_mutex_t			fork;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
	unsigned long long int	times_eaten;
	unsigned long long int	last_t_eat;
}	t_philosopher;

//====================(DECLARATIONS)========================//

//philo_utils

void			tempo(t_philo *philo, long int t);
void			tell(char *str, t_philo *philo, int id, long long int n_eat);
int				create_threads(t_philo *philo, t_philosopher *head);
int				lock_mutex(t_philosopher *philo);
int				join_threads(t_philo *philo, t_philosopher *head);

//utils
long long int	ft_atolli(const char *str);
int				count_occ(char *str, int c);
int				total_occ(char **split, int c);
int				is_number(char *str);
long			get_timestamp(t_philo *philo);

//process
int				process(t_philo *philo);
void			*monitor(void *arg);
void			*routine(void *arg);
long			get_time(void);
int				check_stop(t_philo *philo);

//philo_init
int				init_philo(t_philo *philos, char **av);
int				init_philosophers(t_philo *philo);

//philo_clear
void			clear_head(t_philosopher *head);

//debug
void			show_philo(t_philo philo);
void			print_philosophers(t_philosopher *head);

#endif
