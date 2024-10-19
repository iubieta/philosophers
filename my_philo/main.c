/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:15 by iubieta-          #+#    #+#             */
/*   Updated: 2024/10/19 17:01:06 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t *check_args(int argc, char **argv);

int main(int argc, char **argv)
{
	size_t			*args;
	t_philo 		**table;
	t_mutex_group 	*mutex_gr;
	pthread_t		*routines;

	args = check_args(argc, argv);
	if (!args)
		return (printf("PROGRAM TERMINATED"), 0);
	mutex_gr = malloc(sizeof(t_mutex_group));
	if (!mutex_gr)
		return (printf("PROGRAM TERMINATED"), mutex_gr = NULL, 0);
	mutex_gr = init_mutex(mutex_gr, args);
	if (!mutex_gr)
		return (printf("PROGRAM TERMINATED"), mutex_gr = NULL, 0);
	printf("ARGS: %lu , %lu , %lu , %lu , %lu , %lu\n", args[0], args[1], args[2], args[3], args[4], args[5]);
	prints("Mutex initialized successfully\n");
	
	printf("\n--TABLE INFO--\n");
	printf("\nNumber of philosophers: %lu\n", args[1]);
	table = malloc(sizeof(t_philo *) * args[1]);
	init_philos(table, *mutex_gr, args);
	printf("\n");
	
	printf("--STARTING PROGRAM--\n");
	routines = start_routines(args, table, mutex_gr);
	printf("Routines started\n");
	for (int i = 0; i < args[1]; i++) {
        pthread_join(routines[i], NULL);
    }
	prints("PROGRAM FINISHED");
	return (0);
}

size_t *check_args(int argc, char **argv)
{
	int		i;
	size_t	*args;

	args = malloc(sizeof(size_t) * 6);
	if (argc < 5 || argc > 6)
		return (printe("Check your arguments\n"), NULL);
	if (!args)
		return (printe("Failed to initialize 'args'\n"), NULL);
	args[0] = (size_t)argc;
	i = 1;
	while (i < argc)
	{
		args[i] = ft_atosizet(argv[i]);
		i++;
	}
	return (args);
}
