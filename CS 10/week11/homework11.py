from sys import argv
from pathlib import Path

def main():
    if len(argv) != 2:
        print(f"usage: python3 homework11.py <path>")

    path = Path(argv[1])

    if not path.exists():
        raise FileNotFoundError(f"file ${path} cannot be located")
    
    with path.open("r") as file:
        lines = file.readlines()
        lines = lines[:lines.index("q")]
    
    names_count = {name : lines.count(name) for name in lines}
    
    print("\n".join(
        list(
            map(
                lambda name: f"{names_count[name]} student(s) named {name}",
                names_count
            )
        )
    ))

if __name__ == "__main__":
    main()