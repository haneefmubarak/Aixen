# Set compiler
ERR = $(shell which clang >/dev/null; echo $$?)
ifeq "$(ERR)" "0"
    SC = clang
else
    SC = gcc
endif

# Force target choice
.PHONY:	default
.DEFAULT_GOAL: default
default:
	@echo "Please select a legitimate target:"
	@echo "	- debug"
	@echo "	- native"
	@echo "	- release"


# Optimization flags
MOFLAGS = -O2 -m64 -mpc64 -mfpmath=both
	# Unused flags
MOFLAGS	+= -Qunused-arguments
	# Constant propagation
MOFLAGS += -fipa-pta
	# Loop manipulation
MOFLAGS += -ftree-loop-linear -floop-interchange -floop-strip-mine
MOFLAGS += -floop-block -ftree-loop-distribution
MOFLAGS += -ftree-loop-distribute-patterns -funswitch-loops
	# Vectorization
MOFLAGS += -ftree-vectorize

CFLAGS = -pthread
debug:		CFLAGS += -Os -g
native:		CFLAGS += $(MOFLAGS) -march=native
release:	CFLAGS += $(MOFLAGS) -mtune=generic

HFLAGS = -Ibuild -I.
LFLAGS = -lev

HC = $(SC) $(HFLAGS)
CC = $(HC) $(CFLAGS)
LC = $(CC) $(LFLAGS)


# Final Targets
debug:		build/aixen
native:		build/aixen
release:	build/aixen

# Generics
.PHONY:	all
all: default

build:
	mkdir -pv build

.PHONY: clean
clean:
	rm -rvf build

# Aixen
build/aixen:		build build/files_c
	$(LC) build/*.o -o build/aixen

build/files_c:		build build/aixen.o
	touch build/files_c

build/aixen.o:		build aixen.c build/aixen.h.gch
	$(CC) aixen.c -c -o build/aixen.o

build/aixen.h.gch:	build aixen.h
	$(HC) aixen.h -o build/aixen.h
