/* Tenes Empanadas Graciela
 *
 * Copyright (C) 2000 Ricardo Quesada
 *
 * Author: Ricardo Calixto Quesada <rquesada@core-sdi.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; only version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 */

#include <type_traits>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "fcintl.h"
#include "missions.h"
#include "common.h"


MISSIONS g_missions[]= {
	// common mission, all time active: conquer the whole world
	[MISSION_CONQWORLD] = {
		.player_number=0,
		.name=N_("Conquer the world"),
		.continents={
			[CONTINENTE_AMERICASUR]=CONT_AMERICASUR_CANT,
			[CONTINENTE_AMERICANORTE]=CONT_AMERICANORTE_CANT,
			[CONTINENTE_AFRICA]=CONT_AFRICA_CANT,
			[CONTINENTE_OCEANIA]=CONT_OCEANIA_CANT,
			[CONTINENTE_EUROPA]=CONT_EUROPA_CANT,
			[CONTINENTE_ASIA]=CONT_ASIA_CANT,
			[CONTINENTE_AMERICACENTRO]=CONT_AMERICACENTRO_CANT
		},
		.islands=0,
		.tot_countries=0
	},
	// optional common mission: conquer 45 countries
	[MISSION_COMMON] = {
		.player_number=0,
		.name=N_("Conquer 45 countries"),
		.continents={0, 0, 0, 0, 0, 0},
		.islands=0,
		.tot_countries=45
	},
	{
		.player_number=-1,
		.name=N_("Conquer &4 and &0"),
		.continents={
			[CONTINENTE_AMERICASUR]=CONT_AMERICASUR_CANT,
			[CONTINENTE_AMERICANORTE]=CONT_AMERICANORTE_CANT,
			[CONTINENTE_AFRICA]=0,
			[CONTINENTE_OCEANIA]=0,
			[CONTINENTE_EUROPA]=0,
			[CONTINENTE_ASIA]=0,
			[CONTINENTE_AMERICACENTRO]=0
		},
		.islands=0,
		.tot_countries=0
	},

#ifdef WITH_ALL_MISSIONS
        /*
         * Estoy viendo como implementarlo.
         * Por ahora se me ocurre definir un continente bobo que tenga a las 13.islands del mapa,
         * pero faltaría el chequeo de al menos 3.continents.
         * Australia no cuenta como isla.
         */
	{
		.player_number=-1,
		.name=N_("Conquer &2\n, 4 countries of &4, 4 countries de &5 and\n6 islands distributed in\nat least 3 continents"),
		.continents={
			[CONTINENTE_AMERICASUR]=0,
			[CONTINENTE_AMERICANORTE]=0,
			[CONTINENTE_AFRICA]=CONT_AFRICA_CANT,
			[CONTINENTE_OCEANIA]=0,
			[CONTINENTE_EUROPA]=4,
			[CONTINENTE_ASIA]=4,
			[CONTINENTE_AMERICACENTRO]=0
		},
		.islands=6,
		.tot_countries=0
	},
#endif /* WITH_ALL_MISSIONS */

	{
		.player_number=-1,
		.name=N_("Conquer &1,\n&3 and\n5 countries of &2"),
		.continents={
			[CONTINENTE_AMERICASUR]=0,
			[CONTINENTE_AMERICANORTE]=CONT_AMERICANORTE_CANT,
			[CONTINENTE_AFRICA]=5,
			[CONTINENTE_OCEANIA]=CONT_OCEANIA_CANT,
			[CONTINENTE_EUROPA]=0,
			[CONTINENTE_ASIA]=0,
                        [CONTINENTE_AMERICACENTRO]=0
		},
		.islands=0,
		.tot_countries=0
	},

	{
		.player_number=-1,
		.name=N_("Conquer &5 and\n&6"),
		.continents={
			[CONTINENTE_AMERICASUR]=0,
			[CONTINENTE_AMERICANORTE]=0,
			[CONTINENTE_AFRICA]=0,
			[CONTINENTE_OCEANIA]=0,
			[CONTINENTE_EUROPA]=0,
			[CONTINENTE_ASIA]=CONT_ASIA_CANT,
                        [CONTINENTE_AMERICACENTRO]=CONT_AMERICACENTRO_CANT
		},
		.islands=0,
		.tot_countries=0
	},

	{
		.player_number=-1,
		.name=N_("Conquer &1,\n4 countries of &4 and\n8 countries of &5"),
		.continents={
			[CONTINENTE_AMERICASUR]=0,
			[CONTINENTE_AMERICANORTE]=CONT_AMERICANORTE_CANT,
			[CONTINENTE_AFRICA]=0,
			[CONTINENTE_OCEANIA]=0,
			[CONTINENTE_EUROPA]=4,
			[CONTINENTE_ASIA]=8,
                        [CONTINENTE_AMERICACENTRO]=0
		},
		.islands=0,
		.tot_countries=0
	},

	{
		.player_number=-1,
		.name=N_("Conquer 3 countries of &3,\n3 of &2, 3 of &0,\n4 of &4, 4 of &1,\n4 of &5 and\n3 of &6"),
		.continents={
			[CONTINENTE_AMERICASUR]=3,
			[CONTINENTE_AMERICANORTE]=4,
			[CONTINENTE_AFRICA]=3,
			[CONTINENTE_OCEANIA]=3,
			[CONTINENTE_EUROPA]=4,
			[CONTINENTE_ASIA]=4,
                        [CONTINENTE_AMERICACENTRO]=3
		},
		.islands=0,
		.tot_countries=0
	},

	{
		.player_number=-1,
		.name=N_("Conquer &3,\n6 countries of &1,\n6 countries of &5 and\n6 countries of &2"),
		.continents={
			[CONTINENTE_AMERICASUR]=0,
			[CONTINENTE_AMERICANORTE]=6,
			[CONTINENTE_AFRICA]=6,
			[CONTINENTE_OCEANIA]=CONT_OCEANIA_CANT,
			[CONTINENTE_EUROPA]=0,
			[CONTINENTE_ASIA]=6,
                        [CONTINENTE_AMERICACENTRO]=0
		},
		.islands=0,
		.tot_countries=0
	},

	{
		.player_number=-1,
		.name=N_("Conquer &6,\n6 countries of &0,\n6 countries of &4 and\n6 countries of &5"),
		.continents={
			[CONTINENTE_AMERICASUR]=6,
			[CONTINENTE_AMERICANORTE]=0,
			[CONTINENTE_AFRICA]=0,
			[CONTINENTE_OCEANIA]=0,
			[CONTINENTE_EUROPA]=6,
			[CONTINENTE_ASIA]=6,
                        [CONTINENTE_AMERICACENTRO]=CONT_AMERICACENTRO_CANT
		},
		.islands=0,
		.tot_countries=0
	},

	{
		.player_number=-1,
		.name=N_("Conquer &0,\n&2 and,\n8 countries of &5"),
		.continents={
			[CONTINENTE_AMERICASUR]=CONT_AMERICASUR_CANT,
			[CONTINENTE_AMERICANORTE]=0,
			[CONTINENTE_AFRICA]=CONT_AFRICA_CANT,
			[CONTINENTE_OCEANIA]=0,
			[CONTINENTE_EUROPA]=0,
			[CONTINENTE_ASIA]=8,
                        [CONTINENTE_AMERICACENTRO]=0
		},
		.islands=0,
		.tot_countries=0
	},

	{
		.player_number=-1,
		.name=N_("Conquer &2,\n&3,\n4 countries of &5 and\n4 countries of &6"),
		.continents={
			[CONTINENTE_AMERICASUR]=0,
			[CONTINENTE_AMERICANORTE]=0,
			[CONTINENTE_AFRICA]=CONT_AFRICA_CANT,
			[CONTINENTE_OCEANIA]=CONT_OCEANIA_CANT,
			[CONTINENTE_EUROPA]=0,
			[CONTINENTE_ASIA]=4,
                        [CONTINENTE_AMERICACENTRO]=4
		},
		.islands=0,
		.tot_countries=0
	},

	{
		.player_number=-1,
		.name=N_("Conquer &4,\n4 countries of &0 and\n4 countries of &5"),
		.continents={
			[CONTINENTE_AMERICASUR]=4,
			[CONTINENTE_AMERICANORTE]=0,
			[CONTINENTE_AFRICA]=0,
			[CONTINENTE_OCEANIA]=0,
			[CONTINENTE_EUROPA]=CONT_EUROPA_CANT,
			[CONTINENTE_ASIA]=4,
                        [CONTINENTE_AMERICACENTRO]=0
		},
		.islands=0,
		.tot_countries=0
	},

	{
		.player_number=-1,
		.name=N_("Conquer 35 countries\nin any place of the map"),

		.continents={
			[CONTINENTE_AMERICASUR]=0,
			[CONTINENTE_AMERICANORTE]=0,
			[CONTINENTE_AFRICA]=0,
			[CONTINENTE_OCEANIA]=0,
			[CONTINENTE_EUROPA]=0,
			[CONTINENTE_ASIA]=0,
                        [CONTINENTE_AMERICACENTRO]=0
		},
		.islands=0,
		.tot_countries=35
	},

};
constexpr auto NRMISSIONS = std::extent<decltype(g_missions)>::value;

int missions_cant()
{
	return NRMISSIONS;
}

std::string missions_get_name(int number)
{
	if((number < 0) || (((unsigned)number) >= NRMISSIONS)) {
		return _("Unknown");
	}
	ContinentNames names{
		_(g_conts[0].name),
		_(g_conts[1].name),
		_(g_conts[2].name),
		_(g_conts[3].name),
		_(g_conts[4].name),
		_(g_conts[5].name),
		_(g_conts[6].name),
	};
	return replace_continents(_(g_missions[number].name), names);
}
