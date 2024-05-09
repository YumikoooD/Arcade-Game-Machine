from sys import argv

C: str = str(argv[1])
txt: str = ""

for i in range(0, 20):
    for j in range(0, 20):
        txt += f"{C},"
    txt = txt.removesuffix(",")
    txt += "\n"

with open("./f", "w") as f:
    f.write(txt)
