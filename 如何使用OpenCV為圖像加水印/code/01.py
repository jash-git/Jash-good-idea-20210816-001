import cv2
img = cv2.imread('images/deer.JPG')
cv2.imshow("Original Image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()