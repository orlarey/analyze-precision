#include "draw.h"
#include "pbPlots.h"
#include "supportLib.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void plotfile(std::string filename, const std::map<int, int> &H)
{
    std::vector<double> xs;
    std::vector<double> ys;
    for (auto r : H) {
        xs.push_back(r.first);
        ys.push_back(r.second);
    }

    StringReference *         errorMessage   = new StringReference();
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
    bool                      success        = DrawScatterPlot(imageReference, 600, 400, &xs, &ys, errorMessage);

    if (success) {
        std::vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, filename);
        DeleteImage(imageReference->image);
    } else {
        std::cerr << "Error plotting" << std::endl;
    }
}
