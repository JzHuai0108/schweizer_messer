#include <Eigen/Core>

#include <numpy_eigen/boost_python_headers.hpp>
Eigen::Matrix<double, Eigen::Dynamic, 13> test_double_D_13(const Eigen::Matrix<double, Eigen::Dynamic, 13> & M)
{
	return M;
}
void export_double_D_13()
{
	boost::python::def("test_double_D_13",test_double_D_13);
}

