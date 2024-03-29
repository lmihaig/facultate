CC = gcc

LEX_SOURCE = lexer.l

LEXER_SOURCE = lex.yy.c

EXECUTABLE = rust_lexer

all: $(EXECUTABLE)

$(EXECUTABLE): $(LEXER_SOURCE)
	$(CC) $(LEXER_SOURCE) -o $(EXECUTABLE) -lfl

$(LEXER_SOURCE): $(LEX_SOURCE)
	flex $(LEX_SOURCE)

clean:
	rm -f $(LEXER_SOURCE) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE) < test.rs

# Phony targets
.PHONY: all clean run

