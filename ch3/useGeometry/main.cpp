#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

/*******
 * 本程序演示了EIgen几何模块的使用方法
 */

int main() {
    // Eigen/Geometry 模块提供了各种旋转和平移的表示
    // 3D旋转矩阵直接使用 Matrix3d 或 Matrix3f
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    // 旋转向量使用 AngleAxis , 它底层不直接是Matrix,但运算可以当作矩阵（因为重载了运算符）
    // ×××采用 AngleAxisd 完成轴角到旋转矩阵的转换
    Eigen::AngleAxisd rotation_vector(M_PI/4,Eigen::Vector3d(0,0,1));
    // 沿z轴旋转45度
    cout.precision(3);
    cout<<"rotation matrix = \n"<<rotation_vector.matrix() << endl;
    // 用matrix转换成矩阵
    // 也可以直接赋值
    rotation_matrix = rotation_vector.toRotationMatrix();
    // 用 AngleAxisd 可以进行坐标变换
    Eigen::Vector3d v (1,0,0);
    Eigen::Vector3d v_rotated = rotation_vector * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;
    // 或者用旋转矩阵
    v_rotated = rotation_matrix * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

    // 欧拉角： 可以将旋转矩阵直接转换成欧拉角
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles (2,1,0);
    //ZYX顺序，即yaw pitch roll 顺序
    cout<<"yaw pitch roll = "<<euler_angles.transpose()<<endl;

    // 欧式变换矩阵使用 Eigen::Isometry
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity(); // 虽然称为3d，实质上是4X4的矩阵
    T.rotate ( rotation_vector ); // 按照 rotation_vector 进行旋转
    T.pretranslate ( Eigen::Vector3d ( 1,3,4 ) );    // 把平移向量设置成 (1,3,4)
    cout << "Transform matrix = \n" << T.matrix() << endl;

    // 用变换矩阵进行坐标变换
    Eigen::Vector3d v_transformed = T*v;     // 相当于 R*v + t
    cout << "v transformed = "<<v_transformed.transpose()<<endl;

    // 对于仿射和射影变换，使用 Eigen::Affin3d 和 Eigen::Projective3d 即可

    // 四元数
    // 可以直接把 AngleAxis 赋值给四元数，反之亦然
    Eigen::Quaterniond q = Eigen::Quaterniond ( rotation_vector );
    cout << "quaternion = \n"<<q.coeffs() << endl;
    // 使用四元数旋转一个向量，使用重载的乘法即可
    v_rotated = q*v; // 注意数学上是 qvq^{-1}
    cout << "(1,0,0) after rotation = " << v_rotated.transpose()<<endl;


    return 0;
}