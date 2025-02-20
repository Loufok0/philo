/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:12:41 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/20 01:17:55 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo				*philo;
	t_philosopher		*curr;
	long int			current_time;
	int					eaten;

	philo = (t_philo *)arg;
	while (1)
	{
		eaten = 1;
		curr = (t_philosopher *)(philo->head);
		while (curr)
		{
			current_time = get_timestamp(philo);
			pthread_mutex_lock(&(curr->data_m));
			if (current_time - curr->last_t_eat > philo->t_die)
			{
				tell("%ld\tPhilosopher %d \t\033[31mdied\033[0m\n", philo, curr->id, -1);
				pthread_mutex_lock(&(philo->stop_m));
				philo->stop = 1;
				pthread_mutex_unlock(&(philo->stop_m));
				pthread_mutex_unlock(&(curr->data_m));
				return (NULL);
			}
			if (curr->times_eaten < philo->n_eat)
				eaten = 0;
			pthread_mutex_unlock(&(curr->data_m));
			curr = curr->next;
		}
		if (eaten == 1)
		{
			tell(GREEN"%ld\tAll Philosophers have eaten at least %lld times \n"RESET, philo, -1, philo->n_eat);
			pthread_mutex_lock(&(philo->stop_m));
			philo->stop = 1;
			pthread_mutex_unlock(&(philo->stop_m));
			return (NULL);
		}
		tempo(philo, 1);
	}
	return (NULL);
}

int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&(philo->stop_m));
	if (philo->stop == 1)
	{
		pthread_mutex_unlock(&(philo->stop_m));
		return (1);
	}
	pthread_mutex_unlock(&(philo->stop_m));
	return (0);
}

int	actions(t_philosopher *philo)
{
	if (check_stop(philo->philo))
		return (0);
	if (lock_mutex(philo) != 2)
		return (0);
	tell("%ld\tPhilosopher %d \tis \033[32meating\033[0m his meal n°%lld\n", philo->philo, philo->id, philo->times_eaten + 1);
	if (check_stop(philo->philo))
	{
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->prev->fork));
		return (0);
	}
	pthread_mutex_lock(&(philo->data_m));
	philo->last_t_eat = get_timestamp(philo->philo);
	philo->times_eaten++;
	pthread_mutex_unlock(&(philo->data_m));
	tempo(philo->philo, philo->philo->t_eat);
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(&(philo->prev->fork));
	if (check_stop(philo->philo))
		return (0);
	tell("%ld\tPhilosopher %d \tis \033[35msleeping\033[0m\n", philo->philo, philo->id, -1);
	tempo(philo->philo, philo->philo->t_sleep);
	if (check_stop(philo->philo))
		return (0);
	tell("%ld\tPhilosopher %d \tis \033[33mthinking\033[0m\n", philo->philo, philo->id, -1);
	return (1);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!check_stop(philo->philo))
	{
		if (!actions(philo))
			break ;
	}
	return (NULL);
}

int	process(t_philo *philo)
{
	t_philosopher	*curr;

	curr = philo->head;
	if (!create_threads(philo, curr))
		return (0);
	if (!join_threads(philo, curr))
		return (0);
	clear_head(philo->head);
	return (1);
}

//ATTENTION A VALGRIND /!\ (and fuch there is an backslash n error...)
