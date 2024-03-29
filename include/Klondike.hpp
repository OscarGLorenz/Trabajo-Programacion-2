/******************************************************************************
* ARCHIVO :        Klondike.hpp
*
* DESCRIPCIÓN :
*       Clases principales del programa, algoritmo de resolución y navegación
*       por el mapa
*
* AUTOR :    Óscar García Lorenz
******************************************************************************/

#ifndef KLONDIKE_HPP
#define KLONDIKE_HPP

#include <vector>
#include <list>

// Tamaño del Laberinto
#define SIZE 23

/*
 * Clase enumerada: Direction
 * --------------------------------------------------------
 *  Representa una dirección en el mapa
*/
enum class Direction {
  NORTH, EAST, SOUTH, WEST, NORTHEAST, NORTHWEST, SOUTHWEST, SOUTHEAST, NONE
};


/*
 * Clase: Point
 * --------------------------------------------------------
 *   Representa un punto en el mapa, acorde con los índices del mapa.
 */
class Point {
public:
  /*
   * Constructores
   * --------------------------------------------------------
   *   Genera un punto con las coordenadas x e y dados.
   *   Es opcional una dirección
   */
  Point(short X, short Y);
  Point(short X, short Y, Direction dir);

  /*
   * Operador == y !=
   * --------------------------------------------------------
   *   Comprueba si dos puntos son iguales o distintos
   */
  bool operator==(const Point other) const;
  bool operator!=(const Point other) const;

  short x; // Primer coordenada
  short y; // Segunda coordenada
  Direction dir; //Variable auxiliar para ver la dirección
};

/*
 * Clase: SearchResult
 * --------------------------------------------------------
 *  Para no ensuciar el algoritmo de resolver mapas con
 *  llamadas a openGL, se crea un vector de estas clases
 *  Representa un paso del resolvedor del mapa
 */
class SearchResult {
public:
  SearchResult(Point p, std::list<Point> l, int d);
  Point from; // Posición actual
  std::list<Point> adjacent; // Opciones
  int distance; // Distancia a esas nuevas opciones
};

/*
 * Clase: Klondike
 * --------------------------------------------------------
 *   Clase principal, contiene al mapa y tiene funciones para
 *   resolver el mapa, encontrar el camino más corto...
 */
class Klondike {
public:
  /*
   * Constructor
   * --------------------------------------------------------
   *   Genera un objeto Klondike en el que se guarda el mapa dado
   *   inicializa además la matriz de distancias al máximo
   */
  Klondike(short klondikeMap[][SIZE]);

  /*
   * Función: solve
   * --------------------------------------------------------
   *   Resuelve el mapa, desde el punto dado, en la lista se guarda el camino a la
   *   salida más corto, la matriz de distancias se verá completada
   *
   *   start: punto de origen para resolver el mapa
   *   (Opcional) search: da una lista de los pasos necesarios para resolver
   *
   *   resultado: lista de puntos con el camino a la salida
   */
  std::list<Point> solve(Point start, std::vector<SearchResult> * search = nullptr);

  /*
   * Función: adjacent
   * --------------------------------------------------------
   *   Calcula las casillas accesibles desde una dada
   *
   *   now: casilla desde la cual se desea calcular a cuales otras se puede ir
   *
   *   resultado: lista de puntos con las casillas posibles desde la dada
   */
  std::list<Point> adjacent(Point now);

  /*
   * Función: setDist
   * --------------------------------------------------------
   *   Actualiza la distancia de una casilla
   *
   *   p: punto que corresponde a la casilla en cuestión
   *   newDist: nueva distancia
   */
  void setDist(Point p, int newDist);

  /*
   *  Función: getDist
   * --------------------------------------------------------
   *   Obtiene la distancia de una casilla
   *
   *   p: punto que corresponde a la casilla en cuestión
   *
   *  resultado: distancia de la casilla en cuestión
   */
  int getDist(Point p);

  /*
   *  Función: getMap
   * --------------------------------------------------------
   *   Obtiene el valor de una casilla
   *
   *   p: punto que corresponde a la casilla en cuestión
   *
   *  resultado: valor de la casilla en cuestión
   */
  short getMap(Point p);

  /*
   *  Función: setMap
   * --------------------------------------------------------
   *   Actualiza los movimientos de una casilla
   *
   *   p: punto que corresponde a la casilla en cuestión
   *   newMap: nuevos movimientos
   */
  void setMap(Point p, short newMap);

private:

  int dist[SIZE][SIZE]; // Distancias a cada casilla desde el principio
  short map[SIZE][SIZE]; // Movimientos de cada casilla
};

#endif
