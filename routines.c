#include "philosopher.h"

int eat(t_data *data)
{
	printf("Philosopher is eating\n");
	sleep(data->eat_time); // Simulate time taken to eat
	return (0);
}
int slep(t_data *data)
{
	printf("Philosopher is sleeping\n");
	sleep(data->sleep_time); // Simulate time taken to sleep
	return (0);
}
int think(t_data *data)
{
	printf("Philosopher is thinking\n");
	sleep(data->think_time); // Simulate time taken to think
	return (0);
}
int philo_life(t_data *data, philo *philosofer)
{
	while (1)
	{
		if (philosofer->philo_state == PHILO_THINK)
			think(data);
		else if (philosofer->philo_state == PHILO_EAT)
			eat(data);
		else if (philosofer->philo_state == PHILO_SLEEP)
			slep(data);
	}
}
int table_life(t_data *data, table_data *table)
{
	int i;

	table->forks = forks_init(table, data);
	forks_manager(data);
	if (!table->forks)
		return (1);
	table_init(table, data);
	while (1)
	{
		i = -1;
		while (++i <= data->number_of_philo)
		{
			if (is_odd(i) && data->philosophers[i].l_fork.holder == 0 && data->philosophers[i].r_fork.holder == 0)
				data->philosophers[i].auth = 1;
		}
		table_manager(data);
		i = -1;
		while (++i <= data->number_of_philo)
		{
			if (!is_odd(i) && data->philosophers[i].l_fork.holder == 0 && data->philosophers[i].r_fork.holder == 0)
				data->philosophers[i].auth = 1;
		}
	}
	return (0);
}
