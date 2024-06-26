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
/*
 * messages that the robot might say
 */

#include <filesystem>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "fcintl.h"
#include "protocol.h"
#include "client.h"
#include "ai_msg.h"

namespace teg::robot
{

aimsg_t mensajes_hi[] = {
	{ N_("Hi %s"), 1},
	{ N_("Good luck %s"), 1},
	{ N_("How are you %s ?"), 1},
	{ N_("Welcome back %s!"), 1},
	{ N_("%s, I'll be the winner"), 1},
	{ N_("Hey %s!"), 1},
	{ "Ciao %s", 1},
	{ "Hola %s", 1},
};
#define NR_MSGS_HI ( sizeof(mensajes_hi) / sizeof(mensajes_hi[0]))

aimsg_t mensajes_bye[] = {
	{ N_("Goodbye %s"), 1},
	{ N_("%s, you need to improve you game"), 1},
	{ N_("%s, You really dont know how to play!"), 1 },
	{ N_("%s Better luck for the next time"), 1 },
	{ N_("%s, try to improve your game"), 1 },
};
#define NR_MSGS_BYE ( sizeof(mensajes_bye) / sizeof(mensajes_bye[0]))

aimsg_t mensajes_misc[] = {
	{ N_("%s, Do you have a sister ?"), 1},
	{ N_("I love this game"), 0 },
	{ N_("%s, I cant believe it!"), 1 },
	{ N_("%s, Do you have Lewinsky's phone ?"), 1 },
	{ N_("Does anyone speak Speranto ?"), 0},
	{ N_("%s, You play very well"), 0},
	{ N_("Thanks"), 0 },
	{ N_("mmm..."), 0 },
	{ N_("%s, Are you a robot ?"), 1 },
	{ N_("Geronimoooooo"), 0 },
	{ N_("I'm a bit tired"), 0 },
	{ N_("I'm hungry"), 0 },
	{ N_("Who wants an Empanada ?"), 0 },
	{ N_("I like whistling"), 0 },
	{ N_("What is a good strategy to win this game?"), 0 },
	{ N_("%s, Were you here last night ?"), 1 },
	{ N_("nod"), 0 },
	{ N_("What?"), 0 },
	{ N_(":-)"), 0 },
	{ N_("%s, Do you think so?"), 1 },
	{ N_("%s, What can I say ?"), 1 },
	{ N_("%s, Do you think I'm ugly ?"), 1 },
	{ N_("%s, Do you think I'm pretty ?"), 1 },
	{ N_("%s, Are you pretty ?"), 1 },
	{ N_("%s, Where do you live ?"), 1 },
	{ N_("%s, miauuuuuuuuu"), 1 },

	/* frases que no deben ser traducidas */
	{ "Empanadas sin dientes, para las viejas sin dientes", 0 },
	{ "Se me escapo la tortuga", 0 },
	{ "%s parla tedesco", 1 },
	{ "Alguien ha visto a mi gata?", 0 },
};
#define NR_MSGS_MISC ( sizeof(mensajes_misc) / sizeof(mensajes_misc[0]))

aimsg_t mensajes_answer[] = {
	{ N_("%s, I dont agree"), 1 },
	{ N_("%s, Are you sure what you are saying?"), 1 },
	{ N_("%s, What are you saying"), 1 },
	{ N_("%s, I dont understand you"), 1 },
	{ N_("%s, funny"), 1 },
	{ N_("%s, What?"), 1 },
	{ N_("%s, sure"), 1 },
	{ N_("%s, Are you talking to me?"), 1 },
	{ N_("%s, you make me laugh"), 1 },
	{ N_("%s, you make me laugh"), 1 },
	{ N_("%s, I dont think so"), 1 },
	{ N_("No %s, I dont believe that"), 1 },
	{ N_("Yes, why not ? %s, but are you sure ?"), 1 },
	{ N_("Tomorrow, not today. %s dont get me wrong"), 1 },
};
#define NR_MSGS_ANSWER ( sizeof(mensajes_answer) / sizeof(mensajes_answer[0]))


static char const *names[] = {
	N_("Coca Sarli"),
	N_("Ciccolina"),
	N_("Raton Perez"),
	N_("Geniol"),
	N_("Fantoche"),
	N_("Jirafa"),
	N_("Guaymayen"),
	N_("Lio Messi"),
	N_("Havanna"),
	N_("Shakira"),
	N_("Kun Agüero"),
	N_("Spice Girls"),
	N_("Britney Spears"),
	N_("Cameron Diaz"),
	N_("Betty la fea"),
	N_("Pitufina"),
	N_("Topacio"),
	N_("Batman"),
	N_("Gatubela"),
	N_("La cuca"),
	N_("Bush"),
	N_("Lewinsky"),
	N_("Clinton"),
	N_("Chupete"),
	N_("Gaturro"),
	N_("Mr.President"),
	N_("Batistuta"),
	N_("Perla"),
	N_("Dibu Martínez"),
	N_("Pele"),
	N_("Comanche"),
	N_("Tehuelche"),
	N_("Pampita"),
	N_("Pampa"),
	N_("Pamela"),
};
#define NR_NAMES ( sizeof(names) / sizeof(names[0]))


TEG_STATUS ai_out_mensaje(int r, char const *format, ...)
{
	va_list args;
	char buf[PROT_MAX_LEN];
	int i = random_between(0, r-1);

	if(i > 3) {
		return TEG_STATUS_ERROR;
	}

	va_start(args, format);
	vsnprintf(buf, sizeof(buf) -1, format, args);

	buf[ sizeof(buf) -1 ] = 0;

	va_end(args);

	return ::teg::client::out_mensaje(buf);
}

TEG_STATUS ai_msg(int type, char const *name)
{
	int i;
	char dst_name[max_playername_length];

	if(name) {
		strncpy(dst_name, name, sizeof(dst_name)-1);
		dst_name[sizeof(dst_name)-1]=0;
	} else {
		i = random_between(0, NR_NAMES-1);
		strncpy(dst_name, _(names[i]), sizeof(dst_name)-1);
		dst_name[sizeof(dst_name)-1]=0;
	}

	switch(type) {
	case AI_MSG_MISC:
		i = random_between(0, NR_MSGS_MISC-1);
		ai_out_mensaje(500, _(mensajes_misc[i].msg), dst_name);
		break;
	case AI_MSG_HI:
		i = random_between(0, NR_MSGS_HI-1);
		ai_out_mensaje(30, _(mensajes_hi[i].msg), dst_name);
		break;
	case AI_MSG_BYE:
		i = random_between(0, NR_MSGS_BYE-1);
		ai_out_mensaje(30, _(mensajes_bye[i].msg), dst_name);
		break;
	case AI_MSG_ANSWER:
		i = random_between(0, NR_MSGS_ANSWER-1);
		ai_out_mensaje(4, _(mensajes_answer[i].msg), dst_name);
		break;
	}
	return TEG_STATUS_SUCCESS;
}

char const * ai_name()
{
	int i = random_between(0, NR_NAMES-1);
	return _(names[i]);
}

TEG_STATUS ai_findname(char const *name)
{
	for(unsigned i=0; i<NR_NAMES; i++) {
		if(strstr(_(name), _(names[i])) != NULL) {
			return TEG_STATUS_SUCCESS;
		}
	}

	return TEG_STATUS_NOTFOUND;
}

}
