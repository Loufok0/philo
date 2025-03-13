/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:30:03 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/13 14:30:08 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *philo, t_philosopher *head)
{
	unsigned int	i;

	i = -1;
	if (pthread_create(&(philo->monitor), NULL, monitor, philo) != 0)
		return (printf(RED "Error: monitor's pthread_create failed!\n"\
			RESET), 0);
	while (++i < philo->n_philo)
	{
		if (pthread_create(&(head->thread), NULL, routine, head) != 0)
			return (printf(RED "Error: pthread_create failed!\n" RESET), 0);
		head = head->next;
	}
	return (1);
}

int	lock_a(t_philosopher *philo)
{
	int	n_forks;

	n_forks = 0;
	if (philo->prev)
	{
		pthread_mutex_lock(&(philo->prev->fork));
		n_forks ++;
		tell("%ld\tPhilosopher %d \thas taken a fork\n"\
			, philo->philo, philo->id, -1);
	}
	pthread_mutex_lock(&(philo->fork));
	n_forks ++;
	tell("%ld\tPhilosopher %d \thas taken a fork\n"\
		, philo->philo, philo->id, -1);
	return (n_forks);
}

int	lock_b(t_philosopher *philo)
{
	int	n_forks;

	n_forks = 0;
	pthread_mutex_lock(&(philo->fork));
	n_forks++;
	tell("%ld\tPhilosopher %d \thas taken a fork\n"\
		, philo->philo, philo->id, -1);
	if (philo->prev)
	{
		pthread_mutex_lock(&(philo->prev->fork));
		n_forks++;
		tell("%ld\tPhilosopher %d \thas taken a fork\n"\
			, philo->philo, philo->id, -1);
	}
	return (n_forks);
}

int	lock_mutex(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
		return (lock_a(philo));
	return (lock_b(philo));
}

int	join_threads(t_philo *philo, t_philosopher *head)
{
	unsigned int	i;

	i = -1;
	while (++i < philo->n_philo)
	{
		if (pthread_join(head->thread, NULL) != 0)
			return (printf(RED "Error: pthread_join failed!\n" RESET), 0);
		head = head->next;
	}
	if (pthread_join(philo->monitor, NULL) != 0)
		return (printf(RED "Error: monitor's pthread_join failed!\n"\
			RESET), 0);
	return (1);
}
