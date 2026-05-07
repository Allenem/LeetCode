import sys

for line in sys.stdin:
    line_i = line.strip()
    print(line_i)
    print(type(line_i))
    print(len(line_i))
    line_i_list = line_i.split()
    if len(line_i_list) > 1:
        if all(x.isdigit() for x in line_i_list):
            line_i_list = list(map(int, line_i_list))
            print(line_i_list)
            print(type(line_i_list[0])) # int
        elif all(x.replace('.', '', 1).isdigit() for x in line_i_list):
            line_i_list = list(map(float, line_i_list))
            print(line_i_list)
            print(type(line_i_list[0])) # float
        elif all(x.isalpha() for x in line_i_list):
            print(line_i_list)
            print(type(line_i_list[0])) # str
        else:
            print(line_i_list)
            print(type(line_i_list[0])) # str