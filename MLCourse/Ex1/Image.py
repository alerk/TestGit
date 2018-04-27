import numpy as np
import cv2

# def display_image(filename, n_channel):
#     """
#     :param filename:
#     :param n_channel:
#     :return:
#     """
#     if n_channel == 3:
#         img = cv2.imread(filename, cv2.IMREAD_UNCHANGED)
#     elif n_channel == 4:
#         img = cv2.imread(filename, cv2.IMREAD_UNCHANGED)
#
#     cv2.imshow("image", img)
#     cv2.waitKey(0)
#     cv2.destroyAllWindows()
#     return img


# Load the color image file downloaded in Step 1
filename = "image1.png"
img = cv2.imread(filename, cv2.IMREAD_UNCHANGED)
img_bgr = img[:, :, :3]
img_alpha = img[:, :, 3]
img_white = np.ones_like(img_bgr, dtype=np.uint8) * 255 # An image with all white
alpha_factor = img_alpha[:, :, np.newaxis].astype(np.float32) / 255.0
alpha_factor = np.concatenate((alpha_factor, alpha_factor, alpha_factor), axis=2)

# Display the color image
img_base = img_bgr.astype(np.float32) * alpha_factor
img_white = img_white.astype(np.float32) * (1 - alpha_factor)
img_display = (img_base + img_white).astype(np.uint8)
cv2.imshow("image", img_display)
cv2.waitKey(0)
cv2.destroyAllWindows()

# Convert the color image to a gray image, save to a file
img_gray = cv2.cvtColor(img_display, cv2.COLOR_BGR2GRAY)
output_fname = "image_grayscale.png"
cv2.imwrite(output_fname, img_gray)
print("Write Gray-scale Image to file: ", output_fname)

# Reload the file with gray image and display
# Make sure your saved files can be opened and displayed by other programs
img_gray_display = cv2.imread(output_fname, cv2.IMREAD_UNCHANGED)
cv2.imshow("image", img_gray_display)
cv2.waitKey(0)
cv2.destroyAllWindows()
print("Finished display grayscale image")
