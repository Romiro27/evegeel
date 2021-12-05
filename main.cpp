#include <png++/png.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

class Pixel
{
    public:
        Pixel() {};
        Pixel(png::basic_rgb_pixel<png::byte> p)
        {
            this->setRGB(p.red, p.green, p.blue);
        }

        void setRGB(unsigned char r, unsigned char g, unsigned char b)
        {
            this->m_r = r;
            this->m_g = g;
            this->m_b = b;
        }

        unsigned char getRed()
        {
            return this->m_r;
        }

        unsigned char getGreen()
        {
            return this->m_g;
        }
        
        unsigned char getBlue()
        {
            return this->m_b;
        }

       /* unsigned char* getRGB()
        {
            return unsigned char*{this->m_r, this->m_g, this->m_b};
        }*/

    private:
        unsigned char m_r;
        unsigned char m_g;
        unsigned char m_b;
};

class Image
{
    public:
        void load(std::string filename)
        {
            png::image<png::rgb_pixel> img;

            try
            {
                img.read(filename); 
            }
            catch(const png::error& e)
            {
                if(std::string(e.what()) != std::string("Not a PNG file"))
                {
                    throw std::runtime_error(e.what());
                }
            }

            this->m_height = img.get_height();
            this->m_width = img.get_width();

            this->m_pixels.resize(this->m_width);

            for(size_t i = 0; i < this->m_width; i++)
            {
                this->m_pixels[i].resize(this->m_height);
                for(size_t j = 0; j < this->m_height; j++)
                {
                    this->m_pixels[i][j] = Pixel(img.get_pixel(i, j));
                }
            }
        }

    private:
        size_t m_height;
        size_t m_width;
        std::vector<std::vector<Pixel>> m_pixels;
};

enum IMG_FORMAT
{
    UNKNOWN,
    PNG,
    JPEG
};

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
            Image img;
            img.load(argv[1]);
        }
    }

    return 0;
}
