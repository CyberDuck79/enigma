/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:21:19 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/22 18:21:28 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enigma.h"

int		main(int ac, char **av)
{
	t_conf	conf_ini;

	if (ac == 3)
	{
		if (get_conf(&conf_ini, av[1]))
		{
			write(1, "configuration error\n", 20);
			return (0);
		}
		if (encode(&conf_ini, av[2]))
			write(1, "encoding error\n", 15);
		return (0);
	}
	write(1, "USAGE : configuration message\n", 30);
}