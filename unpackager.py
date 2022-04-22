from os import listdir
from os.path import isfile, join

for i in range(10):
    onlyfiles = [f for f in listdir('.\\' + str(i)) if isfile(join('.\\' + str(i), f))]
    for f in onlyfiles:
        if (f[-3:] != 'txt'):
            continue
        #print(f)
        newfile = open('.\\unpackaged_decoded\\' + f, 'w')
        oldfile = open('.\\' + str(i) + '\\' + f, 'r')
        newfile.write(oldfile.read())
        newfile.close()
        oldfile.close()
    print(i)
