#include "philosopher.h"

t_fork *forks_init(t_fork *forks, t_data *data)
{
	int	i;

	i = 0;
	forks = malloc(sizeof(t_fork) *( data->number_of_forks + 1));
	if (!forks)
		return (NULL);
	while (i < data->number_of_forks)
	{
		forks[i].id = i;
		forks[i].holder = 0;
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philosophers[i].l_fork = forks[i];
		data->philosophers[i].r_fork = forks[(i + 1) % data->number_of_forks];
		i++;
	}
	return (forks);
}
int table_init(table_data *table, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		data->philosophers->auth = 0; // Setting to 0 to indicate uninitialized or unauthorized philosopher.
		i++;
	}
	table->Available_Forks = malloc(sizeof(int) * data->number_of_forks);
	if (!table->Available_Forks)
		return (1);
	while (i < data->number_of_forks)
	{
		data->philosophers[i].l_fork.holder = data->philosophers->philo_id; // Setting to 0 to indicate unused fork.
		data->philosophers[i].r_fork.holder = data->philosophers->philo_id;
		i++;
	}
	return (0);
}
int table_manager(t_data *data)
{
	int	i;

	i = 0;
	if ()
	return (0);
}
