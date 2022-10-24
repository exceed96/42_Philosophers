/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangyeki <sangyeki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:41:57 by sangyeki          #+#    #+#             */
/*   Updated: 2022/07/08 12:06:16 by sangyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_philos *philos)
{
	t_philo	*philo;

	philo = philos->philo;
	if (philo->n_philo == 1)
		ft_one_philo(philos);
	else
	{
		pthread_mutex_lock(&philo->forks[philos->l_fork]);
		ft_print_state(philo, philos->p_id, "has taken a fork");
		pthread_mutex_lock(&philo->forks[philos->r_fork]);
		ft_print_state(philo, philos->p_id, "has taken a fork");
		pthread_mutex_lock(&philo->m_eat);
		ft_print_state(philo, philos->p_id, "is eating");
		philos->time_eat = ft_get_time();
		pthread_mutex_unlock(&philo->m_eat);
		ft_sleep(philo->time_to_eat);
		pthread_mutex_lock(&philo->m_eat);
		(philos->eat)++;
		pthread_mutex_unlock(&philo->m_eat);
		pthread_mutex_unlock(&philo->forks[philos->l_fork]);
		pthread_mutex_unlock(&philo->forks[philos->r_fork]);
	}
}

static void	*ft_create(void *void_philos)
{
	t_philo		*philo;
	t_philos	*philos;

	philos = (t_philos *)void_philos;
	philo = philos->philo;
	if (philos->p_id % 2)
		usleep(20000);
	pthread_mutex_lock(&philo->m_die);
	while (!(philo->death))
	{
		pthread_mutex_unlock(&philo->m_die);
		ft_eat(philos);
		pthread_mutex_lock(&philo->m_all_eat);
		if (philo->all_eat)
		{
			pthread_mutex_unlock(&philo->m_all_eat);
			break ;
		}
		pthread_mutex_unlock(&philo->m_die);
		pthread_mutex_unlock(&philo->m_all_eat);
		ft_think_sleep(philo, philos);
	}
	pthread_mutex_unlock(&philo->m_die);
	return (0);
}

static void	ft_join_destroy(t_philo *philo, t_philos *philos)
{
	int	i;

	i = -1;
	while (++i < philo->n_philo)
		pthread_join(philos[i].thread, 0);
	i = -1;
	while (++i < philo->n_philo)
		pthread_mutex_destroy(&philo->forks[i]);
	pthread_mutex_destroy(&philo->m_print);
}

void	ft_dead_check(t_philo *philo, t_philos *philos)
{
	int	i;

	while (!(philo->all_eat))
	{
		i = -1;
		while (++i < philo->n_philo && !(philo->death))
			ft_die(philo, philos, i);
		if (ft_dead_flag(philo))
			break ;
		i = 0;
		pthread_mutex_lock(&philo->m_eat);
		while ((philo->eat_max != -42) && (i < philo->n_philo)
			&& (philos[i].eat >= philo->eat_max))
		{
			pthread_mutex_unlock(&philo->m_eat);
			i++;
			pthread_mutex_lock(&philo->m_eat);
		}
		pthread_mutex_unlock(&philo->m_eat);
		if (i == philo->n_philo)
			ft_all_eat(philo);
	}
}

int	ft_init_state(t_philo *philo)
{
	int			i;
	t_philos	*philos;

	i = 0;
	philos = philo->philos;
	philo->start = ft_get_time();
	while (i < philo->n_philo)
	{
		if (pthread_create(&philos[i].thread, 0, &ft_create, &philos[i]))
			return (ft_error("thread create error()"), 0);
		pthread_mutex_lock(&philo->m_eat);
		philos[i].time_eat = ft_get_time();
		pthread_mutex_unlock(&philo->m_eat);
		i++;
	}
	ft_dead_check(philo, philo->philos);
	ft_join_destroy(philo, philos);
	return (1);
}
