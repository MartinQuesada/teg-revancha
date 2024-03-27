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

#include "country.h"

#include <stdexcept>

#include "fcintl.h"

COUNTRY g_countries[] = {
        /* AMERICA DEL SUR */
        COUNTRY{0, N_("Argentina"), CONTINENTE_AMERICASUR, TARJETA_NULL_SUPERTARJETA ,0},
        COUNTRY{1, N_("Brazil"), CONTINENTE_AMERICASUR, TARJETA_NULL_GLOBO ,0},
        COUNTRY{2, N_("Chile"), CONTINENTE_AMERICASUR, TARJETA_NULL_GLOBO ,0},
        COUNTRY{3, N_("Colombia"), CONTINENTE_AMERICASUR, TARJETA_NULL_GLOBO ,0},
        COUNTRY{4, N_("Paraguay"), CONTINENTE_AMERICASUR, TARJETA_NULL_CANION ,0},
        COUNTRY{5, N_("Uruguay"), CONTINENTE_AMERICASUR, TARJETA_NULL_CANION ,0},
        COUNTRY{6, N_("Bolivia"), CONTINENTE_AMERICASUR, TARJETA_NULL_GLOBO ,0},
        COUNTRY{7, N_("Venezuela"), CONTINENTE_AMERICASUR, TARJETA_NULL_CANION ,0},

        /* AMERICA DEL NORTE */
        COUNTRY{ 8, N_("California"), CONTINENTE_AMERICANORTE, TARJETA_NULL_GLOBO ,0},
        COUNTRY{ 9, N_("Las Vegas"), CONTINENTE_AMERICANORTE, TARJETA_NULL_SUPERTARJETA ,0},
        COUNTRY{10, N_("Oregon"), CONTINENTE_AMERICANORTE, TARJETA_NULL_CANION ,0},
        COUNTRY{11, N_("New York"), CONTINENTE_AMERICANORTE, TARJETA_NULL_CANION ,0},
        COUNTRY{12, N_("Alaska"), CONTINENTE_AMERICANORTE, TARJETA_NULL_COMODIN ,0},
        COUNTRY{13, N_("Florida"), CONTINENTE_AMERICANORTE, TARJETA_NULL_GALEON ,0},
        COUNTRY{14, N_("Canada"), CONTINENTE_AMERICANORTE, TARJETA_NULL_GLOBO ,0},
        COUNTRY{15, N_("Terranova"), CONTINENTE_AMERICANORTE, TARJETA_NULL_CANION ,0},
        COUNTRY{16, N_("Labrador"), CONTINENTE_AMERICANORTE, TARJETA_NULL_GALEON ,1},
        COUNTRY{17, N_("Greenland"), CONTINENTE_AMERICANORTE, TARJETA_NULL_GALEON ,1},
        COUNTRY{18, N_("Chicago"), CONTINENTE_AMERICANORTE, TARJETA_NULL_GLOBO ,0},
        COUNTRY{19, N_("Victoria Island"), CONTINENTE_AMERICANORTE, TARJETA_NULL_GALEON ,1},

        /* AFRICA */
        COUNTRY{20, N_("Somalia"), CONTINENTE_AFRICA, TARJETA_NULL_COMODIN ,0},
        COUNTRY{21, N_("Sahara"), CONTINENTE_AFRICA, TARJETA_NULL_CANION ,0},
        COUNTRY{22, N_("Nigeria"), CONTINENTE_AFRICA, TARJETA_NULL_CANION ,0},
        COUNTRY{23, N_("Etiopia"), CONTINENTE_AFRICA, TARJETA_NULL_GLOBO ,0},
        COUNTRY{24, N_("Egypt"), CONTINENTE_AFRICA, TARJETA_NULL_GLOBO ,0},
        COUNTRY{25, N_("Madagascar"), CONTINENTE_AFRICA, TARJETA_NULL_GALEON ,0},
        COUNTRY{26, N_("South Africa"), CONTINENTE_AFRICA, TARJETA_NULL_CANION ,0},
        COUNTRY{27, N_("Mozambique"), CONTINENTE_AFRICA, TARJETA_NULL_SUPERTARJETA ,0},

        /* OCEANIA */
        COUNTRY{28, N_("Australia"), CONTINENTE_OCEANIA, TARJETA_NULL_GLOBO ,0},
        COUNTRY{29, N_("Philippines"), CONTINENTE_OCEANIA, TARJETA_NULL_GLOBO ,1},
        COUNTRY{30, N_("Tonga"), CONTINENTE_OCEANIA, TARJETA_NULL_CANION ,1},
        COUNTRY{31, N_("Sumatra"), CONTINENTE_OCEANIA, TARJETA_NULL_CANION ,1},
        COUNTRY{32, N_("Tasmania"), CONTINENTE_OCEANIA, TARJETA_NULL_CANION ,1},
        COUNTRY{33, N_("New Zealand"), CONTINENTE_OCEANIA, TARJETA_NULL_CANION ,1},

        /* EUROPA */
        COUNTRY{34, N_("Spain"), CONTINENTE_EUROPA, TARJETA_NULL_GLOBO ,0},
        COUNTRY{35, N_("France"), CONTINENTE_EUROPA, TARJETA_NULL_GALEON ,0},
        COUNTRY{36, N_("Germany"), CONTINENTE_EUROPA, TARJETA_NULL_COMODIN ,0},
        COUNTRY{37, N_("Italy"), CONTINENTE_EUROPA, TARJETA_NULL_GALEON ,0},
        COUNTRY{38, N_("Poland"), CONTINENTE_EUROPA, TARJETA_NULL_CANION ,0},
        COUNTRY{39, N_("Croatia"), CONTINENTE_EUROPA, TARJETA_NULL_GLOBO ,0},
        COUNTRY{40, N_("Serbia"), CONTINENTE_EUROPA, TARJETA_NULL_CANION ,0},
        COUNTRY{41, N_("Great Britain"), CONTINENTE_EUROPA, TARJETA_NULL_GALEON ,1},
        COUNTRY{42, N_("Iceland"), CONTINENTE_EUROPA, TARJETA_NULL_GALEON ,1},
        COUNTRY{43, N_("Ireland"), CONTINENTE_EUROPA, TARJETA_NULL_GLOBO ,1},
        COUNTRY{44, N_("Albania"), CONTINENTE_EUROPA, TARJETA_NULL_COMODIN ,0},
        COUNTRY{45, N_("Ukraine"), CONTINENTE_EUROPA, TARJETA_NULL_SUPERTARJETA ,0},
        COUNTRY{46, N_("Belarus"), CONTINENTE_EUROPA, TARJETA_NULL_GLOBO ,0},
        COUNTRY{47, N_("Finland"), CONTINENTE_EUROPA, TARJETA_NULL_GALEON ,0},
        COUNTRY{48, N_("Norway"), CONTINENTE_EUROPA, TARJETA_NULL_CANION ,0},
        COUNTRY{49, N_("Portugal"), CONTINENTE_EUROPA, TARJETA_NULL_CANION ,0},

        /* ASIA */
        COUNTRY{50, N_("Arabia"), CONTINENTE_ASIA, TARJETA_NULL_GLOBO ,0},
        COUNTRY{51, N_("Israel"), CONTINENTE_ASIA, TARJETA_NULL_GALEON ,0},
        COUNTRY{52, N_("Turkey"), CONTINENTE_ASIA, TARJETA_NULL_CANION ,0},
        COUNTRY{53, N_("India"), CONTINENTE_ASIA, TARJETA_NULL_GALEON ,0},
        COUNTRY{54, N_("Malaysia"), CONTINENTE_ASIA, TARJETA_NULL_GALEON ,0},
        COUNTRY{55, N_("Iran"), CONTINENTE_ASIA, TARJETA_NULL_GALEON ,0},
        COUNTRY{56, N_("Irak"), CONTINENTE_ASIA, TARJETA_NULL_GALEON ,0},
        COUNTRY{57, N_("China"), CONTINENTE_ASIA, TARJETA_NULL_GLOBO ,0},
        COUNTRY{58, N_("Russia"), CONTINENTE_ASIA, TARJETA_NULL_CANION ,0},
        COUNTRY{59, N_("Siberia"), CONTINENTE_ASIA, TARJETA_NULL_CANION ,0},
        COUNTRY{60, N_("Chuckchi"), CONTINENTE_ASIA, TARJETA_NULL_GLOBO ,0},
        COUNTRY{61, N_("Chechenia"), CONTINENTE_ASIA, TARJETA_NULL_SUPERTARJETA ,0},
        COUNTRY{62, N_("Vietnam"), CONTINENTE_ASIA, TARJETA_NULL_CANION ,0},
        COUNTRY{63, N_("Katchatka"), CONTINENTE_ASIA, TARJETA_NULL_GALEON ,0},
        COUNTRY{64, N_("Japan"), CONTINENTE_ASIA, TARJETA_NULL_GALEON ,1},
        COUNTRY{65, N_("Korea"), CONTINENTE_ASIA, TARJETA_NULL_GLOBO ,0},

        /* AMERICA CENTRAL */
        COUNTRY{66, N_("Nicaragua"), CONTINENTE_AMERICACENTRO, TARJETA_NULL_GALEON ,0},
        COUNTRY{67, N_("El Salvador"), CONTINENTE_AMERICACENTRO, TARJETA_NULL_GLOBO ,0},
        COUNTRY{68, N_("Honduras"), CONTINENTE_OCEANIA, TARJETA_NULL_GALEON ,0},
        COUNTRY{69, N_("Mexico"), CONTINENTE_AMERICACENTRO, TARJETA_NULL_GALEON ,0},
        COUNTRY{70, N_("Cuba"), CONTINENTE_AMERICACENTRO, TARJETA_NULL_GLOBO ,1},
        COUNTRY{71, N_("Jamaica"), CONTINENTE_AMERICACENTRO, TARJETA_NULL_GALEON, 1},
};
constexpr std::size_t COUNTRIES_TOT = std::extent<decltype(g_countries)>::value;

COUNTRY::COUNTRY()
	: COUNTRY(-1, "INVALID", CONTINENTE_LAST, TARJTIPO(0), 0)
{
}

COUNTRY::COUNTRY(CountryId id, char const* name, CONTINENTE continente, TARJTIPO kindOfCard, bool esisla)
	: id{id}
	, name{name}
	, continente{continente}
	, tarjeta{kindOfCard, -1, false, id}
	, esisla{esisla}
{
}

#include "limitrof.h"

/* returns true if country a and b are border */
bool countries_eslimitrofe(int a, int b)
{
	if(a > b) {
		return(mat_ady[b][a]==1);
	} else {
		return(mat_ady[a][b]==1);
	}
}

/* returns the quantity of border contries that a country has */
int countries_cantlimitrofes( int p )
{
        int i;
        int cant=0;

        if(p < 0 || p >= COUNTRIES_CANT )
                return -1;

        for(i=0; i < COUNTRIES_CANT; i++ ) {
                if(  countries_eslimitrofe( p, i ) )
                        cant++;
        }

        return cant;
}

/* Initializes country p */
void countries_initcountry(PCOUNTRY p)
{
	p->numjug=-1;
	p->ejercitos=0;
	tarjeta_inittarj(&p->tarjeta);
	p->selected = COUNTRY_SELECT_NONE;
}

/* initializes all the countries */
void countries_init()
{
	for(size_t i=0; i<COUNTRIES_CANT; i++) {
		countries_initcountry(&g_countries[i]);
	}
}

/* says if a country is free or not */
bool country_libre(int i)
{
	return(g_countries[i].numjug == -1);
}

/* returns the name of a country */
char const * countries_get_name(int i)
{
	if(i >= 0 && i < COUNTRIES_CANT) {
		return _(g_countries[i].name);
	} else {
		return _("Unknown");
	}
}

bool countrynumber_is_valid(int country_number)
{
	return (country_number >= 0) && (country_number < COUNTRIES_CANT);
}

void countries_map(CountryMapFn fn)
{
	std::for_each(std::begin(g_countries), std::end(g_countries), fn);
}

void countries_map(int player, CountryMapFn fn)
{
	std::for_each(std::begin(g_countries), std::end(g_countries),
	[player, fn](COUNTRY & c) {
		if(player == c.numjug) {
			fn(c);
		}
	});
}

void countries_map_int(int player, InterruptableCountryMapFn fn)
{
	for(COUNTRY& country: g_countries) {
		if(player == country.numjug) {
			if(!fn(country)) {
				break;
			}
		}
	}
}

COUNTRY& COUNTRY_FROM_TARJETA(TARJETA& tarjeta)
{
	if(!countrynumber_is_valid(tarjeta.country)) {
		throw std::runtime_error("Can't find the country for this card, because the country number is invalid." + std::to_string(tarjeta.country));
	}

	return g_countries[tarjeta.country];
}

/* says if a country is locked or not
   j = jugador que tiene el country */
bool country_esbloqueado ( PCOUNTRY p, int j )
{
        int jugador_bloqueo = -1;
        int paises_bloqueantes = 0;
        int i;

        for( i=0; i<COUNTRIES_CANT; i++ )
        {
                if( g_countries[i].ejercitos >=2 && g_countries[i].numjug != j && countries_eslimitrofe( p->id, i ) && p->id != i )
                {
                        if( g_countries[i].numjug == jugador_bloqueo )
                        {
                                //fprintf(stderr, "Pais: %s. Bloqueantes: %i.\n",g_countries[i].name, paises_bloqueantes );
                                paises_bloqueantes++;
                        }

                        // Si es el primer país que verifico asigno el usuario

                        if( jugador_bloqueo == -1 )
                        {
                                //fprintf(stderr, "Pais (-1): %s. Bloqueantes: %i.\n",g_countries[i].name, paises_bloqueantes );
                                paises_bloqueantes++;
                                jugador_bloqueo=g_countries[i].numjug;
                        }
                }
        }

        //fprintf(stderr, _("Pais: %s, Bloqueantes: %i, Limitrofes: %i.\n"), p->name, paises_bloqueantes, countries_cantlimitrofes(p->id) );

        return( paises_bloqueantes == countries_cantlimitrofes ( p->id ) && paises_bloqueantes > 2 );
}
