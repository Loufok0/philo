/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_occ.c                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:45:08 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/18 15:53:59 by malapoug       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	count_occ(char *str, int c)
{
	int		i;
	int		count;

	if (str == NULL)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	total_occ(char **split, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (split[i])
	{
		count += count_occ(split[i], c);
		i++;
	}
	return (count);
}
