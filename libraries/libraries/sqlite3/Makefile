SQLITE_OBJ = sqlite3.o
SQLITE_LIBNAME = libsqlite3

CC = gcc -std=c89

#library file extensions
STATIC = a

SQLITE_STATIC = ../../lib/$(SQLITE_LIBNAME).$(STATIC)

.PHONY: all static clean uninstall reinstall

all: static

static: $(SQLITE_STATIC)

$(SQLITE_STATIC): $(SQLITE_OBJ)
	@cp sqlite3.h ../../include/
	@$(AR) rcs $@ $<
	@printf "\033[32;1m$(notdir $@) created\033[0m\n"

$(SQLITE_OBJ): sqlite3.c sqlite3.h
	@$(CC) -DSQLITE_ENABLE_UPDATE_DELETE_LIMIT=1 -c $<

uninstall: clean
	@rm -rf $(SQLITE_STATIC)

clean:
	@rm -rf $(SQLITE_OBJ)
	@rm -rf ../../include/sqlite3.h
reinstall: uninstall all
