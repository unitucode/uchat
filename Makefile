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
LIB_DIR = libraries/include libraries/lib

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

$(SQLITEO) $(CJSONO) $(UTILSO): | $(LIB_DIR)
	@make -sC $<

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

uninstall: clean
	@make -sC $(SQLITED) $@
	@make -sC $(CJSOND) $@
	@make -sC $(UTILSD) $@
	@make -sC $(CLIENTD) $@
	@make -sC $(SERVERD) $@
	@rm -rf $(LIB_DIR)

clean:
	@rm -rf $(CLIENT)
	@rm -rf $(SERVER)
	@make -sC $(SQLITED) $@
	@make -sC $(CJSOND) $@
	@make -sC $(UTILSD) $@
	@make -sC $(CLIENTD) $@
	@make -sC $(SERVERD) $@

reinstall: uninstall all

.PHONY: + uninstall clean reinstall $(CLIENTO) $(SERVERO) $(SQLITEO) $(CJSONO) $(UTILSO)
