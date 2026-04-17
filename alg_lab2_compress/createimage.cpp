
#include "fun.h"

void createImages(string filename, string outpath) {
	Image img;
	img.load(filename);
    img.save(outpath + "RGB.raw");
    string outfile = outpath + "RGB.jpg";

    img.saveJPEG(outfile);
    cout << "ORIGINAL IMAGE: " << img.width << "x" << img.height;
    if (img.type == 0) cout << ", BLACK AND WHITE";
    else if(img.type == 1) cout << ", GREY-SCALE";
    else cout << ", RGB";
    cout << "\n";

    Image grayImg; grayImg.load(filename);
    grayImg.toGrayscale();
    grayImg.save(outpath + "grey.raw");
    
    outfile = outpath + "grey.jpg";
    grayImg.saveJPEG(outfile);
    cout << "+ grey.jpg\n";

    Image bwRoundImg; bwRoundImg.load(filename);
    bwRoundImg.toBW_byrounding();
    bwRoundImg.save(outpath + "bw_round.raw");

    outfile = outpath + "bw_round.jpg";
    bwRoundImg.saveJPEG(outfile);
    cout << "+ bw_round.jpg\n";

    Image bwDitherImg; bwDitherImg.load(filename);
    bwDitherImg.toBW_byDithering();
    bwDitherImg.save(outpath + "bw_dither.raw");

    outfile = outpath + "bw_dither.jpg";
    bwDitherImg.saveJPEG(outfile);
    cout << "+ bw_dither.jpg\n";

}

void Image::saveJPEG(string outfile) {
    const char* name = outfile.c_str();
    stbi_write_jpg(name, width, height, pixel, data, 0);
}