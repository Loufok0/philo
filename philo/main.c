/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:06:14 by malapoug          #+#    #+#             */
/*   Updated: 2025/01/28 16:21:30 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage(void)
{
	printf(BOLD BLUE "Usage: ./philo    number_of_philosophers    \
	time_to_die time_to_eat    time_to_sleep    \
	[number_of_times_each_philosopher_must_eat] \n\n" RESET);
}

int	check(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (count_occ(av[i], '-') != 0)
			return (0);
		i++;
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo->stop != 1)
	{
		pthread_mutex_lock(&(philo->prev->fork));
		pthread_mutex_lock(&(philo->fork));
		printf("timestamp_in_ms %d has taken a fork", philo->id);
		printf("timestamp_in_ms %d is eating", philo->id);
		usleep(philo->t_eat);
		pthread_mutex_unlock(&(philo->prev->fork));
		pthread_mutex_unlock(&(philo->fork));
		printf("timestamp_in_ms %d is sleeping", philo->id);
		usleep(philo->t_sleep);
		printf("timestamp_in_ms %d is thinking", philo->id);
	}
	return (NULL);
}

int	process(t_philo *philo)
{
	t_philosopher	*curr;

	curr = philo->philosophers;
	while (curr)
	{
		pthread_create(&(curr->thread), NULL, routine, curr);
		curr = curr->next;
	}
	curr = philo->philosophers;
	while (curr)
	{
		pthread_join(curr->thread, NULL);
		curr = curr->next;
	}
	while (curr)
	{
		pthread_mutex_destroy(&(curr->fork));
		curr = curr->next;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	philo;
	if (!(ac >= 5 && ac <= 6))
		return (usage(), 1);
	else if (!check(av))
		return (printf(RED "Error in args" RED), 1);
	else if (!init_philo(&philo, av))
		return (printf(RED "Error in init of principal struct" RED), 1);
	else if (!init_philosophers(&philo))
		return (printf(RED "Error in init of philosophers" RED), 1);
	else
	{
		show_philo(philo);
		if (!process(&philo))
			return (printf(RED "ERROR" RED), 1);
	}
}
