/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <anbaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:41:54 by anbaya            #+#    #+#             */
/*   Updated: 2025/07/05 13:45:42 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	still_alive(t_philosopher *philo, size_t time_to_die)
{
	size_t	last_meal_time;
	int		life;

	pthread_mutex_lock(philo->eat_lock);
	last_meal_time = philo->end;
	if (philo->meals == 0)
		last_meal_time = philo->start;
	if (timer() - last_meal_time > time_to_die && philo->eating == 0)
		life = 0;
	else
		life = 1;
	pthread_mutex_unlock(philo->eat_lock);
	return (life);
}

int	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (-1);
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_checks(char **argv)
{
	int	i;

	i = 1;
	if (ft_atoi(argv[1]) > 200)
	{
		printf("Error: Too many philosophers\n");
		return (1);
	}
	while (argv[i])
	{
		if ((ft_atoi(argv[i]) <= 0) || (ft_isdigit(argv[i])) == 0)
		{
			if (ft_atoi(argv[i]) == -1)
				printf("Error: Integer overflow\n");
			else
				printf("Error: Invalid arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_simulation	*sim;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: num_philosophers time_to_die time_to_eat "
			"time_to_sleep [num_meals](optional)\n");
		return (1);
	}
	if (ft_checks(av))
		return (1);
	sim = malloc(sizeof(t_simulation));
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	philos = malloc(sizeof(t_philosopher) * ft_atoi(av[1]));
	sim_init(sim, philos);
	forks_init(forks, ft_atoi(av[1]));
	init_philosophers(philos, sim, forks, av);
	simulation(sim, forks);
	return (cleaner(NULL, sim, forks, 0));
}
