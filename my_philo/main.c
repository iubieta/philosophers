#include "philo.h"

void *main(int argc, char **argv)
{
	t_philo **table;
	t_mutex_group *mutex_gr;

	mutex_gr = malloc(sizeof(t_mutex_group));
	if (!mutex_gr)
		return (printf("PROGRAM TERMINATED"), mutex_gr = NULL, NULL);
	mutex_gr = init_mutex(mutex_gr, argv);
	if (!mutex_gr)
		return (printf("PROGRAM TERMINATED"), mutex_gr = NULL, NULL);
	prints("Mutex initialized successfully\n");
	printf("\n--TABLE INFO--\n");
	printf("\nNumber of philosophers: %d\n",ft_atoi(argv[1]));
	table = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	init_philos(table, argc, argv);


}