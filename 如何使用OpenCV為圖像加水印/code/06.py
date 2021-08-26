import cv2
watermark = cv2.imread("watermark.PNG")
wm_scale = 40
wm_width = int(watermark.shape[1] * wm_scale/100)
wm_height = int(watermark.shape[0] * wm_scale/100)
wm_dim = (wm_width, wm_height)
resized_wm = cv2.resize(watermark, wm_dim, interpolation=cv2.INTER_AREA)
h_wm, w_wm, _ = resized_wm.shape

for image in  imgList:
    img = cv2.imread(f'{folderPath}/{image}')
    percent_of_scaling = 20
    new_width = int(img.shape[1] * percent_of_scaling/100)
    new_height = int(img.shape[0] * percent_of_scaling/100)
    new_dim = (new_width, new_height)
    resized_img = cv2.resize(img, new_dim, interpolation=cv2.INTER_AREA)
    h_img, w_img, _ = resized_img.shape
    center_y = int(h_img/2)
    center_x = int(w_img/2)
    top_y = center_y - int(h_wm/2)
    left_x = center_x - int(w_wm/2)
    bottom_y = top_y + h_wm
    right_x = left_x + w_wm
    roi = resized_img[top_y:bottom_y, left_x:right_x]
    result = cv2.addWeighted(roi, 1, resized_wm, 0.3, 0)
    resized_img[top_y:bottom_y, left_x:right_x] = result
    filename = os.path.basename(image)
    cv2.imwrite("watermarked images/watermarked_"+filename, resized_img)
    cv2.imshow("Watermarked Image", resized_img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()