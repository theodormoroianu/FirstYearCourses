# Generating graph from a note file
# Sample usage: python3 scripts/generate_graph.py data/notes/sample
# The main ideea is this script to be called from the server.js
# And the result to be served as a png to the version control


import json, sys
import subprocess

if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise Exception()

    path = sys.argv[1]

    with open(path, "r") as fin:
        note = json.load(fin)

    nodes, edges = ["\"Version " + str(i) + "\";" for i in range(0, note['head'] + 1)], []
    for i in range(1, note['head'] + 1):
        origin = note['versions'][i]['origin']
        if origin < 0 or origin >= i:
            raise Exception()
        edges.append("\"Version " + str(origin) + "\" -> \"Version " + str(i) + "\";")

    with open("scripts/diagram.gv", "w") as fout:
        fout.write("digraph G {\n")
        for i in nodes:
            fout.write("    " + i + "\n")
        for i in edges:
            fout.write("    " + i + "\n")
        fout.write("}\n")

    subprocess.run(["dot", "-Tpng", "scripts/diagram.gv", "-o", "scripts/diagram.png", "-Gsize=9,15\!"])
    # subprocess.run(["convert", "diagram.png", "-transparent", "white", "diagram.png"])

    print("Success!")


