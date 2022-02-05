import cv2 as cv
import os.path
import numpy as np
from tqdm import tqdm


CURRENT_PATH = os.path.dirname(os.path.abspath(__file__))
IMAGE_DIR = 'images'
COMPLETE_DIR_NAME = os.path.join(CURRENT_PATH, IMAGE_DIR)

def ResizeWithAspectRatio(image, width=None, height=None, inter=cv.INTER_AREA):
    dim = None
    (h, w) = image.shape[:2]

    if width is None and height is None:
        return image
    if width is None:
        r = height / float(h)
        dim = (int(w * r), height)
    else:
        r = width / float(w)
        dim = (width, int(h * r))

    return cv.resize(image, dim, interpolation=inter)

def calibrate_chessboard(dir_path, image_format, square_size, width, height):
    '''Calibrate a camera using chessboard images.'''
    # termination criteria
    criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 30, 0.001)
    
    # prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(8,6,0)
    objp = np.zeros((height*width, 3), np.float32)
    objp[:, :2] = np.mgrid[0:width, 0:height].T.reshape(-1, 2)

    objp = objp * square_size

    # Arrays to store object points and image points from all the images.
    objpoints = []  # 3d point in real world space
    imgpoints = []  # 2d points in image plane.

    # images = pathlib.Path(dir_path).glob(f'*.{image_format}')
    images = [f for f in os.listdir(dir_path) if os.path.isfile(os.path.join(dir_path, f))]
    # Iterate through all images
    if len(images) > 0:
        for fname in tqdm(images):
            img = cv.imread(os.path.join(dir_path,str(fname)))
            gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
            resize = ResizeWithAspectRatio(gray, width=1280)
            cv.imshow('Frame', resize)
            cv.waitKey(0)

            # Find the chess board corners
            ret, corners = cv.findChessboardCorners(resize, (width, height), None)
            print(ret, corners)
            # If found, add object points, image points (after refining them)
            if ret:
                objpoints.append(objp)

                corners2 = cv.cornerSubPix(resize, corners, (11, 11), (-1, -1), criteria)
                imgpoints.append(corners2)
        

        # Calibrate camera
        if len(objpoints) > 0 and len(imgpoints) > 0:
            ret, mtx, dist, rvecs, tvecs = cv.calibrateCamera(objpoints, imgpoints, resize.shape[::-1], None, None)
            return [ret, mtx, dist, rvecs, tvecs]
        else:
            print("not enough images for calibration")
            print("legth of objpoints", len(objpoints))
            print("legth of imgpoints", len(imgpoints))
    else:
        print("no images in directory", dir_path)

def save_coefficients(mtx, dist, path):
    '''Save the camera matrix and the distortion coefficients to given path/file.'''
    cv_file = cv.FileStorage(path, cv.FILE_STORAGE_WRITE)
    cv_file.write('K', mtx)
    cv_file.write('D', dist)
    # note you *release* you don't close() a FileStorage object
    cv_file.release()

def load_coefficients(path):
    '''Loads camera matrix and distortion coefficients.'''
    # FILE_STORAGE_READ
    cv_file = cv.FileStorage(path, cv.FILE_STORAGE_READ)

    # note we also have to specify the type to retrieve other wise we only get a
    # FileNode object back instead of a matrix
    camera_matrix = cv_file.getNode('K').mat()
    dist_matrix = cv_file.getNode('D').mat()

    cv_file.release()
    return [camera_matrix, dist_matrix]


if __name__ == '__main__':
    # Parameters
    IMAGES_FORMAT = '.jpg'
    SQUARE_SIZE = 4.7333
    WIDTH = 7
    HEIGHT = 4
    try:
        # Calibrate 
        ret, mtx, dist, rvecs, tvecs = calibrate_chessboard(
            COMPLETE_DIR_NAME, 
            IMAGES_FORMAT, 
            SQUARE_SIZE, 
            WIDTH, 
            HEIGHT
        )
        # Save coefficients into a file
        save_coefficients(mtx, dist, os.path.join(CURRENT_PATH, "calibration_chessboard.yml"))
    except Exception as e:
        print("THERE WAS AN ERROR")
        print(e)