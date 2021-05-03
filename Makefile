LEX=flex
YACC=bison
CC=g++ 
CPP_FLAGS='-std=c++17'
OBJECT=main #生成的目标文件

$(OBJECT): lex.yy.o  yacc.tab.o Interpreter.o Graph.o Typing.o
	$(CC) $(CPP_FLAGS) lex.yy.o yacc.tab.o Interpreter.o Graph.o Typing.o -o $(OBJECT)
# @./$(OBJECT) #编译后立刻运行

lex.yy.o: lex.yy.c  yacc.tab.h Utils.hpp
	$(CC) $(CPP_FLAGS) -c lex.yy.c

yacc.tab.o: yacc.tab.c Utils.hpp Interpreter.hpp
	$(CC) $(CPP_FLAGS) -c yacc.tab.c

Interpreter.o: Interpreter.cpp Typing.hpp Interpreter.hpp Graph.hpp yacc.tab.h Utils.hpp
	$(CC) $(CPP_FLAGS) -c Interpreter.cpp

Typing.o: Typing.cpp Typing.hpp
	$(CC) $(CPP_FLAGS) -c Typing.cpp

Graph.o: Graph.cpp Graph.hpp yacc.tab.h Utils.hpp
	$(CC) $(CPP_FLAGS) -c Graph.cpp

yacc.tab.c  yacc.tab.h: yacc.y
# bison使用-d参数编译.y文件
	$(YACC) -d yacc.y

lex.yy.c: lex.l
	$(LEX) lex.l

clean:
	@rm -f $(OBJECT)  *.o