import cv2
img = cv2.imread('images/deer.JPG')
watermark = cv2.imread("watermark.PNG")

percent_of_scaling = 20
new_width = int(img.shape[1] * percent_of_scaling/100)
new_height = int(img.shape[0] * percent_of_scaling/100)
new_dim = (new_width, new_height)
resized_img = cv2.resize(img, new_dim, interpolation=cv2.INTER_AREA)

wm_scale = 40
wm_width = int(watermark.shape[1] * wm_scale/100)
wm_height = int(watermark.shape[0] * wm_scale/100)
wm_dim = (wm_width, wm_height)
resized_wm = cv2.resize(watermark, wm_dim, interpolation=cv2.INTER_AREA)