// This file automatically generated by create_export_module.py
#include <NumpyEigenConverter.hpp>


void import_14_09_float()
{
	// Without this import, the converter will segfault
	import_array();
	NumpyEigenConverter<Eigen::Matrix< float, 14, 9 > >::register_converter();
}

