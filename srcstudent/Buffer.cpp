#include <Buffer.h>
#include <FastMath.h>


void Buffer::DrawLine(const Coord2D p1, const Coord2D p2, const Color c1,
		const Color c2)
{
    int X, Y, longX, longY, incX, incY, critere, const1, const2, cpt;
    double wA, wB;
    Coord2D myPoint;
    Color c3;

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
            //coordonnées du nouveau point à dessiner
            myPoint.x = X;
            myPoint.y = Y;

            //couleur du nouveau point à dessiner
            wA = 1 - (p1.Distance(myPoint) / p1.Distance(p2));
            wB = 1 - wA;
            c3.red = ((wA * c1.red) + (wB * c2.red)) / (wA + wB);
            c3.green = ((wA * c1.green) + (wB * c2.green)) / (wA + wB);
            c3.blue = ((wA * c1.blue) + (wB * c2.blue)) / (wA + wB);

            SetPoint(myPoint, c3);

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
            //coordonnées du nouveau point à dessiner
            myPoint.x = X;
            myPoint.y = Y;

            //couleur du nouveau point à dessiner
            wA = 1 - (p1.Distance(myPoint) / p1.Distance(p2));
            wB = 1 - wA;
            c3.red = ((wA * c1.red) + (wB * c2.red)) / (wA + wB);
            c3.green = ((wA * c1.green) + (wB * c2.green)) / (wA + wB);
            c3.blue = ((wA * c1.blue) + (wB * c2.blue)) / (wA + wB);

            SetPoint(myPoint, c3);

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

void Buffer::DrawFilledTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3)
{
    int cpt;
    double wA4, wB4, wC4, wA5, wB5, wC5;
    Coord2D myPoint1, myPoint2;
    Color c4, c5;

    ScanLineComputer myScan;
    myScan.SetSize(wxSize(width, height));
    myScan.Init();
	myScan.Compute(p1, p2, p3);
	for(cpt = myScan.ymin; cpt <= myScan.ymax; cpt++)
    {
        /* Les extrêmités de la ligne */
        myPoint1.x = myScan.left.data[cpt];
        myPoint1.y = cpt;
        myPoint2.x = myScan.right.data[cpt];
        myPoint2.y = cpt;

        /* Les couleurs de ces extrêmités */
        wA4 = myScan.leftweight.data[cpt].data[0];
        wB4 = myScan.leftweight.data[cpt].data[1];
        wC4 = myScan.leftweight.data[cpt].data[2];
        c4.red = ((wA4 * c1.red) + (wB4 * c2.red) + (wC4 * c3.red)) / (wA4 + wB4 + wC4);
        c4.green = ((wA4 * c1.green) + (wB4 * c2.green) + (wC4 * c3.green)) / (wA4 + wB4 + wC4);
        c4.blue = ((wA4 * c1.blue) + (wB4 * c2.blue) + (wC4 * c3.blue)) / (wA4 + wB4 + wC4);

        wA5 = myScan.rightweight.data[cpt].data[0];
        wB5 = myScan.rightweight.data[cpt].data[1];
        wC5 = myScan.rightweight.data[cpt].data[2];
        c5.red = ((wA5 * c1.red) + (wB5 * c2.red) + (wC5 * c3.red)) / (wA5 + wB5 + wC5);
        c5.green = ((wA5 * c1.green) + (wB5 * c2.green) + (wC5 * c3.green)) / (wA5 + wB5 + wC5);
        c5.blue = ((wA5 * c1.blue) + (wB5 * c2.blue) + (wC5 * c3.blue)) / (wA5 + wB5 + wC5);

        /* Traçage de la ligne avec les 2 extrêmités précédentes comme sommets */
        DrawLine(myPoint1, myPoint2, c4, c5);
    }
}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
	// compléter ici
}

