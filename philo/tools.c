/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:42:44 by anbaya            #+#    #+#             */
/*   Updated: 2025/06/18 16:42:46 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	timer(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error: gettimeofday\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	splited_usleep(size_t milliseconds, t_philosopher *philo)
{
	size_t	start;

	start = timer();
	while ((timer() - start) < milliseconds && !simulation_stopped(philo))
		usleep(60);
	return (0);
}

int	simulation_stopped(t_philosopher *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	printer(t_philosopher *philo, char *str)
{
	pthread_mutex_lock(philo->print_lock);
	if (!simulation_stopped(philo))
		printf("%ld %d %s\n", timer() - philo->start, philo->id, str);
	pthread_mutex_unlock(philo->print_lock);
}

void	cleaner(char *str, t_simulation *sim, pthread_mutex_t *forks,
		int exit_code)
{
	int	i;

	i = 0;
	if (str)
		printf("%s\n", str);
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->eat_lock);
	pthread_mutex_destroy(&sim->dead_lock);
	while (i < sim->philos[0].philo_count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	if (forks)
		free(forks);
	if (sim->philos)
		free(sim->philos);
	if (sim)
		free(sim);
	exit(exit_code);
}
