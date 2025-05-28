#include "vec3.h"
#include<iostream>

using namespace std;

int main(){
    float x,y,z;
    cout<<"Enter vector A (x y z): ";
    cin >> x >> y >> z;
    Vec3 A(x,y,z);
    cout<<"Enter vector B (x y z): ";
    cin >> x >> y >> z;
    Vec3 B(x,y,z);
    cout<<"Enter vector N (x y z): ";
    cin >> x >> y >> z;
    Vec3 N(x,y,z);
    cout<<"Enter refractive index (e.g., 4/3 = 1.333): "; 
    float refractive;
    cin>>refractive;
    cout<<endl;cout<<endl;
    cout<<"Vector A: "<<A[0]<<" "<<A[1]<<" "<<A[2]<<" "<<endl;
    cout<<"Vector B: "<<B[0]<<" "<<B[1]<<" "<<B[2]<<" "<<endl;
    cout<<"Vector N: "<<N[0]<<" "<<N[1]<<" "<<N[2]<<" "<<endl;
    cout<<"Refractive Index (eta): "<<refractive<<endl;
    cout<<endl;
    cout<<"A + B = "<<(A+B)[0]<<" "<<(A+B)[1]<<" "<<(A+B)[2]<<" "<<endl;
    cout<<"A - B = "<<(A-B)[0]<<" "<<(A-B)[1]<<" "<<(A-B)[2]<<" "<<endl;
    cout<<"A dot B = "<<A.dot(B)<<endl;
    cout<<"A cross B = "<<(A.cross(B))[0]<<" "<<(A.cross(B))[1]<<" "<<(A.cross(B))[2]<<" "<<endl;
    cout<<"Length of A = "<<A.length()<<endl;
    cout<<"Unit vector of A = "<<(A.unit())[0]<<" "<<(A.unit())[1]<<" "<<(A.unit())[2]<<endl;
    cout<<"Reflect A about N = "<<(A.reflect(N))[0]<<" "<<(A.reflect(N))[1]<<" "<<(A.reflect(N))[2]<<endl;
    cout<<"Refract A through N = "<<(A.refract(N,refractive))[0]<<" "<<(A.refract(N,refractive))[1]<<" "<<(A.refract(N,refractive))[2]<<endl;
}