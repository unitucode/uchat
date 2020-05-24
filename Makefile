CLIENT = uchat
SERVER = uchat_server
UTILS = libutils
CJSON = libcjson

CLIENTD = client
SERVERD = server
UTILSD = utils
CJSOND = libraries/libraries/cjson

CLIENTO = $(CLIENTD)/$(CLIENT)
SERVERO = $(SERVERD)/$(SERVER)
UTILSO = $(UTILSD)/$(UTILS).a
CJSONO = libraries/lib/$(CJSON).a

all: $(CJSON) $(UTILS) $(CLIENT) $(SERVER)

$(CJSON): $(CJSONO)
$(UTILS): $(UTILSO)
$(CLIENT): $(CLIENTO)
$(SERVER): $(SERVERO)

$(CJSONO): $(CJSOND)
$(UTILSO): $(UTILSD)
$(CLIENTO): $(CLIENTD)
$(SERVERO): $(SERVERD)

$(CLIENTO) $(SERVERO):
	@make -sC $<
	@cp $@ .

$(CJSONO) $(UTILSO):
	@make -sC $<

uninstall: clean
	@make -sC $(CJSOND) $@
	@make -sC $(UTILSD) $@
	@make -sC $(CLIENTD) $@
	@make -sC $(SERVERD) $@

clean:
	@rm -rf $(CLIENT)
	@rm -rf $(SERVER)
	@make -sC $(CJSOND) $@
	@make -sC $(UTILSD) $@
	@make -sC $(CLIENTD) $@
	@make -sC $(SERVERD) $@

reinstall: uninstall all

.PHONY: all uninstall clean reinstall $(CLIENTO) $(SERVERO) $(CJSONO) $(UTILSO)
