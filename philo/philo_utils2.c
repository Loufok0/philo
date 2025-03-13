/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 01:37:06 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/13 15:40:36 by malapoug         ###   ########.fr       */
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

void	find_and_lock(t_philo philo, int id, int mode)
{
	t_philosopher	*p;

	p = philo.head;
	while (p->id != id)
		p = p->next;
	if (mode == 'l')
		pthread_mutex_lock(&(p->data_m));
	else
		pthread_mutex_unlock(&(p->data_m));
}

void	tell(char *str, t_philo *philo, int id, long long int n_eat)
{
	long int	time;

	time = get_timestamp(philo);
	if (id != -1)
		find_and_lock(*philo, id, 'l');
	pthread_mutex_lock(&(philo->printf));
	if (check_stop(philo))
	{
		if (id != -1)
			find_and_lock(*philo, id, 'u');
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
	if (id != -1)
		find_and_lock(*philo, id, 'u');
}
