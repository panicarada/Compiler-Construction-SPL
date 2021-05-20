import io
import sys

from graphviz import Digraph

dot = Digraph(comment='AST Tree')

if len(sys.argv) <= 1:
    raise Exception("No Input file!!")

filename = './AST_raw/' + sys.argv[1] + '.raw.ast'

with io.open(filename, mode="r", encoding="utf-8") as file:
    words = iter(file.read().splitlines())
    while True:
        word = next(words, None)
        if word is None:
            break
        if word != '':  # 非空
            if word == "*edge*":
                dot.edge(next(words), next(words))
            else:
                dot.node(word, label="[" + word + "] " + next(words), shape=next(words))

dot.render('./AST_py/' + sys.argv[1] + '.py.ast', view=True)
