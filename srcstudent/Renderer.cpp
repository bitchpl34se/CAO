#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>
#include <stdio.h>

void Renderer::DrawFilaire()
{
	int cpt;

	for(cpt = 0; cpt < drawable->faces.size ; cpt++)
    {
       buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index1], renderable.points2D.data[drawable->faces.data[cpt].index2], drawable->pointColors.data[drawable->faces.data[cpt].index1], drawable->pointColors.data[drawable->faces.data[cpt].index2]);
       buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index2], renderable.points2D.data[drawable->faces.data[cpt].index3], drawable->pointColors.data[drawable->faces.data[cpt].index2], drawable->pointColors.data[drawable->faces.data[cpt].index3]);
       buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index1], renderable.points2D.data[drawable->faces.data[cpt].index3], drawable->pointColors.data[drawable->faces.data[cpt].index1], drawable->pointColors.data[drawable->faces.data[cpt].index3]);
    }
}
void Renderer::DrawFilaireCache()
{
	int cpt;

	for(cpt = 0; cpt < drawable->faces.size; cpt++)
    {
        if(effectiveDrawable->faceVisibles.data[cpt] == 1)
        {
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index1], renderable.points2D.data[drawable->faces.data[cpt].index2], drawable->pointColors.data[drawable->faces.data[cpt].index1], drawable->pointColors.data[drawable->faces.data[cpt].index2]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index2], renderable.points2D.data[drawable->faces.data[cpt].index3], drawable->pointColors.data[drawable->faces.data[cpt].index2], drawable->pointColors.data[drawable->faces.data[cpt].index3]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[cpt].index1], renderable.points2D.data[drawable->faces.data[cpt].index3], drawable->pointColors.data[drawable->faces.data[cpt].index1], drawable->pointColors.data[drawable->faces.data[cpt].index3]);
        }
    }
}
void Renderer::DrawFacePleine()
{
    int cpt;

	for(cpt = 0; cpt < drawable->faces.size; cpt++)
    {
        if(effectiveDrawable->faceVisibles.data[cpt] == 1)
        {
            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[cpt].index1],
                                       renderable.points2D.data[drawable->faces.data[cpt].index2],
                                       renderable.points2D.data[drawable->faces.data[cpt].index3],
                                       drawable->pointColors.data[drawable->faces.data[cpt].index1],
                                       drawable->pointColors.data[drawable->faces.data[cpt].index2],
                                       drawable->pointColors.data[drawable->faces.data[cpt].index3]);
        }
    }
}

void Renderer::DrawLambert()
{
	int cpt;
    Color  c1, c2, c3;
	for(cpt = 0; cpt < drawable->faces.size; cpt++)
    {
        if(effectiveDrawable->faceVisibles.data[cpt] == 1)
        {
            c1 = drawable->pointColors.data[drawable->faces.data[cpt].index1];
            c2 = drawable->pointColors.data[drawable->faces.data[cpt].index2];
            c3 = drawable->pointColors.data[drawable->faces.data[cpt].index3];

            /* on ajoute la lumière ambiante et la lumière ponctuelle ponctuelle à nos couleurs */
            c1 = c1 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[cpt].index1], effectiveDrawable->faceNormals.data[cpt]));
            c2 = c2 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[cpt].index2], effectiveDrawable->faceNormals.data[cpt]));
            c3 = c3 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[cpt].index3], effectiveDrawable->faceNormals.data[cpt]));

            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[cpt].index1],
                                       renderable.points2D.data[drawable->faces.data[cpt].index2],
                                       renderable.points2D.data[drawable->faces.data[cpt].index3],
                                       c1,
                                       c2,
                                       c3);
        }
    }
}

void Renderer::DrawGouraud()
{
	int cpt;
    Color  c1, c2, c3;
	for(cpt = 0; cpt < drawable->faces.size; cpt++)
    {
        if(effectiveDrawable->faceVisibles.data[cpt] == 1)
        {
            c1 = drawable->pointColors.data[drawable->faces.data[cpt].index1];
            c2 = drawable->pointColors.data[drawable->faces.data[cpt].index2];
            c3 = drawable->pointColors.data[drawable->faces.data[cpt].index3];

            /* on ajoute la lumière ambiante et la lumière ponctuelle ponctuelle à nos couleurs */
            c1 = c1 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[cpt].index1], effectiveDrawable->faceNormals.data[cpt]));
            c2 = c2 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[cpt].index2], effectiveDrawable->faceNormals.data[cpt]));
            c3 = c3 * (ambientLight.ambientColor + pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[cpt].index3], effectiveDrawable->faceNormals.data[cpt]));

            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[cpt].index1],
                                       renderable.points2D.data[drawable->faces.data[cpt].index2],
                                       renderable.points2D.data[drawable->faces.data[cpt].index3],
                                       c1,
                                       c2,
                                       c3);
        }
    }
}

void Renderer::DrawPhong()
{
	// compléter ici
}
