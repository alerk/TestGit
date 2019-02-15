import numpy as np
import cv2


def display_image(img, n_channel=3):
    """
    :param img:
    :param n_channel: number of channel
    :return:
    """
    if n_channel == 4:
        img_bgr = img[:, :, :3]
        img_alpha = img[:, :, 3]
        img_white = np.ones_like(img_bgr, dtype=np.uint8) * 255 # An image with all white
        alpha_factor = img_alpha[:, :, np.newaxis].astype(np.float32) / 255.0
        alpha_factor = np.concatenate((alpha_factor, alpha_factor, alpha_factor), axis=2)

        # Display the color image
        img_base = img_bgr.astype(np.float32) * alpha_factor
        img_white = img_white.astype(np.float32) * (1 - alpha_factor)
        img = (img_base + img_white).astype(np.uint8)

    cv2.imshow("image", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    return img


# Load the color image file downloaded in Step 1
filename = "image1.png"
img = cv2.imread(filename, cv2.IMREAD_UNCHANGED)
img_bgr = display_image(img, 4)

# Convert the color image to a gray image, save to a file
img_gray = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2GRAY)
output_fname = "image_grayscale.png"
cv2.imwrite(output_fname, img_gray)
print("Write Gray-scale Image to file: ", output_fname)

# Reload the file with gray image and display
# Make sure your saved files can be opened and displayed by other programs
img_gray_display = cv2.imread(output_fname, cv2.IMREAD_UNCHANGED)
display_image(img_gray_display)
print("Finished display grayscale image")

# Reload the color image file downloaded in Step 1
img = cv2.imread(filename, cv2.IMREAD_UNCHANGED)

# Resize the image to the size of 256 (pixels) x 256 (pixels)
img_resize = cv2.resize(img, (256, 256), cv2.INTER_LINEAR)

# Display the image
display_image(img_resize, 4)

# Save to a file
cv2.imwrite("image_resize.png", img_resize)
print("Finished save resized image")

# Reload the gray image file converted in Step 2
img_gray_display = cv2.imread(output_fname, cv2.IMREAD_UNCHANGED)

# Resize the gray image to the  size of 256 (pixels) x 256 (pixels)
img_gray_resize = cv2.resize(img_gray_display, (256, 256), cv2.INTER_LINEAR)

# Display the image
display_image(img_gray_resize)

# Save to a file
cv2.imwrite("image_gray_resize.png", img_gray_resize)
print("Finished save resized gray-scale image")

