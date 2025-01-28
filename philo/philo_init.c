/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:01:19 by malapoug          #+#    #+#             */
/*   Updated: 2025/01/28 16:12:38 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philos, char **av)
{
	philos->n_philo = ft_atolli(av[1]);
	philos->t_die = ft_atolli(av[2]);
	philos->t_eat = ft_atolli(av[3]);
	philos->t_sleep = ft_atolli(av[4]);
	philos->n_eat = ft_atolli(av[5]);
	return (1);
}

t_philosopher	*create_philosopher(int id)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->id = id;
	pthread_mutex_init(&(philosopher->fork), NULL);
	philosopher->next = NULL;
	philosopher->prev = NULL;
	philosopher->times_eaten = 0;
	philosopher->last_t_eat = 0;
	return (philosopher);
}

int	init_philosophers(t_philo *philo)
{
	unsigned int	i;
	t_philosopher	*curr;
	t_philosopher	*prev;

	prev = NULL;
	philo->philosophers = create_philosopher(1);
	if (!philo->philosophers)
		return (0);
	i = 2;
	curr = philo->philosophers;
	while (i < philo->n_philo)
	{
		curr->next = create_philosopher(i);
		if (!curr->next)
			return (0);//free philo
		if (prev)
			prev->next = curr;
		curr->prev = prev;
		i++;
	}
	if (philo->n_philo != 1)
		philo->philosophers->prev = curr;
	return (1);
}
