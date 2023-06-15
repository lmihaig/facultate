CC = mpic++

CFLAGS = -std=c++11 -g -lgslcblas -lm  -lgsl

DIR = .

ifeq ($(DIR),)
	DIR := .
endif

SRCS := $(wildcard $(DIR)/*.cpp)
EXES := $(patsubst $(DIR)/%.cpp,$(DIR)/%.exe,$(SRCS))

all: $(EXES)

$(DIR)/%.exe: $(DIR)/%.cpp
	$(CC) -o $@ $< $(CFLAGS)

run: $(EXES)
	for exe in $(EXES); do \
		mpirun --oversubscribe -n 4 $$exe; \
	done

clean:
	rm -f $(EXES)
