#include "lib_ccx.h"
#include "utility.h"

#ifdef ENABLE_HARDSUBX
//TODO: Correct FFMpeg integration
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include "allheaders.h"
#include "hardsubx.h"

int detect_italics()
{
	//TODO: Get orientation of the detected subtitles
}

int edit_distance(char * word1, char * word2, int len1, int len2)
{
	int matrix[len1 + 1][len2 + 1];
	int i,delete,insert,substitute,minimum;
	for (i = 0; i <= len1; i++)matrix[i][0] = i;
	for (i = 0; i <= len2; i++)matrix[0][i] = i;
	for (i = 1; i <= len1; i++)
	{
		int j;
		char c1;
		c1 = word1[i-1];
		for (j = 1; j <= len2; j++)
		{
			char c2;
			c2 = word2[j-1];
			if (c1 == c2)
			{
				matrix[i][j] = matrix[i-1][j-1];
			}
			else 
			{
				delete = matrix[i-1][j] + 1;
				insert = matrix[i][j-1] + 1;
				substitute = matrix[i-1][j-1] + 1;
				minimum = delete;
				if (insert < minimum)
				{
					minimum = insert;
				}
				if (substitute < minimum)
				{
					minimum = substitute;
				}
				matrix[i][j] = minimum;
			}
		}
	}
	return matrix[len1][len2];
}

#endif
