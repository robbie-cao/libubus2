BUILD_DIR=build_dir
STATIC_LIB=libubus2.a
SHARED_LIB=libubus2.so 
SOURCE=\
	src/ubus_context.c \
	src/ubus_method.c \
	src/ubus_object.c \
	src/ubus_method.c \
	src/ubus_id.c \
	src/ubus_peer.c \
	src/ubus_request.c \
	src/ubus_server.c \
	src/ubus_socket.c \
	src/libubus2.c 

INSTALL_PREFIX:=/usr

OBJECTS=$(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(SOURCE)))

CFLAGS+=-g -Isrc -Wall -Werror -std=gnu99
LDFLAGS+=-lblobpack -lusys -lutype -ljson-c -ldl

all: $(BUILD_DIR) $(STATIC_LIB) $(SHARED_LIB) cli-example socket-example client-example threads-example

#extras: 
#	make -C lua 

.PHONY: extras

$(BUILD_DIR): 
	mkdir -p $(BUILD_DIR)

$(SHARED_LIB): $(OBJECTS) 
	$(CC) -shared -fPIC -Wl,--no-undefined -o $@ $^ $(LDFLAGS) 

$(STATIC_LIB): $(OBJECTS)
	$(AR) rcs -o $@ $^

threads-example: examples/threads.o $(OBJECTS)
	$(CC) -I$(shell pwd) $(CFLAGS) -o $@ examples/threads.o $(LDFLAGS) -L$(BUILD_DIR) -lubus2 -lpthread

client-example: examples/client.o $(OBJECTS)
	$(CC) -I$(shell pwd) $(CFLAGS) -o $@ examples/client.o $(LDFLAGS) -L$(BUILD_DIR) -lubus2 -lpthread

socket-example: examples/socket.o $(OBJECTS)
	$(CC) -I$(shell pwd) $(CFLAGS) -o $@ examples/socket.o $(LDFLAGS) -L$(BUILD_DIR) -lubus2 -lpthread

cli-example: examples/cli.o $(OBJECTS)
	$(CC) -I$(shell pwd) $(CFLAGS) -o $@ examples/cli.o $(LDFLAGS) -L$(BUILD_DIR) -lubus2 -lpthread


$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -fPIC $(CFLAGS) -c $^ -o $@

install: 
	mkdir -p $(INSTALL_PREFIX)/lib/
	mkdir -p $(INSTALL_PREFIX)/include/libubus2/
	cp -R $(SHARED_LIB) $(STATIC_LIB) $(INSTALL_PREFIX)/lib
	cp -R src/*.h $(INSTALL_PREFIX)/include/libubus2/
clean: 
	rm -rf build_dir
	rm -f examples/*.o
