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
img_bgr = cv2.resize(display_image(img, 4), (125, 125), cv2.INTER_CUBIC)

# Apply Gaussian filter with different kernel sizes and sigma
img_gaussian = list()
img_background = None
for i in range(1, 5):
    img_row = None
    for s in range(1, 5):
        kernel_size = 2*i + 1
        img_blur = cv2.GaussianBlur(img_bgr, (kernel_size, kernel_size), sigmaX=s)
        img_gaussian.append(img_blur)
        if img_row is None:
            img_row = img_blur
        else:
            img_row = np.hstack((img_row, img_blur))
    if img_background is None:
        img_background = img_row
    else:
        img_background = np.vstack((img_background, img_row))

# Display all blurred images in the same window
display_image(img_background)

# Explain the differences
