CLIENT = uchat
SERVER = uchat_server

CLIENTD = $(CLIENT)_work
SERVERD = $(SERVER)_work

LIBRARIES = libraries
LIBRARIESD = $(LIBRARIES)/$(LIBRARIES)/
LIBSD = $(addprefix $(LIBRARIES)/, lib include)

CJSOND = $(LIBRARIESD)cjson
CJSON = libcjson
CJSON_LIB = $(LIBRARIES)/lib/$(CJSON).a
INCD_LIBS = $(LIBRARIES)/include
LIBS = $(LIBRARIES)/lib

EMPTY = 
SPACE = $(EMPTY) $(EMPTY)
VPATH = $(subst $(SPACE), :, $(SRCD_UTILS) $(SRCD_SERVER) $(SRCD_CLIENT))

OBJD = obj
SRCD = src
INCD = inc


SRCD_CLIENT = $(addprefix $(SRCD)/, client client/gui)
SRCD_SERVER = $(addprefix $(SRCD)/, server server/client_handler)
SRCD_UTILS = $(addprefix $(SRCD)/, utils utils/wrappers utils/list \
utils/config /utils/logger utils/protocol utils/ssl utils/database)


INCD_CLIENT = $(addprefix -I$(INCD)/, client_inc)
INCD_SERVER = $(addprefix -I$(INCD)/, server_inc)
INCD_UTILS = $(addprefix -I$(INCD)/, utils_inc utils_inc/protocol)


SRC_CLIENT = $(foreach dir, $(SRCD_CLIENT), $(wildcard $(dir)/*.c))
SRC_SERVER = $(foreach dir, $(SRCD_SERVER), $(wildcard $(dir)/*.c))
SRC_UTILS = $(foreach dir, $(SRCD_UTILS), $(wildcard $(dir)/*.c))


OBJS_CLIENT = $(addprefix $(OBJD)/, $(notdir $(SRC_CLIENT:%.c=%.o)))
OBJS_SERVER = $(addprefix $(OBJD)/, $(notdir $(SRC_SERVER:%.c=%.o)))
OBJS_UTILS = $(addprefix $(OBJD)/, $(notdir $(SRC_UTILS:%.c=%.o)))

CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic)
CPPFLAGS += $(INCD_UTILS) -I$(INCD_LIBS) -I/usr/local/opt/openssl/include -D_GNU_SOURCE
LDLIBS += -lssl -lcjson -lcrypto -lsqlite3 -lpthread -L/usr/local/opt/openssl/lib -L$(LIBS)
CC = clang
GTK_INC = -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 \
-I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 \
-I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 \
-I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 \
-I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 \
-I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid \
-I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 \
-I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 \
-I/usr/lib/x86_64-linux-gnu/glib-2.0/include
GTK_LIBS = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 \
-lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 \
-rdynamic

all: $(LIBRARIES) $(SERVER) $(CLIENT)

$(LIBRARIES): $(CJSON)
	
$(CJSON): $(CJSON_LIB)

$(CJSON_LIB): | $(LIBSD)
	@make -sC $(CJSOND)

$(LIBSD):
	@mkdir -p $(LIBSD)

$(CLIENT): CPPFLAGS += $(INCD_CLIENT) $(GTK_INC) -DMX_CLIENT='"$(CLIENTD)"'
$(CLIENT): LDLIBS += $(GTK_LIBS)
$(SERVER): CPPFLAGS += $(INCD_SERVER) -DMX_SERVER='"$(SERVERD)"'

$(CLIENT): $(OBJS_CLIENT) $(OBJS_UTILS)
$(SERVER): $(OBJS_SERVER) $(OBJS_UTILS)

$(SERVER) $(CLIENT):
	@$(CC) -g -o $@ $^ $(LDLIBS)
	@printf "\033[32;1m$@ created\033[0m\n"


$(OBJS_CLIENT) $(OBJS_UTILS) $(OBJS_SERVER): obj/%.o: %.c | $(OBJD)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -g -c -o $@ $<
	@printf "\033[32mcompiled: \033[0m$(notdir $<)\n"

$(OBJD):
	@mkdir -p $@
	@printf "\033[32;1m$@ created\033[0m\n"

uninstall: clean
	@rm -rf $(CLIENT)
	@printf "\033[34;1mdeleted $(CLIENT)\033[0m\n"
	@rm -rf $(SERVER)
	@printf "\033[34;1mdeleted $(SERVER)\033[0m\n"
	@make -sC $(CJSOND) $@

clean:
	@rm -rf $(OBJD)
	@printf "\033[34;1mdeleted $(OBJD)\033[0m\n"
	@make -sC $(CJSOND) $@
	@rm -rf $(LIBSD)

reinstall: uninstall all

.PHONY: all uninstall clean reinstall
