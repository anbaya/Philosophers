/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:42:25 by anbaya            #+#    #+#             */
/*   Updated: 2025/06/18 16:42:27 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philosopher *philos)
{
	printer(philos, "is sleeping");
	splited_usleep(philos->time_to_sleep, philos);
	printer(philos, "is thinking");
}

void	fork_taking(t_philosopher *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->left_fork);
		printer(philos, "has taken a fork");
		if (simulation_stopped(philos))
		{
			pthread_mutex_unlock(philos->left_fork);
			return ;
		}
		pthread_mutex_lock(philos->right_fork);
		printer(philos, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philos->right_fork);
		printer(philos, "has taken a fork");
		if (simulation_stopped(philos))
		{
			pthread_mutex_unlock(philos->right_fork);
			return ;
		}
		pthread_mutex_lock(philos->left_fork);
		printer(philos, "has taken a fork");
	}
}

void	eating(t_philosopher *philos)
{
	fork_taking(philos);
	pthread_mutex_lock(philos->eat_lock);
	philos->eating = 1;
	printer(philos, "is eating");
	philos->end = timer();
	pthread_mutex_unlock(philos->eat_lock);
	splited_usleep(philos->time_to_eat, philos);
	pthread_mutex_lock(philos->eat_lock);
	philos->eating = 0;
	philos->meals++;
	pthread_mutex_unlock(philos->eat_lock);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
}

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
	int	eaten;

	i = 0;
	eaten = 0;
	if (philos[0].meals_goal == -1)
		return (0);
	while (i < philos[0].philo_count)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].meals >= philos[i].meals_goal)
			eaten++;
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (eaten == philos[0].philo_count)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}
