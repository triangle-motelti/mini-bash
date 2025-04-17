/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:40:48 by motelti           #+#    #+#             */
/*   Updated: 2025/04/17 14:52:30 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    echo(int ac, char **av)
{
    int newline;
    int start;
    int i;

    newline = 1;
    start = 0;
    if (ac > 0 && strcmp(av[0], "-n") == 0)
    {
        newline = 0;
        start = 1;
    }
    i = start;
    while (i < ac) 
    {
        printf("%s", av[i]);
        if (i < ac - 1)
        {
            ft_putchar(' ');
        }
        i++;
    }
    if (newline) {
        putchar('\n');
    }
}