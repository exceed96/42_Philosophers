/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangyeki <sangyeki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:12:50 by sangyeki          #+#    #+#             */
/*   Updated: 2022/07/07 21:48:34 by sangyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_PHILO 401

typedef struct s_philos
{
	pthread_t		thread;
	int				p_id;
	int				eat;
	int				l_fork;
	int				r_fork;
	long long		time_eat;
	struct s_philo	*philo;
}	t_philos;

typedef struct s_philo
{
	pthread_mutex_t	forks[MAX_PHILO];
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_die;
	pthread_mutex_t	m_all_eat;
	t_philos		philos[MAX_PHILO];
	int				n_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				death;
	int				all_eat;
	int				eat_max;
	long long		start;
}	t_philo;

void		ft_error(char *str);
long long	ft_atol(char *str);
int			ft_strlen(char *str);

int			ft_init(t_philo *philo, char **ag);

int			ft_init_state(t_philo *philo);
void		ft_dead_check(t_philo *philo, t_philos *philos);

long long	ft_get_time(void);
void		ft_sleep(long long time);
void		ft_print_state(t_philo *philo, int id, char *str);
void		ft_one_philo(t_philos *philos);

void		ft_die(t_philo *philo, t_philos *philos, int i);
void		ft_think_sleep(t_philo *philo, t_philos *philos);
void		ft_all_eat(t_philo *philo);
int			ft_dead_flag(t_philo *philo);
#endif
