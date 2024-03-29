TARGET=code
EXPR_LEXER=lexer.cpp
EXPR_PARSER=grammar.cpp
SRC_FILES=$(EXPR_PARSER) $(EXPR_LEXER) AST.cpp main.cpp
OBJFILES =${SRC_FILES:.cpp = .o}

.PHONY: clean

$(TARGET):$(OBJFILES) AST.h
	g++ -std=c++11 -o $@ $^

%.o: %.cpp tokens.h
	g++ -std=c++11 -c -o $< $@

$(EXPR_PARSER): grammar.y
	bison -v --defines=tokens.h -o $@ $^

$(EXPR_LEXER): lexer.l
	flex -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o
	rm -f ${EXPR_PARSER}
	rm -f ${EXPR_LEXER}
	rm -f tokens.h
	rm -f ${TARGET}
	rm -f grammar.output