from mss.windows import MSS as mss
import numpy as np
from time import time

MONITOR = {"top": 0, "left": 0, "width": 1920, "height": 1080}
FILENAME = "DataTransfer\SharedData\shared_data_image_array.npy"

# ToDo: check whether it still works with constantly open file
while(True):
    with mss() as sct:
        img = np.array(sct.grab(MONITOR))
        with open(FILENAME, 'wb') as file:
            np.save(file, img)

# open file with this code
#with open("DataTransfer\SharedData\currentImage.npy", 'rb') as file:
#    img2 = numpy.load(file)
