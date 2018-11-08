# Project Proposal

## Summary

My project involves identifying birds' species based on their songs. I will 
limit the bird species to a specific region, since obtaining enough audio data 
for every species of bird will be impossible. Currently, I am thinking about 
implementing my program on birds in Madagascar, but I may change the region 
later on. I will have a GUI that allows the user to submit an audio file of a 
bird's song. My program will then identify the species of the bird and display 
an image of it.

### How the Program will Work

**Outside of the program:**
The classifier will be trained on the audio data and the model produced will be 
stored in a file.

**The program:**
Upon running the program, a window will open with a button. Pressing the button 
will allow the user to select an audio file from their computer. The audio file 
will be classified to a bird species based on the model stored in the pre-
produced file. The window will then display an image of the bird species as well
as relevant information such as its common name, its scientific name, its size,
etc. The user may select another audio file for classification by pressing the 
button again.

## Development Steps

1. **Obtain Audio Recordings and Extract Feature Set:**
	I will start by obtaining audio recordings of the songs of the bird species.
	I will need to analyze the audio data and decide which features to extract 
	to use with my classifier.

2. **Make and Tune the Classifier:**
	I will write a neural network classifier and use cross validation to test
	it. I will use those results to tune the specifications of my classifier 
	to make a more accurate model. 

3. **Make the GUI:**
	I will make a simple window with a button that, when pressed, allows the 
	user to look through their computer for an audio file. I will display a
	picture of the species that the audio is classifies as and information 
	regarding that species. I will make it so that pressing the button again
	allows the user to select another file.

## Background

I completed a machine learning project involving the identification of malware
during a program at Boston University. I completed a digit identification 
machine learning program in cs 126.

## Resources

- Bird song recordings
	- xeno-canto (https://www.xeno-canto.org/)
- libraries
	- GUI
		- ofxGUI
	- Audio Analysis
		- ofxAudioAnalyzer (https://github.com/leozimmerman/ofxAudioAnalyzer)
		- MARSYAS (http://marsyas.info/)
- guides/tutorials/studies
	- similar study (https://ieeexplore.ieee.org/document/6123334)
	- neural networks tutorial (https://www.youtube.com/watch?v=KkwX7FkLfug)
	- https://www.analyticsindiamag.com/using-deep-learning-for-sound-classification-an-in-depth-analysis/
	- https://www.kdnuggets.com/2017/12/audio-classifier-deep-neural-networks.html
