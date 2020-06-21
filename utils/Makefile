# name
UTILS = libutils

UTILS_STATIC = $(UTILS).a

EMPTY = 
SPACE = $(EMPTY) $(EMPTY)
VPATH = VPATH = $(subst $(SPACE), :, $(SRCD))

OBJD = obj

INCD_LIBS = -I../libraries/include
LIBD_LIBS = -L../libraries/lib
INCD := inc inc/protocol
INCD_UTILS := $(addprefix -I, $(INCD))
INCS = $(foreach dir, $(INCD), $(wildcard $(dir)/*.h))
GTK_INC = `pkg-config --cflags gtk+-3.0`
GTK_LIBS = -rdynamic `pkg-config --cflags --libs gtk+-3.0`


SRCD := src src/wrappers src/config src/logger \
src/protocol src/ssl src/database src/file_transfer
SRCS = $(foreach dir, $(SRCD), $(wildcard $(dir)/*.c))
OBJS = $(addprefix $(OBJD)/, $(notdir $(SRCS:%.c=%.o)))

#compilier
CC = clang

CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic)
CPPFLAGS = $(INCD_UTILS) $(GTK_INC) \
-D_GNU_SOURCE $(INCD_LIBS) -I/usr/local/opt/openssl/include
LIBS = $(LIBD_LIBS) $(GTK_LIBS) -L/usr/local/opt/openssl/lib \
-lssl -lcjson -lcrypto -lsqlite3 -lpthread

all: $(UTILS)

$(UTILS): $(UTILS_STATIC)

$(UTILS_STATIC): $(OBJS)
	@$(AR) rcs $@ $^ 
	@printf "\033[32;1m$(notdir $@) created\033[0m\n"

$(OBJS): obj/%.o: %.c | $(OBJD)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -g -c -o $@ $<
	@printf "\033[32mcompiled: \033[0m$(notdir $<)\n"

$(OBJD):
	@mkdir -p $@
	@printf "\033[32;1m$@ created\033[0m\n"

uninstall: clean
	@rm -rf $(UTILS_STATIC)
	@printf "\033[34;1mdeleted $(UTILS_STATIC)\033[0m\n"

clean:
	@rm -rf $(OBJD)
	@printf "\033[34;1mdeleted $(OBJD)\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall