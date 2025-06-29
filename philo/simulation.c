/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:42:36 by anbaya            #+#    #+#             */
/*   Updated: 2025/06/18 16:42:38 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*watcher_routine(void *pointer)
{
	t_philosopher	*philos;

	philos = (t_philosopher *)pointer;
	while (1)
	{
		if (starving(philos) || full(philos))
			return (pointer);
	}
	return (pointer);
}

void	*philosopher_routine(void *pointer)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)pointer;
	if (philo->id % 2 == 0)
		usleep(500);
	while (!simulation_stopped(philo))
	{
		if (philo->philo_count == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			printer(philo, "has taken a fork");
			splited_usleep(philo->time_to_die, philo);
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		eating(philo);
		sleeping(philo);
	}
	return (pointer);
}

int	simulation(t_simulation *sim, pthread_mutex_t *forks)
{
	pthread_t	watcher;
	int			i;

	if (pthread_create(&watcher, NULL, &watcher_routine, sim->philos) != 0)
		cleaner("Error: thread creation", sim, forks, 1);
	i = 0;
	while (i < sim->philos[0].philo_count)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, &philosopher_routine,
				&sim->philos[i]) != 0)
			cleaner("Error: thread creation", sim, forks, 1);
		i++;
	}
	i = 0;
	if (pthread_join(watcher, NULL) != 0)
		cleaner("Error: thread join", sim, forks, 1);
	while (i < sim->philos[0].philo_count)
	{
		if (pthread_join(sim->philos[i].thread, NULL) != 0)
			cleaner("Error: thread join", sim, forks, 1);
		i++;
	}
	return (0);
}
