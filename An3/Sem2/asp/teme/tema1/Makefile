CC = mpic++

CFLAGS = -std=c++11 -g

DIR = .

ifeq ($(DIR),)
	DIR := .
endif

SRCS := $(wildcard $(DIR)/*.cpp)
EXES := $(patsubst $(DIR)/%.cpp,$(DIR)/%.exe,$(SRCS))

all: $(EXES)

$(DIR)/%.exe: $(DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

run: $(EXES)
	for exe in $(EXES); do \
		mpirun --oversubscribe -n 8 $$exe; \
	done
	cat res.dat && echo

clean:
	rm -f $(EXES)
