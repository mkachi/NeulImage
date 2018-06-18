## NeulImage 
### Functions  
#### niGetError  
``` cpp  
NL_SM const char* niGetError();
```  
**Author**  
[맛카치](https://github.com/MKachi)  
  
**Description**  
The errors are stacked on the stack and pulled one by one.  
  
**Returns**  
Error message  
  
#### niLoadImage  
``` cpp  
NL_SM bool niLoadImage(const char* filePath, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
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
  
#### niLoadImage  
``` cpp  
NL_SM bool niLoadImage(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
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
  
#### niLoadPng  
``` cpp  
NL_SM bool niLoadPng(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
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
  
#### niLoadBmp  
``` cpp  
NL_SM bool niLoadBmp(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
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
NL_SM bool niLoadTga(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
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
  
#### niLoadJpeg  
``` cpp  
NL_SM bool niLoadJpeg(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
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