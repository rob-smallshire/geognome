#!python


f = open('results.txt')
for line in f.readlines():
    if line.startswith('Trial'):
        fields = line.split()
        x = float(fields[2][1:-1])
        y = float(fields[3][0:-1])
        z = float(fields[5])
        print "%f\t%f\t%f" % (x, y, z)