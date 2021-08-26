import cv2
img = cv2.imread('images/deer.JPG')
new_dim = (img.shape[1], 500) # changes height
resized_img = cv2.resize(img, new_dim, interpolation=cv2.INTER_AREA)
cv2.imshow("Original Image", img)
cv2.imshow("Resized Image", resized_img)
cv2.waitKey(0)
cv2.destroyAllWindows()