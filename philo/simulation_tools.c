/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <anbaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:42:25 by anbaya            #+#    #+#             */
/*   Updated: 2025/07/04 11:16:26 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philosopher *philo)
{
	printer(philo, "is thinking");
	splited_usleep(1, philo);
}

void	sleeping(t_philosopher *philos)
{
	printer(philos, "is sleeping");
	splited_usleep(philos->time_to_sleep, philos);
}

int	fork_taking(t_philosopher *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->left_fork);
		printer(philos, "has taken a fork");
		pthread_mutex_lock(philos->right_fork);
		printer(philos, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock((philos)->right_fork);
		printer(philos, "has taken a fork");
		pthread_mutex_lock(philos->left_fork);
		printer(philos, "has taken a fork");
	}
	return (1);
}

int	fork_unlocking(t_philosopher *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
	}
	return (1);
}

void	eating(t_philosopher *philos)
{
	if (!fork_taking(philos))
		return ;
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
	fork_unlocking(philos);
}
