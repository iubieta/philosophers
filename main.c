#include "philo.h"

int main(int argc, char **argv)
{
	int n_philo;
	int t_die;
	int t_eat;
	int t_sleep;
	int n_meals;

	if (argc != 5 && argc != 6)
		return(printf("ERROR: Check your arguments"));
	n_philo = atoi(argv[1]);
	t_die = atoi(argv[2]);
	t_eat = atoi(argv[3]);
	t_sleep = atoi(argv[4]);
	if (argc == 5)
		n_meals = atoi(argv[5]);
}