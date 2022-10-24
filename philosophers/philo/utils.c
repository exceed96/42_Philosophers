/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangyeki <sangyeki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:36:50 by sangyeki          #+#    #+#             */
/*   Updated: 2022/07/07 21:39:39 by sangyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atol(char *str)
{
	int			i;
	long long	n;

	i = 0;
	n = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10 + str[i++] - '0';
	if (str[i] || n > 2147483648 || n < 0)
		return (-1);
	return (n);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + time.tv_usec / 1000);
}

void	ft_sleep(long long time)
{
	long long	t;

	t = ft_get_time();
	while (1)
	{
		if (ft_get_time() - t >= time)
			break ;
		usleep(300);
	}
}
