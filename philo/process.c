/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:12:41 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/12 15:52:28 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo			*philo;
	t_philosopher	*curr;
	long			current_time;

	philo = (t_philo *)arg;
	while (1)
	{
		curr = philo->head;
		while (curr)
		{
			current_time = get_timestamp(philo);
			if (!curr)
				break;
			pthread_mutex_lock(&(curr->data_m));
			if (current_time - curr->last_t_eat > philo->t_die)
			{
				pthread_mutex_lock(&(philo->printf));
				printf("%ld %d died\n", current_time, curr->id);
				pthread_mutex_unlock(&(philo->printf));
				pthread_mutex_lock(&(philo->stop_m));
				philo->stop = 1;
				pthread_mutex_unlock(&(philo->stop_m));
				pthread_mutex_unlock(&(curr->data_m));
				return (NULL);
			}
			pthread_mutex_unlock(&(curr->data_m));
			curr = curr->next;
		}
		usleep(1000);
	}
	return (NULL);
}


int	create_threads(t_philo *philo, t_philosopher *head)
{
	if (pthread_create(&(philo->monitor), NULL, monitor, head) != 0)
			return (printf(RED "Error: monitor's pthread_create failed!\n" RESET), 0);

	while (head)
	{
		if (pthread_create(&(head->thread), NULL, routine, head) != 0)
			return (printf(RED "Error: pthread_create failed!\n" RESET), 0);
		head = head->next;
	}
	return (1);
}

void	lock_mutex(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->prev->fork));
		pthread_mutex_lock(&(philo->philo->printf));
		printf("%ld %d has taken a fork\n", get_timestamp(philo->philo), philo->id);
		pthread_mutex_unlock(&(philo->philo->printf));
		pthread_mutex_lock(&(philo->fork));
		pthread_mutex_lock(&(philo->philo->printf));
		printf("%ld %d has taken a fork\n", get_timestamp(philo->philo), philo->id);
		pthread_mutex_unlock(&(philo->philo->printf));
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(&(philo->fork));
		pthread_mutex_lock(&(philo->prev->fork));
	}
}

int	join_threads(t_philo *philo, t_philosopher *head)
{
	if (pthread_join(philo->monitor, NULL) != 0)
			return (printf(RED "Error: monitor's pthread_join failed!\n" RESET), 0);

	while (head)
	{
		if (pthread_join(head->thread, NULL) != 0)
			return (printf(RED "Error: pthread_join failed!\n" RESET), 0);
		head = head->next;
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo->philo->stop != 1)
	{
		lock_mutex(philo);
		pthread_mutex_lock(&(philo->philo->printf));
		printf("%ld %d is\033[32m eating\033[0m\n", get_timestamp(philo->philo), philo->id);
		pthread_mutex_unlock(&(philo->philo->printf));
		pthread_mutex_lock(&(philo->data_m));
		philo->last_t_eat = get_timestamp(philo->philo);
		pthread_mutex_unlock(&(philo->data_m));
		usleep(philo->philo->t_sleep);
		pthread_mutex_unlock(&(philo->prev->fork));
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_lock(&(philo->philo->printf));
		printf("%ld %d is\033[35m sleeping\033[0m\n", get_timestamp(philo->philo), philo->id);
		pthread_mutex_unlock(&(philo->philo->printf));
		usleep(philo->philo->t_sleep);
		pthread_mutex_lock(&(philo->philo->printf));
		printf("%ld %d is\033[33m thinking\033[0m\n", get_timestamp(philo->philo), philo->id);
		pthread_mutex_unlock(&(philo->philo->printf));
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
	while (curr)
	{
		pthread_mutex_destroy(&(curr->fork));
		curr = curr->next;
	}
	return (1);
}






//gerer pour 1 philo !
//gerer le nombre de repas avant l'arret de la simu!
