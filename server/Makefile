# name
SERVER = uchat_server

EMPTY = 
SPACE = $(EMPTY) $(EMPTY)
VPATH = VPATH = $(subst $(SPACE), :, $(SRCD))

# client working directory
SERVER_WD = server/$(SERVER)_wd

OBJD = obj
INCD_LIBS = -I../libraries/include
LIBD_LIBS = -L../libraries/lib
INCD_SERVER = -Iinc/
UTILS_INC = -I../utils/inc
UTILS_LIB = ../utils/libutils.a
GTK_INC = `pkg-config --cflags gtk+-3.0`
GTK_LIBS = -rdynamic `pkg-config --cflags --libs gtk+-3.0`

SRCD = src src/client_handler src/client_handler/receiver \
src/client_handler/api src/database src/client_handler/api/up_down_load_file
INCD = inc
SRCS = $(foreach dir, $(SRCD), $(wildcard $(dir)/*.c))
OBJS = $(addprefix $(OBJD)/, $(notdir $(SRCS:%.c=%.o)))
INCS = $(foreach dir, $(INCD), $(wildcard $(dir)/*.h))

#compilier
CC = clang

CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic)
CPPFLAGS = -DMX_SERVER='"$(SERVER_WD)"' $(UTILS_INC) \
$(INCD_SERVER) -D_GNU_SOURCE $(INCD_LIBS) $(GTK_INC) -I/usr/local/opt/openssl/include
LIBS = $(LIBD_LIBS) $(GTK_LIBS) -L/usr/local/opt/openssl/lib \
-lssl -lcjson -lcrypto -lsqlite3 -lpthread -ldl

all: $(SERVER)

$(SERVER): $(OBJS)
	@$(CC) -fsanitize=address -g -o $@ $^ $(UTILS_LIB) $(LIBS)
	@printf "\033[32;1m$@ created\033[0m\n"

$(OBJS): obj/%.o: %.c $(INCS) | $(OBJD)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -g -c -o $@ $<
	@printf "\033[32mcompiled: \033[0m$(notdir $<)\n"

$(OBJD):
	@mkdir -p $(SERVER)_wd
	@mkdir -p $@
	@printf "\033[32;1m$@ created\033[0m\n"

uninstall: clean
	@rm -rf $(SERVER)
	@printf "\033[34;1mdeleted $(SERVER)\033[0m\n"

clean:
	@rm -rf $(OBJD)
	@rm -rf $(SERVER_WD)/files
	@rm -rf $(SERVER_WD)/database.db
	@printf "\033[34;1mdeleted $(OBJD)\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall