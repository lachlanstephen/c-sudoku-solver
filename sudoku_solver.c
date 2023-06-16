/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku_solver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstephen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:23:51 by lstephen          #+#    #+#             */
/*   Updated: 2023/06/17 04:24:23 by darkwater        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void	ft_putchar(int x, int j)
{
	x += '0';
	write(1, &x, 1);
	if (j != 8)
	{
		write(1, " ", 1);
	}
}

int	*find_next_empty(int (*puzzle)[9], int (empty)[2])
{
	int	i;
	int	j;

	i = 0;
	empty[0] = -1;
	empty[1] = -1;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			if (puzzle[i][j] == -1)
			{
				empty[0] = i;
				empty[1] = j;
				return (empty);
			}
			j++;
		}
		i++;
	}
	return (empty);
}

bool	is_valid(int (*puzzle)[9], int guess, int row_col[2])
{
	int	i;
	int	j;
	int	row_vals[9];
	int	col_vals[9];
	int	row_start;
	int	col_start;

	i = 0;
	while (i < 9)
	{
		row_vals[i] = puzzle[(row_col[0])][i];
		col_vals[i] = puzzle[i][(row_col[1])];
		i++;
	}
	i = 0;
	while (i < 9)
	{
		if (guess == row_vals[i])
		{
			return (false);
		}
		i++;
	}
	i = 0;
	while (i < 9)
	{
		if (guess == col_vals[i])
		{
			return (false);
		}
		i++;
	}
	row_start = (row_col[0] / 3) * 3;
	col_start = ((row_col[1]) / 3) * 3;
	i = row_start;
	while (i < row_start + 3)
	{
		j = col_start;
		while (j < col_start + 3)
		{
			if (guess == puzzle[i][j])
			{
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	solve_puzzle(int (*puzzle)[9])
{
	int	row_col[2];
	bool	complete;
	int	guess;

	complete = false;
	find_next_empty(puzzle, row_col);
	guess = 1;
	while (complete == false)
	{
		if (row_col[0] == -1)
		{
			return (true);
		}
		while (guess < 10)
		{
			if (is_valid(puzzle, guess, row_col) == true)
			{
				puzzle[(row_col[0])][(row_col[1])] = guess;
				if (solve_puzzle(puzzle) == true)
				{
					return (true);
				}
			}
			puzzle[(row_col[0])][(row_col[1])] = -1;
			guess++;
		}
		complete = true;
	}
	return (false);
}

void	prn_grid(int (*puzzle)[9])
{
	int	i;
	int	j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			ft_putchar(puzzle[i][j], j);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int	main(void)
{
	int	arr[9][9] =
	{{-1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1}};

	if (solve_puzzle(arr) == true)
	{
		prn_grid(arr);
	}
	else
	{
		write(1, "Error\n", 6);
	}
	return (0);
}
