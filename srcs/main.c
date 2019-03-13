/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:52:43 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/13 19:12:33 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	t_tab_parser *tab_parser;

	//init map
	if (!(tab_parser = (t_tab_parser*)malloc(sizeof(t_tab_parser) * 4)))
		return (1);
	tab_parser[0].step = 0;
	tab_parser[0].f = &verif_com;
	tab_parser[1].step = 0;
	tab_parser[1].f = &verif_ants;
	tab_parser[2].step = 1;
	tab_parser[2].f = &verif_room;
	tab_parser[3].step = 2;
	tab_parser[3].f = &verif_link;
}