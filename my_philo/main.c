/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:15 by iubieta-          #+#    #+#             */
/*   Updated: 2024/10/31 17:29:43 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(size_t **args, int argc, char **argv);

int main(int argc, char **argv)
{
	size_t			*args;
	t_philo 		*table;
	t_mutex_group 	mutex_gr;
	pthread_t		*routines;

	if (0 != check_args(&args, argc, argv))
		return (printe("PROGRAM TERMINATED\n"), 0);
	printf("ARGS: %lu , %lu , %lu , %lu , %lu , %lu\n", args[0], args[1], args[2], args[3], args[4], args[5]);
	printf("\n--TABLE INFO--\n\n");
	printf("Number of philosophers: %lu\n", args[1]);
	if (0 != init_all_mutex(&mutex_gr, args))
		return (printe("PROGRAM TERMINATED\n"), 0);
	init_philos(&table, &mutex_gr, args);
	printf("\n");

	printf("--STARTING PROGRAM--\n\n");
	routines = start_routines(args, &table/*, mutex_gr*/);
	printf("Routines started\n");
	for (size_t i = 0; i < args[1]; i++) {
        pthread_join(routines[i], NULL);
    }
	prints("PROGRAM FINISHED");
	return (0);
}

int	check_args(size_t **args, int argc, char **argv)
{
	int		i;
	size_t	*array;
	if (argc < 5 || argc > 6)
		return (printe("Check your arguments\n"), 1);
	array = malloc(sizeof(size_t) * 6);
	if (!array)
		return (printe("Failed to initialize arguments array\n"), 2);
	array[0] = (size_t)argc;
	i = 1;
	while (i < argc)
	{
		array[i] = ft_atosizet(argv[i]);
		i++;
	}
	*args = array;
	return (0);
}
