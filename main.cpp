#include <png++/png.hpp>

#include <fstream>
#include <iostream>
#include <string>

enum IMG_FORMAT
{
    UNKNOWN,
    PNG,
    JPEG
};

unsigned char* PNGtoArray(std::string filename)
{
    try
    {
        png::image<png::rgb_pixel> img(filename); 
    }
    catch(const png::error& e)
    {
        if(std::string(e.what()) != std::string("Not a PNG file"))
        {
            std::cerr << e.what();
            return nullptr;
        }
    }
}

IMG_FORMAT signatureCheck(char* file)
{
    if(file[0] == (char)137 &&
       file[1] == (char)80 &&
       file[2] == (char)78 &&
       file[3] == (char)71 &&
       file[4] == (char)13 &&
       file[5] == (char)10 &&
       file[6] == (char)26 &&
       file[7] == (char)10)
    {
        return IMG_FORMAT::PNG;
    }

    return IMG_FORMAT::UNKNOWN;
}

int main(int argc, char* argv[])
{
    std::fstream fs(argv[1], std::fstream::in | std::fstream::binary);
    if(fs.good())
    {
        char* buf = new char[8];
        fs.read(buf, 8);
        fs.close();
        if(signatureCheck(buf) == IMG_FORMAT::PNG)
        {
            std::cout << "PNG" << std::endl;
            PNGtoArray(argv[1]);
        }
    }

    return 0;
}
