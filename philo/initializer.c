/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <anbaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:41:27 by anbaya            #+#    #+#             */
/*   Updated: 2025/07/01 17:11:44 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	add_timers(t_philosopher *philosopher, char **args)
{
	philosopher->time_to_die = ft_atoi(args[2]);
	philosopher->time_to_eat = ft_atoi(args[3]);
	philosopher->time_to_sleep = ft_atoi(args[4]);
	philosopher->philo_count = ft_atoi(args[1]);
}

void	init_philosophers(t_philosopher *philosophers, t_simulation *sim,
		pthread_mutex_t *forks, char **av)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		philosophers[i].id = i + 1;
		philosophers[i].eating = 0;
		philosophers[i].meals = 0;
		add_timers(&philosophers[i], av);
		philosophers[i].dead = &sim->dead_flag;
		philosophers[i].print_lock = &sim->print_lock;
		philosophers[i].dead_lock = &sim->dead_lock;
		philosophers[i].eat_lock = &sim->eat_lock;
		if (av[5])
			philosophers[i].meals_goal = ft_atoi(av[5]);
		else
			philosophers[i].meals_goal = -1;
		philosophers[i].start = timer();
		philosophers[i].end = timer();
		philosophers[i].right_fork = &forks[i];
		if (i == 0)
			philosophers[i].left_fork = &forks[philosophers[i].philo_count - 1];
		else
			philosophers[i].left_fork = &forks[i - 1];
	}
}

void	sim_init(t_simulation *sim, t_philosopher *philosophers)
{
	sim->dead_flag = 0;
	sim->philos = philosophers;
	pthread_mutex_init(&sim->print_lock, NULL);
	pthread_mutex_init(&sim->dead_lock, NULL);
	pthread_mutex_init(&sim->eat_lock, NULL);
}

void	forks_init(pthread_mutex_t *forks, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
