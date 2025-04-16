#include "philosopher.h"

int main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (parsing(argc, argv) == 1)
		return (1);
	data->philosophers = thread_init(ft_atoi(argv[1]), data);
	return (0);
}
