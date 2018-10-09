#ifndef BITMAP_H
#define BITMAP_H

#include <GL/glew.h>
#include <string>
#include <vector>

/**
 * @brief The Image class is a wrapper to use images as textures
 *
 * You can use this class to load textures and send them
 * to your shader. The image will be present in
 * 32-bit RGBA format (4 * 8 bit)
 */
class Image
{
public:

    /**
     * @brief Image constructor
     * @param path The path of the image
     */
    Image(std::string path);

    /**
     * @brief getWidth Getter for the image width
     * @return the width of the image in pixels
     */
    unsigned int getWidth() const;

    /**
     * @brief getHeight Getter for the image height
     * @return the height of the image in pixels
     */
    unsigned int getHeight() const;

    /**
     * @brief getData Getter for the image data
     * @return the image data as uchar array
     *
     * You can pass this data directly to the shader
     */
    void *getData();

private:
    /**
     * @brief load Loads the image
     * @param path the path to the image
     */
    void load(std::string path);
    unsigned width_, height_;
    std::vector<unsigned char> data_;
};

#endif // BITMAP_H
