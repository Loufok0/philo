/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:49:52 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/19 13:24:32 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long int	ft_atolli(const char *str)
{
	int				signe;
	long long int	res;

	if (str == NULL)
		return (-1);
	signe = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		signe *= (44 - *str);
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str) - '0';
		str++;
	}
	return (res * signe);
}

/*(-: 45 and +: 43)
int main()
{
	printf("%d", ft_atoi("123456789"));
}
*/
