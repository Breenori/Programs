c = 'A'
i = ord(c)

print("char: '%s'" % (c))
print("ASCII code (dec): %s" % (i))
print("ASCII code (hex): %s" % (hex(i)))
print("ASCII code (oct): %s" % (oct(i)))

s = "hello"
t = "hagenberg"
u = str("\"" + s + " " + t + "\"")

#u[9] = 'x';
print("%s" % u)

inp = input("Please enter a string: ")

for count in range(0, len(inp)):
    if((inp[count] >= 'A' and inp[count] <= 'Z') or (inp[count] >= "a" and inp[count] <= "z")):
        print("%s " % chr(ord(inp[count]) ^ (1 << 5)), end = '')
    else:
        print("%s " % inp[count], end = '')

inp = inp.replace("blabla")

print ("%s " % inp)