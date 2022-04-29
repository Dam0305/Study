class STACK(object):
    global Top
    Top = -1
    def __init__(self):
        self.data = []

    def empty(self):
        if Top == -1:
            return 1
        else:
            return 0

    def push(self, x):
        self.data.append(x)
        Top += 1

    def pop(self):
        if Top == -1:
            return -1
        else:
            self.data.pop()
            Top -= 1

    def top(self):
        if Top == -1:
            return -1
        else:
            return self.data[-1]

    def size(self):
        Top += 1
        return Top


def main():
    s = STACK()
    cnt = int(input())

    while cnt != 0:
        order = input()

        if order == "push":
            x = int(input())
            s.push(x)

        elif order == "pop":
            print(s.pop())

        elif order == "size":
            print(s.size())

        elif order == "top":
            print(s.top())

        elif order == "empty":
            print(s.empty())


main()
