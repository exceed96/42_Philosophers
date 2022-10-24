/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangyeki <sangyeki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:42:57 by sangyeki          #+#    #+#             */
/*   Updated: 2022/07/07 21:25:54 by sangyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_philo *philo)
{
	int	i;

	i = philo->n_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&philo->forks[i], 0))
			return (ft_error("forks mutex init error()"), 0);
	}
	if (pthread_mutex_init(&philo->m_print, 0))
		return (ft_error("state mutex init error()"), 0);
	if (pthread_mutex_init(&philo->m_eat, 0))
		return (ft_error("m_eat mutex init error()"), 0);
	if (pthread_mutex_init(&philo->m_die, 0))
		return (ft_error("m_die mutex init error()"), 0);
	if (pthread_mutex_init(&philo->m_all_eat, 0))
		return (ft_error("m_all_eat mutex init error()"), 0);
	return (1);
}

void	ft_init_philo(t_philo *philo)
{
	int	i;

	i = philo->n_philo;
	while (--i >= 0)
	{
		philo->philos[i].p_id = i;
		philo->philos[i].eat = 0;
		philo->philos[i].l_fork = i;
		philo->philos[i].r_fork = (i + 1) % philo->n_philo;
		philo->philos[i].time_eat = 0;
		philo->philos[i].philo = philo;
	}
}

void	ft_init_info(t_philo *philo, char **ag)
{
	philo->n_philo = ft_atol(ag[1]);
	philo->time_to_die = ft_atol(ag[2]);
	philo->time_to_eat = ft_atol(ag[3]);
	philo->time_to_sleep = ft_atol(ag[4]);
	philo->death = 0;
	philo->all_eat = 0;
	philo->eat_max = -42;
	if (ag[5])
		philo->eat_max = ft_atol(ag[5]);
}

int	ft_init(t_philo *philo, char **ag)
{
	ft_init_info(philo, ag);
	ft_init_philo(philo);
	if (!ft_init_mutex(philo))
		return (ft_error("init_mutex()"), 0);
	return (1);
}
