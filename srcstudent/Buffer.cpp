#include <Buffer.h>
#include <FastMath.h>

/** Algorithme de Bresenham */
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
            /* coordonnées du nouveau point à dessiner */
            myPoint.x = X;
            myPoint.y = Y;

            /* poids et composantes de la couleur du nouveau point à dessiner */
            wA = 1 - (p1.Distance(myPoint) / p1.Distance(p2));
            wB = 1 - wA;
            c3.red = ((wA * c1.red) + (wB * c2.red)) / (wA + wB);
            c3.green = ((wA * c1.green) + (wB * c2.green)) / (wA + wB);
            c3.blue = ((wA * c1.blue) + (wB * c2.blue)) / (wA + wB);

            /* interpolation de la profondeur pour le z-buffer */
            myPoint.depth = ((wA * p1.depth) + (wB * p2.depth)) / (wA + wB);

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
            /* coordonnées du nouveau point à dessiner */
            myPoint.x = X;
            myPoint.y = Y;

            /* poids et composantes de la couleur du nouveau point à dessiner */
            wA = 1 - (p1.Distance(myPoint) / p1.Distance(p2));
            wB = 1 - wA;
            c3.red = ((wA * c1.red) + (wB * c2.red)) / (wA + wB);
            c3.green = ((wA * c1.green) + (wB * c2.green)) / (wA + wB);
            c3.blue = ((wA * c1.blue) + (wB * c2.blue)) / (wA + wB);

            /* interpolation de la profondeur pour le z-buffer */
            myPoint.depth = ((wA * p1.depth) + (wB * p2.depth)) / (wA + wB);

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
        /* extrêmités de la ligne */
        myPoint1.x = myScan.left.data[cpt];
        myPoint1.y = cpt;
        myPoint2.x = myScan.right.data[cpt]+1;
        myPoint2.y = cpt;

        /* poids et composantes de la couleur de l'extrêmité 1 */
        wA4 = myScan.leftweight.data[cpt].data[0];
        wB4 = myScan.leftweight.data[cpt].data[1];
        wC4 = myScan.leftweight.data[cpt].data[2];
        c4.red = ((wA4 * c1.red) + (wB4 * c2.red) + (wC4 * c3.red)) / (wA4 + wB4 + wC4);
        c4.green = ((wA4 * c1.green) + (wB4 * c2.green) + (wC4 * c3.green)) / (wA4 + wB4 + wC4);
        c4.blue = ((wA4 * c1.blue) + (wB4 * c2.blue) + (wC4 * c3.blue)) / (wA4 + wB4 + wC4);

        /* interpolation de la profondeur de l'extrêmité 1 pour le z-buffer */
        myPoint1.depth = ((wA4 * p1.depth) + (wB4 * p2.depth) + (wC4 * p3.depth)) / (wA4 + wB4 + wC4);

        /* poids et couleurs de l'extrêmité 2 */
        wA5 = myScan.rightweight.data[cpt].data[0];
        wB5 = myScan.rightweight.data[cpt].data[1];
        wC5 = myScan.rightweight.data[cpt].data[2];
        c5.red = ((wA5 * c1.red) + (wB5 * c2.red) + (wC5 * c3.red)) / (wA5 + wB5 + wC5);
        c5.green = ((wA5 * c1.green) + (wB5 * c2.green) + (wC5 * c3.green)) / (wA5 + wB5 + wC5);
        c5.blue = ((wA5 * c1.blue) + (wB5 * c2.blue) + (wC5 * c3.blue)) / (wA5 + wB5 + wC5);

        /*interpolation de la profondeur de l'extrêmité 2 pour le z-buffer*/
        myPoint2.depth = ((wA5 * p1.depth) + (wB5 * p2.depth) + (wC5 * p3.depth)) / (wA5 + wB5 + wC5);

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
    int cpt, cpt2;
    double wA4, wB4, wC4, wA5, wB5, wC5, wA6, wB6;
    Coord2D myPoint1, myPoint2, myPoint3;
    Coord3D normal4, normal5, normal6, myPoint1_3D, myPoint2_3D, myPoint3_3D;
    Color c4, c5, c6;

    ScanLineComputer myScan;
    myScan.SetSize(wxSize(width, height));
    myScan.Init();
	myScan.Compute(p1, p2, p3);
	for(cpt = myScan.ymin; cpt <= myScan.ymax; cpt++)
    {
        /* extrêmités de la ligne */
        myPoint1.x = myScan.left.data[cpt];
        myPoint1.y = cpt;
        myPoint2.x = myScan.right.data[cpt]+1;
        myPoint2.y = cpt;

        /* poids associés au point 1 */
        wA4 = myScan.leftweight.data[cpt].data[0];
        wB4 = myScan.leftweight.data[cpt].data[1];
        wC4 = myScan.leftweight.data[cpt].data[2];

        /* interpollation des normales du point 1 */
        normal4.x = ((wA4 * normal1.x) + (wB4 * normal2.x) + (wC4 * normal3.x)) / (wA4 + wB4 + wC4);
        normal4.y = ((wA4 * normal1.y) + (wB4 * normal2.y) + (wC4 * normal3.y)) / (wA4 + wB4 + wC4);
        normal4.z = ((wA4 * normal1.z) + (wB4 * normal2.z) + (wC4 * normal3.z)) / (wA4 + wB4 + wC4);

        /* interpollation des composantes 3D du point 1 */
        myPoint1_3D.x = ((wA4 * posi1.x) + (wB4 * posi2.x) + (wC4 * posi3.x)) / (wA4 + wB4 + wC4);
        myPoint1_3D.y = ((wA4 * posi1.y) + (wB4 * posi2.y) + (wC4 * posi3.y)) / (wA4 + wB4 + wC4);
        myPoint1_3D.z = ((wA4 * posi1.z) + (wB4 * posi2.z) + (wC4 * posi3.z)) / (wA4 + wB4 + wC4);

        /* interpollation des composantes de la couleur du point 1 */
        c4.red = ((wA4 * c1.red) + (wB4 * c2.red) + (wC4 * c3.red)) / (wA4 + wB4 + wC4);
        c4.green = ((wA4 * c1.green) + (wB4 * c2.green) + (wC4 * c3.green)) / (wA4 + wB4 + wC4);
        c4.blue = ((wA4 * c1.blue) + (wB4 * c2.blue) + (wC4 * c3.blue)) / (wA4 + wB4 + wC4);

        /* interpolation de la profondeur du point 1 pour le z-buffer */
        myPoint1.depth = ((wA4 * p1.depth) + (wB4 * p2.depth) + (wC4 * p3.depth)) / (wA4 + wB4 + wC4);

        /* idem pour le point 2 */
        wA5 = myScan.rightweight.data[cpt].data[0];
        wB5 = myScan.rightweight.data[cpt].data[1];
        wC5 = myScan.rightweight.data[cpt].data[2];

        normal5.x = ((wA5 * normal1.x) + (wB5 * normal2.x) + (wC5 * normal3.x)) / (wA5 + wB5 + wC5);
        normal5.y = ((wA5 * normal1.y) + (wB5 * normal2.y) + (wC5 * normal3.y)) / (wA5 + wB5 + wC5);
        normal5.z = ((wA5 * normal1.z) + (wB5 * normal2.z) + (wC5 * normal3.z)) / (wA5 + wB5 + wC5);

        myPoint2_3D.x = ((wA5 * posi1.x) + (wB5 * posi2.x) + (wC5 * posi3.x)) / (wA5 + wB5 + wC5);
        myPoint2_3D.y = ((wA5 * posi1.y) + (wB5 * posi2.y) + (wC5 * posi3.y)) / (wA5 + wB5 + wC5);
        myPoint2_3D.z = ((wA5 * posi1.z) + (wB5 * posi2.z) + (wC5 * posi3.z)) / (wA5 + wB5 + wC5);

        c5.red = ((wA5 * c1.red) + (wB5 * c2.red) + (wC5 * c3.red)) / (wA5 + wB5 + wC5);
        c5.green = ((wA5 * c1.green) + (wB5 * c2.green) + (wC5 * c3.green)) / (wA5 + wB5 + wC5);
        c5.blue = ((wA5 * c1.blue) + (wB5 * c2.blue) + (wC5 * c3.blue)) / (wA5 + wB5 + wC5);

        myPoint2.depth = ((wA5 * p1.depth) + (wB5 * p2.depth) + (wC5 * p3.depth)) / (wA5 + wB5 + wC5);

        /* Traçage de la ligne avec les 2 extrêmités précédentes comme sommets */
        for(cpt2 = myPoint1.x; cpt2 <= myPoint2.x; cpt2++)
        {
            myPoint3.x = cpt2;
            myPoint3.y = cpt;
            wA6 = 1 - (myPoint1.Distance(myPoint3) / myPoint1.Distance(myPoint2));
            wB6 = 1 - wA6;

            normal6.x = ((wA6 * normal4.x) + (wB6 * normal5.x)) / (wA6 + wB6);
            normal6.y = ((wA6 * normal4.y) + (wB6 * normal5.y)) / (wA6 + wB6);
            normal6.z = ((wA6 * normal4.z) + (wB6 * normal5.z)) / (wA6 + wB6);

            c6.red = ((wA6 * c4.red) + (wB6 * c5.red)) / (wA6 + wB6);
            c6.blue = ((wA6 * c4.blue) + (wB6 * c5.blue)) / (wA6 + wB6);
            c6.green = ((wA6 * c4.green) + (wB6 * c5.green)) / (wA6 + wB6);

            myPoint3_3D.x = ((wA6 * myPoint1_3D.x) + (wB6 * myPoint2_3D.x)) / (wA6 + wB6);
            myPoint3_3D.y = ((wA6 * myPoint1_3D.y) + (wB6 * myPoint2_3D.y)) / (wA6 + wB6);
            myPoint3_3D.z = ((wA6 * myPoint1_3D.z) + (wB6 * myPoint2_3D.z)) / (wA6 + wB6);

            myPoint3.depth = ((wA6 * myPoint1.depth) + (wB6 * myPoint2.depth)) / (wA6 + wB6);

            SetPoint(myPoint3, c6 * (pointLight.GetColor(myPoint3_3D, normal6) + ambientLight.ambientColor));
        }
    }
}
