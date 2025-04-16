# ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>


# define PHILO_EAT 1
# define PHILO_SLEEP 2
# define PHILO_THINK 3
# define PHILO_DEAD 4
# define PHILO_ALIVE 5
# define FORK_TAKEN 1
# define FORK_FREE 0

typedef struct s_fork
{
	int id;
	int holder;
} t_fork;


typedef struct s_table_data
{
	pthread_t thread;
	int	*Available_Forks;
	t_fork *forks;
} table_data;

typedef struct s_philo_data
{
	pthread_t	thread;
	int	philo_id;
	int	philo_state;
	int auth;
	t_fork	r_fork;
	t_fork	l_fork;
} philo;

typedef struct s_data
{
	int	number_of_philo;
	int	number_of_forks;
	int	sleep_time;
	int	think_time;
	int	eat_time;
	int	die_time;
	table_data table;
	philo	*philosophers;
} t_data;

size_t	ft_atoi(char *str);
int		is_max(char **args);
int		is_int(char **s);
int		checker(char **args);
int parsing(int argc, char **argv);
philo	*thread_init(int philo_num, t_data *data);
int philo_life(t_data *data, philo *philosofer);
int table_life(t_data *data, table_data *table);
int table_manager(t_data *data);
int table_init(table_data *table, t_data *data);
t_fork *forks_init(t_fork *forks, t_data *data);
int is_odd(int number);

# endif
