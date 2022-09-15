#include "../Headers/menor.h"

struct point
{
   double x, y;    // Coordenadas
   // Construtor
   point(double theX = 0, double theY = 0)
   {
      x = theX;
      y = theY;
   }
};

struct point1 : point
{
   int id;        
  
   // Construtor
   point1(double theX = 0, double theY = 0, int theID = 0)
   {
      x = theX;
      y = theY;
      id = theID;
   }
   operator double() const {return x;} 
};

struct point2 : point
{
   int p;          

   // Construtor
   point2(double theX = 0, double theY = 0, int theP = 0)
   {
      x = theX;
      y = theY;
      p = theP;
   }

   operator double() {return y;}
};

struct pointPair
{
   point1 a;       
   point1 b;       
   double dist;    

   // constructor
   pointPair(point1& theA, point1& theB, double theDist)
   {
      a = theA;
      b = theB;
      dist = theDist;
   }
};

double dist(const point& u, const point& v)
{// Retorna a distancia entre os pontos 'u' e 'v'.
   double dx = u.x - v.x;
   double dy = u.y - v.y;
   return sqrt(dx * dx + dy * dy);
}

pointPair closestPair(point1 x[], point2 y[], point2 z[], int l, int r)
{// x[l:r] Pontos ordenados pela coordenada x, r > l.
 // y[l:r] Pontos ordenados pela coordenada y.
 // Retorna o para mais próxima de x[l:r].
   if (r - l == 1)  // Apenas dois pontos
      return pointPair(x[l], x[r], dist(x[l], x[r]));

   if (r - l == 2)
   {// Três pontos
      // Faz a distância entre todos os pontos
      double d1 = dist(x[l], x[l + 1]);
      double d2 = dist(x[l + 1], x[r]);
      double d3 = dist(x[l], x[r]);
      // Acha o par mais próximo
      if (d1 <= d2 && d1 <= d3)
         return pointPair(x[l], x[l + 1], d1);
      if (d2 <= d3)
         return pointPair(x[l + 1], x[r], d2);
      else
         return pointPair(x[l], x[r], d3);
   }

   // Mais de 3 pontos, divide o problema
   int m = (l + r) / 2;    // x[l:m] em A, resto in B

   // Cria ordenados em y em z[l:m] & z[m+1:r]
   int f = l,      // Cursor para z[l:m]
       g = m + 1;  // Cursor para z[m+1:r]
   for (int i = l; i <= r; i++)
      if (y[i].p > m) z[g++] = y[i];
      else z[f++] = y[i];

   // Resolve as duas partes
   pointPair best = closestPair(x, z, y, l, m);
   pointPair right = closestPair(x, z, y, m + 1, r);

   // Acha o melhor par entre as duas partes
   if (right.dist < best.dist)
      best = right;

   merge(z, y, l, m, r);   // Reconstrói y

   // Coloca os pontos dentro best.d do ponto médio em z
   int k = l;                        // Cursor para z
   for (int i = l; i <= r; i++)
      if (fabs(x[m].x - y[i].x) < best.dist)
         z[k++] = y[i];

   // Procura para os 3 melhores pontos
   // Olhando para todos os pares de z[l:k-1]
   for (int i = l; i < k; i++)
   {
      for (int j = i + 1; j < k && z[j].y - z[i].y < best.dist; j++)
      {
         double dp = dist(z[i], z[j]);
         if (dp < best.dist) // Par de pontos mais próximo encontrado
            best = pointPair(x[z[i].p], x[z[j].p], dp);
      }
   }
   return best;
}

pointPair closestPair(point1 x[], int numberOfPoints)
{// Retorna o par de pontos mais próximo do vetor x[0:numberOfPoints-1].
 // Imprime se o vetor tiver quantidade menor que 2 elementos.
   int n = numberOfPoints;
   if (n < 2)
      std::cout << "Number of points must be > 1\n";

   // Ordena a coordenada x
   mergeSort(x, n);

   // Cria um vetor
   point2 *y = new point2 [n];
   for (int i = 0; i < n; i++)
      // Copia o ponto i de x para y e indexa-o
      y[i] = point2(x[i].x, x[i].y, i);
   mergeSort(y, n);  // Ordena a coordenada y

   // Cria um vetor temporário
   point2 *z = new point2 [n];

   // Encontra o par de pontos mais próximo
   return closestPair(x, y, z, 0, n - 1);
}
  
std::vector<Menor::suporte> Menor::calculaMinimo(sf::Vector2f jogador, std::vector<sf::Vector2f> inimigos, int tamanho){
   point1 *x = new point1 [tamanho];
   for(int i = 0; i < tamanho - 1; i++){
      x[i] = point1((double)(inimigos[i].x), (double)(inimigos[i].y), i+1);
   }
   x[tamanho - 1] = point1((double)(jogador.x), (double)(jogador.y), tamanho);
   pointPair best = closestPair(x, tamanho);
   vector<Menor::suporte> vetor_resultado;
   struct suporte valores1;
   suporte valores2;
   valores1.x = best.a.x;
   valores1.y = best.a.y;
   valores2.x = best.b.x;
   valores2.y = best.b.y;
   vetor_resultado.push_back(valores1);
   vetor_resultado.push_back(valores2);
   return vetor_resultado;
}
