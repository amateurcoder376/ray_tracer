#include<iostream>
#include<cmath>
#ifndef vec3_H
#define vec3_H

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

class vec3{
    public:
        float x,y,z;
        vec3(float x=0, float y=0, float z=0): x(x), y(y), z(z) {}

        vec3 operator+(const vec3 &other) const{
            return vec3(x+other.x,y+other.y,z+other.z);
        }
        vec3 operator-(const vec3 &other) const{
            return vec3(x-other.x,y-other.y,z-other.z);
        }
        vec3 operator*(float scalar) const{
            return vec3(x*scalar, y*scalar, z*scalar);
        }
        vec3 operator/(float scalar) const{
            if(scalar == 0) {
                std::cerr << "Error: Division by zero in vec3 operator/." << std::endl;
                return vec3();
            }
            return vec3(x/scalar, y/scalar, z/scalar);
        }
        vec3 operator-()const{
            return vec3(-x,-y,-z);
        }
        float operator[](int index) const{
            if(index<0 ||index>2){
                std::cerr<<"index out of range of vec3 operator[],try 0,1,2"<<std::endl;
            }else if(index==0) return x;
            else if(index==1) return y;
            else return z;
            return 0;
        }


        float length() const {
            return sqrt(x*x + y*y + z*z);
        }
        vec3 unit() const{
            return (*this)/length();
        }
        float dot(const vec3& other) const {
            return x*other.x + y*other.y + z*other.z;
        }
        vec3 cross(const vec3& other) const{
            return vec3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }
        vec3 reflect(const vec3& normal)const{
            float d = dot(normal),l=normal.length()*normal.length();
            return (*this - normal*(2*d/l)).unit();
        }
        vec3 refract(const vec3& normal,float refractive_index) const{
            float eta = 1/refractive_index;
            vec3 N = normal.unit(), I = unit();
            float k = 1 - eta*eta*(1 - (N.dot(I))*(N.dot(I)));
            if(k < 0) return reflect(normal);
            else return I * eta + N * (eta * (N.dot(I)) - sqrt(k));
        }

};

#endif