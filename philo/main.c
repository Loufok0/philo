/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:06:14 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/11 11:27:28 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	usage(void)
{
	printf(BOLD BLUE "Usage: ./philo    number_of_philosophers (0 - 200)    \
	time_to_die time_to_eat    time_to_sleep    \
	[number_of_times_each_philosopher_must_eat] \n\n" RESET);
	return (1);
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
	else if (ft_atolli(av[1]) == 0)
		return (printf(YELLOW "No one is here... 👀\n" RESET), usage());
	else if (ft_atolli(av[1]) > 200 || ft_atolli(av[1]) == -1)
		return (printf(YELLOW \
			"Too much people in there... 👀\n" RESET), usage());
	else if (!check(av))
		return (printf(RED "Error in args\n" RESET), 1);
	else if (!init_philo(&philo, av))
		return (printf(RED "Error in init of principal struct\n" RESET), 1);
	else if (!init_philosophers(&philo))
		return (printf(RED "Error in init of philosophers\n" RESET), 1);
	else
	{
		if (!process(&philo))
			return (printf(RED "ERROR\n" RESET), 1);
	}
	return (0);
}
