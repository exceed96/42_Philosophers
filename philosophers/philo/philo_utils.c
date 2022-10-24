/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangyeki <sangyeki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:01:05 by sangyeki          #+#    #+#             */
/*   Updated: 2022/07/07 21:38:12 by sangyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_state(t_philo *philo, int id, char *str)
{
	pthread_mutex_lock(&philo->m_print);
	pthread_mutex_lock(&philo->m_die);
	if (!(philo->death))
	{
		printf("%lld", ft_get_time() - philo->start);
		printf(" philo %d ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&philo->m_die);
	pthread_mutex_unlock(&philo->m_print);
	return ;
}

void	ft_one_philo(t_philos *philos)
{
	t_philo	*philo;

	philo = philos->philo;
	ft_print_state(philo, philos->p_id, "has taken a fork");
	ft_sleep(philo->time_to_die);
	ft_dead_check(philo, philo->philos);
}
