/*
 * Copyright (C) 2015 Martin Schröder <mkschreder.uk@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 2.1
 * as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#pragma once

#include <inttypes.h>

struct ubus_socket_api; 
typedef const struct ubus_socket_api** ubus_socket_t; 

ubus_socket_t json_socket_new(void); 

/*
struct json_socket *json_socket_new(void); 
void json_socket_delete(struct json_socket **self); 

void json_socket_init(struct json_socket *self); 
void json_socket_destroy(struct json_socket *self); 

int json_socket_listen(struct json_socket *self, const char *path); 
int json_socket_connect(struct json_socket *self, const char *path, uint32_t *id);

#define UBUS_TARGET_PEER (0)

int json_socket_send(struct json_socket *self, int32_t peer, int type, uint16_t serial, struct blob_field *msg); 
static inline void json_socket_on_message(struct json_socket *self, json_socket_data_cb_t cb){
	self->on_message = cb; 
}
static inline void json_socket_on_client_connected(struct json_socket *self, json_socket_client_cb_t cb){
	self->on_client_connected = cb; 
}

void  json_socket_poll(struct json_socket *self, int timeout); 

static inline void json_socket_set_userdata(struct json_socket *self, void *ptr){
	self->user_data = ptr; 
}
static inline void* json_socket_get_userdata(struct json_socket *self) { return self->user_data; }
*/
