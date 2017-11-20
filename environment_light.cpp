#include "environment_light.h"
#include <iostream>

namespace CMU462 { namespace StaticScene {

EnvironmentLight::EnvironmentLight(const HDRImageBuffer* envMap)
    : envMap(envMap) {
  // TODO: initialize things here as needed
	if (envMap != NULL)
	{
		p_phi_theta.resize(envMap->w*envMap->h);
		p_theta.resize(envMap->h);

		double theta;
		double normalizer;
		double norm_theta;

		norm_theta = 0.;
		for (size_t j = 0; j < envMap->h; j++)
		{
			normalizer = 0.;
			for (size_t i = 0; i < envMap->w; i++)
			{
				theta = (((double)j + 0.5) / (double)(envMap->h))*PI;
				normalizer = normalizer + (double)(envMap->data[j*envMap->w + i].illum())*sin(theta);
				p_phi_theta[j*envMap->w + i] = normalizer;
			}
			
			if (normalizer != 0.) //Normalizing only if there are non-zero elements
			{
				for (size_t i = 0; i < envMap->w; i++)
				{
					p_phi_theta[j*envMap->w + i] = p_phi_theta[j*envMap->w + i] / normalizer;
				}
			}
			norm_theta = norm_theta + normalizer;
			p_theta[j] = norm_theta;
		}

		//Normalizing p_theta
		if (norm_theta != 0.)
		{
			for (size_t j = 0; j < envMap->h; j++)
			{
				p_theta[j] = p_theta[j] / norm_theta;
				
			}
		}
	}

}

Spectrum EnvironmentLight::sample_L(const Vector3D& p, Vector3D* wi,
                                    float* distToLight,
                                    float* pdf) const {
  // TODO: Implement
	
	double phi, theta;
	size_t y_cord, x_cord;
	double rand_1, rand_2;
	Spectrum output;
	
	//Importance sampling
	//double x_cord, y_cord;
	
	rand_1 = (double)rand() / (double)RAND_MAX;
	rand_2 = (double)rand() / (double)RAND_MAX;

	y_cord = binary_search_vector((size_t)0, p_theta.size() - 1, rand_1, &p_theta);

	x_cord = (binary_search_vector((y_cord*envMap->w), (y_cord + (size_t)1)*envMap->w - (size_t)1, rand_2, &p_phi_theta))%envMap->w;
	
	phi = ((double)x_cord + 0.5) / (double)envMap->w*2.*PI;
	theta = ((double)y_cord + 0.5) / (double)envMap->h*PI;
	*wi = Vector3D(-cos(theta)*sin(phi), cos(theta), cos(theta)*cos(phi));
	*distToLight = INF_D;
	
	output = envMap->data[(y_cord*envMap->w) + x_cord];
	
	*pdf = p_theta[y_cord] * p_phi_theta[x_cord];
	return output;

}

Spectrum EnvironmentLight::sample_dir(const Ray& r) const {
  // TODO: Implement
	
	Vector3D r_direction;
		
	double phi, theta, x_cord, y_cord;

	r_direction = r.d;
	r_direction.normalize();

	//phi from 0 to 2*PI
	//theta from 0 to PI
	//atan2 from -PI to PI
	// acos from 0 to PI
	phi = atan2(-r_direction.x ,r_direction.z);
	theta = acos(r_direction.y);

	if (phi < 0.)
	{
		phi = 2* PI + phi;
	}

	x_cord = (phi / (2.*PI))*(envMap->w - 1);
	y_cord = (theta / (PI))*(envMap->h - 1);

	return bilinear_inter(x_cord, y_cord);
}

Spectrum EnvironmentLight::bilinear_inter(double x_cord, double y_cord) const
{
	double x_low, x_high, y_low, y_high;
	Spectrum s_y_low, s_y_high, s_final;

	x_low = floor(x_cord);
	x_high = ceil(x_cord);

	y_low = floor(y_cord);
	y_high = ceil(y_cord);

	if (x_low != x_high)
	{
		s_y_low = (x_high + 0.5 - x_cord)*envMap->data[(size_t)y_low*envMap->w + (size_t)x_low] + (x_cord - x_low + 0.5)*envMap->data[(size_t)y_low*envMap->w + (size_t)x_high];
		s_y_high = (x_high + 0.5 - x_cord)*envMap->data[(size_t)y_high*envMap->w + (size_t)x_low] + (x_cord - x_low + 0.5)*envMap->data[(size_t)y_high*envMap->w + (size_t)x_high];
	}
	else
	{
		s_y_low = envMap->data[(size_t)y_low*envMap->w + (size_t)x_low];
		s_y_high = envMap->data[(size_t)y_high*envMap->w + (size_t)x_low];
	}

	if (y_low != y_high)
	{
		s_final = (y_high + 0.5 - y_cord)*s_y_low + (y_cord - y_low + 0.5)*s_y_high;
	}
	else
	{
		s_final = s_y_low;
	}

	
	return s_final;
}

size_t EnvironmentLight::binary_search_vector(size_t begin, size_t end, double value, const std::vector<double>* start) const
{
	if (begin == end || begin + 1==end)
	{
		
		return begin;
	}
	
	size_t middle;
	middle = (begin + end) / 2;

	if ((*start)[middle] == value) return middle;

	if ((*start)[middle] < value) return binary_search_vector(middle, end, value, start);

	if ((*start)[middle] > value) return binary_search_vector(begin, middle, value, start);
	
}

} // namespace StaticScene
} // namespace CMU462
