/* Tenes Empanadas Graciela
 *
 * Copyright (C) 2001 Ricardo Quesada
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

#include "xml_support.h"

#include <assert.h>

xmlNodePtr xml_get_element_children( xmlNodePtr cur )
{
	xmlNodePtr ret;

	ret = cur->xmlChildrenNode;

	while( ret && ret->type != XML_ELEMENT_NODE )
		ret = ret->next;

	return ret;
}

xmlNodePtr xml_get_element_next( xmlNodePtr cur )
{
	xmlNodePtr ret;

	ret = cur->next;

	while( ret && ret->type != XML_ELEMENT_NODE )
		ret = ret->next;

	return ret;
}

void add_numeric_attribute(xmlNodePtr node, char const* name, int number)
{
	char buf[22]; // enough for a 64bit integer with sign and zero terminator
	int res = snprintf(buf, sizeof(buf), "%d", number);
	assert((res > 0) && (res < sizeof(buf)));
	xmlSetProp(node, (xmlChar*)name, (xmlChar*)buf );
}
