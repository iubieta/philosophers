/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta <iubieta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:15 by iubieta-          #+#    #+#             */
/*   Updated: 2024/11/22 12:44:41y iubieta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_program *program, int argc, char **argv);
void	destroy_all(t_program *program);
int	destroy_mutex_gr(t_mutex_group *mutex_gr, size_t *args);

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
	destroy_all(&program);
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

void	destroy_all(t_program *program)
{
	free(program->routines);
	program->routines = NULL;
	destroy_mutex_gr(&program->mutex_gr, program->args);
	free(program->table);
	program->table = NULL;
	free(program->args);
	program->args = NULL;
}

int	destroy_mutex_gr(t_mutex_group *mutex_gr, size_t *args)
{
	size_t	i;

	if (0 != pthread_mutex_destroy(&mutex_gr->death_lock))
		return(printe("(1) Imposible to destroy mutex"), 1);
	if (0 != pthread_mutex_destroy(&mutex_gr->write_lock))
		return(printe("(2) Imposible to destroy mutex"), 2);
	i = 0;
	while (i < args[1])
	{
		if (0 != pthread_mutex_destroy(&mutex_gr->forks[i]))
			return(printe("(3) Imposible to destroy mutex"), 3);
		i++;
	}
	free(mutex_gr->forks);
	mutex_gr->forks = NULL;
	return (0);	
}
