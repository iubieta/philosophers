#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	int	id;
	int status;
	int	t_die;
	int t_eat;
	int t_sleep;
	int	n_meals;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *death_lock;
	pthread_mutex_t *write_lock;
}	t_philo;

typedef struct s_mutex_group
{
	pthread_mutex_t death_lock;
	pthread_mutex_t write_lock;
	pthread_mutex_t *forks;
}	t_mutex_group;

//MEMORY
t_philo	**init_philos(t_philo **philo, int argc, char **argv);
t_mutex_group	*init_mutex(t_mutex_group *mutex_group, char **argv);


//UTILS
int	ft_atoi(const char *s);
int printe(char *str);
int prints(char *str);

#endif