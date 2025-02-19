/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:25:35 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/19 13:37:24 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_philo(t_philosopher *philo)
{
	pthread_mutex_destroy(&(philo->fork));
	pthread_mutex_destroy(&(philo->data_m));
	free(philo);
}

void	clear_head(t_philosopher *head)
{
	t_philosopher	*curr;

	curr = head;
	while (head)
	{
		curr = head->next;
		clear_philo(head);
		head = curr;
	}
}
