
#include "fun.h"

void createImages(string filename, string outpath) {
	Image img;
	img.load(filename);
    img.save(outpath + "RGB.raw");
    cout << "ORIGINAL IMAGE: " << img.width << "x" << img.height;
    if (img.type == 0) cout << ", BLACK AND WHITE";
    else if(img.type == 1) cout << ", GREY-SCALE";
    else cout << ", RGB";
    cout << "\n";

    Image grayImg; grayImg.load(filename);
    grayImg.toGrayscale();
    grayImg.save(outpath + "grey.raw");
    
    string outfile = outpath + "grey.png";
    const char* name = outfile.c_str();
    stbi_write_png(name, grayImg.width, grayImg.height, 1, grayImg.data, 0);
    cout << "+ grey.png\n";

    Image bwRoundImg; bwRoundImg.load(filename);
    bwRoundImg.toBW_byrounding();
    bwRoundImg.save(outpath + "bw_round.raw");

    outfile = outpath + "bw_round.png";
    name = outfile.c_str();
    stbi_write_png(name, bwRoundImg.width, bwRoundImg.height, 1, bwRoundImg.data, 0);
    cout << "+ bw_round.png\n";

    Image bwDitherImg; bwDitherImg.load(filename);
    bwDitherImg.toBW_byDithering();
    bwDitherImg.save(outpath + "bw_dither.raw");

    outfile = outpath + "bw_dither.png";
    name = outfile.c_str();
    stbi_write_png(name, bwDitherImg.width, bwDitherImg.height, 1, bwDitherImg.data, 0);
    cout << "+ bw_dither.png\n";

}