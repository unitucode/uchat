# name
CLIENT = uchat

EMPTY = 
SPACE = $(EMPTY) $(EMPTY)
VPATH = VPATH = $(subst $(SPACE), :, $(SRCD))

# client working directory
CLIENT_WD = client/$(CLIENT)_wd

OBJD = obj
INCD_LIBS = -I../libraries/include
LIBD_LIBS = -L../libraries/lib
INCD_CLIENT = -Iinc/
UTILS_INC = -I../utils/inc
UTILS_LIB = ../utils/libutils.a

SRCD = src src/gui src/receiver src/api src/gui/wrappers
INCD = inc
SRCS = $(foreach dir, $(SRCD), $(wildcard $(dir)/*.c))
OBJS = $(addprefix $(OBJD)/, $(notdir $(SRCS:%.c=%.o)))
INCS = $(foreach dir, $(INCD), $(wildcard $(dir)/*.h))

# GTK library flags
# GTK_INC = -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 \
# -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 \
# -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 \
# -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 \
# -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 \
# -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid \
# -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 \
# -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 \
# -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
GTK_LIBS = -rdynamic `pkg-config --cflags --libs gtk+-3.0`

GTK_INC = `pkg-config --cflags gtk+-3.0`
# GTK_LIBS = -L/Users/okhomin/.brew/opt/icu4c/lib

#compilier
CC = clang

CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic)
CPPFLAGS = -DMX_CLIENT='"$(CLIENT_WD)"' $(INCD_CLIENT) -D_GNU_SOURCE \
$(UTILS_INC) $(GTK_INC) $(INCD_LIBS) -I/usr/local/opt/openssl/include
LIBS = $(GTK_LIBS) $(LIBD_LIBS) -L/usr/local/opt/openssl/lib \
-lssl -lcjson -lcrypto -lsqlite3 -lpthread

all: $(CLIENT)

$(CLIENT): $(OBJS)
	$(CC) -o $@ $^ $(UTILS_LIB) $(LIBS)
	@printf "\033[32;1m$@ created\033[0m\n"

$(OBJS): obj/%.o: %.c $(INCS) | $(OBJD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	@printf "\033[32mcompiled: \033[0m$(notdir $<)\n"

$(OBJD):
	@mkdir -p $@
	@printf "\033[32;1m$@ created\033[0m\n"

uninstall: clean
	@rm -rf $(CLIENT)
	@printf "\033[34;1mdeleted $(CLIENT)\033[0m\n"

clean:
	@rm -rf $(OBJD)
	@printf "\033[34;1mdeleted $(OBJD)\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall
