import cv2 as cv
import uuid
import os

CURRENT_PATH = os.path.dirname(os.path.abspath(__file__))
IMAGE_DIR = 'images'
COMPLETE_DIR_NAME = os.path.join(CURRENT_PATH, IMAGE_DIR)

cap = cv.VideoCapture("http://localhost:8081/stream/video.mjpeg", cv.CAP_FFMPEG)

return_value, image = cap.read()

cv.imshow('Frame',image)

uuid_str = str(uuid.uuid4())
print("saved as {0}".format(uuid_str))
cv.imwrite(os.path.join(COMPLETE_DIR_NAME, r'capture' + uuid_str + r'.jpg'), image)

cv.waitKey(0)

cap.release()

cv.destroyAllWindows()