import cv2 as cv
from time import sleep
# cap = cv.VideoCapture("http://localhost:8081/stream/video.mjpeg ", cv.CAP_DSHOW)
cap = cv.VideoCapture("http://localhost:8081/stream/video.mjpeg", cv.CAP_FFMPEG)
print(cap)
sleep(2)

return_value, image = cap.read()
# print("opened img")
# print(return_value, image)
# cv.imshow('Frame',image)

# cv.waitKey(0)

# Read until video is completed
# print(cap.isOpened())
while(cap.isOpened()):
  # Capture frame-by-frame
  ret, frame = cap.read()
  if ret == True:

    # Display the resulting frame
    cv.imshow('Frame',frame)

    # Press Q on keyboard to  exit
    if cv.waitKey(25) & 0xFF == ord('q'):
      break

  # Break the loop
  else:
    print("ret is not true")
    break

# When everything done, release the video capture object
cap.release()

# Closes all the frames
cv.destroyAllWindows()