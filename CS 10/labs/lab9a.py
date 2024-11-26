def split_it_up(string: str, seperator: str):
    start, sep, rest = "", "", ""
    for i, c in enumerate(string):
        if seperator.startswith(c) and string[i:i+len(seperator)] == seperator:
            start = string[0 : i]
            sep = seperator
            rest = string[i + len(seperator):]
            break
        

    return start, sep, rest

print(split_it_up("hello world", " "))

#('hello', ' ', 'world')

 

print(split_it_up("hello world", "wo"))

#('hello ', 'wo', 'rld')

 

print(split_it_up("hello world", "r"))

#('hello wo', 'r', 'ld')

 

print(split_it_up("hello world, I am ready to program", " "))

#('hello', ' ', 'world, I am ready to program')

 

print(split_it_up("hello world", "|"))

#('hello world', '', '')