#include "philosopher.h"

int	is_max(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_atoi(args[i]) > 2147483647 || ft_atoi(args[i]) < -2147483648)
			return (1);
		i++;
	}
	return (0);
}

int	is_int(char **s)
{
	int	i;
	int	j;

	if (!s || !s[0])
		return (0);
	i = 0;
	while (s[i])
	{
		j = 0;
		if (s[i][j] == '-' || s[i][j] == '+')
			j++;
		if (s[i][j] == '\0')
			return (0);
		while (s[i][j])
		{
			if (!(s[i][j] >= '0' && s[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int checker(char **args)
{
	if (!args || !args[0])
		return (0);
	if (!is_int(args))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (is_max(args) == 1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	return (1);
}
int parsing(int argc, char **argv)
{
	int	i;
	if (argc < 5 || argc > 6)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (checker(argv) == 0)
		return (1);
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
