#include "window_factory.hpp"

#include <cmath>
#include <string>
#include <iostream>

WindowFactory::WindowFactory() {

}

std::function<double(double)> WindowFactory::make_window(
	WindowType window_type, int radius, 
	std::map<std::string, double> interpolation_settings) {
	switch (window_type) {
		case WindowType::RECTANGLE: {
			return [] (double x) {
				return 1.0f;
			};
		}
		case WindowType::BARTLETT: {
			double m_factor = 1.0f / ((double)radius);

			return [m_factor] (double x) {
				return 1.0f - (fabs(x)*m_factor);
			};
		}
		case WindowType::BLACKMAN: {
			double m_factor1 = M_PI / (double)radius;
			double m_factor2 = 2.0f * M_PI / (double)radius;

			return [m_factor1, m_factor2] (double x) {
				return (0.42 + 0.5 * std::cos(x*m_factor1) 
					+ 0.08 * std::cos(x*m_factor2));
			};
		}
		case WindowType::COSINE_BELL: {
			double m_factor = M_PI / ((double)radius);

			return [m_factor] (double x) {
				return 1.0f + std::cos(x*m_factor);
			};
		}
		case WindowType::COSINE_WINDOW: {
			double m_factor = M_PI / (2.0f * (double)radius);

			return [m_factor] (double x) {
				return std::cos(x*m_factor);
			};
		}
		case WindowType::HAMMING: {
			double m_factor = M_PI / (double)radius;

			return [m_factor] (double x) {
				return 0.54f + 0.46f * std::cos(x*m_factor);
			};
		}
		case WindowType::HANN: {
			double m_factor = M_PI / (double)radius;

			return [m_factor] (double x) {
				return 0.5f + 0.5f * std::cos(x*m_factor);
			};
		}
		case WindowType::LANCZOS: {
			double m_factor = M_PI / (double)radius;

			return [m_factor] (double x) {
				if (x == 0.0)
					return 1.0;

				double z = m_factor * x;
				return std::sin(z) / z;
			};
		}
		case WindowType::WELCH: {
			double m_factor = 1.0f / ((double)(radius*radius));

			return [m_factor] (double x) {
				return 1.0f - x * m_factor * x;
			};
		}
		case WindowType::KAISER: {
			double m_factor = 1.0f / ((double)(radius*radius));
			double alpha = interpolation_settings["alpha"];

			return [m_factor, alpha] (double x) {
				// modified bessel function
				auto bessi0 = [] (float x) {
					float ax, ans;
					double y;

					if ((ax=fabs(x)) < 3.75f) {
						y = x/3.75f;
						y *= y;

						ans = 1.0+y*(3.5156229+y*(3.0899424+y*(1.2067492+y*
							(0.2659732+y*(0.360768e-1+y*0.45813e-2)))));
					}
					else {
						y = 3.75/ax;
						ans = (exp(ax)/sqrt(ax))*(0.39894228+y*(0.1328592e-1+y*
							(0.225319e-2+y*(-0.157565e-2+y*(0.916281e-2+y*
							(-0.2057706e-1+y*(0.2635537e-1+y*(-0.1647633e-1+y*
							0.392377e-2))))))));
					}
					return ans;
				};

				// kaiser window
				return bessi0(alpha*sqrt(1-x*m_factor*x))/bessi0(alpha);
			};	
		}
		default:
			return NULL;
	}
}