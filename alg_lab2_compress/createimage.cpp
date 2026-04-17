
#include "fun.h"

void createImages(string filename, string outpath) {
	Image img;
	img.load(filename);
    img.save(outpath + "RGB.raw");
    string outfile = outpath + "RGB.png";

    img.savePNG(outfile);
    cout << "ORIGINAL IMAGE: " << img.width << "x" << img.height;
    if (img.type == 0) cout << ", BLACK AND WHITE";
    else if(img.type == 1) cout << ", GREY-SCALE";
    else cout << ", RGB";
    cout << "\n";

    Image grayImg; grayImg.load(filename);
    grayImg.toGrayscale();
    grayImg.save(outpath + "grey.raw");
    
    outfile = outpath + "grey.png";
    grayImg.savePNG(outfile);
    cout << "+ grey.png\n";

    Image bwRoundImg; bwRoundImg.load(filename);
    bwRoundImg.toBW_byrounding();
    bwRoundImg.save(outpath + "bw_round.raw");

    outfile = outpath + "bw_round.png";
    bwRoundImg.savePNG(outfile);
    cout << "+ bw_round.png\n";

    Image bwDitherImg; bwDitherImg.load(filename);
    bwDitherImg.toBW_byDithering();
    bwDitherImg.save(outpath + "bw_dither.raw");

    outfile = outpath + "bw_dither.png";
    bwDitherImg.savePNG(outfile);
    cout << "+ bw_dither.png\n";

}

void Image::saveJPEG(string outfile) {
    const char* name = outfile.c_str();
    stbi_write_jpg(name, width, height, pixel, data, 0);
}

void Image::savePNG(string outfile) {
    const char* name = outfile.c_str();
    stbi_write_png(name, width, height, pixel, data, 0);
}

