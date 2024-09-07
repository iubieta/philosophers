#include "philo.h"

int	ft_atoi(const char *s)
{
	size_t	i;
	long	number;
	int		sign;

	i = 0;
	sign = 1;
	number = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == '\f' )
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		number = number * 10 + s[i] - 48;
		i++;
	}
	i++;
	return (number * sign);
}