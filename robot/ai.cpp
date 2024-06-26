/* Tenes Empanadas Graciela
 *
 * Copyright (C) 2000 Ricardo Quesada
 *
 * Author: Ricardo Calixto Quesada <riq@core-sdi.com>
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
/**
 * @file ai.c
 * Inteligecia artificial del robot
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <unistd.h>

#include "client.h"
#include "../server/server.h"
#include "ai.h"
#include "ai_fichas.h"

namespace teg::robot
{

namespace c = ::teg::client;
namespace s = ::teg::server;

/**
 * Risk of buffer overflow: When cards are traded for armies, there is NO upper
 * limit for how many armies you can place! When set to 50 this was a cause of
 * overflows when games lasted longer. But 500 armies should be enough for everyone.
*/
int ai_puntaje[COUNTRIES_CANT*10];
int ai_sorted[COUNTRIES_CANT*10];
static int attack_dst[COUNTRIES_CANT];

TEG_STATUS ai_puntaje_sort(int cant)
{
	int i, j;
	int max;

	//check if the buffer is big enough
	if(cant > COUNTRIES_CANT * 10) {
		return TEG_STATUS_ERROR;
	}

	for(j=0; j<cant; j++) {
		max = 0;
		for(i=0; i<COUNTRIES_CANT; i++) {
			if(ai_puntaje[i] > ai_puntaje[max]) {
				max = i;
			}
		}
		ai_sorted[j] = max;
		ai_puntaje[max] -= 2;
	}
	return TEG_STATUS_SUCCESS;
}

/**
 * @fn TEG_STATUS ai_puntaje_sort_for_attack( int cant)
 * Algoritmo para ordernar como se va a hacer el attack
 */
TEG_STATUS ai_puntaje_sort_for_attack()
{
	int i;
	int max=0;

	for(i=0; i<COUNTRIES_CANT; i++) {
		if(ai_puntaje[i] > ai_puntaje[max]) {
			max = i;
		}
	}
	ai_sorted[0] = max;
	return TEG_STATUS_SUCCESS;
}

void ai_puntaje_clean()
{
	int i;
	for(i=0; i<COUNTRIES_CANT; i++) {
		ai_puntaje[i] = -10000;
	}
}

/**
 * @fn int ai_many_country_enemigo( int p )
 * Dice la cantidad de countries enemigos que tiene un country
 */
int ai_many_country_enemigo(int p)
{
	int i;
	int c=0;

	for(i=0; i<COUNTRIES_CANT; i++) {
		if(g_countries[i].numjug != c::WHOAMI() && countries_eslimitrofe(p, i)) {
			c++;
		}
	}

	return c;
}

/**
 * @fn BOOLEAN ai_is_country_border( int p )
 * Tells if a country border of its continent
 */
bool ai_is_country_border(int p)
{
	int i;
	for(i=0; i<COUNTRIES_CANT; i++) {
		if(countries_eslimitrofe(i, p) && g_countries[i].continente != g_countries[p].continente) {
			return true;
		}
	}

	return false;
}

bool ai_own_continent(CONTINENTE c)
{
	int i;
	int t=0;

	for(i=0; i<COUNTRIES_CANT; i++) {
		if(g_countries[i].numjug == c::WHOAMI()
		        && g_countries[i].continente == c) {
			t++;
		}
	}

	return (t == g_conts[c].cant_countries);

}

TEG_STATUS ai_init()
{
	ai_puntaje_clean();
	return TEG_STATUS_SUCCESS;
}

/**
 * This function decides if it is dangerous to attack country dst by src. It is
 * taken into consideration if the the player of the country to be attacked has
 * already done with the turn.
 */
bool ai_is_country_peligroso(int src, int dst)
{
	/// \todo rename and scope limit variables
	bool aparecio_empezo = false;
	bool dst_jugo = false;
	int tmp;

	c::players_map_int(
	[&aparecio_empezo, dst, &dst_jugo](c::Player& player) {

		if(player.empezo_turno) {
			aparecio_empezo = true;
		}

		if(player.numjug == g_countries[dst].numjug) {
			dst_jugo = aparecio_empezo;
			return false;
		}
		return true;
	});

	if(dst_jugo) {
		return false;
	}

	tmp = (g_countries[src].ejercitos > 3) ? 3: g_countries[src].ejercitos-1;
	if(g_countries[dst].ejercitos > (g_countries[src].ejercitos-tmp)) {
		return true;
	}
	return false;
}

/**
 * @fn int ai_puntaje_atacar_warning( int src )
 * Resta puntos si existe un country limitrofe a 'src' que puede atacarlo antes
 * de que se acabe el turno
 */
int ai_puntaje_atacar_warning(int src)
{
	int p=0;
	int i;

	for(i=0; i<COUNTRIES_CANT; i++) {
		if(countries_eslimitrofe(src, i) &&
		        g_countries[src].numjug != g_countries[i].numjug &&
		        ai_is_country_peligroso(src, i)) {

			p += (g_countries[i].ejercitos - g_countries[src].ejercitos);
		}
	}

	return -(5+2*p);
}


/**
 * @fn int ai_puntaje_atacar_country( int src, int dst )
 * Dice los puntos que tiene de atacar src a dst
 */
int ai_puntaje_atacar_country(int src, int dst)
{
	int p=0;

	if(g_countries[src].ejercitos > g_countries[dst].ejercitos) {

		if(g_countries[src].continente == g_countries[dst].continente) {
			p++;
		}

		p += 10 + g_countries[src].ejercitos - g_countries[dst].ejercitos;

	} else {

		int r = random_between(1, 10);

		if((r>7) && (g_countries[src].ejercitos > 7)) {
			p++;
		}
	}

	return p;
}

/* Recibe un país y un número de jugador y devuelve verdadero si ese país es parte del objetivo del jugador  */
bool country_inmission( PCOUNTRY pP, int numjug )
{
        //PCPLAYER pJ;
        teg::client::PCPLAYER pJ_enemigo;

        // player_whois(numjug, &pJ);
        player_whois(pP->numjug, &pJ_enemigo);

        //for (i=0; i<missions_cant(); i++)
        //{
                fprintf(stderr, ("Pais(Jug): %s(%i), Col-Enemigo: %i, Obj-dest: %i, Obj-cont: %i\n"), pP->name,pP->numjug,pJ_enemigo->color,g_missions[c::g_game.secret_mission].jugadores[pJ_enemigo->color], g_missions[c::g_game.secret_mission].continents[pP->continente]);
                //fprintf(stderr, _("Numjug: %i , Pais: %s, Obj: %i\nObj-name: %s"), numjug, pP->name,c::g_game.secret_mission, g_missions[c::g_game.secret_mission].name);

                // Misión común o conquistar el mundo
                if (c::g_game.secret_mission == MISSION_COMMON || c::g_game.secret_mission == MISSION_CONQWORLD)
                        return true;

                // Objetivo de cant. de países
                if (g_missions[c::g_game.secret_mission].tot_countries != 0)
                        return true;

                // Misión de destrucción
                if (g_missions[c::g_game.secret_mission].jugadores[pJ_enemigo->color] == pJ_enemigo->color)
                        return true;

                // Por continente
                if (g_missions[c::g_game.secret_mission].continents[pP->continente] > 0)
                        return true;

                // Por islas
                /*if (g_missions[i].numjug == numjug && g_missions[i].limitrofes > 0 && pP->isIsla == 1)
                        return true; */

        //}

        return false;
}

/**
 * @fn int ai_puntaje_attack( int p )
 * Evalua los puntos que tiene el country para atacar
 * y dice al country que convendria atacar
 */
TEG_STATUS ai_puntaje_atacar(int country)
{
	int i;
	int p=0;
	int p_tmp;
	int dst=-1;

	for(i=0; i<COUNTRIES_CANT; i++) {
		if(countries_eslimitrofe(country, i) && g_countries[i].numjug != c::WHOAMI()) {
			p_tmp = ai_puntaje_atacar_country(country, i);

			/* son negativos estos valores, por eso sumo */
			p_tmp += ai_puntaje_atacar_warning(country);

                        // Verifico si está en mi objetivo
                        PCOUNTRY pP = &g_countries[country];
                        if ( country_inmission( pP, c::WHOAMI() ) == true){
                                p_tmp += 10;
                                fprintf(stderr, ("País: %s, Jugador: %i. Puntaje +10.\n"),g_countries[i].name,c::WHOAMI() );
                        }
                        else {
                                fprintf(stderr, ("País: %s, Jugador: %i. Puntaje nada.\n"),g_countries[i].name,c::WHOAMI() );
                        }

			if(p_tmp > p) {
				p = p_tmp;
				dst = i;
			}
		}
	}

	/* return the best candidate */
	if(dst >=0) {
		ai_puntaje[ country ] = p;
		attack_dst[ country ] = dst;
	}

	return TEG_STATUS_SUCCESS;
}

TEG_STATUS ai_turno()
{
	int i;
	int j;

	ai_puntaje_clean();
	for(i=0; i<COUNTRIES_CANT; i++) {
		if(g_countries[i].numjug == c::WHOAMI() && g_countries[i].ejercitos > 1) {
			ai_puntaje_atacar(i);
		}
	}
	ai_puntaje_sort_for_attack();

	i = ai_sorted[0];
	j = attack_dst[i];
	if(ai_puntaje[i] > 0) {

		c::attack_init();
		c::attack_click(&g_countries[i]);
		c::attack_click(&g_countries[j]);
		return TEG_STATUS_SUCCESS;
	}
	return TEG_STATUS_ERROR;
}

TEG_STATUS __ai_reagrupe(int  p, int cant)
{
	int i;
	int own = ai_own_continent(g_countries[p].continente);

	if(own) {
		int new_cant = cant;

		/* try to defend, undefended frontiers */
		for(i=0; i<COUNTRIES_CANT; i++) {
			if(g_countries[i].numjug != c::WHOAMI() &&
			        countries_eslimitrofe(i, p) &&
			        g_countries[i].ejercitos > g_countries[p].ejercitos) {

				c::reagrupe_out(p, i, cant);
				return TEG_STATUS_SUCCESS;
			}
		}

		/* I will leave 3 armies in border country of the continent */
		if(g_countries[p].ejercitos - g_countries[p].ejer_reagrupe - cant < 3) {
			new_cant -= 2;
		}

		for(i=0; i<COUNTRIES_CANT && (new_cant>0); i++) {
			if(g_countries[i].numjug == c::WHOAMI() && countries_eslimitrofe(p, i) &&
			        g_countries[i].continente != g_countries[p].continente) {

				c::reagrupe_out(p, i, new_cant);
				return TEG_STATUS_SUCCESS;
			}
		}
	}

	/*... si falla, los muevo a una frontera */
	for(i=0; i<COUNTRIES_CANT; i++) {
		if(g_countries[i].numjug == c::WHOAMI() && countries_eslimitrofe(p, i) &&
		        g_countries[i].continente == g_countries[p].continente) {

			if(ai_is_country_border(i)) {
				c::reagrupe_out(p, i, cant);
				return TEG_STATUS_SUCCESS;
			}
		}
	}

	/*... y si no hay frontera lo mando al 1ro que tenga a mano */
	for(i=0; i<COUNTRIES_CANT; i++) {
		if(g_countries[i].numjug == c::WHOAMI() && countries_eslimitrofe(p, i) &&
		        g_countries[i].continente == g_countries[p].continente) {

			c::reagrupe_out(p, i, cant);
			return TEG_STATUS_SUCCESS;
		}
	}

	return TEG_STATUS_ERROR;
}

TEG_STATUS ai_reagrupe()
{
	int i, p;
	c::reagrupe_init();

	for(i=0; i < COUNTRIES_CANT ; i++) {
		if(g_countries[i].numjug == c::WHOAMI()) {
			if(ai_many_country_enemigo(i) == 0) {
				p = g_countries[i].ejercitos - g_countries[i].ejer_reagrupe;

				if(p < 2) {
					continue;
				}

				__ai_reagrupe(i, p-1);
			}
		}
	}
	return TEG_STATUS_SUCCESS;
}

TEG_STATUS ai_tropas(int src, int dst, int cant)
{
	int i;
	int c=0;

	ai_puntaje_clean();
	ai_fichas_calc_puntaje(src);
	ai_fichas_calc_puntaje(dst);

	for(i=0; i<cant; i++) {
		if(ai_puntaje[dst] > ai_puntaje[src] + i) {
			c++;
		}
	}

	if(c > 0) {
		c::out_tropas(src, dst, c);
	}

	return TEG_STATUS_SUCCESS;
}

TEG_STATUS ai_puedocanje(int *p1, int *p2, int *p3)
{
	return c::canje_puedo(p1, p2, p3);
}

}
