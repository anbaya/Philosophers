#include "philosopher.h"

philo	*thread_init(int philo_num, t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(philo) * philo_num);
	pthread_create (data->table.thread, NULL, table_life, data);
	while(philo_num >= i)
	{
		data->philosophers[i].philo_id = i;
		pthread_create(&data->philosophers[i].thread, NULL, philo_life, data);
		i++;
	}
	return(data->philosophers);
}
