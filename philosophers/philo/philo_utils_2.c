/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangyeki <sangyeki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:27:33 by sangyeki          #+#    #+#             */
/*   Updated: 2022/07/07 21:46:37 by sangyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_all_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_all_eat);
	philo->all_eat = 1;
	pthread_mutex_unlock(&philo->m_all_eat);
}

void	ft_die(t_philo *philo, t_philos *philos, int i)
{
	pthread_mutex_lock(&philo->m_eat);
	if (ft_get_time() - philos[i].time_eat > philo->time_to_die)
	{
		ft_print_state(philo, i, "died");
		pthread_mutex_lock(&philo->m_die);
		philo->death = 1;
		pthread_mutex_unlock(&philo->m_die);
	}
	pthread_mutex_unlock(&philo->m_eat);
	usleep(1000);
}

void	ft_think_sleep(t_philo *philo, t_philos *philos)
{
	ft_print_state(philo, philos->p_id, "is sleeping");
	ft_sleep(philo->time_to_sleep);
	ft_print_state(philo, philos->p_id, "is thinking");
}

int	ft_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_die);
	if (philo->death)
	{
		pthread_mutex_unlock(&philo->m_die);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->m_die);
		return (0);
	}
}
