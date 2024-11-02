/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:38 by iubieta-          #+#    #+#             */
/*   Updated: 2024/11/02 18:41:53 by iubieta-         ###   ########.fr       */
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
long	millis()
{
	struct timeval	tv;
	long			millis;

	gettimeofday(&tv, NULL);
	millis = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (millis);
}

int printe(char *str)
{
	return (printf("\u2717 ERROR: %s", str));
}

int prints(char *str)
{
	return (printf("\u2713 %s", str));
}
