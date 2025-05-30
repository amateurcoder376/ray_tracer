#include<iostream>

using namespace std;

int main(){
    int image_width=256,image_height=256;

    cout<<"P3"<<endl; //it tells its in ascii value
    cout<<"256"<<" "<<"256"<<endl; //rows and coloumn
    cout<<"255"<<endl;//max colour

    //RGB triplets

    for (int j = 0; j < image_height; j++) {
        clog << "\rScanlines remaining: " << (image_height - j) << ' ' << endl << flush;
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    clog << "\rDone.                 \n";
}