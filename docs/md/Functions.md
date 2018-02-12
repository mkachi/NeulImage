## SnowPlainImage  
### Functions  
#### spGetError  
``` cpp  
SP_SM const char* spGetError();
```  
**Author**  
[맛카치](https://github.com/MKachi)  
  
**Description**  
The errors are stacked on the stack and pulled one by one.  
  
**Returns**  
Error message  
  
#### spLoadImage  
``` cpp  
SP_SM bool spLoadImage(const char* filePath, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
```  
**Author**  
[맛카치](https://github.com/MKachi)  
  
**Description**  
Load png, bmp, tga, jpeg image file.  
  
**Params**  
| Variable | Description |  
|----------|--------------------|  
| filePath | Image file path |  
| width    | Variable to store image width |  
| height    | Variable to store image height |  
|format    | Variable to store image color format |  
| pixels    | Variable to store image pixels |  
  
**Returns**  
| Result | Return Value |  
|--------|--------------|  
| Success| true         |  
| Failed | false        |  
  
#### spLoadImage  
``` cpp  
SP_SM bool spLoadImage(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
```  
**Author**  
[맛카치](https://github.com/MKachi)  
  
**Description**  
Load png, bmp, tga, jpeg image file.  
  
**Params**  
| Variable | Description |  
|----------|--------------------|  
| file | File pointer |  
| width    | Variable to store image width |  
| height    | Variable to store image height |  
|format    | Variable to store image color format |  
| pixels    | Variable to store image pixels |  
  
**Returns**  
| Result | Return Value |  
|--------|--------------|  
| Success| true         |  
| Failed | false        |  
  
#### spLoadPng  
``` cpp  
SP_SM bool spLoadPng(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
```  
**Author**  
[맛카치](https://github.com/MKachi)  
  
**Description**  
Load png image file.  
  
**Params**  
| Variable | Description |  
|----------|--------------------|  
| file | File pointer |  
| width    | Variable to store image width |  
| height    | Variable to store image height |  
|format    | Variable to store image color format |  
| pixels    | Variable to store image pixels |  
  
**Returns**  
| Result | Return Value |  
|--------|--------------|  
| Success| true         |  
| Failed | false        |  
  
#### spLoadBmp  
``` cpp  
SP_SM bool spLoadBmp(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
```  
**Author**  
[맛카치](https://github.com/MKachi)  
  
**Description**  
Load 24bit Bitmap or 32bit Bitmap image file.  
  
**Params**  
| Variable | Description |  
|----------|--------------------|  
| file | File pointer |  
| width    | Variable to store image width |  
| height    | Variable to store image height |  
|format    | Variable to store image color format |  
| pixels    | Variable to store image pixels |  
  
**Returns**  
| Result | Return Value |
|--------|--------------|
| Success| true         |
| Failed | false        |  

#### spLoadTga  
``` cpp  
SP_SM bool spLoadTga(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
```  
**Author**  
[맛카치](https://github.com/MKachi)  
  
**Description**  
Load 24bit Targa or 32bit Targa image file.  
  
**Params**  
| Variable | Description |  
|----------|--------------------|  
| file | File pointer |  
| width    | Variable to store image width |  
| height    | Variable to store image height |  
|format    | Variable to store image color format |  
| pixels    | Variable to store image pixels |  
  
**Returns**  
| Result | Return Value |  
|--------|--------------|  
| Success| true         |  
| Failed | false        |  
  
#### spLoadJpeg  
``` cpp  
SP_SM bool spLoadJpeg(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
```  
**Author**  
[맛카치](https://github.com/MKachi)  
  
**Description**  
Load jpeg image file.  

**Params**  
| Variable | Description |  
|----------|--------------------|  
| file | File pointer |  
| width    | Variable to store image width |  
| height    | Variable to store image height |  
|format    | Variable to store image color format |  
| pixels    | Variable to store image pixels |  
  
**Returns**  
| Result | Return Value |  
|--------|--------------|  
| Success| true         |  
| Failed | false        |  
  
##### [Back](Document.md)