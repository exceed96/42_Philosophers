/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangyeki <sangyeki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:12:38 by sangyeki          #+#    #+#             */
/*   Updated: 2022/07/06 14:02:26 by sangyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *str)
{
	printf("Error -> %s\n", str);
}

int	ft_arg_check(int ac, char **ag)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (ft_error("Invalid number of arguments"), 0);
	while (ag[i])
	{
		if (ft_atol(ag[i]) < 1 || ft_strlen(ag[i]) > 10)
			return (ft_error("Invalid format of arguments"), 0);
		i++;
	}
	return (1);
}

int	main(int ac, char **ag)
{
	t_philo	philo;

	if (!(ft_arg_check(ac, ag)))
		return (ft_error("check_ag()"), ft_error("main()"), 0);
	if (!(ft_init(&philo, ag)))
		return (ft_error("main()"), 0);
	if (!(ft_init_state(&philo)))
		return (ft_error("main()"), 0);
	return (0);
}
