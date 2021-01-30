r = [7,
4,
7,
5,
6,
6,
9,
2,
8,
6,
4,
5,
7,
3,
2,
4,
6,
2,
5,
6]

for a in range(0, 20):
    i = "_{"+str(a)+"}"
    print("\left(x-a"+i+"\\right)^{2}+\left(y-b"+i+"\\right)^{2}="+str(r[a]*r[a]))
    print("\left(a"+i+",b"+i+"\\right)")
    print("a"+i+"=16.2")
    print("b"+i+"=9.9")