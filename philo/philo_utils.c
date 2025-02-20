/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                      +:+                   */
/*   By: malapoug <malapoug@student.42lausanne         +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/18 15:41:00 by malapoug       #+#    #+#                */
/*   Updated: 2025/02/20 01:09:14 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tempo(t_philo *philo, long int t)
{
	long int	curr_t;

	curr_t = get_timestamp(philo);
	while (get_timestamp(philo) - curr_t < t)
		;
}

void	tell(char *str, t_philo *philo, int id, long long int n_eat)
{
	long int	time;

	time = get_timestamp(philo);
	pthread_mutex_lock(&(philo->printf));
	if (check_stop(philo))
	{
		pthread_mutex_unlock(&(philo->printf));
		return ;
	}
	if (n_eat == -1)
		printf(str, time, id);
	else if (id == -1)
		printf(str, time, n_eat);
	else
		printf(str, time, id, n_eat);
	pthread_mutex_unlock(&(philo->printf));
}

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

int	lock_mutex(t_philosopher *philo)
{
	int	n_forks;

	n_forks = 0;
	if (philo->id % 2 == 0)
	{
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
	}
	else
	{
		pthread_mutex_lock(&(philo->fork));
		n_forks ++;
		tell("%ld\tPhilosopher %d \thas taken a fork\n"\
			, philo->philo, philo->id, -1);
		if (philo->prev)
		{
			pthread_mutex_lock(&(philo->prev->fork));
			n_forks ++;
			tell("%ld\tPhilosopher %d \thas taken a fork\n"\
				, philo->philo, philo->id, -1);
		}
	}
	return (n_forks);
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
