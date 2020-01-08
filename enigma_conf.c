/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma_conf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:16:21 by fhenrion          #+#    #+#             */
/*   Updated: 2020/01/08 11:49:27 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enigma.h"

/*
tocken controller
skip all the char before next token char

**str) pointer to input
c) token
return error if \0 or success if c
*/
static t_error	next_token(char **str, char c)
{
	while (**str && **str != c)
		(*str)++;
	if (!**str)
		return (ERROR);
	(*str)++;
	return (NO_ERROR);
}

/*
Rotor checker
check of rotor number is valid and if there no rotor in double

rotor) the rotor sequence
nb) index of the rotor
return error or success
*/
static t_error	check_rotor_nb(int *rotor, int nb)
{
	if (rotor[nb] < 0 || rotor[nb] > 7)
		return (ERROR);
	if (nb > 0 && rotor[1] == rotor[0])
		return (ERROR);
	if (nb > 1 && (rotor[2] == rotor[0] || rotor[2] == rotor[1]))
		return (ERROR);
	return (NO_ERROR);
}

/*
copy the rotor from the rotors tab at index i
*/
static void		copy_rotor(const int **rotors, int i, int *rotor)
{
	memcpy(rotor, rotors[i], sizeof(int) * 26);
}

/*
Rotors parsing controller
control the rotors and reflector parsing sequence

**str) pointer to input
return error in the parsing sequence or parsing success
*/
static t_error	parse_rotors(t_conf *conf, char **str)
{
	int	rotor_nb[3] = {0};

	rotor_nb[0] = atoi(*str) - 1;
	if (check_rotor_nb(rotor_nb, 0) || next_token(str, '-'))
		return (ERROR);
	copy_rotor(ROTORS, rotor_nb[0], conf->rotor[0][0]);
	copy_rotor(R_ROTORS, rotor_nb[0], conf->rotor[0][1]);
	rotor_nb[1] = atoi(*str) - 1;
	if (check_rotor_nb(rotor_nb, 1) || next_token(str, '-'))
		return (ERROR);
	copy_rotor(ROTORS, rotor_nb[1], conf->rotor[1][0]);
	copy_rotor(R_ROTORS, rotor_nb[1], conf->rotor[1][1]);
	rotor_nb[2] = atoi(*str) - 1;
	if (check_rotor_nb(rotor_nb, 2) || next_token(str, '-'))
		return (ERROR);
	copy_rotor(ROTORS, rotor_nb[2], conf->rotor[2][0]);
	copy_rotor(R_ROTORS, rotor_nb[2], conf->rotor[2][1]);
	if (**str == 'B')
		copy_rotor(REFLECTORS, 0, conf->reflector);
	else if (**str == 'C')
		copy_rotor(REFLECTORS, 1, conf->reflector);
	else
		return (ERROR);
	return (next_token(str, '-'));
}

/*
check if position < 0 || position > 25
*/
static t_error	check_position(int position)
{
	if (position < 0 || position > 25)
		return (ERROR);
	return (NO_ERROR);
}

/*
Positions parsing controller
control the parsing of a Position, check syntax

**str) pointer to input
return error in the parsing or parsing success
*/
static t_error	parse_positions(t_conf *conf, char **str)
{
	conf->position[0] = (**str - 65);
	if (check_position(conf->position[0]) || next_token(str, '-'))
		return (ERROR);
	conf->position[1] = (**str - 65);
	if (check_position(conf->position[1]) || next_token(str, '-'))
		return (ERROR);
	conf->position[2] = (**str - 65);
	if (check_position(conf->position[2]) || next_token(str, '-'))
		return (ERROR);
	return (NO_ERROR);
}

/*
Duplicate letter checker
check if no letter already in connected wires

return error or succes
*/
static t_error	check_wire(t_conf *conf, char *str)
{
	size_t	i = 0;

	while (conf->wires[0][i])
	{
		if (*str == conf->wires[0][i] || *str == conf->wires[1][i])
			return (ERROR);
		i++;
	}
	return (NO_ERROR);
}

/*
Wire parsing controller
control the parsing of a wire, check syntax

**str) pointer to input
wire_nb) index of the connection
return error in the parsing or parsing success
*/
static t_error	parse_wire(t_conf *conf, char **str, size_t wire_nb)
{
	if (check_wire(conf, *str))
		return (ERROR);
	conf->wires[0][wire_nb] = **str;
	if (next_token(str, '/'))
		return (ERROR);
	if (check_wire(conf, *str))
		return (ERROR);
	conf->wires[1][wire_nb] = **str;
	next_token(str, '-');
	return (NO_ERROR);
}

/*
Wires parsing controller
initialize the wires tabs control the sequence of wires parsing

**str) pointer to input
return error in the parsing sequence or parsing success
*/
static t_error	parse_wires(t_conf *conf, char **str)
{
	size_t	i = 0;

	bzero(conf->wires[0], 13);
	bzero(conf->wires[1], 13);
	while (**str >= 'A' && **str <= 'Z' && i < 13)
	{
		if (parse_wire(conf, str, i))
			return (ERROR);
		i++;
	}
	return (**str ? ERROR : NO_ERROR);
}

/*
Configuration controller
control the sequence of parsing

conf) contains the rotors, positions and the reflector
str) input
return error in the parsing sequence or parsing success
*/
t_error			get_conf(t_conf *conf, char *str)
{
	if (parse_rotors(conf, &str))
		return (ERROR);
	if (parse_positions(conf, &str))
		return (ERROR);
	if (parse_wires(conf, &str))
		return (ERROR);
	return (NO_ERROR);
}