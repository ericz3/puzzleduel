# Project Proposal - Object Identifier

## Summary

My project involves identifying objects in images. I will have a GUI that allows
the user to submit an image. My program will be able to identify chosen objects 
within that image and will display some basic information about those objects.

### User Experience

Upon running the program, a window will open with a button. Pressing the button 
will allow the user to select an image file from their computer. The user will 
then have the option to either classify the entire image (if the image contains 
a single object), or drag and select a region in the image that contains a single
object to classify. After the object is classified, the name of the object will 
be displayed as well as basic info such as its color, dictionary definition, etc.
The user will have the option to upload another image by pressing the button 
again.

## Development Checklist

### Core Goals
- [x] Obtain image data
- [ ] Set up libraries
- [ ] Learn and implement OpenCV
	- [ ] manipulate images (crop, resize, etc.)
- [ ] Learn and implement Tensorflow
	- [ ] train on image data
	- [ ] save model
	- [ ] identify objects
- [ ] GUI
	- [ ] buttons
	- [ ] browse for and upload image from computer
	- [ ] browse for and upload image from url
	- [ ] display text
	- [ ] links

### Stretch Goals
- [ ] User history that contains previously submitted images
- [ ] Glossary containing all objects as well as example images
- [ ] Count number of other objects in image that are the same as one selected
- [ ] Classify all objects in image at once
	- [ ] Allow user to select an object to display info

## Resources

- Images
	- [ImageNet](http://image-net.org/)
- Libraries
	- GUI
		- [ofxGUI](https://openframeworks.cc/documentation/ofxGui/)
	- Image Analysis
		- [ofxCv](https://github.com/kylemcdonald/ofxCv)
		- [tensorflow](https://www.tensorflow.org/)