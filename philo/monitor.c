/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:00:28 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/13 14:32:30 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	loop_check(t_philo *philo, int *eaten)
{
	t_philosopher		*curr;
	long int			current_time;

	curr = (t_philosopher *)(philo->head);
	while (curr)
	{
		current_time = get_timestamp(philo);
		pthread_mutex_lock(&(curr->data_m));
		if (current_time - curr->last_t_eat > philo->t_die)
		{
			pthread_mutex_unlock(&(curr->data_m));
			tell("%ld\tPhilosopher %d \t\033[31mdied\033[0m\n"\
				, philo, curr->id, -1);
			pthread_mutex_lock(&(philo->stop_m));
			philo->stop = 1;
			pthread_mutex_unlock(&(philo->stop_m));
			return (0);
		}
		if (curr->times_eaten < philo->n_eat)
			*(eaten) = 0;
		pthread_mutex_unlock(&(curr->data_m));
		curr = curr->next;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_philo				*philo;
	int					eaten;

	philo = (t_philo *)arg;
	tempo(philo, philo->t_die);
	while (1)
	{
		eaten = 1;
		if (!loop_check(philo, &eaten))
			return (NULL);
		if (eaten == 1)
		{
			tell(GREEN"%ld\tAll Philosophers have eaten at least %lld times \n"\
				RESET, philo, -1, philo->n_eat);
			pthread_mutex_lock(&(philo->stop_m));
			philo->stop = 1;
			pthread_mutex_unlock(&(philo->stop_m));
			return (NULL);
		}
		tempo(philo, 1);
	}
	return (NULL);
}
