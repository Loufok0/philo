/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:01:19 by malapoug          #+#    #+#             */
/*   Updated: 2025/01/29 12:54:15 by malapoug         ###   ########.fr       */
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
	philo->n_eat = ft_atolli(av[5]);
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
	if (pthread_mutex_init(&(philosopher->fork), NULL) != 0)
		return (0);
	philosopher->next = NULL;
	philosopher->prev = NULL;
	philosopher->times_eaten = 0;
	philosopher->last_t_eat = get_timestamp();
	return (philosopher);
}

int	init_philosophers(t_philo *philo)
{
	unsigned int	i;
	t_philosopher	*head;
	t_philosopher	*curr;
	t_philosopher	*prev;

	prev = NULL;
	curr = create_philosopher(philo, 1);
	if (!curr)
		return (0);
	head = curr;
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
	head->prev = curr;
	philo->head = head;
	return (1);
}
