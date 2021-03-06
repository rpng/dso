/**
* This file is part of DSO.
* 
* Copyright 2016 Technical University of Munich and Intel.
* Developed by Jakob Engel <engelj at in dot tum dot de>,
* for more information see <http://vision.in.tum.de/dso>.
* If you use this code, please cite the respective publications as
* listed on the above website.
*
* DSO is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* DSO is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with DSO. If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once
#include <cstring>
#include <iostream>


namespace dso
{


/**
 * This class is used to transport the image data, exposure time, w, h,
 * and timestamp throughout the system.
 * TODO: it may me useful to give this class the stereo pair instead of just the mono imagealready here.
 * See https://docs.opencv.org/3.1.0/d3/d63/classcv_1_1Mat.html -- cv::Mat(int rows, int cols, int type, void *data, size_t step=AUTO_STEP).
 * This is a constructor for a cv::Mat that can be used with a float* so we can use opencv's depth map functions
 */
class ImageAndExposure
{
public:

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    float* imageL;          // irradiance. between 0 and 256 (stereo rectified)
    float* imageR;          // irradiance. between 0 and 256 (stereo rectified)
    int w,h;                // width and height;
    double timestamp;       // timestamp of this image if we have it
    float exposure_time;    // exposure time in ms.
    float baseline;       // baseline times focal length (top right of projection matrix)

    /**
     * Default constructor
     * Will make a set of empty images to size
     */
    inline ImageAndExposure(int w_, int h_, double timestamp_=0) : w(w_), h(h_), timestamp(timestamp_)
    {
        imageL = new float[w*h];
        imageR = new float[w*h];
        exposure_time=1;
    }

    /**
     * Deconstructor
     * deletes our allocated image arrays
     */
    inline ~ImageAndExposure()
    {
        delete[] imageL;
        delete[] imageR;
    }

    /**
     * Simply copies this.exposure_time to other.exposure_time
     */
    inline void copyMetaTo(ImageAndExposure &other)
    {
        other.exposure_time = exposure_time;
    }

    /**
     * Get a copy of the object that points to a separate place in memory.
     */
    inline ImageAndExposure* getDeepCopy()
    {
        ImageAndExposure* img = new ImageAndExposure(w,h,timestamp);
        img->exposure_time = exposure_time;
        memcpy(img->imageL, imageL, w*h*sizeof(float));
        memcpy(img->imageR, imageR, w*h*sizeof(float));
        return img;
    }
};


}
