#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>
#include <stdio.h>

void Renderer::DrawFilaire()
{
	int cpt;
    if(drawable->colorOnFace)
    {
        /* cas où l'on est en mode kaléidoscope */
        for(cpt = 0; cpt < drawable->faces.size ; cpt++)
        {
            /* Pour chaque face, on en dessine les 3 arêtes */
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index1], renderable.points2D.data[drawable->faces.data[cpt].index2], drawable->pointColors.data[drawable->faces.data[cpt].index1], drawable->pointColors.data[drawable->faces.data[cpt].index2]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index2], renderable.points2D.data[drawable->faces.data[cpt].index3], drawable->pointColors.data[drawable->faces.data[cpt].index2], drawable->pointColors.data[drawable->faces.data[cpt].index3]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index1], renderable.points2D.data[drawable->faces.data[cpt].index3], drawable->pointColors.data[drawable->faces.data[cpt].index1], drawable->pointColors.data[drawable->faces.data[cpt].index3]);
        }
    }
    else
    {
        /* cas avec des faces de couleur unie */
        for(cpt = 0; cpt < drawable->faces.size ; cpt++)
        {
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index1], renderable.points2D.data[drawable->faces.data[cpt].index2], drawable->faceColors.data[cpt], drawable->faceColors.data[cpt]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index2], renderable.points2D.data[drawable->faces.data[cpt].index3], drawable->faceColors.data[cpt], drawable->faceColors.data[cpt]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index1], renderable.points2D.data[drawable->faces.data[cpt].index3], drawable->faceColors.data[cpt], drawable->faceColors.data[cpt]);
        }
    }


}
void Renderer::DrawFilaireCache()
{
	int cpt;
    if(drawable->colorOnFace)
    {
        /* On n'affichera à partir de maintenant que les faces visibles (faces filaires dans ce cas) */
        for(cpt = 0; cpt < effectiveDrawable->sortedVisibleFaces.size; cpt++)
        {
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]);
        }
    }
    else
    {
        for(cpt = 0; cpt < effectiveDrawable->sortedVisibleFaces.size; cpt++)
        {
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index], drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index], drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index], drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index]);
        }
    }

}
void Renderer::DrawFacePleine()
{
    int cpt;
    if(drawable->colorOnFace)
    {
        for(cpt = 0; cpt < effectiveDrawable->sortedVisibleFaces.size; cpt++)
        {
            /* On affiche les faces pleines dans ce cas */
            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]);
        }
    }
    else
    {
        for(cpt = 0; cpt < effectiveDrawable->sortedVisibleFaces.size; cpt++)
        {
            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index], drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index], drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index]);
        }
    }

}

void Renderer::DrawLambert()
{
	int cpt;
    Color  c1, c2, c3;

    if(drawable->colorOnFace)
    {
        for(cpt = 0; cpt < effectiveDrawable->sortedVisibleFaces.size; cpt++)
        {
            /* couleurs initiales des 3 sommets */
            c1 = drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1];
            c2 = drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2];
            c3 = drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3];

            /* on ajoute la lumière ambiante et la lumière ponctuelle ponctuelle à nos couleurs(pour getColor, on considère ici le point central de la face ainsi que sa normale pour trouver la couleur des 3 sommets) */
            c1 = c1 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1]*0.33 + effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2]*0.33+effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]*0.33, effectiveDrawable->faceNormals.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index]));
            c2 = c2 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1]*0.33 + effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2]*0.33+effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]*0.33, effectiveDrawable->faceNormals.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index]));
            c3 = c3 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1]*0.33 + effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2]*0.33+effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]*0.33, effectiveDrawable->faceNormals.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index]));

            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], c1, c2, c3);
         }
    }
    else
    {
        for(cpt = 0; cpt < effectiveDrawable->sortedVisibleFaces.size; cpt++)
        {
            c1 = drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index];
            c2 = drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index];
            c3 = drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index];

            c1 = c1 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1]*0.33 + effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2]*0.33+effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]*0.33, effectiveDrawable->faceNormals.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index]));
            c2 = c2 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1]*0.33 + effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2]*0.33+effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]*0.33, effectiveDrawable->faceNormals.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index]));
            c3 = c3 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1]*0.33 + effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2]*0.33+effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]*0.33, effectiveDrawable->faceNormals.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index]));

            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], c1, c2, c3);
         }
    }
}

void Renderer::DrawGouraud()
{
	int cpt;
    Color  c1, c2, c3;

    if(drawable->colorOnFace)
    {
        for(cpt = 0; cpt < effectiveDrawable->sortedVisibleFaces.size; cpt++)
        {
            /* couleurs initiales des 3 sommets */
            c1 = drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1];
            c2 = drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2];
            c3 = drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3];

            /* on ajoute la lumière ambiante et la lumière ponctuelle ponctuelle à nos couleurs(pour getColor, on considère ici les 3 sommets ainsi que leurs normales) */
            c1 = c1 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1]));
            c2 = c2 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2]));
            c3 = c3 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]));

            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], c1, c2, c3);
        }
    }
    else
    {
         for(cpt = 0; cpt < effectiveDrawable->sortedVisibleFaces.size; cpt++)
        {
            c1 = drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index];
            c2 = drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index];
            c3 = drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index];

            c1 = c1 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1]));
            c2 = c2 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2]));
            c3 = c3 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3]));

            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2], renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3], c1, c2, c3);
        }
    }
}

void Renderer::DrawPhong()
{
    int cpt;
    if(drawable->colorOnFace)
    {
        for(cpt = 0; cpt < effectiveDrawable->sortedVisibleFaces.size; cpt++)
        {
            buffer->DrawPhongTriangle(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1],
                                      renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2],
                                      renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3],
                                      drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1],
                                      drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2],
                                      drawable->pointColors.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3],
                                      effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1],
                                      effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2],
                                      effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3],
                                      effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1],
                                      effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2],
                                      effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3],
                                      ambientLight,
                                      pointLight
                                      );
        }
    }
    else
    {
        for(cpt = 0; cpt < effectiveDrawable->sortedVisibleFaces.size; cpt++)
        {
            buffer->DrawPhongTriangle(renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1],
                                      renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2],
                                      renderable.points2D.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3],
                                      drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index],
                                      drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index],
                                      drawable->faceColors.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index],
                                      effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1],
                                      effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2],
                                      effectiveDrawable->points.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3],
                                      effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index1],
                                      effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index2],
                                      effectiveDrawable->pointNormals.data[drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[cpt].index].index3],
                                      ambientLight,
                                      pointLight
                                      );
        }
    }
}
