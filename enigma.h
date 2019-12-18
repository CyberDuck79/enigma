/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:10:47 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/18 18:47:48 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENIGMA_H
# define ENIGMA_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

# define ALPHABET		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define ROTOR_I		"EKMFLGDQVZNTOWYHXUSPAIBRCJ"
# define ROTOR_II		"AJDKSIRUXBLHWTMCQGZNPYFVOE"
# define ROTOR_III		"BDFHJLCPRTXVZNYEIWGAKMUSQO"
# define ROTOR_IV		"ESOVPZJAYQUIRHXLNFTGKDCMWB"
# define ROTOR_V		"VZBRGITYUPSDNHLXAWMJQOFECK"
# define ROTOR_VI		"JPGVOUMFYQBENHZRDKASXLICTW"
# define ROTOR_VII		"NZJHGRCXMYSWBOUFAIVLPEKQDT"
# define ROTOR_VIII		"FKQHTLXOCBJSPDZRAMEWNIUYGV"
# define REFLECTOR_B	"YRUHQSLDPXNGOKMIEBFZCWVJAT"
# define REFLECTOR_C	"RDOBJNTKVEHMLFCWZAXGYIPSUQ"

typedef enum	e_error
{
	NO_ERROR,
	ERROR
}				t_error;

typedef struct	s_conf
{
	char		*rotor[3];
	char		*reflector;
	int			position[3];
	char		wire[5][2];
}				t_conf;

t_error			get_conf(t_conf *conf, char *str);
t_error			encode(t_conf *conf, char *str);

#endif