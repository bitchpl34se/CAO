#include <ZBuffer.h>

/** Initialise le Z-Buffer (les pixels sont à une profondeur infinie initialement) */
void ZBuffer::Init()
{
    int cpt, cpt2;
    for (cpt = 0; cpt < depths.size; cpt++)
    {
        for(cpt2 = 0; cpt2 < depths.data[cpt].size; cpt2++)
        {
            /* pour chaque pixel, on initialise sa profondeur à la valeur max du type double (~ infini) */
            depths.data[cpt].data[cpt2] = DBL_MAX;
        }
    }
}

/** Fonction permettant de déterminer si le pixel (p.x,p.y) peut être remplacé par le point p.
	 * @return true si p doit remplacer le point de même coordonnées (p.x,p.y) selon la règle du Z-buffer
	 * i.e. si p est plus proche de la caméra que le même pixel mais de profondeur depths[x][y]. */
bool ZBuffer::ReplaceCurrent(const Coord2D p)
{
    if(enabled)
    {
        if(p.depth >= depths.data[p.y].data[p.x])
        {
            /* p est plus profond que le point de même coordonnées (p.x,p.y), on ne remplace donc pas ce dernier par p */
            return false;
        }
        /* on remplace la valeur de profondeur du point (p.x,p.y) */
        depths.data[p.y].data[p.x] = p.depth;
    }
    return true;
}
