/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                      +:+                   */
/*   By: malapoug <malapoug@student.42lausanne         +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/18 15:41:00 by malapoug       #+#    #+#                */
/*   Updated: 2025/02/21 01:37:02 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *philo, t_philosopher *head)
{
	if (pthread_create(&(philo->monitor), NULL, monitor, philo) != 0)
		return (printf(RED "Error: monitor's pthread_create failed!\n"\
			RESET), 0);
	while (head)
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
	if (pthread_join(philo->monitor, NULL) != 0)
		return (printf(RED "Error: monitor's pthread_join failed!\n"\
			RESET), 0);
	while (head)
	{
		if (pthread_join(head->thread, NULL) != 0)
			return (printf(RED "Error: pthread_join failed!\n" RESET), 0);
		head = head->next;
	}
	return (1);
}
