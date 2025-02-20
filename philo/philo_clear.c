/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:25:35 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/20 01:10:25 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_head(t_philosopher *head)
{
	t_philosopher	*curr;

	curr = head;
	while (head)
	{
		curr = head->next;
		free(head);
		head = curr;
	}
}
