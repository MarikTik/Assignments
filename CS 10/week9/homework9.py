make_str1 = lambda s1, s2: "Yes" if all(c in s1 for c in s2) else "No"
make_str2 = lambda s1, s2: "Yes" if set(s2).issubset(set(s1)) else "No"

# make_str1 is shorter but make_str2 is more efficient