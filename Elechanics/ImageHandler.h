using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;

namespace Elechanics
{
	public ref class ImageHandler
	{
	private:
		String ^_bitmapPath;
		Bitmap ^_currentBitmap;
		Bitmap ^_bitmapbeforeProcessing;
		Bitmap ^_bitmapPrevCropArea;


	public: ImageHandler();

			property Bitmap ^CurrentBitmap
			{
				Bitmap ^get();
				void set(Bitmap ^value);
			}

			property Bitmap ^BitmapBeforeProcessing
			{
				Bitmap ^get();
				void set(Bitmap ^value);
			}

			property String ^BitmapPath
			{
				String ^get();
				void set(String ^value);
			}

	public: enum class ColorFilterTypes
			{
				Red,
				Green,
				Blue
			};

	public:
		void ResetBitmap();

		void SaveBitmap(String ^saveFilePath);

		void ClearImage();

		void RestorePrevious();

		void SetColorFilter(ColorFilterTypes colorFilterType);

		void SetGamma(double red, double green, double blue);

	private:
		array<Byte> ^CreateGammaArray(double color);
	public:
		void SetBrightness(int brightness);

		void SetContrast(double contrast);

		void SetGrayscale();

		void SetInvert();

		void Resize(int newWidth, int newHeight);

		void RotateFlip(RotateFlipType rotateFlipType);

		void Crop(int xPosition, int yPosition, int width, int height);

		void DrawOutCropArea(int xPosition, int yPosition, int width, int height);

		void RemoveCropAreaDraw();

		void InsertText(String ^text, int xPosition, int yPosition, String ^fontName, float fontSize, String ^fontStyle, String ^colorName1, String ^colorName2);

		void InsertImage(String ^imagePath, int xPosition, int yPosition);

		void InsertShape(String ^shapeType, int xPosition, int yPosition, int width, int height, String ^colorName);

	};
}