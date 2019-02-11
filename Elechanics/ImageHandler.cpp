#include "ImageHandler.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;

namespace Elechanics
{

	ImageHandler::ImageHandler()
	{

	}

	Bitmap ^ImageHandler::CurrentBitmap::get()
	{
		if (_currentBitmap == nullptr)
		{
			_currentBitmap = gcnew Bitmap(1, 1);
		}
		return _currentBitmap;
	}

	void ImageHandler::CurrentBitmap::set(Bitmap ^value)
	{
		_currentBitmap = value;
	}

	Bitmap ^ImageHandler::BitmapBeforeProcessing::get()
	{
		return _bitmapbeforeProcessing;
	}

	void ImageHandler::BitmapBeforeProcessing::set(Bitmap ^value)
	{
		_bitmapbeforeProcessing = value;
	}

	String ^ImageHandler::BitmapPath::get()
	{
		return _bitmapPath;
	}

	void ImageHandler::BitmapPath::set(String ^value)
	{
		_bitmapPath = value;
	}

	void ImageHandler::ResetBitmap()
	{
		if (_currentBitmap != nullptr && _bitmapbeforeProcessing != nullptr)
		{
			Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap->Clone());
			_currentBitmap = safe_cast<Bitmap^>(_bitmapbeforeProcessing->Clone());
			_bitmapbeforeProcessing = safe_cast<Bitmap^>(temp->Clone());
		}
	}

	void ImageHandler::SaveBitmap(String ^saveFilePath)
	{
		_bitmapPath = saveFilePath;
		if (System::IO::File::Exists(saveFilePath))
		{
			System::IO::File::Delete(saveFilePath);
		}
		_currentBitmap->Save(saveFilePath);
	}

	void ImageHandler::ClearImage()
	{
		_currentBitmap = gcnew Bitmap(1, 1);
	}

	void ImageHandler::RestorePrevious()
	{
		_bitmapbeforeProcessing = _currentBitmap;
	}

	void ImageHandler::SetColorFilter(ColorFilterTypes colorFilterType)
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		Color c;
		for (int i = 0; i < bmap->Width; i++)
		{
			for (int j = 0; j < bmap->Height; j++)
			{
				c = bmap->GetPixel(i, j);
				int nPixelR = 0;
				int nPixelG = 0;
				int nPixelB = 0;
				if (colorFilterType == ColorFilterTypes::Red)
				{
					nPixelR = c.R;
					nPixelG = c.G - 255;
					nPixelB = c.B - 255;
				}
				else if (colorFilterType == ColorFilterTypes::Green)
				{
					nPixelR = c.R - 255;
					nPixelG = c.G;
					nPixelB = c.B - 255;
				}
				else if (colorFilterType == ColorFilterTypes::Blue)
				{
					nPixelR = c.R - 255;
					nPixelG = c.G - 255;
					nPixelB = c.B;
				}

				nPixelR = Math::Max(nPixelR, 0);
				nPixelR = Math::Min(255, nPixelR);

				nPixelG = Math::Max(nPixelG, 0);
				nPixelG = Math::Min(255, nPixelG);

				nPixelB = Math::Max(nPixelB, 0);
				nPixelB = Math::Min(255, nPixelB);

				bmap->SetPixel(i, j, Color::FromArgb(safe_cast<Byte>(nPixelR), safe_cast<Byte>(nPixelG), safe_cast<Byte>(nPixelB)));
			}
		}
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}

	void ImageHandler::SetGamma(double red, double green, double blue)
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		Color c;
		array<Byte> ^redGamma = CreateGammaArray(red);
		array<Byte> ^greenGamma = CreateGammaArray(green);
		array<Byte> ^blueGamma = CreateGammaArray(blue);
		for (int i = 0; i < bmap->Width; i++)
		{
			for (int j = 0; j < bmap->Height; j++)
			{
				c = bmap->GetPixel(i, j);
				bmap->SetPixel(i, j, Color::FromArgb(redGamma[c.R], greenGamma[c.G], blueGamma[c.B]));
			}
		}
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}

	array<Byte> ^ImageHandler::CreateGammaArray(double color)
	{
		array<Byte> ^gammaArray = gcnew array<Byte>(256);
		for (int i = 0; i < 256; ++i)
		{
			gammaArray[i] = safe_cast<Byte>(Math::Min(255, safe_cast<int>((255.0 * Math::Pow(i / 255.0, 1.0 / color)) + 0.5)));
		}
		return gammaArray;
	}

	void ImageHandler::SetBrightness(int brightness)
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		if (brightness < -255)
		{
			brightness = -255;
		}
		if (brightness > 255)
		{
			brightness = 255;
		}
		Color c;
		for (int i = 0; i < bmap->Width; i++)
		{
			for (int j = 0; j < bmap->Height; j++)
			{
				c = bmap->GetPixel(i, j);
				int cR = c.R + brightness;
				int cG = c.G + brightness;
				int cB = c.B + brightness;

				if (cR < 0)
				{
					cR = 1;
				}
				if (cR > 255)
				{
					cR = 255;
				}

				if (cG < 0)
				{
					cG = 1;
				}
				if (cG > 255)
				{
					cG = 255;
				}

				if (cB < 0)
				{
					cB = 1;
				}
				if (cB > 255)
				{
					cB = 255;
				}

				bmap->SetPixel(i, j, Color::FromArgb(safe_cast<Byte>(cR), safe_cast<Byte>(cG), safe_cast<Byte>(cB)));
			}
		}
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}

	void ImageHandler::SetContrast(double contrast)
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		if (contrast < -100)
		{
			contrast = -100;
		}
		if (contrast > 100)
		{
			contrast = 100;
		}
		contrast = (100.0 + contrast) / 100.0;
		contrast *= contrast;
		Color c;
		for (int i = 0; i < bmap->Width; i++)
		{
			for (int j = 0; j < bmap->Height; j++)
			{
				c = bmap->GetPixel(i, j);
				double pR = c.R / 255.0;
				pR -= 0.5;
				pR *= contrast;
				pR += 0.5;
				pR *= 255;
				if (pR < 0)
				{
					pR = 0;
				}
				if (pR > 255)
				{
					pR = 255;
				}

				double pG = c.G / 255.0;
				pG -= 0.5;
				pG *= contrast;
				pG += 0.5;
				pG *= 255;
				if (pG < 0)
				{
					pG = 0;
				}
				if (pG > 255)
				{
					pG = 255;
				}

				double pB = c.B / 255.0;
				pB -= 0.5;
				pB *= contrast;
				pB += 0.5;
				pB *= 255;
				if (pB < 0)
				{
					pB = 0;
				}
				if (pB > 255)
				{
					pB = 255;
				}

				bmap->SetPixel(i, j, Color::FromArgb(safe_cast<Byte>(pR), safe_cast<Byte>(pG), safe_cast<Byte>(pB)));
			}
		}
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}

	void ImageHandler::SetGrayscale()
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		Color c;
		for (int i = 0; i < bmap->Width; i++)
		{
			for (int j = 0; j < bmap->Height; j++)
			{
				c = bmap->GetPixel(i, j);
				Byte gray = safe_cast<Byte>(.299 * c.R + .587 * c.G + .114 * c.B);

				bmap->SetPixel(i, j, Color::FromArgb(gray, gray, gray));
			}
		}
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}

	void ImageHandler::SetInvert()
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		Color c;
		for (int i = 0; i < bmap->Width; i++)
		{
			for (int j = 0; j < bmap->Height; j++)
			{
				c = bmap->GetPixel(i, j);
				bmap->SetPixel(i, j, Color::FromArgb(255 - c.R, 255 - c.G, 255 - c.B));
			}
		}
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}

	void ImageHandler::Resize(int newWidth, int newHeight)
	{
		if (newWidth != 0 && newHeight != 0)
		{
			Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
			Bitmap ^bmap = gcnew Bitmap(newWidth, newHeight, temp->PixelFormat);

			double nWidthFactor = safe_cast<double>(temp->Width) / safe_cast<double>(newWidth);
			double nHeightFactor = safe_cast<double>(temp->Height) / safe_cast<double>(newHeight);

			double fx, fy, nx, ny;
			int cx, cy, fr_x, fr_y;
			Color color1 = Color();
			Color color2 = Color();
			Color color3 = Color();
			Color color4 = Color();
			Byte nRed, nGreen, nBlue;

			Byte bp1, bp2;

			for (int x = 0; x < bmap->Width; ++x)
			{
				for (int y = 0; y < bmap->Height; ++y)
				{

					fr_x = safe_cast<int>(Math::Floor(x * nWidthFactor));
					fr_y = safe_cast<int>(Math::Floor(y * nHeightFactor));
					cx = fr_x + 1;
					if (cx >= temp->Width)
					{
						cx = fr_x;
					}
					cy = fr_y + 1;
					if (cy >= temp->Height)
					{
						cy = fr_y;
					}
					fx = x * nWidthFactor - fr_x;
					fy = y * nHeightFactor - fr_y;
					nx = 1.0 - fx;
					ny = 1.0 - fy;

					color1 = temp->GetPixel(fr_x, fr_y);
					color2 = temp->GetPixel(cx, fr_y);
					color3 = temp->GetPixel(fr_x, cy);
					color4 = temp->GetPixel(cx, cy);

					// Blue
					bp1 = safe_cast<Byte>(nx * color1.B + fx * color2.B);

					bp2 = safe_cast<Byte>(nx * color3.B + fx * color4.B);

					nBlue = safe_cast<Byte>(ny * safe_cast<double>(bp1)+fy * safe_cast<double>(bp2));

					// Green
					bp1 = safe_cast<Byte>(nx * color1.G + fx * color2.G);

					bp2 = safe_cast<Byte>(nx * color3.G + fx * color4.G);

					nGreen = safe_cast<Byte>(ny * safe_cast<double>(bp1)+fy * safe_cast<double>(bp2));

					// Red
					bp1 = safe_cast<Byte>(nx * color1.R + fx * color2.R);

					bp2 = safe_cast<Byte>(nx * color3.R + fx * color4.R);

					nRed = safe_cast<Byte>(ny * safe_cast<double>(bp1)+fy * safe_cast<double>(bp2));

					bmap->SetPixel(x, y, System::Drawing::Color::FromArgb(255, nRed, nGreen, nBlue));
				}
			}
			_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
		}
	}

	void ImageHandler::RotateFlip(RotateFlipType rotateFlipType)
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		bmap->RotateFlip(rotateFlipType);
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}

	void ImageHandler::Crop(int xPosition, int yPosition, int width, int height)
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		if (xPosition + width > _currentBitmap->Width)
		{
			width = _currentBitmap->Width - xPosition;
		}
		if (yPosition + height > _currentBitmap->Height)
		{
			height = _currentBitmap->Height - yPosition;
		}
		Rectangle rect = Rectangle(xPosition, yPosition, width, height);
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone(rect, bmap->PixelFormat));
	}

	void ImageHandler::DrawOutCropArea(int xPosition, int yPosition, int width, int height)
	{
		_bitmapPrevCropArea = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(_bitmapPrevCropArea->Clone());
		Graphics ^gr = Graphics::FromImage(bmap);
		Brush ^cBrush = (gcnew Pen(Color::FromArgb(150, Color::White)))->Brush;
		Rectangle rect1 = Rectangle(0, 0, _currentBitmap->Width, yPosition);
		Rectangle rect2 = Rectangle(0, yPosition, xPosition, height);
		Rectangle rect3 = Rectangle(0, (yPosition + height), _currentBitmap->Width, _currentBitmap->Height);
		Rectangle rect4 = Rectangle((xPosition + width), yPosition, (_currentBitmap->Width - xPosition - width), height);
		gr->FillRectangle(cBrush, rect1);
		gr->FillRectangle(cBrush, rect2);
		gr->FillRectangle(cBrush, rect3);
		gr->FillRectangle(cBrush, rect4);
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}

	void ImageHandler::RemoveCropAreaDraw()
	{
		_currentBitmap = safe_cast<Bitmap^>(_bitmapPrevCropArea->Clone());
	}

	void ImageHandler::InsertText(String ^text, int xPosition, int yPosition, String ^fontName, float fontSize, String ^fontStyle, String ^colorName1, String ^colorName2)
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		Graphics ^gr = Graphics::FromImage(bmap);
		if (String::IsNullOrEmpty(fontName))
		{
			fontName = "Times New Roman";
		}
		if (fontSize.Equals(nullptr))
		{
			fontSize = 10.0F;
		}
		Font ^font = gcnew Font(fontName, fontSize);
		if (!String::IsNullOrEmpty(fontStyle))
		{
			FontStyle fStyle = FontStyle::Regular;
			//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
			//		switch (fontStyle.ToLower())
			//ORIGINAL LINE: case "bold":
			if (fontStyle->ToLower() == "bold")
			{
				fStyle = FontStyle::Bold;
			}
			//ORIGINAL LINE: case "italic":
			else if (fontStyle->ToLower() == "italic")
			{
				fStyle = FontStyle::Italic;
			}
			//ORIGINAL LINE: case "underline":
			else if (fontStyle->ToLower() == "underline")
			{
				fStyle = FontStyle::Underline;
			}
			//ORIGINAL LINE: case "strikeout":
			else if (fontStyle->ToLower() == "strikeout")
			{
				fStyle = FontStyle::Strikeout;

			}
			font = gcnew Font(fontName, fontSize, fStyle);
		}
		if (String::IsNullOrEmpty(colorName1))
		{
			colorName1 = "Black";
		}
		if (String::IsNullOrEmpty(colorName2))
		{
			colorName2 = colorName1;
		}
		Color color1 = Color::FromName(colorName1);
		Color color2 = Color::FromName(colorName2);
		int gW = safe_cast<int>(text->Length * fontSize);
		gW = gW == 0 ? 10 : gW;
		LinearGradientBrush ^LGBrush = gcnew LinearGradientBrush(Rectangle(0, 0, gW, safe_cast<int>(fontSize)), color1, color2, LinearGradientMode::Vertical);
		gr->DrawString(text, font, LGBrush, xPosition, yPosition);
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}

	void ImageHandler::InsertImage(String ^imagePath, int xPosition, int yPosition)
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		Graphics ^gr = Graphics::FromImage(bmap);
		if (!String::IsNullOrEmpty(imagePath))
		{
			Bitmap ^i_bitmap = safe_cast<Bitmap^>(Bitmap::FromFile(imagePath));
			Rectangle rect = Rectangle(xPosition, yPosition, i_bitmap->Width, i_bitmap->Height);
			gr->DrawImage(Bitmap::FromFile(imagePath), rect);
		}
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}

	void ImageHandler::InsertShape(String ^shapeType, int xPosition, int yPosition, int width, int height, String ^colorName)
	{
		Bitmap ^temp = safe_cast<Bitmap^>(_currentBitmap);
		Bitmap ^bmap = safe_cast<Bitmap^>(temp->Clone());
		Graphics ^gr = Graphics::FromImage(bmap);
		if (String::IsNullOrEmpty(colorName))
		{
			colorName = "Black";
		}
		Pen ^pen = gcnew Pen(Color::FromName(colorName));
		//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
		//	switch (shapeType.ToLower())
		//ORIGINAL LINE: case "filledellipse":
		if (shapeType->ToLower() == "filledellipse")
		{
			gr->FillEllipse(pen->Brush, xPosition, yPosition, width, height);
		}
		//ORIGINAL LINE: case "filledrectangle":
		else if (shapeType->ToLower() == "filledrectangle")
		{
			gr->FillRectangle(pen->Brush, xPosition, yPosition, width, height);
		}
		//ORIGINAL LINE: case "ellipse":
		else if (shapeType->ToLower() == "ellipse")
		{
			gr->DrawEllipse(pen, xPosition, yPosition, width, height);
		}
		//ORIGINAL LINE: case "rectangle":
		else if (shapeType->ToLower() == "rectangle")
		{
		}
		else
		{
			gr->DrawRectangle(pen, xPosition, yPosition, width, height);

		}
		_currentBitmap = safe_cast<Bitmap^>(bmap->Clone());
	}
}