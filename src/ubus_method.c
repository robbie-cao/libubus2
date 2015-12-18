#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED

#include "ubus_method.h"

#include <string.h>

struct ubus_method* ubus_method_new(const char *name, ubus_request_handler_t cb){
	struct ubus_method *self = calloc(1, sizeof(struct ubus_method)); 
	ubus_method_init(self, name, cb); 
	return self; 
}

void ubus_method_delete(struct ubus_method **self){
	ubus_method_destroy(*self); 
	*self = NULL; 
}

void ubus_method_init(struct ubus_method *self, const char *name, ubus_request_handler_t cb){
	if(name) self->name = strdup(name); 
	else self->name = 0; 
	self->handler = cb; 
	blob_buf_init(&self->signature, 0, 0); 
}

void ubus_method_destroy(struct ubus_method *self){
	if(self->name) free(self->name); 
	self->handler = 0; 
}

void ubus_method_add_param(struct ubus_method *self, const char *name, const char *signature){
	blob_offset_t ofs = blob_buf_open_array(&self->signature); 
		blob_buf_put_i8(&self->signature, UBUS_METHOD_PARAM_IN); 
		blob_buf_put_string(&self->signature, name); 
		blob_buf_put_string(&self->signature, signature); 
	blob_buf_close_array(&self->signature, ofs); 
}

void ubus_method_add_return(struct ubus_method *self, const char *name, const char *signature){
	blob_offset_t ofs = blob_buf_open_array(&self->signature); 
		blob_buf_put_i8(&self->signature, UBUS_METHOD_PARAM_OUT); 
		blob_buf_put_string(&self->signature, name); 
		blob_buf_put_string(&self->signature, signature); 
	blob_buf_close_array(&self->signature, ofs); 
}

