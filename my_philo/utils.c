/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:38 by iubieta-          #+#    #+#             */
/*   Updated: 2024/10/24 23:00:02 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

size_t	ft_atosizet(const char *s)
{
	size_t	i;
	size_t	number;

	i = 0;
	number = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == '\f' )
		i++;
	if (s[i] == '-')
		i++;
	else if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		number = number * 10 + s[i] - 48;
		i++;
	}
	i++;
	return (number);
}

int printe(char *str)
{
	return (printf("\u2717 ERROR: %s", str));
}

int prints(char *str)
{
	return (printf("\u2713 %s", str));
}
void init_mutex(void *mutex) {
   	mutex = malloc(sizeof(pthread_mutex_t));  // Reservar memoria para el mutex
    if (mutex != NULL) {
        pthread_mutex_init(mutex, NULL);  // Inicializar el mutex
    }
}
void lock_mutex(void *mutex) {
    if (mutex != NULL) {  // Comprobar si el puntero no es NULL
        pthread_mutex_lock(mutex);  // Bloquear el mutex
    } else {
        printe("Mutex no inicializado\n");
    }
}