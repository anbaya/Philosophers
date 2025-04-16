#include "philosopher.h"

size_t	ft_atoi(char *str)
{
	size_t	i;
	size_t	r;
	size_t	sign;
	char	*s;

	s = str;
	i = 0;
	r = 0;
	sign = 1;
	while (s[i] == ' ' || (s[i] >= 8 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		r *= 10;
		r += (s[i] - 48);
		i++;
	}
	return (r * sign);
}
int is_odd(int number)
{
    if (number % 2 != 0) {
        return 1;
    } else {
        return 0;
    }
}
