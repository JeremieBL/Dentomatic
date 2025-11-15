//
//  ImageAlign.cpp
//

#include <iostream>
#include <vector>
#include <cmath>

#include "Eigen/Dense"

#define cimg_display 0

#include "CImg.h"

using namespace Eigen;
using namespace cimg_library;
using namespace std;


float F(float x, float y)
{
    return(8 * exp(-(x * x + y * y) / 5));
}

int main(int argc, const char* argv[]) {
  
    //CImg<unsigned char> randomTexture(300, 300, 1, 1);
    //CImg<unsigned char> champVectoriel(300, 300, 1, 1);

    //cimg_forXY(randomTexture, x, y)
    //{
    //    int randNumb = (rand() % 256) + 1;

    //    const int color[] = { randNumb };
    //    randomTexture.draw_point(x, y, color, 1.f);
    //}

    //randomTexture.save("RandomTexture.ppm");


    //cimg_forXY(champVectoriel, x, y)
    //{
    //    Vector2f coord(x / 30.f - 5.f, y / 30.f - 5.f);
   
    //    //cout << " x " << coord.x()<<" y "<< coord.y() << endl;

    //    float delta = 0.0005;

    //    float Gx = (F(coord.x() + delta, coord.y()) - F(coord.x(), coord.y())) / delta;
    //    float Gy = (F(coord.x(), coord.y() + delta) - F(coord.x(), coord.y())) / delta;
    //    //cout << " Gx " << Gx <<" Gy "<< Gy<< endl;

    //    float alpha = (0.976 * 2*3.1415926535897932);
   
    //    float Vx = cos(alpha) * Gx - sin(alpha) * Gy;
    //    float Vy = sin(alpha) * Gx - cos(alpha) * Gy;
  
    //    float intensity = 0;
    //    int nbr = 0;

    //    float a = Vy / Vx;
    //    float b = Vx / Vy;
    //    a = b;

    //    float dist = 0;

    //    int startx = x;
    //    int starty = y;

    //    bool maxtouched = false;

    //    for (int i = startx; !maxtouched; i++)
    //    {
    //        int j = (i - startx) * a + starty;
    //        
    //     //   for (int refy = j; (refy - starty) * b + startx == i; i++)
    //        {
    //            Vector2f dir(i - startx, j - starty);
    //            dist = dir.x() * dir.x() + dir.y() * dir.y();

    //            if (dist > 400)
    //            {
    //                maxtouched = true;
    //                break;
    //            }

    //            if (i >= 0 && i <= 300 && j >= 0 && j <= 300)
    //            {
    //                intensity += randomTexture(i, j);
    //                nbr++;
    //            }

    //            dir = Vector2f(startx - i, starty - j);
    //            if (i >= 0 && i <= 300 && j >= 0 && j <= 300)
    //            {
    //                intensity += randomTexture(i, j);
    //                nbr++;
    //            }
    //        }
    //    }        

    //    const int color[] = { (float)intensity/nbr };

    //    champVectoriel.draw_point(x, y, color, 1.f);
    //}

    //champVectoriel.save("ChampVectoriel.ppm");









  //  //  #1 Doit loader une banque d'images...commençons par 1 seule en premier
  //  vector<CImg<unsigned char>> images;
  //  cout << "Try to initiate matrixes " << endl;
  //  
  //  int N = 20;
  //  int K = 200;

  //  MatrixXd MatrixFace(K * K, N);
  //  MatrixXd unfold(K * K, 1);
  //  MatrixXd mean(K * K, 1);

  //  cout << "Matrix were initiated " << endl;

  //  //  Faces K x K bitmap of pixels
  //  //  Unflod is vector of K^2 
  //  //  MatrixFace is the big matrix K^2 x N
  //  //  PCA_Matrix is the K^2 x m eigen vector
  //  //  1 row is 1 EigenVector, fold into a new photo ( each are vector of F^2 dimensions


  //  //  Formatage des images        //  Si besoin est
  //  for (char i = 0; i < N; i++)
  //  {
  //      string incomingname = "BD/face" + to_string(i);
  //      incomingname += ".pgm";
  //      
  //      CImg<unsigned char> image(incomingname.c_str());

  //      image.resize(K, K);
  //      image = image.get_channel(0);
  //      images.push_back(image);
  //  }

  //  cout << "Faces were loaded" << endl;

  //  //  Unfold a un vector d'une matrice
  //  for (int i = 0; i < N; i++)
  //  {
  //      cimg_forXY(images[i], x, y)
  //      {
  //          //  Ici, c'est conditionnel à ce que les images aient été formatées...
  //          unfold(x + y * K, 0) = images[i](x, y);
  //      }
  //      MatrixFace.col(i) = unfold.col(0);
  //  }
  //  cout << "MatrixFace was build " << endl;

  //  //  PCA
  //
  //  //  Mean
  //  mean.col(0) = MatrixFace.rowwise().mean();
  //  cout << "Mean was calculated " << endl;
  //  
  //  //  Substract the mean
  //  MatrixFace = MatrixFace.colwise() - mean.col(0);
  //  cout << "Mean was substracted " << endl;

  //  MatrixXd Q = (MatrixFace.transpose() * MatrixFace) / (N - 1);
  //  EigenSolver<MatrixXd> ES(Q);

  //  MatrixXd EigenTrickFaces = ES.eigenvectors().real();
  //  //int maxIndex;
  //  //ES.eigenvalues().real().maxCoeff(&maxIndex);
  //  //Vector2d eigen1((ES.eigenvectors().col(maxIndex)).real());

  //  cout << "EigenTrickFaces were calculated " << endl;

  ////  MatrixFace = MatrixFace.colwise() + mean.col(0);

  //  //  Calcul pour retrouver les eigen faces
  //  MatrixXd RebuildMatrix = MatrixFace * EigenTrickFaces;

  ////  cout << mean.col(0).transpose();
  //  //*eigen1.transpose();
  //  
  //  //cout << EigenTrickFacesEigenTrickFaces << endl;

  //  //  #2 Quantifier l'impact du nbr d'images sur la qualité de la représentation dans l'espace réduit.
 
  //  //  #3 Production de n visage propres dans l'espace réduit (soit les eigen faces)

  //  //  #4 recherche dans l'espace de dimension réduite à partir d'une image quelconque
  //  //  et produire une liste des k meilleurs résultats ( ou du meilleur résultat).

  //  //  #5 Justification du nombre n de visage propres (ou vecteur propres) à utiliser :
  //  //  doit être justifié en quantifiant l'impact du nombre de dimensions
  //  //  sur la quanlité de la représentation dans l'espace réduit.

  //  //  #6 Optimiser tout ça si ce n'est pas déjà fait
  //  //



  //  //  Refabrication de la grosse matrice pour chaque image
  //  for (int i = 0; i < N; i++)
  //  {
  //      unfold.col(0) = RebuildMatrix.col(i);

  //      cimg_forXY(images[i], x, y)
  //      {
  //          const float color[] = { (float) unfold(x + y * K, 0) };
  //          images[i].draw_point(x, y, color, 1.f);
  //      }

  //      string imageName = "ImagesPropres/face" + to_string(i);
  //      imageName += ".ppm";
  //      images[i].save(imageName.c_str());
  //  }

    return 0;
}

