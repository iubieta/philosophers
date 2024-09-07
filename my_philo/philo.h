#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <stdlib.h>

typedef struct s_philo
{
	int	n_philo;
	int	t_die;
	int t_eat;
	int t_sleep;
	int	n_meals;
}	t_philo;


int	ft_atoi(const char *s);

#endif