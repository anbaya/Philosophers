/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:42:12 by anbaya            #+#    #+#             */
/*   Updated: 2025/06/18 16:42:15 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define NUM 255

typedef struct s_philosopher
{
	int				id;
	int				eating;
	int				meals;
	int				philo_count;
	int				meals_goal;
	int				*dead;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*eat_lock;
	size_t			end;
	size_t			start;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
}					t_philosopher;

typedef struct s_simulation
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	print_lock;
	t_philosopher	*philos;
}					t_simulation;

void				forks_init(pthread_mutex_t *forks, int philo_num);
void				init_input(t_philosopher *philo, char **args);
void				init_philosophers(t_philosopher *philos, t_simulation *sim,
						pthread_mutex_t *forks, char **args);
void				sim_init(t_simulation *sim, t_philosopher *philos);
int					ft_atoi(char *str);
int					simulation_stopped(t_philosopher *philo);
int					simulation(t_simulation *sim, pthread_mutex_t *forks);
void				*philosopher_routine(void *pointer);
size_t				timer(void);
int					still_alive(t_philosopher *philo, size_t time_to_die);
void				cleaner(char *str, t_simulation *sim,
						pthread_mutex_t *forks, int exit_code);
int					splited_usleep(size_t milliseconds, t_philosopher *philo);
void				printer(t_philosopher *philo, char *str);
void				eating(t_philosopher *philos);
void				sleeping(t_philosopher *philos);
int					starving(t_philosopher *philos);
int					full(t_philosopher *philos);

#endif /* PHILOSOPHERS_H */
