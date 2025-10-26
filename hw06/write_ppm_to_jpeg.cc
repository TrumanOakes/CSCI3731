#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>

int rd_ppm(const char* path, unsigned char** px_out, int* width_out, int* height_out){
    FILE *fp = fopen(path, "rb"); /* open file in binary */
    if(!fp){
        return 0;
    }
    char header[3] = {0};
    int maxval = 0;

    if (fscanf(fp, "%2s %d %d %d%*c", header, width_out, height_out, &maxval) != 4 || /* %2s = "P6", %d %d = width,height , %d = maxval, %*c = consume '\n'*/
    strcmp(header, "P6") != 0 || maxval != 255 ||*width_out <= 0 || *height_out <= 0) {
        fclose(fp);
        return 0;
    }
    size_t size = (size_t)(*width_out) * (size_t)(*height_out) * 3; /*multiply by 3 for each pixel*/
    unsigned char* bufferpx = (unsigned char*)malloc(size); /*allocates a heap buffer of (size) to hold pixels*/
    if(!bufferpx) {
        fclose(fp);
        return 0;
    }
    size_t n = fread(bufferpx, 1, size, fp); /*read pixels*/
    fclose(fp);
    if(n != size){
        free(bufferpx); /*free's the memory allocated if not all bytes were read*/
        return 0;
    }
    *px_out = bufferpx;
    return 1;
}

int write_ppm(const char* path,  const unsigned char* px_out, int width_out, int height_out){
    if(!path || !px_out || width_out <= 0 || height_out <= 0){ /*same checks for inconsistencies*/
        return 0;
    }
    FILE *fp = fopen(path, "wb"); /*open file for writing*/
    if(!fp){
        return 0;
    }
    if (fprintf(fp, "P6\n%d %d\n255\n", width_out, height_out) < 0) {
        fclose(fp);
        return 0;
    }
    size_t size = (size_t)width_out * (size_t)height_out * 3;
    size_t n = fwrite(px_out, 1, size, fp);
    fclose(fp);
    return n == size;
}

int write_jpeg(const char* path, const unsigned char* rgb, int width, int height, int quality){
    if(!path || !rgb || width <= 0 || height <= 0) return 0;
    if(quality < 1) quality = 75;
    if(quality > 100) quality = 100;

    FILE* fp = fopen(path, "wb");
    if(!fp) return 0;

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, fp);

    cinfo.image_width      = (JDIMENSION)width;
    cinfo.image_height     = (JDIMENSION)height;
    cinfo.input_components = 3;
    cinfo.in_color_space   = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, 1);

    jpeg_start_compress(&cinfo, 1);

    JSAMPROW row_pointer[1];
    int row_stride = width * 3;
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = (JSAMPROW)&rgb[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(fp);
    return 1;
}

int main(int argc, char** argv){
    const char* in_path = (argc >= 2) ? argv[1] : "test.ppm";
    const char* out_jpg = (argc >= 3) ? argv[2] : "out.jpg";
    int quality = (argc >= 4) ? atoi(argv[3]) : 90;

    unsigned char* px = NULL;
    int w = 0, h = 0;

    if(!rd_ppm(in_path, &px, &w, &h)){
        fprintf(stderr, "Failed to read PPM: %s\n", in_path);
        return 1;
    }

    if(!write_jpeg(out_jpg, px, w, h, quality)){
        fprintf(stderr, "Failed to write JPEG: %s\n", out_jpg);
        free(px);
        return 1;
    }

    printf("Wrote %s (quality=%d)\n", out_jpg, quality);
    free(px);
    return 0;
}