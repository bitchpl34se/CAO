
#include <ScanLineComputer.h>
#include <Buffer.h>
#include <FastMath.h>
#include <limits.h>



void ScanLineComputer::AddEdge(const Coord2D p1, const Coord2D p2,
															 const int index1, const int index2)
{
	// compléter ici : calculer les points de la bordure et appeler AddPoint
	// on utitlise la méthode de Bresenheim pour calculer les points du segment [p1,p2] et on les ajoute via la méthode AddPoint
    int X, Y, longX, longY, incX, incY, critere, const1, const2, cpt;

	X = p1.x;
	Y = p1.y;

	longX = p2.x - p1.x;
	longY = p2.y - p1.y;

	if(longX >= 0)
    {
        incX = 1;
    }
    else
    {
        incX = -1;
        longX = -longX;
    }

    if(longY >= 0)
    {
        incY = 1;
    }
    else
    {
        incY = -1;
        longY = -longY;
    }

    if(longY < longX)
    {
        const2 = 2 * (longY);
        const1 = const2 - 2 * (longX);
        critere = const2 - (longX);
        for(cpt = 0; cpt <= longX; cpt++)
        {
            AddPoint(X, Y, p1, p2, index1, index2);

            if(critere > 0)
            {
                Y += incY;
                critere += const1;
            }
            else
            {
                critere += const2;
            }
            X += incX;
        }
    }
    else
    {
        const1 = 2 * (longX - longY);
        const2 = 2 * longX;
        critere = const2 - longY;
        for(cpt = 0; cpt <= longY; cpt++)
        {
            AddPoint(X, Y, p1, p2, index1, index2);

            if(critere > 0)
            {
                X += incX;
                critere += const1;
            }
            else
            {
                critere += const2;
            }
            Y += incY;
        }
    }
}


