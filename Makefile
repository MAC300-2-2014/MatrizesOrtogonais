# Nome do binário
BIN := matrizesOrtogonais

# Flags
CFLAGS  := -ansi -pedantic -O2
LDFLAGS := -lm

# Diretórios
SRCDIR  := src
OBJDIR  := obj
INCDIR  := include
BINDIR  := bin

# Programas
CC    := gcc
RM    := rm -f
RMDIR := rm -rf
MKDIR := mkdir -p

# Variáveis automáticas
SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.c=.o))
CLIBS   := -I $(INCDIR)


# Regras
.PHONY: all
all: $(BINDIR)/$(BIN)
	@echo "$(GREEN)Compilação terminada com sucesso$(RES)"

$(BINDIR)/$(BIN): $(OBJ) | $(BINDIR)
	$(CC) $^ -o $@ $(LDFLAGS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CLIBS) $(CFLAGS) -c $< -o $@

$(OBJ): | $(OBJDIR)
$(OBJDIR) $(BINDIR):
	$(MKDIR) $@	

# Limpeza
.PHONY: clean
clean: 
	$(RMDIR) $(OBJDIR)

.PHONY: distclean 
distclean: clean
	$(RMDIR) $(BINDIR)

# Debug
dump: 
	@echo $(SRC)
	@echo $(OBJ)

# Cores
GREEN = \033[1;32m
RES   = \033[0m
