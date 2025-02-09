/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:06:14 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/09 18:06:23 by malapoug         ###   ########.fr       */
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
		if (count_occ(av[i], '-') != 0 || !is_number(av[i]))
			return (0);
		i++;
	}
	return (1);
}

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
			current_time = get_timestamp();
			if (!curr)
				break;
			pthread_mutex_lock(&(curr->data_m));
			if (current_time - curr->last_t_eat > philo->t_die)
			{
				printf("%ld %d died\n", current_time, curr->id);
				philo->stop = 1;
				//pthread_mutex_unlock(&(curr->data_m));
				return (NULL);
			}
			pthread_mutex_unlock(&(curr->data_m));
			curr = curr->next;
		}
		usleep(1000);
	}
	return (NULL);
}

void	lock_mutex(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->prev->fork));
		printf("%ld %d has taken a fork\n", get_timestamp(), philo->id);
		pthread_mutex_lock(&(philo->fork));
		printf("%ld %d has taken a fork\n", get_timestamp(), philo->id);
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(&(philo->fork));
		pthread_mutex_lock(&(philo->prev->fork));
	}
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo->philo->stop != 1)
	{
		lock_mutex(philo);
		printf("%ld %d is eating\n", get_timestamp(), philo->id);
		pthread_mutex_lock(&(philo->data_m));
		philo->last_t_eat = get_timestamp();
		pthread_mutex_unlock(&(philo->data_m));
		usleep(philo->philo->t_sleep + 1000000000);
		pthread_mutex_unlock(&(philo->prev->fork));
		pthread_mutex_unlock(&(philo->fork));
		printf("%ld %d is sleeping\n", get_timestamp(), philo->id);
		usleep(philo->philo->t_sleep);
		printf("%ld %d is thinking\n", get_timestamp(), philo->id);
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

int	main(int ac, char **av)
{
	t_philo	philo;
	if (!(ac >= 5 && ac <= 6))
		return (usage(), 1);
	else if (!check(av))
		return (printf(RED "Error in args\n" RED), 1);
	else if (!init_philo(&philo, av))
		return (printf(RED "Error in init of principal struct\n" RED), 1);
	else if (!init_philosophers(&philo))
		return (printf(RED "Error in init of philosophers\n" RED), 1);
	else
	{
	print_philosophers(philo.head);
		show_philo(philo);
		if (!process(&philo))
			return (printf(RED "ERROR\n" RED), 1);
	}
	return (0);
}
