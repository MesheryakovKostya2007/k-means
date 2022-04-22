from PIL import Image
from os import listdir
from os.path import isfile, join
for i in range(10):
    onlyfiles = [f for f in listdir('.\\' + str(i)) if isfile(join('.\\' + str(i), f))]


    for file in onlyfiles:
        #print(file)
        if (file[-3:] == 'png'):
            pass
        else:
            continue
        im = Image.open('.\\' + str(i) + '\\' + file, 'r')
        im = im.convert("RGB")
        pix_val = list(im.getdata())
    
        d = open('.\\' + str(i) + '\\' + file[:-3] + '-transformed.txt', 'w')
        # i = 0
        #print(im.getpixel((0, 0)))
        for el in pix_val:
            d.write(str(el) + ' ')
            #d.write(
            #print(el)
            #print(i)
            #i += 1
        d.close()
    print(i)
