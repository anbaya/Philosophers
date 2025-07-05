/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <anbaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:23:59 by anbaya            #+#    #+#             */
/*   Updated: 2025/07/05 13:44:44 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	starving(t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].philo_count)
	{
		if (!still_alive(&philos[i], philos[i].time_to_die))
		{
			printer(&philos[i], "died");
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	full(t_philosopher *philos)
{
	int	i;
	int	full_philos;

	i = 0;
	full_philos = 0;
	if (philos[0].meals_goal == -1)
		return (0);
	while (i < philos[0].philo_count)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].meals >= philos[i].meals_goal)
			full_philos++;
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (full_philos == philos[0].philo_count)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

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
	if (philo->id % 2 == 1)
		thinking(philo);
	while (!simulation_stopped(philo))
	{
		if (philo->philo_count == 1)
		{
			pthread_mutex_lock(philo->right_fork);
			printer(philo, "has taken a fork");
			splited_usleep(philo->time_to_die, philo);
			pthread_mutex_unlock(philo->right_fork);
			return (NULL);
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (pointer);
}

int	simulation(t_simulation *sim, pthread_mutex_t *forks)
{
	pthread_t	watcher;
	int			i;

	if (pthread_create(&watcher, NULL, &watcher_routine, sim->philos) != 0)
		return (cleaner("Error: thread join", sim, forks, 1));
	i = 0;
	while (i < sim->philos[0].philo_count)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, &philosopher_routine,
				&sim->philos[i]) != 0)
			return (cleaner("Error: thread join", sim, forks, 1));
		i++;
	}
	i = 0;
	if (pthread_join(watcher, NULL) != 0)
		return (cleaner("Error: thread join", sim, forks, 1));
	while (i < sim->philos[0].philo_count)
	{
		if (pthread_join(sim->philos[i].thread, NULL) != 0)
			return (cleaner("Error: thread join", sim, forks, 1));
		i++;
	}
	return (0);
}
