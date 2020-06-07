CLIENT = uchat
SERVER = uchat_server
UTILS = libutils
CJSON = libcjson
SQLITE = libsqlite3

CLIENTD = client
SERVERD = server
UTILSD = utils
CJSOND = libraries/libraries/cjson
SQLITED = libraries/libraries/sqlite3

CLIENTO = $(CLIENTD)/$(CLIENT)
SERVERO = $(SERVERD)/$(SERVER)
UTILSO = $(UTILSD)/$(UTILS).a
CJSONO = libraries/lib/$(CJSON).a
SQLITEO = libraries/lib/$(SQLITE).a

all: $(SQLITE) $(CJSON) $(UTILS) $(CLIENT) $(SERVER)

$(SQLITE): $(SQLITEO)
$(CJSON): $(CJSONO)
$(UTILS): $(UTILSO)
$(CLIENT): $(CLIENTO)
$(SERVER): $(SERVERO)

$(SQLITEO): $(SQLITED)
$(CJSONO): $(CJSOND)
$(UTILSO): $(UTILSD)
$(CLIENTO): $(CLIENTD)
$(SERVERO): $(SERVERD)

$(CLIENTO) $(SERVERO):
	@make -sC $<
	@cp $@ .

$(SQLITEO) $(CJSONO) $(UTILSO):
	@make -sC $<

uninstall: clean
	@make -sC $(SQLITED) $@
	@make -sC $(CJSOND) $@
	@make -sC $(UTILSD) $@
	@make -sC $(CLIENTD) $@
	@make -sC $(SERVERD) $@

clean:
	@rm -rf $(CLIENT)
	@rm -rf $(SERVER)
	@make -sC $(SQLITED) $@
	@make -sC $(CJSOND) $@
	@make -sC $(UTILSD) $@
	@make -sC $(CLIENTD) $@
	@make -sC $(SERVERD) $@

reinstall: uninstall all

.PHONY: all uninstall clean reinstall $(CLIENTO) $(SERVERO) $(SQLITEO) $(CJSONO) $(UTILSO)
