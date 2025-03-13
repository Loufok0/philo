/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:12:41 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/13 15:43:01 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	update_data(t_philosopher *philo)
{
	pthread_mutex_lock(&(philo->data_m));
	philo->last_t_eat = get_timestamp(philo->philo);
	philo->times_eaten++;
	pthread_mutex_unlock(&(philo->data_m));
}

int	actions(t_philosopher *philo)
{
	if (lock_mutex(philo) != 2)
		return (0);
	tell("%ld\tPhilosopher %d \tis \033[32meating\033[0m his meal n°%lld\n"\
		, philo->philo, philo->id, philo->times_eaten + 1);
	update_data(philo);
	tempo(philo->philo, philo->philo->t_eat);
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(&(philo->prev->fork));
	tell("%ld\tPhilosopher %d \tis \033[35msleeping\033[0m\n"\
		, philo->philo, philo->id, -1);
	tempo(philo->philo, philo->philo->t_sleep);
	tell("%ld\tPhilosopher %d \tis \033[33mthinking\033[0m\n"\
		, philo->philo, philo->id, -1);
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
