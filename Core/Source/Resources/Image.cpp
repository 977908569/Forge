#include "Image.h"
#include "Platform/Api/File.h"
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
#include "Resources.h"
#include "Platform/Api/FileSystem.h"
#include "Core/Engine.h"

namespace Forge
{
	
	Image::Image()
	{}

	Image::~Image()
	{
		_pixels.clear();
	}

    void Image::Create(const Vector2i& size, Color color)
    {
        _pixels.resize(size.x * size.y * 4);
        for(int i = 0; i < size.x; i++)
        {
            for(int j = 0; j < size.y; j++)
            {
                SetPixel(i, j, color);
            }
        }
    }

    void Image::Save(String filename)
	{
		stbi_write_png(filename.cString(), _size.x, _size.y, 4, _pixels.data(), 0);
	}

	const Vector2i& Image::GetSize() const
	{
		return _size;
	}

	void Image::SetPixel(uint x, uint y, const Color& color)
	{
		if (_pixels.size() < (x + y * _size.x) * 4)
			return;

		byte* pixel = &_pixels[(x + y * _size.x) * 4];
		
		pixel[0] = color.r;
		pixel[1] = color.g;
		pixel[2] = color.b;
		pixel[3] = color.a;
	}

	Color Image::GetPixel(uint x, uint y)
	{
		byte *pixel = &_pixels[(x + y * _size.x)];
		return Color(pixel[0], pixel[1], pixel[2], pixel[3]);
	}

	const byte* Image::GetPixels() const
	{
		return _pixels.data();
	}

	void Image::FlipX()
	{
		if (_pixels.size() > 0)
		{
			uint rowSize = _size.x * 4;
			for(int y = 0; y < _size.y; y++)
			{
				byte* left = &*(_pixels.begin() + y * rowSize);
				byte* right = &*(_pixels.begin() + (y + 1) * rowSize - 4);

				for (int x = 0; x < _size.x / 2; x++)
				{
					SwapColors(left, right, 4);

					left += 4;
					right -= 4;
				}
			}
		}
	}

	void Image::FlipY()
	{
		if (_pixels.size() > 0)
		{
			uint rowSize = _size.x * 4;
			byte* top = &*_pixels.begin();
			byte* bottom = &*(_pixels.end() - rowSize);

			for (int y = 0; y < _size.y / 2; y++)
			{
				SwapColors(top, bottom, rowSize);

				top += rowSize;
				bottom -= rowSize;
			}
		}
	}

	void Image::Load(const String& filename)
	{
		resourceName = filename;
		File file = engine->getFileSystem()->readFile(filename);
		byte* pixels = stbi_load_from_memory(file.getData(), file.getSize(), &_size.x, &_size.y, &fileChannels, 4);
		_pixels.resize(_size.x * _size.y * 4);

		memcpy(_pixels.data(), pixels, _pixels.size() * sizeof(byte));
		delete[] pixels;
	}

	void Image::UnLoad()
	{
		_pixels.clear();
	}

	void Image::SwapColors(byte* color1, byte* color2, uint count)
	{
		byte* left = color1;
		byte* right = color2;
		byte* end = left + count;

		while(left != end)
		{
			byte temp = *left;
			*left = *right;
			*right = temp;
			left++;
			right++;
		}
	}
}
