#include "philo.h"

int main(int argc, char **argv)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (argc != 5 && argc != 6)
		return(printf("ERROR: Check your arguments"));
	
	philo->n_philo = ft_atoi(argv[1]);
	philo->t_die = ft_atoi(argv[2]);
	philo->t_eat= ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->n_meals = ft_atoi(argv[5]);

	printf("Number of philosophers: %d\n",philo->n_philo);
	printf("Time to die: %d\n", philo->t_die);
	printf("Time to eat: %d\n", philo->t_eat);
	printf("Time to sleep: %d\n", philo->t_sleep);
	if (argc == 6)
		printf("Number of meals %d\n", philo->n_meals);
}