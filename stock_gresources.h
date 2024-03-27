#ifndef __RESOURCE_stock_H__
#define __RESOURCE_stock_H__

#include <gio/gio.h>

extern GResource *stock_get_resource (void);

extern void stock_register_resource (void);
extern void stock_unregister_resource (void);

#endif
