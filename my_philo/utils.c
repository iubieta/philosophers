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

void* ft_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        perror("Error al asignar memoria con malloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void ft_mutex_init(pthread_mutex_t* mutex) {
    if (pthread_mutex_init(mutex, NULL) != 0) {
        perror("Error al inicializar el mutex");
        exit(EXIT_FAILURE);
    }
}