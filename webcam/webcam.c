#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define WIDTH 1920
#define HEIGHT 1080
#define BYTES_PER_PIXEL_YUYV 2

void paint_image(uint8_t *image_buffer, size_t size, int t)
{
    for (int y=0;y<HEIGHT;y++)
    {
        for(int x=0;x<WIDTH;x++)
        {
            uint8_t y0, u0, y1, v0;
            y0 = (y+x+t) % 256;
            u0 = (t) % 256;
            y1 = (y+t) % 256;
            v0 = (x+t) % 256;
            image_buffer[BYTES_PER_PIXEL_YUYV*y*WIDTH+x + x] = y0;
            image_buffer[BYTES_PER_PIXEL_YUYV*y*WIDTH+x + x + 1] = u0;
            image_buffer[BYTES_PER_PIXEL_YUYV*y*WIDTH+x + x + 2] = y1;
            image_buffer[BYTES_PER_PIXEL_YUYV*y*WIDTH+x + x + 1] = v0;
        }
    }
}

int main()
{
    int cam_fd = open("/dev/video4", O_WRONLY);

    if (cam_fd < 0)
    {
        perror("Cannot open video device file:");
        return -1;
    }

    //define format
    struct v4l2_format format;
    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    format.fmt.pix.width = WIDTH;
    format.fmt.pix.height = HEIGHT;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    format.fmt.pix.field = V4L2_FIELD_NONE;
    format.fmt.pix.bytesperline = 0;
    format.fmt.pix.sizeimage = WIDTH*HEIGHT*BYTES_PER_PIXEL_YUYV; //YUYV usees 2 byptes per pixel
    format.fmt.pix.colorspace = V4L2_COLORSPACE_DEFAULT;


   int code = ioctl(cam_fd, VIDIOC_S_FMT, &format);

   if(code < 0)
   {
    perror("ioctl error:");
    return -1;
   }

    //write images to webcam
   uint8_t *image_buffer = (uint8_t*)calloc(WIDTH*HEIGHT, BYTES_PER_PIXEL_YUYV);

   double targetFPS = 30;
   int counter = 0;
    while(1)
    {
        paint_image(image_buffer, format.fmt.pix.sizeimage, counter++);
        write(cam_fd, image_buffer, format.fmt.pix.sizeimage);
        usleep(1.0f/targetFPS * 1000 * 1000);
    }

    free(image_buffer);
    return 0;
}