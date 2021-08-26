import cv2
img = cv2.imread('images/deer.JPG')
percent_of_scaling = 20
new_width = int(img.shape[1] * percent_of_scaling/100)
new_height = int(img.shape[0] * percent_of_scaling/100)
new_dim = (new_width, new_height)
resized_img = cv2.resize(img, new_dim, interpolation=cv2.INTER_AREA)
filename = 'resized_img_aspect ratio.jpg'
cv2.imwrite(filename, resized_img)
cv2.imshow("Original Image", img)
cv2.imshow("Resized Image", resized_img)
cv2.waitKey(0)
cv2.destroyAllWindows()