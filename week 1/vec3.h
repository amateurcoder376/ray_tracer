#include<iostream>
#include<cmath>
#ifndef Vec3_H
#define Vec3_H

class Vec3{
    public:
        float x,y,z;
        Vec3(float x=0, float y=0, float z=0): x(x), y(y), z(z) {}

        Vec3 operator+(const Vec3 &other) const{
            return Vec3(x+other.x,y+other.y,z+other.z);
        }
        Vec3 operator-(const Vec3 &other) const{
            return Vec3(x-other.x,y-other.y,z-other.z);
        }
        Vec3 operator*(float scalar) const{
            return Vec3(x*scalar, y*scalar, z*scalar);
        }
        Vec3 operator/(float scalar) const{
            if(scalar == 0) {
                std::cerr << "Error: Division by zero in Vec3 operator/." << std::endl;
                return Vec3();
            }
            return Vec3(x/scalar, y/scalar, z/scalar);
        }
        Vec3 operator-()const{
            return Vec3(-x,-y,-z);
        }
        float operator[](int index) const{
            if(index<0 ||index>2){
                std::cerr<<"index out of range of Vec3 operator[],try 0,1,2"<<std::endl;
            }else if(index==0) return x;
            else if(index==1) return y;
            else return z;
            return 0;
        }

        float length() const {
            return sqrt(x*x + y*y + z*z);
        }
        Vec3 unit() const{
            return (*this)/length();
        }
        float dot(const Vec3& other) const {
            return x*other.x + y*other.y + z*other.z;
        }
        Vec3 cross(const Vec3& other) const{
            return Vec3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }
        Vec3 reflect(const Vec3& normal)const{
            float d = dot(normal),l=normal.length()*normal.length();
            return (*this - normal*(2*d/l)).unit();
        }
        Vec3 refract(const Vec3& normal,float refractive_index) const{
            float eta = 1/refractive_index;
            Vec3 N = normal.unit(), I = unit();
            float cos = max(-1.0f,min(1.0f,I.dot(N)));
            float k = 1 - eta*eta*(1 - cos*cos);
            if(k < 0) return reflect(normal);
            else return I * eta + N * (eta * (N.dot(I)) - sqrt(k));
        }

};

#endif
