
bulbs = set()

buttons = int(input())

bulb_nr = int(input())

for i in range(0, buttons):
    k = int(input())
    for j in range(0, k):
        bulb = int(input())
        bulbs.add(bulb)

ok = True

for i in range(1, bulb_nr + 1):
    if i not in bulbs:
        ok = False

if ok:
    print("YES")
else:
    print("NO")