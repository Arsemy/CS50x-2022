while True:
    height = input("height: ")
    if height.isnumeric() and int(height) >= 1 and int(height) <= 8:
        height = int(height)
        break

for i in range(1, height + 1):
    print(" " * (height - i), end="")
    print("#" * i)