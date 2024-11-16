/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta <iubieta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:15 by iubieta-          #+#    #+#             */
/*   Updated: 2024/11/16 19:28:47 by iubieta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_program *program, int argc, char **argv);

int	main(int argc, char **argv)
{
	t_program	program;
	
	printf("\n");
	if (0 != check_args(&program, argc, argv))
		return (printe("PROGRAM TERMINATED\n"), 1);
	printf("\n--TABLE INFO--\n\n");
	printf("Number of philosophers: %lu\n", program.args[1]);
	if (0 != init_all_mutex(&program.mutex_gr, program.args))
		return (printe("PROGRAM TERMINATED\n"), 0);
	init_philos(&program.table, &program.mutex_gr, program.args);
	printf("\n");
	printf("--STARTING PROGRAM--\n\n");
	program.routines = start_routines(program.args, program.table);
	size_t i = 0;
	while (i <= program.args[1])
	{
		pthread_join(program.routines[i], NULL);
		i++;
	}
	printf("\n");
	prints("PROGRAM FINISHED");
	return (0);
}

int	check_args(t_program *program, int argc, char **argv)
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
		if (array[i] <= 0)
			return (printe("Invalid argument\n"));
		i++;
	}
	program->args= array;
	printf("ARGS: %lu , %lu , %lu , %lu , %lu , %lu\n", program->args[0], 
		program->args[1], program->args[2], program->args[3], program->args[4], 
		program->args[5]);
	return (0);
}
