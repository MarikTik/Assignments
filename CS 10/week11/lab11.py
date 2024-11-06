def f1(path: str) -> None:
    with open(path, 'w') as f:
        f.writelines(["Mark", "Computer Science", "sleeping"])

def f2(path: str) -> None:
    with open(path, 'r') as f:
        print(f.read())

