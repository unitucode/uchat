CLIENT = uchat
SERVER = chat_server

EMPTY = 
SPACE = $(EMPTY) $(EMPTY)
VPATH = $(subst $(SPACE), :, $(SRCD_UTILS) $(SRCD_SERVER) $(SRCD_CLIENT))

OBJD = obj
SRCD = src
INCD = inc


SRCD_CLIENT = $(addprefix $(SRCD)/, client)
SRCD_SERVER = $(addprefix $(SRCD)/, server server/client_handler)
SRCD_UTILS = $(addprefix $(SRCD)/, utils utils/wrappers utils/list utils/loger utils/protocol)


INCD_CLIENT = $(addprefix $(INCD)/, client_inc)
INCD_SERVER = $(addprefix $(INCD)/, server_inc)
INCD_UTILS = $(addprefix $(INCD)/, utils_inc)


SRC_CLIENT = $(foreach dir,$(SRCD_CLIENT), $(wildcard $(dir)/*.c))
SRC_SERVER = $(foreach dir,$(SRCD_SERVER), $(wildcard $(dir)/*.c))
SRC_UTILS = $(foreach dir,$(SRCD_UTILS), $(wildcard $(dir)/*.c))


OBJS_CLIENT = $(addprefix $(OBJD)/, $(notdir $(SRC_CLIENT:%.c=%.o)))
OBJS_SERVER = $(addprefix $(OBJD)/, $(notdir $(SRC_SERVER:%.c=%.o)))
OBJS_UTILS = $(addprefix $(OBJD)/, $(notdir $(SRC_UTILS:%.c=%.o)))


CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic)
CPPFLAGS = -I$(INCD_UTILS)
CC = clang

all: $(CLIENT) $(SERVER)

$(CLIENT): CPPFLAGS += -I$(INCD_CLIENT)
$(SERVER): CPPFLAGS += -I$(INCD_SERVER)

$(CLIENT): $(OBJS_CLIENT) $(OBJS_UTILS)
$(SERVER): $(OBJS_SERVER) $(OBJS_UTILS)

$(SERVER) $(CLIENT):
	@$(CC) -o $@ $^
	@printf "\x1b[32;1m$@ created\x1b[0m\n"

$(OBJS_CLIENT) $(OBJS_UTILS) $(OBJS_SERVER): obj/%.o: %.c | $(OBJD)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	@printf "\x1b[32mcompiled: \x1b[0m$<\n"

$(OBJD):
	@mkdir -p $@

uninstall: clean
	@rm -rf $(CLIENT)
	@printf "\x1b[34;1mdeleted $(CLIENT)\x1b[0m\n"
	@rm -rf $(SERVER)
	@printf "\x1b[34;1mdeleted $(SERVER)\x1b[0m\n"

clean:
	@rm -rf $(OBJD)
	@printf "\x1b[34;1mdeleted $(OBJD)\x1b[0m\n"

reinstall: uninstall all
