/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                        :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:01:19 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/18 15:58:29 by malapoug       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philo, char **av)
{
	philo->head = NULL;
	philo->n_philo = ft_atolli(av[1]);
	philo->t_die = ft_atolli(av[2]);
	philo->t_eat = ft_atolli(av[3]);
	philo->t_sleep = ft_atolli(av[4]);
	philo->t_start = get_time();
	if (av[5])
		philo->n_eat = ft_atolli(av[5]);
	else
		philo->n_eat = LLONG_MAX;
	if (pthread_mutex_init(&(philo->stop_m), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(philo->printf), NULL) != 0)
		return (0);
	philo->stop = 0;
	return (1);
}

t_philosopher	*create_philosopher(t_philo *philo, int id)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->philo = philo;
	philosopher->id = id;
	if (pthread_mutex_init(&(philosopher->fork), NULL) != 0)//free
		return (NULL);
	if (pthread_mutex_init(&(philosopher->data_m), NULL) != 0)//free
		return (NULL);
	philosopher->next = NULL;
	philosopher->prev = NULL;
	philosopher->times_eaten = 0;
	philosopher->last_t_eat = get_timestamp(philo);
	return (philosopher);
}

int	init_philosophers(t_philo *philo)
{
	unsigned int	i;
	t_philosopher	*curr;
	t_philosopher	*prev;

	prev = NULL;
	philo->head = create_philosopher(philo, 1);
	if (!philo->head)
		return (0);
	curr = philo->head;
	i = 2;
	while (i <= philo->n_philo)
	{
		if (prev)
			prev->next = curr;
		curr->prev = prev;
		prev = curr;
		curr->next = create_philosopher(philo, i);
		if (!curr->next)
			return (0);//free philo
		curr = curr->next;
		i++;
	}
	curr->prev = prev;
	if (philo->n_philo > 1)
		philo->head->prev = curr;
	return (1);
}
