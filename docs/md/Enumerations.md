## SnowPlainImage  
### Enumerations  
#### ImageType  
``` cpp  
enum class ImageType
{
    Png,
    Bmp,
    Tga,
    Jpeg,
    Unknown,
};
```  
**Description**  
ImageType is images file format.  
  
**Values**  
| Value   | Description                                |  
|---------|--------------------------------------------|  
| Png     | png image format.                          |  
| Bmp     | 24bit Bitmap or 32bit Bitmap image format. |  
| Tga     | 24bit Targa or 32bit Targa image format.   |  
| Jpeg    | jpeg image format.                         |  
| Unknown | Unsupported image format.                  |  
#### ColorFormat  
``` cpp  
enum class ColorFormat
{
    RGB,
    RGBA,
};
```  
**Description**  
ColorFormat is images color format.  
  
**Values**  
| Value   | Description                                  |  
|---------|----------------------------------------------|  
| RGB     | Image color format (Red, Green, Blue)        |  
| RGBA    | Image color format (Red, Green, Blue, Alpha) |  
  
##### [Back](Document.md)