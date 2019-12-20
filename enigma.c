/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 11:04:45 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/20 20:55:06 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enigma.h"

static t_error	next_token(char **str, char c)
{
	while (**str && **str != c)
		(*str)++;
	if (!**str)
		return (ERROR);
	(*str)++;
	return (NO_ERROR);
}

const char	*get_rotor_conf(t_rotor i, char **rotors)
{
	return (rotors[i]);
}

t_error	parse_rotors(t_conf *conf, char **str)
{
	t_rotor	rotor[3];

	rotor[0] = atoi(*str);
	if (rotor[0] < 1 || rotor[0] > 8 || next_token(str, '-'))
		return (ERROR);
	conf->rotor[0] = get_rotor_conf(rotor[0] - 1, ROTORS);
	rotor[1] = atoi(*str);
	if (rotor[1] < 1 || rotor[1] > 8 || rotor[1] == rotor[0]
	|| next_token(str, '-'))
		return (ERROR);
	conf->rotor[1] = get_rotor_conf(rotor[1] - 1, ROTORS);
	rotor[2] = atoi(*str);
	if (rotor[2] < 1 || rotor[2] > 8 || rotor[2] == rotor[0]
	|| rotor[2] == rotor[1] || next_token(str, '-'))
		return (ERROR);
	conf->rotor[2] = get_rotor_conf(rotor[2] - 1, ROTORS);
	if (**str == 'B')
		conf->reflector = REFLECTOR_B;
	else if (**str == 'C')
		conf->reflector = REFLECTOR_C;
	else
		return (ERROR);
	return (next_token(str, '-'));
}

t_error	parse_positions(t_conf *conf, char **str)
{
	conf->position[0] = atoi(*str);
	if (conf->position[0] < 1 || conf->position[0] > 26 || next_token(str, '-'))
		return (ERROR);
	conf->position[1] = atoi(*str);
	if (conf->position[1] < 1 || conf->position[1] > 26 || next_token(str, '-'))
		return (ERROR);
	conf->position[2] = atoi(*str);
	if (conf->position[2] < 1 || conf->position[2] > 26 || next_token(str, '-'))
		return (ERROR);
	return (NO_ERROR);
}

int	in_string(char c, char *str)
{
	size_t	i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_error parse_wire(t_conf *conf, char **str, size_t i)
{
	static char	used[11] = {0};
	size_t		used_i = 10 - i;

	if (**str < 65|| **str > 90 || in_string(**str, used + used_i))
		return (ERROR);
	used[used_i - 1] = **str;
	conf->wire[i / 2][i % 2] = **str;
	if (i == 9)
		return (NO_ERROR);
	else if (i % 2)
		return (next_token(str, '-'));
	else
		return (next_token(str, '/'));
}

t_error	parse_wires(t_conf *conf, char **str)
{
	size_t	i = 0;

	while (i < 10)
	{
		if (parse_wire(conf, str, i))
			return (ERROR);
		i++;
	}
	return (NO_ERROR);
}

t_error	get_conf(t_conf *conf, char *str)
{
	if (parse_rotors(conf, &str))
		return (ERROR);
	if (parse_positions(conf, &str))
		return (ERROR);
	if (parse_wires(conf, &str))
		return (ERROR);
	return (NO_ERROR);
}

char	wire(t_conf *conf, char c)
{
	size_t i = 0;

	while (i < 5)
	{
		if (conf->wire[i][0] == c)
			return (conf->wire[i][1]);
		if (conf->wire[i][1] == c)
			return (conf->wire[i][0]);
		i++;
	}
	return (c);
}

void	rotors_shift(t_conf *conf, t_rotor r)
{
	if (++conf->position[r] > 25)
	{
		conf->position[r] = 0;
		if (++conf->position[r + 1] > 25)
		{
			conf->position[r + 1] = 0;
			if (++conf->position[r + 2] > 25)
				conf->position[r + 2] = 0;
		}
	}
}

// mauvaise comprehension du shift ?
char	cypher(t_conf *conf, char c, t_rotor r, t_dir dir)
{
	size_t	i = c - 65;

	if (r == 0 && dir == REFLECTION)
		return (c);
	if (r == 0 && dir == FIRST_PASS)
		rotors_shift(conf, r);
	if (r == 3)
		return (cypher(conf, conf->reflector[i], r - 1, REFLECTION));
	if ((i += conf->position[r]) > 25)
		i %= 26;
	return (cypher(conf, conf->rotor[r][i], dir ? r - 1 : r + 1, dir));
}

t_error	encode(t_conf *conf, char *str)
{
	char	*enc_char = malloc(strlen(str) + 1);
	char	*enc_str = enc_char;

	while (*str)
	{
		if (*str == ' ')
			*enc_char = ' ';
		else if (!(*enc_char = cypher(conf, wire(conf, *str), 0, FIRST_PASS)))
			return (ERROR);
		enc_char++;
		str++;
	}
	*enc_char = '\0';
	write(1, enc_str, strlen(enc_str));
	return (NO_ERROR);
}

// TODO : position du reflecteur
int		main(int ac, char **av)
{
	t_conf	conf_ini;

	if (ac == 3)
	{
		// encore un decalage en plus en parametre ?
		if (get_conf(&conf_ini, av[1]))
		{
			write(1, "configuration error\n", 20);
			return (0);
		}
		if (encode(&conf_ini, av[2]))
		{
			write(1, "encoding error\n", 15);
			return (0);
		}
		return (0);
	}
	write(1, "USAGE : configuration message\n", 30);
}