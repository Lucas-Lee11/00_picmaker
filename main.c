#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char const *argv[]) {

    int rand = open("/dev/random", O_RDONLY);
    int fd = open("./image.ppm", O_WRONLY | O_CREAT, 0664);
    if(fd == -1) {
        printf("Error: %d %s\n",errno, strerror(errno));
        return -1;
    }


    char data[] = "P6 500 500 255\n";
    write(fd, data, sizeof(data));


    unsigned char pixels[500][500][3], r;
    int row, col, ch;
    for(row = 0; row < 500; row++){
        read(rand, &r, sizeof(unsigned char));
        for(col = 0; col < 500; col++){
            pixels[row][col][r % 3] = (row + col) * r;
        }
    }

    write(fd, pixels, sizeof(pixels));
    close(fd);
    close(rand);



    return 0;
}
