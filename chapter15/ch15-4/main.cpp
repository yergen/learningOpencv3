//Example 15-4.Codebook algorithm implementation

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

class CodeBook : public vector<CodeElement>{

public:

	int t;												//count every access

	CodeBook(){ t = 0; }								//Default is an empty book
	CodeBook(int n) : vector<CodeElement>(n) { t = 0; } //Construct book of size n

};

#define CHANNELS 3

class CodeElement{

public:

	uchar learnHigh[CHANNELS];	//High side threshold for learning
	uchar learnLow[CHANNELS];	//Low side threshold for learning
	uchar max[CHANNELS];		//High side of box boundary
	uchar min[CHANNELS];		//Low side of box boundary
	int	  t_last_update;		//Allow us to kill stale entries
	int   stale;				//max negative run (longest period of inactivity)

	CodeElement(){
		for (int i = 0; i < CHANNELS; i++){
			learnHigh[i] = learnLow[i] = max[i] = min[i] = 0;
		}
		t_last_update = 0;
	}

	CodeElement& operator=(const CodeElement& ce){
		for (int i = 0; i < CHANNELS; i++){
			learnHigh[i] = ce.learnHigh[i];
			learnLow[i] = ce.learnLow[i];
			min[i] = ce.min[i];
			max[i] = ce.max[i];
		}
		t_last_update = ce.t_last_update;
		stale = ce.stale;
		return *this;
	}

	CodeElement(const CodeElement& ce) { *this = ce; }
};

//Updates the codebook entry with a new data point
//Note: cbBounds must be of length equal to numChannels
//
int updateCodebook(			 //return CodeBook index
	const Vec3b& p,			 //incoming YUV pixel
	CodeBook&    c,			 //CodeBook for the pixel
	unsigned*	 cbBounds,	 //Bounds for codebook (usually:{10,10,10})
	int			 numChannels //Number of color channels we're learning
	){
	unsigned int high[3], low[3], n;
	for (int n = 0; n < numChannels; n++){
		high[n] = p[n] + *(cbBounds + n); if (high[n]>255) high[n] = 255;
		low[n] = p[n] + *(cbBounds + n); if (low[n] < 0) low[n] = 0;
	}
	//SEE IF THIS FITS AN EXISTING CODEWORD
	//
	int i;
	int matchChannel;
	for (int i = 0; i < c.size(); i++){
		
		matchChannel = 0;
		for (int n = 0; n < numChannels; n++){
			if (//Found an entry for this channel
				(c[i].learnLow[n] <= p[n]) && (p[n] <= c[i].learnHigh[i])
				)
				matchChannel++;
		}

		if (matchChannel == numChannels){ //If an entry was found
			c[i].t_last_update = c.t;

			//adjust this codeword for the first channel
			//
			for (int n = 0; n < numChannels; n++){
				if (c[i].max[n] < p[n])		c[i].max[n] = p[n];
				else if (c[i].min[n]>p[n])	c[i].min[n] = p[n];
			}
			break;
		}
	}

	//OVERHEARD TO TRACK POTENTIAL STALE ENTRIES
	//
	for (int s = 0; s < c.size(); s++){

		//Track which codebook entries are going stale:
		//
		int negRun = c.t - c[s].t_last_update;
		if (c[s].stale < negRun) c[s].stale = negRun;

	}

	//ENTER A NEW CODEWORD IF NEEDED
	//
	if (i == c.size()){ //if no existing codeword found, make one

		CodeElement ce;
		for (int n = 0; n < numChannels; n++){
			ce.learnHigh[n] = high[n];
			ce.learnLow[n] = low[n];
			ce.max[n] = p[n];
			ce.min[n] = p[n];
		}
		ce.t_last_update = c.t;
		ce.stale = 0;
		c.push_back(ce);

		//SLOWLY ADJUST LEARNING BOUNDS
		//
		for (int n = 0; n < numChannels; n++){
			if (c[i].learnHigh[n] < high[n]) c[i].learnHigh[n] += 1;
			if (c[i].learnLow[n] > low[n]) c[i].learnLow[n] -= 1;
		}

		return i;
	}

}

//During learning,after you've learned for some period of time,
//periodically call this to clear out stale codebook entries
//
int clearStaleEntries(// return number of entries cleared
	CodeBook &c		  // Codebook to clean up
	){
	int staleThresh = c.t >> 1;
	int *keep = new int[c.size()];
	int keepCnt = 0;

	//SEE WHICH CODEBOOK ENTRIES ARE TOO STALE
	//
	for (int i = 0; i < c.size(); i++){
		if (c[i].stale > staleThresh)
			keep[i] = 0; //Mark for destruction
		else
		{
			keep[i] = 1; //Mark to keep
			keepCnt += 1;
		}
	}

	//move the entries we want to keep to the front of the vector and then
	//truncate to the correct length once all of the good stuff is saved.
	//
	int k = 0;
	int numCleared = 0;
	for (int ii = 0; ii < c.size(); ii++){
		if (keep[ii]){
			c[k] = c[ii];
			//We have to refresh these entries for next clearStale
			c[k].t_last_update = 0;
			k++;
		}
		else{
			numCleared++;
		}
	}
	c.resize(keepCnt);
	delete[] keep;

	return numCleared;

}

//Given a pixel and a codebook, determine whether the pixel is
//covered by the codebook
//
//NOTES:
//minMod and maxMod must have length numChannels,
//e.g. 3 channels ==> minMod[3], maxMod[3].There is one min and
//one max threshold per channel.
//
//
uchar backgroundDiff( // return 0 => background, 255 => foreground
	const Vec3b& p,	  //Pixel (YUV)
	CodeBook& c,	  //Codebook
	int numChannels,  //Number of channels we are testing
	int* minMod,      //Add this (possibly negative) number onto max level
					  //when determining whether new pixel is foreground
	int* maxMod		  //Subtract this (possibly negative) number from min level
					  //when determining whether new pixel is foreground
	){
	int matchChannel;
	int i;
	//SEE IF THIS FITS AN EXISTING CODEWORD
	//
	for ( i = 0; i < c.size(); i++){
		matchChannel = 0;
		for (int n = 0; n < numChannels; n++){
			if ((c[i].min[n] - minMod[n] <= p[n]) && (p[n] <= c[i].max[n] + maxMod[n])){
				matchChannel++;
			}
			else{
				break;
			}
		}
		if (matchChannel == numChannels){
			break;	//Found an entry that matched all channels
		}
	}

	if (i >= c.size()) return 0;
	return 255;

}

int main(int argc, char** argv)
{

	return 0;
}