import sys

line = sys.stdin.readline().split(" ")
S = int(line[0])
E = int(line[1])
for i in range(E - S + 1):
	x = S + i
	x_str = str(x)
	if x_str == x_str[::-1]:
		print("Palindrome!")
	else:
		print(x)
