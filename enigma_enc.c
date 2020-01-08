/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma_enc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 11:04:45 by fhenrion          #+#    #+#             */
/*   Updated: 2020/01/08 11:49:38 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enigma.h"
#include <stdio.h>

/*
return the the char to encrypt
*/
static char	wire(t_conf *conf, char c)
{
	size_t	i = 0;

	while (conf->wires[0][i])
	{
		if (c == conf->wires[0][i])
			return (conf->wires[1][i]);
		if (c == conf->wires[1][i])
			return (conf->wires[0][i]);
		i++;
	}
	return (c);
}

/*
Rotors shift
do the rotations of the rotors
*/
static void	rotors_shift(t_conf *conf)
{
	if (++conf->position[0] > 25)
	{
		conf->position[0] = 0;
		if (++conf->position[1] > 25)
		{
			conf->position[1] = 0;
			if (++conf->position[2] > 25)
				conf->position[2] = 0;
		}
	}
}

/*
Recursive Encryption cypher
Enter in recursion for each rotor of the cypher

d) control the direction through rotors circuit
r) index of the rotor in execution
i) index of the translation
return the final encrypted char
*/
static char	cypher(t_conf *conf, int i, t_rotor r, t_dir d)
{
	if (r == REFLECTOR)
		return (cypher(conf, conf->reflector[i], 2, REFLECTION));
	if ((i += conf->position[r]) > 25)
		i -= 26;
	i = conf->rotor[r][d][i];
	if ((i -= conf->position[r]) < 0)
		i += 26;
	if (r == ROTOR_I && d == REFLECTION)
		return ((char)(i + 65));
	return (cypher(conf, i, (d ? r - 1 : r + 1), d));
}

/*
Encryption controller
browse the input sequence, do the wires connection
and the cypher execution

conf) contains the rotors, positions and the reflector
str) input sequence
*/
void		encode(t_conf *conf, char *str)
{
	char	enc_str[strlen(str) + 1];
	char	*enc_char = enc_str;

	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
		{
			rotors_shift(conf);
			*enc_char = cypher(conf, wire(conf, *str) - 65, 0, 0);
			*enc_char = wire(conf, *enc_char);
			enc_char++;
		}
		str++;
	}
	*enc_char = '\0';
	write(1, enc_str, strlen(enc_str));
	write(1, "\n", 1);
}
