# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	int	id;
	// int status; // 1:Despierto, 2:Comiendo, 3:Durmiendo, 0:muerto
	// size_t	t_die;
	// size_t t_eat;
	// size_t t_sleep;
	// size_t	n_meals;
	// pthread_mutex_t *left_fork;
	// pthread_mutex_t *right_fork;
	// pthread_mutex_t *death_lock;
	pthread_mutex_t *write_lock;
	int *var;
}	t_philo;

typedef struct s_mutex_group
{
	pthread_mutex_t death_lock;
	pthread_mutex_t write_lock;
	pthread_mutex_t **forks;
}	t_mutex_group;

int	init_mutex(pthread_mutex_t *mutex);

void *rutina(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;

	for (int i = 0; i < 5; i++)
	{
		usleep(1000 );
		pthread_mutex_lock(philo->write_lock);
		*(philo->var) = *(philo->var) + i * philo->id;
		printf("Hilo %i funcionando: VARIABLE CONJUNTA = %i\n",philo->id, *(philo->var));
		pthread_mutex_unlock(philo->write_lock);
		usleep(1000 );
	}
	return (NULL);
}

int main()
{
	t_mutex_group	mutex_gr;
	t_philo			philo[200];
	pthread_t		routines[200];
	int				var = 0;

	init_mutex(&(mutex_gr.write_lock));
	for (int i = 0; i < 3; i++)
	{
		philo[i].id = i;
		philo[i].write_lock = &(mutex_gr.write_lock);
		philo[i].var = &var;
		pthread_create(&routines[i], NULL, rutina, (void*)&philo[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		pthread_join(routines[i], NULL);
	}
	return (0);
}

int	init_mutex(pthread_mutex_t *mutex)
{
	if (0 != pthread_mutex_init(mutex, NULL))
	{
		printf("Error initializing mutex %p\n", (void *)mutex);
		return (-1);
	}
	return (0);
}