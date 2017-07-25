#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_VERT 50

enum {x, y};
typedef struct triangle {
    double v1[2];
    double v2[2];
    double v3[2];
} triangle;
double area(triangle a);
double perimeter(double *vertices, int size);
double side(double *p1, double *p2);

int main(void)
{
  int n, idx;
  int triangles;
  int index;
  int xycount;
  double xy;
  double triangle_area;
  double polygon_area;
  double perim;
  double polygon_vertices[MAX_VERT] = {0.0};
  triangle a;
  FILE *data;

  xycount = 0;
  polygon_area = 0;
  if((data = fopen("questao7.txt", "r")) == NULL)
  {
    fprintf(stderr, "Arquivo nao pode ser aberto.");
    exit(EXIT_FAILURE);
  }

  while(fscanf(data, "%lf", &xy) == 1)
    polygon_vertices[xycount++] = xy;
  fclose(data);
  idx = 0;

  triangles = (xycount / 2) - 2;


  for(index = 2, idx = 0; idx < triangles; index += 2, ++idx)
  {
    a.v1[x] = polygon_vertices[0];
    a.v1[y] = polygon_vertices[1];
    a.v2[x] = polygon_vertices[index+0];
    a.v2[y] = polygon_vertices[index+1];
    a.v3[x] = polygon_vertices[index+2];
    a.v3[y] = polygon_vertices[index+3];

    triangle_area = area(a);
    printf("Area do triangulo = %.2f\n", triangle_area);

    polygon_area += triangle_area;
  }
  printf("Area do poligono = %.2f\n", polygon_area);

  perim = perimeter(polygon_vertices, xycount);
  printf("Perimetro do poligono = %.2f\n", perim);

  return 0;
}

double area(triangle a)
{
  double s1, s2, s3, S, area;

  s1 = side(a.v1, a.v2);
  s2 = side(a.v2, a.v3);
  s3 = side(a.v3, a.v1);
  S = (s1 + s2 + s3) / 2;
  area = sqrt(S*(S - s1)*(S - s2)*(S - s3));

  return area;
}

double perimeter(double *vertices, int size)
{
  int idx, jdx;
  double p1[2], p2[2], pfirst[2], plast[2];
  double perimeter;

  perimeter = 0.0;

  pfirst[x] = vertices[0];
  pfirst[y] = vertices[1];

  plast[x] = vertices[size-2];
  plast[y] = vertices[size-1];

  for(idx = 0; idx <= size-3; idx += 2)
  {
    for(jdx = 0; jdx < 4; ++jdx)
    {
      p1[x] = vertices[idx];
      p1[y] = vertices[idx+1];
      p2[x] = vertices[idx+2];
      p2[y] = vertices[idx+3];
    }
    perimeter += side(p1, p2);
  }

  perimeter += side(plast, pfirst);

  return perimeter;
}

double side(double *p1, double *p2)
{
  double s1, s2, s3;

  s1 = (p1[x] - p2[x]);
  s2 = (p1[y] - p2[y]);
  s3 = (s1 * s1) + (s2 * s2);

  return sqrt(s3);
}
