/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:06:14 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/12 15:41:31 by malapoug         ###   ########.fr       */
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

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	get_timestamp(t_philo *philo)
{

	return (get_time() - philo->t_start);
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
