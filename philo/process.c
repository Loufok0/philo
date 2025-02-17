/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                           :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:12:41 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/17 19:13:35 by malapoug       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo			*philo;
	t_philosopher		*curr;
	long int		current_time;
	int			eaten;

	philo = (t_philo *)arg;
	while (1)
	{
		eaten = 1;
		curr = (t_philosopher *)(philo->head);
		while (curr)
		{
			current_time = get_timestamp(philo);
			pthread_mutex_lock(&(curr->data_m));
			if (current_time - curr->last_t_eat > philo->t_die)
			{
				pthread_mutex_lock(&(philo->printf));
				printf("%ld\tPhilosopher %d \t\033[31mdied\033[0m\n", current_time, curr->id);
				pthread_mutex_unlock(&(philo->printf));
				pthread_mutex_lock(&(philo->stop_m));
				philo->stop = 1;
				pthread_mutex_unlock(&(philo->stop_m));
				pthread_mutex_unlock(&(curr->data_m));
				return (NULL);
			}
			if (curr->times_eaten < philo->n_eat)
				eaten = 0;
			pthread_mutex_unlock(&(curr->data_m));
			curr = curr->next;
		}
		if (eaten == 1)
		{
			pthread_mutex_lock(&(philo->printf));
			printf(GREEN"%ld\tAll Philosophers have eaten %lld times \n"RESET, current_time, philo->n_eat);
			pthread_mutex_unlock(&(philo->printf));
			pthread_mutex_lock(&(philo->stop_m));
			philo->stop = 1;
			pthread_mutex_unlock(&(philo->stop_m));
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	tempo(t_philo *philo, long int t)
{
	long int	curr_t;

	curr_t = get_timestamp(philo);
	while (get_timestamp(philo) - curr_t < t)
		;
}

int	create_threads(t_philo *philo, t_philosopher *head)
{
	if (pthread_create(&(philo->monitor), NULL, monitor, philo) != 0)
			return (printf(RED "Error: monitor's pthread_create failed!\n" RESET), 0);
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
	if (philo->prev)
	{
		pthread_mutex_lock(&(philo->prev->fork));
		n_forks ++;
		pthread_mutex_lock(&(philo->philo->printf));
		printf("%ld\tPhilosopher %d \thas taken a fork\n", get_timestamp(philo->philo), philo->id);
		pthread_mutex_unlock(&(philo->philo->printf));
	}
	pthread_mutex_lock(&(philo->fork));
	n_forks ++;
	pthread_mutex_lock(&(philo->philo->printf));
	printf("%ld\tPhilosopher %d \thas taken a fork\n", get_timestamp(philo->philo), philo->id);
	pthread_mutex_unlock(&(philo->philo->printf));
	return (n_forks);
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

int	check_stop(t_philo *philo)
{
	if (philo->stop != 1)
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		tempo(philo->philo, 1);
	while (philo->philo->stop != 1)
	{
		if (lock_mutex(philo) != 2)
			break ;
		pthread_mutex_lock(&(philo->philo->printf));
		printf("%ld\tPhilosopher %d \tis \033[32meating\033[0m his meal n°%lld\n", get_timestamp(philo->philo), philo->id, philo->times_eaten + 1);
		pthread_mutex_unlock(&(philo->philo->printf));
//		if (check_stop(philo->philo))
//			break;
		pthread_mutex_lock(&(philo->data_m));
		philo->last_t_eat = get_timestamp(philo->philo);
		philo->times_eaten++;
		pthread_mutex_unlock(&(philo->data_m));
//		if (check_stop(philo->philo))
//			break;
		tempo(philo->philo, philo->philo->t_eat);
		if (philo->prev)
			pthread_mutex_unlock(&(philo->prev->fork));
		pthread_mutex_unlock(&(philo->fork));
//		if (!check_stop(philo->philo))
//			break;
		pthread_mutex_lock(&(philo->philo->printf));
		printf("%ld\tPhilosopher %d \tis \033[35msleeping\033[0m\n", get_timestamp(philo->philo), philo->id);
		pthread_mutex_unlock(&(philo->philo->printf));
//		if (check_stop(philo->philo))
//			break;
		tempo(philo->philo, philo->philo->t_sleep);
//		if (check_stop(philo->philo))
//			break;
		pthread_mutex_lock(&(philo->philo->printf));
		printf("%ld\tPhilosopher %d \tis \033[33mthinking\033[0m\n", get_timestamp(philo->philo), philo->id);
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
