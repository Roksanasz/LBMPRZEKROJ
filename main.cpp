//DZIAŁA !
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int L=100;
float U[2][L][L], V[2][L][L], R[2][L][L];
int F[L][L];
const int ex[9] = {0,1,0,-1,0,1,-1,-1,1};
const int ey[9] = {0,0,1,0,-1,1,1,-1,-1};
const int inv[9] = {0,3,4,1,2,7,8,5,6};//tablica odwrotnych kierunków
const float w[9] = {4/9.,1/9.,1/9.,1/9.,1/9.,1/36.,1/36.,1/36.,1/36.};
float U0 = 0.6;

void init()
{

    for(int i=0; i<L; i++)
        {
        for(int j=0; j<L/2; j++)
                    {


            U[0][i][j] = V[0][i][j] = 0;
            U[1][i][j] = V[1][i][j] = 0;
            R[0][i][j] = R[1][i][j] = 1;
            F[i][j] = 0;

            if(j>=0 or j<=L/2-1 )
                F[i][j] = 1;
            if(i==0)
               U[0][i][j] = U[1][i][j] = U0;
        }
    }
}

void LBMTau1 (int c)
{

    float r,u,v,f;




            for(int i=0; i<L; i++)
            {
                for(int j=0; j<L/2; j++)
                {

                if(F[i][j]==0)
                {
                    U[c][i][j] = V[c][i][j] = R[c][i][j] = 0;

                    for(int k = 0; k < 9; k++)
                    {
                        int ip = i+ex[k], jp = j+ey[k], ik = inv[k];//xp, yp - zbieramy z zewnatrz od sasiadow- skupia to co do niego zmierza

                        if(F[ip][jp]==0)
                        {
                            r = R[1-c][ip][jp];
                            u = U[1-c][ip][jp]/r;
                            v = V[1-c][ip][jp]/r;

                            f = w[ik]*r*(1-(3/2.)*(u*u+v*v)+3.*(ex[ik]*u+ey[ik]*v)+(9/2.)*(ex[ik]*u+ey[ik]*v)*(ex[ik]*u+ey[ik]*v));
                            //funkcja stanu w stanie rówowagi w danym węźle - dla danych z poprzedniego kroku

                        }

                        else
                            f = w[ik]*R[1-c][i][j];

                        R[c][i][j] += f;
                        U[c][i][j] += ex[ik]*f;
                        V[c][i][j] += ey[ik]*f;
                    }

                }
            }//koniec L-1

        }//koniec 1 obiegu

}



int main()
{


    init();
    for(int i=0; i<=10000; i++)
    {
        LBMTau1(0);
        LBMTau1(1);
       // cout << u << " " << v << endl;
    }


     std::ofstream plik;
     plik.open ("dane04.vtk", std::fstream::app);
 plik<<  "# vtk DataFile Version 2.0" <<endl;
plik << "KG NN0" <<endl;
plik << "ASCII"<< endl;
plik << "DATASET STRUCTURED_POINTS" << endl;
plik << "DIMENSIONS 100 50 1" << endl;
plik << "ORIGIN 0 0 0" << endl;
plik << "SPACING 1 1 1" << endl;
plik << "POINT_DATA 5000" << endl;
plik << "VECTORS Vectors0 float" << endl;


        for(int j=0; j<L/2; j++)
            {
            for(int i=0; i<L; i++)
            {

                 plik << U[1][i][j] << " " <<  V[1][i][j]  << " " << 0.0 << endl;

            }
        }

 plik.close();

    return 0;

}
