#include <Eigen/Core>

#include <numpy_eigen/boost_python_headers.hpp>
Eigen::Matrix<double, 9, 7> test_double_09_07(const Eigen::Matrix<double, 9, 7> & M)
{
	return M;
}
void export_double_09_07()
{
	boost::python::def("test_double_09_07",test_double_09_07);
}

