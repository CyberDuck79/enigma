/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:21:19 by fhenrion          #+#    #+#             */
/*   Updated: 2020/01/17 09:30:37 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enigma.h"

int		main(int ac, char **av)
{
	t_conf	conf;

	if (ac == 3)
	{
		if (get_conf(&conf, av[1]))
		{
			write(1, "configuration error\n", 20);
			return (0);
		}
		encode(&conf, av[2]);
		return (0);
	}
	write(1, "USAGE : configuration message\n", 30);
}