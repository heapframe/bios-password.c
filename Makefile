#adapted from https://www.throwtheswitch.org/build/make

ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=out
endif

.PHONY: all
.PHONY: clean
.PHONY: test
.PHONY: keygen

PATHU = unity/src/
PATHS = src/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

SRCT = $(wildcard $(PATHT)*.c)
SRCS = $(shell find $(PATHS) -name '*.c' ! -name 'main.c')
SRCOBJS = $(patsubst $(PATHS)%.c,$(PATHO)%.o,$(SRCS))

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

COMPILE=gcc -c
LINK=gcc
DEPEND=gcc -MM -MG -MF
CFLAGS=-I. -I$(PATHU) -I$(PATHS) -I$(PATHS)keygens -I$(PATHS)utils -DTEST \
       -DENABLE_SONY -DENABLE_HPMINI -DENABLE_PHOENIX -DENABLE_HPAMI \
       -DENABLE_INSYDE -DENABLE_ASUS -DENABLE_DELL -DENABLE_SONY4x4

RESULTS = $(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt,$(SRCT) )

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------IGNORES:------------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------FAILURES:-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------PASSED:-------------------------"
	@echo "$(PASSED)"
	@echo "DONE"

$(PATHR)%.txt: $(PATHB)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

$(PATHB)Test%.$(TARGET_EXTENSION): $(PATHO)Test%.o $(SRCOBJS) $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^ -lm

$(PATHO)%.o:: $(PATHT)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c
	$(MKDIR) $(@D)
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)

all: keygen test

keygen: build/keygen

build/keygen: $(PATHO)main.o $(SRCOBJS)
	$(LINK) -o $@ $^ -lm

clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	rm -f build/keygen

.PRECIOUS: $(PATHB)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt