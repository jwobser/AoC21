from ast import match_case
import readline
import time

def isDigit(entry, digit):
    if len(entry) != len(digit):
        return False
    for l in entry:
        if l in digit:
            continue
        else:
            return False
    return True

input = open("input", "r")

start = time.time()

a = True
count = 0
total = 0
while a:
    x = input.readline()
    if x == '':
        a = False
    try:
        splitinput = x.split("|")
        scrambled = splitinput[0]
        output = splitinput[1]
    except:
        continue
    # print(output)
    invalues = scrambled.split()
    for display in invalues:
        length = len(display)
        match length:
            case 2:
                one = display
            case 3:
                seven = display
            case 4:
                four = display
            case 7:
                eight = display
    
    invalues.remove(one)
    invalues.remove(seven)
    invalues.remove(four)
    invalues.remove(eight)

    rhs = list(one)
    for display in invalues:
        if len(display) != 5:
            continue
        if rhs[0] in display and rhs[1] in display:
            three = display
    
    invalues.remove(three)

    # lhs = [i for i in list(eight) if i not in list(three)]
    lhs = list(filter((lambda i: i not in three), eight))

    for display in invalues:
        if len(display) != 6:
            continue
        d = list(display)
        if rhs[0] in d and rhs[1] in d and lhs[0] in d and lhs[1] in d:
            zero = display

    invalues.remove(zero)

    # 1, 3, 7, 8, 0, 4
    # Need 2, 5, 6, 9

    bottomleft = set()
    for l in eight:
        if l not in seven and l not in one and l not in four:
            bottomleft.add(l)

    seg5 = [i for i in bottomleft if i not in three][0]
    # print(seg5)

    for display in invalues:
        if len(display) != 5:
            continue
        d = list(display)
        if seg5 in d:
            two = display
        else:
            five = display

    invalues.remove(two)
    invalues.remove(five)
    
    for display in invalues:
        d = list(display)
        if rhs[0] not in display or rhs[1] not in display:
            six = display
        else:
            nine = display


    invalues.remove(six)
    invalues.remove(nine)

    assert len(invalues) == 0




    values = output.split()
    i = 1000
    sum = 0
    for display in values:
        if isDigit(display, zero):
            sum = sum + (i*0)
        if isDigit(display, one):
            sum = sum + (i*1)
        if isDigit(display, two):
            sum = sum + (i*2)
        if isDigit(display, three):
            sum = sum + (i*3)
        if isDigit(display, four):
            sum = sum + (i*4)
        if isDigit(display, five):
            sum = sum + (i*5)
        if isDigit(display, six):
            sum = sum + (i*6)
        if isDigit(display, seven):
            sum = sum + (i*7)
        if isDigit(display, eight):
            sum = sum + (i*8)
        if isDigit(display, nine):
            sum = sum + (i*9)
        
        i = i / 10
        
    print (int(sum))
    total = total + int(sum)

print(total)

end = time.time()

print("Execution time {} s".format((end - start)))