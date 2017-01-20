#ifndef FUG_CORE_MATHTYPES_HPP
#define FUG_CORE_MATHTYPES_HPP


#include <Eigen/Dense>
#include <gl_core_4_1.h>


#define PI 3.14159265358979323846


namespace fug {

    ///  Typedefs

    typedef Eigen::Matrix<float, 2, 1, Eigen::DontAlign> Vector2f;
    typedef Eigen::Matrix<float, 3, 1, Eigen::DontAlign> Vector3f;
    typedef Eigen::Matrix<float, 4, 1, Eigen::DontAlign> Vector4f;

    typedef Eigen::Matrix<float, 2, 2, Eigen::DontAlign> Matrix2f;
    typedef Eigen::Matrix<float, 3, 3, Eigen::DontAlign> Matrix3f;
    typedef Eigen::Matrix<float, 4, 4, Eigen::DontAlign> Matrix4f;

    typedef Eigen::Matrix<GLfloat, 2, 1, Eigen::DontAlign> Vector2Glf;
    typedef Eigen::Matrix<GLfloat, 3, 1, Eigen::DontAlign> Vector3Glf;
    typedef Eigen::Matrix<GLfloat, 4, 1, Eigen::DontAlign> Vector4Glf;

    typedef Eigen::Matrix<GLfloat, 2, 2, Eigen::DontAlign> Matrix2Glf;
    typedef Eigen::Matrix<GLfloat, 3, 3, Eigen::DontAlign> Matrix3Glf;
    typedef Eigen::Matrix<GLfloat, 4, 4, Eigen::DontAlign> Matrix4Glf;

    typedef Eigen::Quaternion<float>  Quaternionf;
    typedef Eigen::Quaternion<GLfloat>  QuaternionGlf;

} // namespace fug


#endif // FUG_CORE_MATHTYPES_HPP
