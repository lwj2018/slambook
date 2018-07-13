#include <iostream>
#include <ctime>
using namespace std;

//eigen部分
#include <Eigen/Core>
//稠密矩阵的代数运算
#include <Eigen/Dense>

#define MATRIX_SIZE 50


int main() {
    Eigen::Matrix<float,2,3> matrix_23;
    Eigen::Vector3d v_3d;
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();
    //动态大小的矩阵
    Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> matrix_dynamic;
    //更简单的
    Eigen::MatrixXd matrix_x;

    matrix_23<<1,2,3,4,5,6;

    cout<<matrix_23<<endl;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            int t = matrix_23(i,j);
            cout<<t<<endl;
        }
    }

    v_3d<<3,2,1;
    //矩阵和向量相乘

    //显式转换
    Eigen::Matrix<double,2,1> result = matrix_23.cast<double>()*v_3d;
    cout<<result<<endl;

    //一些矩阵运算
    matrix_33 = Eigen::Matrix3d::Random();
    cout<<matrix_33<<endl<<endl;

    cout<<matrix_33.transpose()<<endl;
    cout<<matrix_33.sum()<<endl;
    cout<<matrix_33.trace()<<endl;
    cout << 10*matrix_33 <<endl;
    cout<<matrix_33.inverse()<<endl;
    cout<<matrix_33.determinant()<<endl;

    //特征值
    //实对称矩阵可以保证对角化成功
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose()*matrix_33);
    cout<<"Eigenvalue = "<<eigen_solver.eigenvalues()<<endl;
    cout<<"Eigenvector = "<<eigen_solver.eigenvectors()<<endl;

    //解方程
    //求解matrix_NN * x = v_Nd 这个方程
    //N的大小在前边的宏里定义，矩阵由随机数生成
    //直接求逆自然是最直接的，但是求逆运算量大

    Eigen::Matrix<double , MATRIX_SIZE,MATRIX_SIZE> matrix_NN;
    matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE,MATRIX_SIZE);
    Eigen::Matrix<double ,MATRIX_SIZE,1> v_Nd;
    v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE,1);

    clock_t time_stt = clock();//计时

    //直接求逆
    Eigen::Matrix<double ,MATRIX_SIZE,1> x = matrix_NN.inverse()*v_Nd;
    cout<<"time use in normal inverse is"<< 1000*(clock() - time_stt)/(double)CLOCKS_PER_SEC
        <<"ms"<<endl;

    //通常用矩阵分解来求，例如QR分解，速度会快很多
    time_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout<<"time use in Qr composition is"<<1000 * (clock() - time_stt)/(double)CLOCKS_PER_SEC
        <<"ms"<<endl;

    return 0;

}