#include "TransferFunction.hpp"

#include <stdio.h>
#include <cmath>

TransferFunction::TransferFunction(double base_sample_step) {
   base_sample_step_ = base_sample_step;
   min_dens = min_trans = 0.0;
   max_dens = 1.0;
   max_trans = USHRT_MAX;
}

TransferFunction::~TransferFunction() {

}

void TransferFunction::adapt_with_sampling(double sample_step, double base_sample_step) {
   for (int i=0; i<=USHRT_MAX; i++) {
      transfer_[i].w = 1.0f - pow(1.0f - transfer_[i].w, sample_step/base_sample_step);
   }
}

void TransferFunction::adapt_with_sampling(double sample_step) {
   adapt_with_sampling(sample_step, base_sample_step_);
}

bool TransferFunction::map_transfer_function(std::string red, std::string green, std::string blue, std::string alpha) {
	FILE *red_file, *green_file, *blue_file, *alpha_file;

	red_file = fopen(red.c_str(), "rt");
	green_file = fopen(green.c_str(), "rt");
	blue_file = fopen(blue.c_str(), "rt");
	alpha_file = fopen(alpha.c_str(), "rt");

	if (!red_file || !green_file || !blue_file || !alpha_file) {
      fclose(red_file);
      fclose(green_file);
      fclose(blue_file);
      fclose(alpha_file);
		return false;
	}

   for (int i = 0; i <= USHRT_MAX; ++i)
   {
      int position;
      float value;
      fscanf(red_file, "%d %f\n", &position, &value);
      transfer_[position].x = value;
   }

   for (int i = 0; i <= USHRT_MAX; ++i)
   {
      int position;
      float value;
      fscanf(green_file, "%d %f\n", &position, &value);
      transfer_[position].y = value;
   }

   for (int i = 0; i <= USHRT_MAX; ++i)
   {
      int position;
      float value;
      fscanf(blue_file, "%d %f\n", &position, &value);
      // printf("position:%d, value:%f\n", position, value);
      transfer_[position].z = value;
   }
   
   for (int i = 0; i <= USHRT_MAX; ++i)
   {
      int position;
      float value;
      fscanf(alpha_file, "%d %f\n", &position, &value);
      transfer_[position].w = value;
   }

   return true;
}