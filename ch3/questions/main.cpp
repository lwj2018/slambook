#include <iostream>
#include <Eigen/Core>
//进行稠密运算
#include <Eigen/Dense>
//Eigen几何模块
#include <Eigen/Geometry>

using namespace std;

int main() {
    //question 5
    Eigen::Matrix4d matrix_44 = Eigen::Matrix4d::Random();
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Identity();

    cout<<matrix_44<<endl<<endl;
    cout<<matrix_33<<endl<<endl;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix_44(i,j) = matrix_33(i,j);
        }
    }

    cout<<matrix_44<<endl;

    //question 6
    Eigen::Matrix3d a = Eigen::Matrix3d::Identity();
    cout<<"a = \n"<<a<<endl;
    Eigen::Vector3d b = Eigen::Vector3d::Random();
    cout<<"b = \n"<<b<<endl;
    Eigen::Vector3d x = a.colPivHouseholderQr().solve(b);
    cout<<"x = \n"<<x<<endl;

    x = a.inverse()*b;
    cout<<"x = \n"<<x<<endl;

    //question 7
    Eigen::Isometry3d T1 = Eigen::Isometry3d::Identity();
    Eigen::Isometry3d T2 = Eigen::Isometry3d::Identity();
    Eigen::Quaterniond q1(0.2,0.3,0.1,0.35);
    Eigen::Quaterniond q2(0.4,-0.1,0.2,-0.5);
    Eigen::Vector3d t1(0.3,0.1,0.1);
    Eigen::Vector3d t2(-0.1,0.5,0.3);
    Eigen::Vector3d p(0.5,0,0.2);
    //世界坐标系下p点坐标
    Eigen::Vector3d pw;
    //二号机器人看到的p点坐标
    Eigen::Vector3d p2;

    //四元数归一化
    q1.normalize();
    q2.normalize();

    //求得变换矩阵
    T1.rotate(q1);
    T2.rotate(q2);
    T1.pretranslate(t1);
    T2.pretranslate(t2);

    cout.precision(3);

    cout<<"q1 = \n"<<q1.coeffs()<<endl;
    cout<<"q2 = \n"<<q2.coeffs()<<endl;

    //求得世界坐标系下的p点坐标
    pw = T1.inverse()*p;

    //求得二号机器人看到的p点坐标
    p2 = T2*pw;

    cout<<"p2 = \n"<<p2<<endl;

    return 0;
}