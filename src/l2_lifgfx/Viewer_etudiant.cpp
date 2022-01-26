
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

#include "draw.h" // pour dessiner du point de vue d'une camera
#include "Viewer_etudiant.h"
#include "Viewer.h"
#include "wavefront.h" // Appel lib pour pouvoir ajouter un modèle 3D de type .obj

using namespace std;

Orbiter camera;

/*
 * Creation du Mesh d un quad.
 */
void ViewerEtudiant::init_quad()
{
    m_quad = Mesh(GL_TRIANGLE_STRIP);
    m_quad.color(Color(1, 1, 1));

    m_quad.normal(0, 0, 1);

    m_quad.texcoord(0, 0);
    m_quad.vertex(-1, -1, 0);

    m_quad.texcoord(1, 0);
    m_quad.vertex(1, -1, 0);

    m_quad.texcoord(0, 1);
    m_quad.vertex(-1, 1, 0);

    m_quad.texcoord(1, 1);
    m_quad.vertex(1, 1, 0);
}

//  ================== Procédure init_disque ========================================

void ViewerEtudiant::init_disque()
{

    ///Variation de l'angle de 0 à 2pi.
    const int div = 200; /// Plus on augmente plus on aura de maillage.
    float alpha;
    float step = 2.0 * M_PI / (div);

    /// Choix primitive OpenGL
    m_disque = Mesh(GL_TRIANGLE_FAN);

    m_disque.normal(Vector(0, -1, 0)); /// Normale à la surface
    m_disque.vertex(Point(0, 0, 0));   /// Point du centre du disque

    /// Variation de l'angle de 0 à 2PI
    for (int i = 0; i <= div + 1; i++)
    {
        m_disque.texcoord(float(i + 1) / div, 1.0 - float(i + 1) / div);
        m_disque.vertex(Point(cos(alpha), 0, sin(alpha)));
        alpha = i * step;
    }

    m_disque.restart_strip(); /// Réinitialise les coordo pour pouvoir redefinir un mesh.s
}

// ================================= Procédure init_Cube ==============================
void ViewerEtudiant::init_Cube()
{
    //on définit le type de triangles
    m_Cube = Mesh(GL_TRIANGLE_STRIP);

    //Définition du sommet du cube
    vec3 s[8];
    s[0] = vec3(0, 0, 0); //
    s[1] = vec3(0, 1, 0); //
    s[2] = vec3(1, 1, 0); //     6 -- 5
    s[3] = vec3(1, 0, 0); //     /   /|
    s[4] = vec3(1, 0, 1); //    1- -2 |
    s[5] = vec3(1, 1, 1); //    |   | |
    s[6] = vec3(0, 1, 1); //    |   | 4
    s[7] = vec3(0, 0, 1); //    0- -3
    //Définition d tableau qui stock les faces
    vec3 Vertex[6][4];

    Vertex[0][0] = s[1]; // AVANT
    Vertex[0][1] = s[2];
    Vertex[0][2] = s[0];
    Vertex[0][3] = s[3];

    Vertex[1][0] = s[6]; // ARRIERE
    Vertex[1][1] = s[7];
    Vertex[1][2] = s[5];
    Vertex[1][3] = s[4];

    Vertex[2][0] = s[7]; // DESSOUS
    Vertex[2][1] = s[0];
    Vertex[2][2] = s[4];
    Vertex[2][3] = s[3];

    Vertex[3][0] = s[6]; // DESSUS
    Vertex[3][1] = s[5];
    Vertex[3][2] = s[1];
    Vertex[3][3] = s[2];

    Vertex[4][0] = s[6]; // GAUCHE
    Vertex[4][1] = s[1];
    Vertex[4][2] = s[7];
    Vertex[4][3] = s[0];

    Vertex[5][0] = s[5]; // DROITE
    Vertex[5][1] = s[4];
    Vertex[5][2] = s[2];
    Vertex[5][3] = s[3];

    // Remplissage du Mesh
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //on remplit le sommet
            m_Cube.normal(Vertex[i][j]);
            m_Cube.vertex(Vertex[i][j]);
        }
        // On recommence le strippage.
        m_Cube.restart_strip();
    }
}

// ================================ Procédure init_cylindre ============================
void ViewerEtudiant::init_cylindre()
{

    ///Variation de l'angle de 0 à 2pi.
    const int div = 100; /// Plus on augmente plus on aura de maillage.
    float alpha;
    float step = 2.0 * M_PI / (div);

    /// Choix primitive OpenGL
    m_cylindre = Mesh(GL_TRIANGLE_STRIP);

    for (int i = 0; i <= div; i++)
    {
        /// Variation de l'angle de 0 à 2PI
        alpha = i * step;

        m_cylindre.normal(Vector(cos(alpha), 0, sin(alpha)));
        m_cylindre.texcoord(vec2(float(i) / div, 1.0));
        m_cylindre.vertex(Point(cos(alpha), -1, sin(alpha))); // Sommet du bas

        /// On met un point en haut et un point en bas et on fais varié les deux.

        m_cylindre.normal(Vector(cos(alpha), 0, sin(alpha)));
        m_cylindre.texcoord(vec2(float(i) / div, 0.0));
        m_cylindre.vertex(Point(cos(alpha), 1, sin(alpha))); // Sommet du haut
    }
}

// ====================================== Procédure init_cone ==========================
void ViewerEtudiant::init_cone()
{
    ///Variation de l'angle de 0 à 2PI
    const int div = 100; /// Plus on augmente plus on aura de maillage.
    float alpha;
    float step = 2.0 * M_PI / (div);
    /// Choix primitive OpenGL
    m_cone = Mesh(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= div; i++)
    {
        alpha = i * step; /// Angle varie de 0 à 2PI

        m_cone.normal(Vector(cos(alpha) / sqrtf(2.f),
                             1.f / sqrtf(2.f),
                             sin(alpha) / sqrtf(2.f)));
        m_cone.texcoord(vec2(float(i) / div, 0));
        m_cone.vertex(Point(cos(alpha), 0, sin(alpha))); /// Point du disque du bas.

        m_cone.normal(Vector(cos(alpha) / sqrtf(2.f),
                             1.f / sqrtf(2.f),
                             sin(alpha) / sqrtf(2.f)));
        m_cone.texcoord(vec2(float(i) / div, 1));
        m_cone.vertex(Point(0, 1, 0)); /// Sommet, et on alterne entre les points du bas et du sommet.
    }
}

// ================================== Procédure init_sphere =============================

// Cronstruction du mesh pour la sphere.
void ViewerEtudiant::init_sphere()
{
    /// Variation des angles alpha et beta de 0 à 2PI
    const int divBeta = 100;

    const int divAlpha = divBeta / 2;
    int i, j;

    float beta, alpha, alpha2;

    /// Choix de la primitive OpenGL
    m_sphere = Mesh(GL_TRIANGLE_STRIP);

    /// Variation des angles alpha et beta
    for (int i = 0; i < divAlpha; i++) /// Variations de l'angle Alpha.
    {
        /// On a 1 rayon et 1 positionement, on considère 2 cercles car on va utiliser des gl triangles strip pour les relier entre eux.
        alpha = -0.5f * M_PI + float(i) * M_PI / float(divAlpha); /// On fait varié l'angle de -PI/2 à PI/2
        alpha2 = -0.5f * M_PI + float(i + 1) * M_PI / float(divAlpha);

        for (int j = 0; j <= divBeta; j++) /// Variation de l'angle Beta.
        {
            /// On dessine un cercle.
            beta = float(j) * 2.f * M_PI / (divBeta); /// On va de 0 à 2PI

            /// On définit un cercle avec l'angle alpha (cercle du bas).
            m_sphere.normal(Vector(cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)));
            m_sphere.texcoord(beta / (M_PI * 2.0), 0.5 + alpha / M_PI);
            m_sphere.vertex(Point(cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)));

            /// On définit un autre cercle avec l'angle alpha2 (cercle du haut) et on va mettre des triangle entre les deux pour lier les cercles et avoir une sphere compact.
            m_sphere.normal(Vector(cos(alpha2) * cos(beta), sin(alpha2), cos(alpha2) * sin(beta)));
            m_sphere.texcoord(beta / (M_PI * 2.0), 0.5 + alpha2 / M_PI); /// angle apha2
            m_sphere.vertex(Point(cos(alpha2) * cos(beta), sin(alpha2), cos(alpha2) * sin(beta)));
        }
        m_sphere.restart_strip(); /// Demande un nouveau strip.
    }
}
// =============================== Procédure create_vertex_normal_vase ================================

/// Définition de la silhouette 2D
// Rappel : va est le nom de la variable que l'on a donné pour la structure vase dans le .h
void ViewerEtudiant::create_vertex_normal_vase()
{

    /// Nombre de points de la silhouette 2D
    va.vase_NBPT = 10; /// Déclaré dans la class ViewerEtudiant

    /// Points de la silhouette 2D
    va.vase_p[0] = Point(0, 0, 0);
    va.vase_p[1] = Point(0.6, 0.2, 0);
    va.vase_p[2] = Point(1.0, 0.4, 0);
    va.vase_p[3] = Point(1.2, 0.6, 0);
    va.vase_p[4] = Point(1.3, 0., 0);
    va.vase_p[5] = Point(1.2, 1.0, 0);
    va.vase_p[6] = Point(1.0, 1.2, 0);
    va.vase_p[7] = Point(0., 1.4, 0);
    va.vase_p[8] = Point(1, 1.6, 0);
    va.vase_p[9] = Point(1.2, 1., 0);

    /// Nombre de rotations pour créer le vase par rotation
    va.vase_NBROT = 20; // déclaré dans la class ViewerEtudiant

    for (int i = 0; i < va.vase_NBROT; i++)
    {
        // i indice rotation (angle : 2 pi * i / NBROT)
        ///Angle qui varie de 0 à 2PI
        float teta = 2 * M_PI * i / va.vase_NBROT;

        /// Matrice de rotation de l'angle theta autour axe des y
        /// en coordonnées homogènes : 4 x 4
        float mat[16] = {
            cos(teta), 0, -sin(teta), 0,
            0, 1, 0, 0,
            sin(teta), 0, cos(teta), 0,
            0, 0, 0, 1};

        /// Calcul des coordo des sommets
        for (int j = 0; j < va.vase_NBPT; j++)
        {
            //j indice du point de la silhouette
            /// Application de ma matrice de rotation au point j qui subit la rotation (2PI * i / nbrot)
            va.vase_v[i][j].x = mat[0] * va.vase_p[j].x + mat[1] * va.vase_p[j].y + mat[2] * va.vase_p[j].z + mat[3] * 1;
            va.vase_v[i][j].y = mat[4] * va.vase_p[j].x + mat[5] * va.vase_p[j].y + mat[6] * va.vase_p[j].z + mat[7] * 1;
            va.vase_v[i][j].z = mat[8] * va.vase_p[j].x + mat[9] * va.vase_p[j].y + mat[10] * va.vase_p[j].z + mat[11] * 1;
        } // Fin boucle j

    } // Fin boucle i

    /// Initialise à 0 le tableau des normales
    for (int i = 0; i < va.vase_NBROT; i++)
    {
        for (int j = 0; j < va.vase_NBPT; j++)
        {
            va.vase_vn[i][j] = Vector(0, 0, 0); /// i : rotation de i, j : rotation de j.
        }
    }

    /// Calcul des normales au sommets pour chaque point du tableau de vecteur.
    for (int i = 0; i < va.vase_NBROT; i++)
    {
        for (int j = 0; j < va.vase_NBPT - 1; j++)
        {
            Vector a, b, vntmp;

            a = normalize(va.vase_v[i][j] - va.vase_v[i][j + 1]);
            b = normalize(va.vase_v[i][j] - va.vase_v[(i + 1) % va.vase_NBROT][j]);

            vntmp = cross(a, b); /// Produit vectoriel de a vers b

            /// On récupère cette normale sur les 4 sommets de la face
            /// (accumulation des normales)
            va.vase_vn[i][j] = vntmp + va.vase_vn[i][j];
            va.vase_vn[(i + 1) % va.vase_NBROT][j] = vntmp + va.vase_vn[(i + 1) % va.vase_NBROT][j];
            va.vase_vn[(i + 1) % va.vase_NBROT][j + 1] = vntmp + va.vase_vn[(i + 1) % va.vase_NBROT][j + 1];
            va.vase_vn[i][j + 1] = vntmp + va.vase_vn[i][j + 1];
        } //Fin boucle j
    }     // Fin boucle i

    for (int i = 0; i < va.vase_NBROT; i++)
    {
        for (int j = 0; j < va.vase_NBPT; j++)
        {
            float q = 4.0f;
            if (j == va.vase_NBPT - 1) /// Points du bord
                q = 2.0f;

            va.vase_vn[i][j] = va.vase_vn[i][j] / q;
        } //for_j
    }     // for_i
} /// Fin de la procédure create_vertex_normal_vase

// ============================== Procédure init_vase =========================
/*     
    Créer le mesh qui va être construit avec des Triangles.     
*/
void ViewerEtudiant::init_vase()
{
    create_vertex_normal_vase(); // On initialise tous les points de notre vase.
    m_vase = Mesh(GL_TRIANGLES); /// Primitive OpenGL

    for (int i = 0; i < va.vase_NBROT; i++)
    {
        for (int j = 0; j < va.vase_NBPT - 1; j++)
        { /// Attention boucle de 0 à vase_NBPT - 2 car ( j + 1)
            /// Premier triangle

            // sommet 1
            m_vase.texcoord(0, 0);
            m_vase.normal(va.vase_vn[i][j]);
            m_vase.vertex(va.vase_v[i][j]);
            // sommet 2
            m_vase.texcoord(1, 1);
            m_vase.normal(va.vase_vn[(i + 1) % va.vase_NBROT][j + 1]);
            m_vase.vertex(va.vase_v[(i + 1) % va.vase_NBROT][j + 1]);
            // sommet 3
            m_vase.texcoord(1, 0);
            m_vase.normal(va.vase_vn[(i + 1) % va.vase_NBROT][j]);
            m_vase.vertex(va.vase_v[(i + 1) % va.vase_NBROT][j]);

            /// Deuxième Triangle

            // Sommet 1
            m_vase.texcoord(0, 0);
            m_vase.normal(va.vase_vn[i][j]);
            m_vase.vertex(va.vase_v[i][j]);
            // Sommet 4
            m_vase.texcoord(0, 1);
            m_vase.normal(va.vase_vn[i][j + 1]);
            m_vase.vertex(va.vase_v[i][j + 1]);
            // Sommet 2
            m_vase.texcoord(1, 1);
            m_vase.normal(va.vase_vn[(i + 1) % va.vase_NBROT][j + 1]);
            m_vase.vertex(va.vase_v[(i + 1) % va.vase_NBROT][j + 1]);

        } //for_j
    }     //for_i
}
// ============================== Fonction Globale TerrainNormale =========================
// Principe :
/*     
     On renvoie pour chaque pixel de l'image un vecteur que l'on utilisera pour la normale de notre terrain 
     (c'est ce qui nous permettra d'avoir du relief en fonction des zones blanches et noires).
*/
// Paramètres :
/*    
    - im : Image en noir et blanc que l'on prend comme référence pour notre calcul de terrain.
    - i : entier qui représente la coordonnées en x du pixel.
    - j : entier qui représente la coordonnées en z du pixel.
*/
Vector TerrainNormal(const Image &im, const int i, const int j)
{
    /// Calcul de la normale au point (i,j) de l'image
    int ip = i - 1;
    int in = i + 1;
    int jp = j - 1;
    int jn = j + 1;

    Vector a(ip, im(ip, j).r, j);
    //       x , y = hauteur, z
    Vector b(in, im(in, j).r, j);
    //       x      y         z
    Vector c(i, im(i, jp).r, jp);
    //       x      y         z
    Vector d(i, im(i, jn).r, jn);
    //       x      y         z
    Vector ab = normalize(b - a);
    Vector cd = normalize(d - c);

    Vector n = cross(ab, cd);

    return -n;
}

// ============================== Procédure init_terrain =========================
/*     
    On prend une image en noir et blanc pour la référence des bosses ect ...
    En utilisant la fonction TerrainNoraml qui renvoie un vecteur on calcul les "bosses" pour avoir un relief. 
*/
void ViewerEtudiant::init_terrain()
{
    m_terrain = Mesh(GL_TRIANGLE_STRIP);                   // Définition de l'objet Mesh en lui précisant la "méthode" de maillage que l'on utilisera (TRIANGLE STRIP).
    Image im = read_image("data/terrain/Clipboard01.png"); // Image de référence que l'on aurait pu passer en paramètre.
    for (int i = 1; i < im.width() - 1; i++)
    {
        for (int j = 1; j < im.height() - 1; j++)
        {
            m_terrain.texcoord((float(i) + 1) / im.width(), float(j) / im.height()); // Coordonnées de texture en (i + 1, j).
            m_terrain.normal(TerrainNormal(im, i + 1, j));                           // On calcul la normale au point (i + 1, j)
            m_terrain.vertex(Point(i + 1, 25.0 * im(i + 1, j).r, j));                // On Place le point au coordo (i + 1, j).

            m_terrain.texcoord(float(i) / im.width(), float(j) / im.height()); // Coordonnées de texture en (i,j).
            m_terrain.normal(TerrainNormal(im, i, j));                         // Calcul de la normale au point (i,j).
            m_terrain.vertex(Point(i, 25.0 * im(i, j).r, j));                  // On Place le point au coordo (i,j).
        }
        m_terrain.restart_strip(); // On réinitialise pour pouvoir continuer le maillage.
    }
}
// Procédure pour initialiser les quads qui vont servir à dessiner le billboard.
void ViewerEtudiant::init_arbre()
{
    m_arbre = Mesh(GL_TRIANGLE_STRIP);

    m_arbre.normal(-1, 0, 0);

    m_arbre.texcoord(0, 0);
    m_arbre.vertex(1, 0, -1);
    
    m_arbre.texcoord(1, 0);
    m_arbre.vertex(1, 0, 0);
    
    m_arbre.texcoord(0, 1);
    m_arbre.vertex(1, 1, -1);
    
    m_arbre.texcoord(1, 1);
    m_arbre.vertex(1, 1, 0);
}
// ================================= Fonction init du cubemap =========================
// Variables locales :
// - pt: tableau 2D pour les coordonnées du cube.
// - tex_pt: Déclaration du tableau qui contiendra les coordonnées des sommets de notre cubemap.
// - tex: Tableau 2D pour les coordonnées du cube.
// - f: Tableau 2D de face.
// - n: Tableau 2D pour les normales
void ViewerEtudiant::init_cubemap()
{

    static float pt[8][3] = {{-50, -50, -50}, {50, -50, -50}, {50, -50, 50}, {-50, -50, 50}, {-50, 50, -50}, {50, 50, -50}, {50, 50, 50}, {-50, 50, 50}};
    static float tex_pt[14][2] = {
        {0, 0.33}, {0, 0.66}, {0.25, 0.33},
        // 1            2        3
        {0.25, 0.66}, {0.5, 0.33}, {0.5, 0.66},
        // 4               5             6
        {0.75, 0.33}, {0.75, 0.66},{1.0, 0.33},
        // 7               8            9
        {1.0, 0.66}, {0.25, 1.0}, {0.5, 1.0},
        // 10             11          12
        {0.25, 0},    {0.5, 0}};
        // 13            14

    static int tex[6][4] = {{2, 4, 12, 13}, {10, 11, 3, 5}, {6, 7, 8, 9}, {2, 3, 4, 5}, {4, 5, 6, 7}, {0, 1, 2, 3}};
    static int f[6][4] = {{0, 1, 2, 3}, {5, 4, 7, 6}, {2, 1, 5, 6}, {0, 3, 7, 4}, {3, 2, 6, 7}, {1, 0, 4, 5}};
    static float n[6][3] = {{0, 1, 0}, {0, -1, 0}, {-1, 0, 0}, {1, 0, 0}, {0, 0, -1}, {0, 0, 1}};
    int i, j;

    m_cubemap = Mesh(GL_TRIANGLE_STRIP);
    for (i = 0; i < 6; i++)
    {
        m_cubemap.normal(n[i][0], n[i][1], n[i][2]);
        m_cube.normal(-n[i][0], -n[i][1], -n[i][2]);

        m_cubemap.texcoord(tex_pt[tex[i][0]][0], tex_pt[tex[i][0]][1]);
        m_cubemap.vertex(pt[f[i][0]][0], pt[f[i][0]][1], pt[f[i][0]][2]);

        m_cubemap.texcoord(tex_pt[tex[i][1]][0], tex_pt[tex[i][1]][1]);
        m_cubemap.vertex(pt[f[i][3]][0], pt[f[i][3]][1], pt[f[i][3]][2]);

        m_cubemap.texcoord(tex_pt[tex[i][2]][0], tex_pt[tex[i][2]][1]);
        m_cubemap.vertex(pt[f[i][1]][0], pt[f[i][1]][1], pt[f[i][1]][2]);

        m_cubemap.texcoord(tex_pt[tex[i][3]][0], tex_pt[tex[i][3]][1]);
        m_cubemap.vertex(pt[f[i][2]][0], pt[f[i][2]][1], pt[f[i][2]][2]);

        m_cubemap.restart_strip();
    }
}

void ViewerEtudiant::generate_extrusion(extruded_obj &obj, int nbPoint, Point tab[100])
{
    for (int i = 0; i < nbPoint; i++)
    {
        obj.extrusion_p[i] = tab[i];
    }

    obj.extrud_NBPT = nbPoint; // Nombre de Point de la silhouette 2D.
    //ex_obj.extrud_NBA = 10; // Nombre de fois que l'on va appliquer la fonction pour avoir notre objet extrudé.

    for (int i = 0; i < obj.extrud_NBPT; i++)
    {
        //création des points de l'avant
        obj.extrusion_vec[i][0].x = obj.extrusion_p[i].x;
        obj.extrusion_vec[i][0].y = obj.extrusion_p[i].y;
        obj.extrusion_vec[i][0].z = 0.0;

        //création des points de l'arrière
        obj.extrusion_vec[i][1].x = obj.extrusion_p[i].x;
        obj.extrusion_vec[i][1].y = obj.extrusion_p[i].y;
        obj.extrusion_vec[i][1].z = 1.5;
    }

    // Initialise à 0 les normales
    for (int i = 0; i < obj.extrud_NBPT; i++)
    {
        obj.extrusion_vecNorm[0][i] = Vector(0, 0, 0);
        obj.extrusion_vecNorm[1][i] = Vector(0, 0, 0);
    }

    //normales
    for (int i = 0; i < obj.extrud_NBPT - 1; i++)
    {
        Vector a, b, vntmp;

        a = normalize(obj.extrusion_vec[0][i] - obj.extrusion_vec[1][i + 1]);
        b = normalize(obj.extrusion_vec[0][i] - obj.extrusion_vec[1][i]);

        vntmp = cross(a, b);

        obj.extrusion_vecNorm[0][i] = vntmp + obj.extrusion_vecNorm[0][i];
        obj.extrusion_vecNorm[1][i] = vntmp + obj.extrusion_vecNorm[1][i];
        obj.extrusion_vecNorm[1][i + 1] = vntmp + obj.extrusion_vecNorm[1][i + 1];
        obj.extrusion_vecNorm[0][i + 1] = vntmp + obj.extrusion_vecNorm[0][i + 1];
    }

    // Normale à un sommet = moyenne de la normale des 4 sommets de la face
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < obj.extrud_NBPT; j++)
        {
            float q = 4.0f;
            if (j == obj.extrud_NBPT - 1) // Points du bord
                q = 2.0f;
            obj.extrusion_vecNorm[i][j] = obj.extrusion_vecNorm[i][j] / q;
        }
    }

} // Fin void generate_extrusion

void ViewerEtudiant::init_face_triangle(Mesh &m_extr, extruded_obj &obj)
{
    // Trace la face avant :
    m_extr.texcoord(0, 0);
    m_extr.normal(obj.extrusion_vecNorm[0][0]); // Point 0 (cf triangle dans le init).
    m_extr.vertex(obj.extrusion_vec[0][0].x, obj.extrusion_vec[0][0].y, obj.extrusion_vec[0][0].z);

    m_extr.texcoord(1, 0);
    m_extr.normal(obj.extrusion_vecNorm[0][1]); // Point 1 (cf le triangle dans le init).
    m_extr.vertex(obj.extrusion_vec[1][0].x, obj.extrusion_vec[1][0].y, obj.extrusion_vec[1][0].z);

    m_extr.texcoord(0, 1);
    m_extr.normal(obj.extrusion_vecNorm[0][2]); // Point 2 (cf le triangle dans le init).
    m_extr.vertex(obj.extrusion_vec[2][0].x, obj.extrusion_vec[2][0].y, obj.extrusion_vec[2][0].z);
    // Trace ma face arrière :
    m_extr.texcoord(1, 1);
    m_extr.normal(obj.extrusion_vecNorm[1][1]); // Point 1 de la face arrière. (cf le triangle dans le init)
    m_extr.vertex(obj.extrusion_vec[1][1].x, obj.extrusion_vec[1][1].y, obj.extrusion_vec[1][1].z);

    m_extr.texcoord(1, 1);
    m_extr.normal(obj.extrusion_vecNorm[1][0]); // Point 0 de la face arrière. (cf le triangle dans le init)
    m_extr.vertex(obj.extrusion_vec[0][1].x, obj.extrusion_vec[0][1].y, obj.extrusion_vec[0][1].z);

    m_extr.texcoord(0, 1);
    m_extr.normal(obj.extrusion_vecNorm[1][3]); // Point 2 de la face arrière. (cf le triangle dans le init)
    m_extr.vertex(obj.extrusion_vec[2][1].x, obj.extrusion_vec[2][1].y, obj.extrusion_vec[2][1].z);
}

void ViewerEtudiant::init_extrusion(Mesh &m_extr, extruded_obj &obj, int nbPoint, Point tab[100])
{
    generate_extrusion(obj, nbPoint, tab); // On initialise tous les points de la structure passé en paramètre.
    m_extr = Mesh(GL_TRIANGLES);           // Primitive OpenGL

    if (nbPoint == 3)
        init_face_triangle(m_extr, obj); // On regarde si ce que l'on veut extrudé est un triangle, si oui on init les faces.

    for (int j = 0; j < nbPoint - 1; j++)
    {
        //1er triangle
        m_extr.texcoord(0, 0);
        m_extr.normal(obj.extrusion_vecNorm[1][j]);
        m_extr.vertex(obj.extrusion_vec[j][1].x, obj.extrusion_vec[j][1].y, obj.extrusion_vec[j][1].z);

        m_extr.texcoord(1, 1);
        m_extr.normal(obj.extrusion_vecNorm[0][j + 1]);
        m_extr.vertex(obj.extrusion_vec[j + 1][0].x, obj.extrusion_vec[j + 1][0].y, obj.extrusion_vec[j + 1][0].z);

        m_extr.texcoord(1, 0);
        m_extr.normal(obj.extrusion_vecNorm[0][j]);
        m_extr.vertex(obj.extrusion_vec[j][0].x, obj.extrusion_vec[j][0].y, obj.extrusion_vec[j][0].z);

        //2eme triangle

        m_extr.texcoord(0, 0);
        m_extr.normal(obj.extrusion_vecNorm[1][j]);
        m_extr.vertex(obj.extrusion_vec[j][1].x, obj.extrusion_vec[j][1].y, obj.extrusion_vec[j][1].z);

        m_extr.texcoord(0, 1);
        m_extr.normal(obj.extrusion_vecNorm[1][j + 1]);
        m_extr.vertex(obj.extrusion_vec[j + 1][1].x, obj.extrusion_vec[j + 1][1].y, obj.extrusion_vec[j + 1][1].z);

        m_extr.texcoord(1, 1);
        m_extr.normal(obj.extrusion_vecNorm[0][j + 1]);
        m_extr.vertex(obj.extrusion_vec[j + 1][0].x, obj.extrusion_vec[j + 1][0].y, obj.extrusion_vec[j + 1][0].z);
    }
    // On trace les points pour l'autre coté de l'objet extrudé de manière à le fermer :

    //1er triangle du bas
    m_extr.texcoord(0, 0);
    m_extr.normal(obj.extrusion_vecNorm[1][nbPoint - 1]);
    m_extr.vertex(obj.extrusion_vec[nbPoint - 1][1].x, obj.extrusion_vec[nbPoint - 1][1].y, obj.extrusion_vec[nbPoint - 1][1].z);

    m_extr.texcoord(1, 1);
    m_extr.normal(obj.extrusion_vecNorm[0][0]);
    m_extr.vertex(obj.extrusion_vec[0][0].x, obj.extrusion_vec[0][0].y, obj.extrusion_vec[0][0].z);

    m_extr.texcoord(1, 0);
    m_extr.normal(obj.extrusion_vecNorm[0][3]);
    m_extr.vertex(obj.extrusion_vec[nbPoint - 1][0].x, obj.extrusion_vec[nbPoint - 1][0].y, obj.extrusion_vec[nbPoint - 1][0].z);

    //2eme triangle du bas

    m_extr.texcoord(0, 0);
    m_extr.normal(obj.extrusion_vecNorm[1][3]);
    m_extr.vertex(obj.extrusion_vec[nbPoint - 1][1].x, obj.extrusion_vec[nbPoint - 1][1].y, obj.extrusion_vec[nbPoint - 1][1].z);

    m_extr.texcoord(0, 1);
    m_extr.normal(obj.extrusion_vecNorm[1][0]);
    m_extr.vertex(obj.extrusion_vec[0][1].x, obj.extrusion_vec[0][1].y, obj.extrusion_vec[0][1].z);

    m_extr.texcoord(1, 1);
    m_extr.normal(obj.extrusion_vecNorm[0][0]);
    m_extr.vertex(obj.extrusion_vec[0][0].x, obj.extrusion_vec[0][0].y, obj.extrusion_vec[0][0].z);
}

// Les procédures d'initialisations pour l'initialisation du vaisseau (cf les mesh correspondants aux proc).
void ViewerEtudiant::init_triangle()
{
    m_triangle = Mesh(GL_TRIANGLES);
    Point a(0, 0, 0);
    Point b(1.0, -0.3, 0);
    Point c(1.2, 0, 0.15);

    Vector AB = normalize(b - a);
    Vector AC = normalize(c - a);
    Vector N = cross(AB, AC);
    m_triangle.normal(N.x, N.y, N.z);

    m_triangle.texcoord(0, 0);
    m_triangle.vertex(a.x, a.y, a.z);

    m_triangle.texcoord(1, 0);
    m_triangle.vertex(b.x, b.y, b.z);

    m_triangle.texcoord(0, 1);
    m_triangle.vertex(c.x, c.y, c.z);
}
// Les procédures d'initialisations pour l'initialisation du vaisseau (cf les mesh correspondants aux proc).
void ViewerEtudiant::init_triangle_close()
{
    m_triangle_close = Mesh(GL_TRIANGLES);
    Point a(1.0, -.3, 0);
    Point b(1.2, 0.0, 0);
    Point c(1.2, 0, .15);

    Vector AB = normalize(b - a);
    Vector AC = normalize(c - a);
    Vector N = cross(AB, AC);

    m_triangle_close.normal(N.x, N.y, N.z);

    m_triangle_close.texcoord(0, 0);
    m_triangle_close.vertex(a.x, a.y, a.z);

    m_triangle_close.texcoord(1, 0);
    m_triangle_close.vertex(b.x, b.y, b.z);

    m_triangle_close.texcoord(0, 1);
    m_triangle_close.vertex(c.x, c.y, c.z);
}
// Les procédures d'initialisations pour l'initialisation du vaisseau (cf les mesh correspondants aux proc).
void ViewerEtudiant::init_triangle_left()
{
    m_triangle_left = Mesh(GL_TRIANGLES);
    Point a(0, 0, 0);
    Point b(1.2, .0, .15);
    Point c(1.0, .3, 0);

    Vector AB = normalize(b - a);
    Vector AC = normalize(c - a);
    Vector N = cross(AB, AC);
    m_triangle_left.normal(N.x, N.y, N.z);

    m_triangle_left.texcoord(0, 0);
    m_triangle_left.vertex(a.x, a.y, a.z);

    m_triangle_left.texcoord(1, 0);
    m_triangle_left.vertex(b.x, b.y, b.z);

    m_triangle_left.texcoord(0, 1);
    m_triangle_left.vertex(c.x, c.y, c.z);
}
// Les procédures d'initialisations pour l'initialisation du vaisseau (cf les mesh correspondants aux proc).
void ViewerEtudiant::init_triangle_close_left()
{
    m_triangle_close_left = Mesh(GL_TRIANGLES);
    Point a(1.2, .0, 0);
    Point b(1.0, 0.3, 0);
    Point c(1.2, 0, .15);

    Vector AB = normalize(b - a);
    Vector AC = normalize(c - a);
    Vector N = cross(AB, AC);

    m_triangle_close_left.normal(N.x, N.y, N.z);

    m_triangle_close_left.texcoord(0, 0);
    m_triangle_close_left.vertex(a.x, a.y, a.z);

    m_triangle_close_left.texcoord(1, 0);
    m_triangle_close_left.vertex(b.x, b.y, b.z);

    m_triangle_close_left.texcoord(0, 1);
    m_triangle_close_left.vertex(c.x, c.y, c.z);
}
// Procédure d'initialisation qui va charger toute les images dans le dossier star_wars, on passe également le nombre d'image mais à la base cette fonction est faite pour être réuitiliser pour d'autres images.
void ViewerEtudiant::init_2D_table(const unsigned int nombre_image)
{
    string chemin, file_format;
    chemin = "data/animation/2DImage/star_wars/giphy-";
    file_format = ".png";
    for (unsigned int i = 0; i < nombre_image; i++)
    {
        string link = chemin + to_string(i) + file_format;

        int n = link.length();

        // declaring character array
        char char_link[n + 1];
        strcpy(char_link, link.c_str());

        m_animation[i] = read_texture(0, smart_path(char_link));
    }
}

// ======================================== Fonction init ================================
int ViewerEtudiant::init()
{
    Viewer::init();

    m_camera.lookat(Point(20.0, 30.0, 0.0), 190);
    init_axe();
    // ============= Définition de tableau de point pour extrusion ================

    Point triangle[3];
    triangle[0] = Point(.0, .0, .0);   //    1
    triangle[1] = Point(.0, 1.0, .0);  //  / |
    triangle[2] = Point(1.0, 0.0, .0); // 0--2

    Point rectangle[4];
    rectangle[0] = Point(.0, .0, .0);   // 1- -2
    rectangle[1] = Point(.0, 6.0, .0);  // |   |
    rectangle[2] = Point(7.0, 6.0, .0); // |   |
    rectangle[3] = Point(7.0, .0, .0);  // 0- -3

    /// =========== Appel des fonctions init_votreObjet pour creer les Mesh ==================

    init_cube();
    init_disque();
    init_cone();
    init_cylindre();
    init_sphere();
    init_vase();
    init_terrain();
    init_arbre();
    init_cubemap();
    init_extrusion(m_rectangle_ex, rec, 4, rectangle);
    init_extrusion(m_triangle_ex, tr, 3, triangle);

    init_quad();

    init_triangle();
    init_triangle_close();

    init_triangle_left();
    init_triangle_close_left();

    init_2D_table(34);

    // =================================== Chargement d'un objet .obj ===================================

    m_obj = read_mesh("data/helicopter/modular-helicopter.obj");
    m_fighter = read_mesh("data/fighter/TieFighter.obj");
    //m_obj = read_mesh("data/tree_obj/TEB.obj");

    // =================================== Déclaration des textures =========================================================

    /// Chargement des textures
    terrain_texture = read_texture(0, "data/terrain/afg_texture.jpg"); // Texture du terrain.
    vase_text = read_texture(0, "data/mur.png");                       // Texture mur pour le vase.
    cone_texture = read_texture(0, "data/wood.jpg");                   // Texture bois pour le cone.
    cylindre_texture = read_texture(0, "data/wood.jpg");               // Texture bois pour le cylindre.
    disque_texture = read_texture(0, "data/wood.jpg");                 // Texture bois pour le disque.
    sphere_texture = read_texture(0, "data/cubemap/HDCubemap2.jpg"); // Texture monde pour la sphere.
    obj = read_texture(0, "data/camo.jpg");                          // Texture Camouflage pour hélicoptère.
    arbre_texture = read_texture(0, "data/billboard/tree1.png");     // Texture png pour le billboard.
    cubemap = read_texture(0, "data/cubemap/HDCubemap2.jpg");        // Image du Cubemap.
    texture_croiseur = read_texture(0, "data/croiseur2.jpg");


    return 0;
}

// ======================================= Procédures DrawObjet =================================

// Procédure qui affiche le Cube.
void ViewerEtudiant::draw_Cube(const Transform &T)
{
    gl.model(T * Translation(20, 1, 0));
    gl.texture(cone_texture);
    gl.draw(m_cube);
}
// Procédure qui affiche le cylindre avec 2 disques et un corps.
void ViewerEtudiant::draw_cylindre(const Transform &T)
{
    /// Corps du cylindre
    gl.model(T);
    gl.texture(cylindre_texture);
    gl.draw(m_cylindre);

    /// Disque du haut
    Transform Tch = T * Translation(0, 1, 0) * Rotation(Vector(1, 0, 0), 10);
    gl.model(Tch);
    gl.texture(cylindre_texture);
    gl.draw(m_disque);

    /// Disque du haut
    Transform Tcb = T * Translation(0, -1, 0);
    gl.model(Tcb);
    gl.texture(cylindre_texture);
    gl.draw(m_disque);
}
// Procédure qui affiche le cone.
void ViewerEtudiant::draw_cone(const Transform &T)
{
    gl.model(T);
    gl.texture(cone_texture);
    gl.draw(m_cone);

    //Disque pour fermer le cone
    gl.model(T);
    gl.draw(m_disque);
}
// Procédure qui affiche la sphère.
void ViewerEtudiant::draw_sphere(const Transform &T)
{
    gl.model(T);
    gl.model(T);
    gl.texture(sphere_texture);
    gl.draw(m_sphere);
}
// Procédure qui dessine un vase
void ViewerEtudiant::draw_vase(const Transform &T)
{
    gl.model(T);           /// Applique Transform T.
    gl.texture(vase_text); // Applique Texture.
    gl.draw(m_vase);       /// Affichage du Mesh.
}
// Procédure qui affiche le terrain.
void ViewerEtudiant::draw_terrain(const Transform &T)
{
    gl.model(T);
    Image im = read_image("data/terrain/Clipboard01.png");           // Texture du terrain.
    gl.model(T * Translation(-im.width() / 2, 0, -im.height() / 2)); // Pour que l'image soit centré par rapport au terrain.
    gl.texture(terrain_texture);
    gl.draw(m_terrain);
}
// Procédure affichage de mon objet importé.
void ViewerEtudiant::draw_objet(const Transform &T, Mesh &obj_mesh)
{
    gl.model(T);
    gl.texture(obj); // cf init.
    gl.draw(obj_mesh);
}
// Procédure affichage de l'abre. (On met 2 formes pour pouvoir y voir selon différente perspec).
void ViewerEtudiant::draw_arbre(const Transform& T)
{
    Transform N = T*Translation(9, 6.7, 7);
    gl.model(N);
    gl.alpha(0.5f);
    gl.texture(arbre_texture);
    gl.draw(m_arbre);

    gl.model(N*Translation(1.5, 0, 0.5)*Rotation(Vector(0, 1, 0), 90));
    gl.alpha(0.5f);
    gl.texture(arbre_texture);
    gl.draw(m_arbre);
}
// Procédure affichage du cubemap
void ViewerEtudiant::draw_cubemap(const Transform &T)
{
    // Pour que le cubemap soit directement à la taille du terrain on fait un Scale puis on retranslate pour remettre à la bonne pos.
    gl.model(T * Translation(0, 100, 0) * Scale(2, 2, 2));
    gl.texture(cubemap);
    gl.draw(m_cubemap);
}
// Procédure qui fait l'affichage d'un objet extrudé (ici on fera surtout l'affichage pour la base de notre destroyer).
void ViewerEtudiant::draw_extrusion(const Transform &T, unsigned int tex)
{
    // =========================== RECTANGLES ==============================================
    Transform T_bas = T * Scale(1.5, 1.0, 1.0) * RotationX(-90.0) * Translation(-3.5, 6.0, .0);
    gl.model(T_bas);         /// Applique Transform T.
    gl.texture(tex);         // Applique Texture.
    gl.draw(m_rectangle_ex); /// Affichage du Mesh.

    Transform T_milieu = T * Scale(1.2, 1.0, 1.0) * Translation(-3.5, 0.0, .0) * RotationX(-90.0);
    gl.model(T_milieu);      /// Applique Transform T.
    gl.texture(tex);         // Applique Texture.
    gl.draw(m_rectangle_ex); /// Affichage du Mesh.

    Transform T_milieu_haut = T * Scale(1.0, 1.0, .5) * RotationX(-90.0) * Translation(-3.5, -6.0, .0);
    gl.model(T_milieu_haut); /// Applique Transform T.
    gl.texture(tex);         // Applique Texture.
    gl.draw(m_rectangle_ex); /// Affichage du Mesh.

    Transform T_haut = T * Scale(.7, 1.0, .3) * RotationX(-90.0) * Translation(-3.5, -16.0, .0);
    gl.model(T_haut);        /// Applique Transform T.
    gl.texture(tex);         // Applique Texture.
    gl.draw(m_rectangle_ex); /// Affichage du Mesh.

    // ================================= TRIANGLES Arriere =======================================
    // Triangle droit (vue arrière) en bas de la structure.
    gl.model(T * Scale(5.3, 1.0, 1.0) * RotationX(-90.0) * RotationZ(90.0) * Translation(12.0, .0, .0));
    gl.texture(tex);
    gl.draw(m_triangle_ex);

    // Triangle gauche (vue arrière) en bas de la structure.
    gl.model(T * Scale(5.3, 1.0, 1.0) * RotationX(-90.0) * Translation(.0, 12.0, .0));
    gl.texture(tex);
    gl.draw(m_triangle_ex);

    // ================================== TRIANGLES côté Gauche (VUE AVANT) =====================================
    // Triangle côté gauche (vue avant) par rapport à T_milieu bas
    gl.model(T * RotationX(-90.0) * RotationZ(180.0) * Translation(4.2, -6.0, .0));
    gl.texture(tex); // cf init.
    gl.draw(m_triangle_ex);

    // Triangle côté gauche (vue avant) par rapport à T_milieu
    gl.model(T * Scale(0.7, 1.0, 1.0) * RotationX(-90.0) * RotationZ(180.0) * Translation(5.0, .0, .0));
    gl.texture(tex); // cf init.
    gl.draw(m_triangle_ex);

    // Triangle côté gauche (vue avant) par rapport à T_milieu_haut
    gl.model(T * Scale(0.6, 1.0, 1.0) * RotationX(-90.0) * RotationZ(180.0) * Translation(4.0, 3.0, .0));
    gl.texture(tex); // cf init.
    gl.draw(m_triangle_ex);

    // Triangle côté gauche (vue avant) par rapport à T_haut
    gl.model(T * Scale(2.5, 1.0, 1.0) * RotationX(-90.0) * RotationZ(180.0) * Translation(.0, 4.8, .0));
    gl.texture(tex); // cf init.
    gl.draw(m_triangle_ex);

    // ================================== TRIANGLES COTE DROIT (VUE AVANT) =====================================
    // Triangle côté droit (vue avant) par rapport à T_haut
    gl.model(T * Scale(2.5, 1.0, 1.0) * RotationX(-90.0) * RotationZ(270.0) * Translation(4.8, .0, .0));
    gl.texture(tex); // cf init.
    gl.draw(m_triangle_ex);

    // Triangle côté droit (vue avant) par rapport à T_milieu_haut
    gl.model(T * Scale(0.6, 1.0, 1.0) * RotationX(-90.0) * RotationZ(270.0) * Translation(3.0, 4.0, .0));
    gl.texture(tex); // cf init.
    gl.draw(m_triangle_ex);

    // Triangle côté droit (vue avant) par rapport à T_milieu
    gl.model(T * Scale(0.7, 1.0, 1.0) * RotationX(-90.0) * RotationZ(270.0) * Translation(.0, 5.0, .0));
    gl.texture(tex); // cf init.
    gl.draw(m_triangle_ex);

    // Triangle côté droit (vue avant) par rapport à T_milieu bas
    gl.model(T * RotationX(-90.0) * RotationZ(270.0) * Translation(-6.0, 4.2, .0));
    gl.texture(tex); // cf init.
    gl.draw(m_triangle_ex);

    // ================================ Couvercles pour les blocs ===============================================
    // Couvercle pour le rectangle en bas. 
    gl.model(T * Scale(5.25, 1.0, 3.0) * RotationX(-90.0) * Translation(.0, 3.0, 1.5));
    gl.texture(tex);
    gl.draw(m_quad);

    // Couvercle pour le rectangle du milieu. 
    gl.model(T * Scale(4.25, 1.0, 3.0) * RotationX(-90.0) * Translation(.0, 1.0, 1.5));
    gl.texture(tex);
    gl.draw(m_quad);

    // Couvercle pour le rectangle milieu_haut. 
    gl.model(T * Scale(3.5, 1.0, 1.5) * RotationX(-90.0) * Translation(.0, -1.0, 1.5));
    gl.texture(tex);
    gl.draw(m_quad);

    // Couvercle pour le rectangle en haut. 
    gl.model(T * Scale(2.5, 1.0, .95) * RotationX(-90.0) * Translation(.0, -4.1, 1.5));
    gl.texture(tex);
    gl.draw(m_quad);
}
 // Procédure de rendu de la tour de controle (Rectangle et Triangle pour la base).
void ViewerEtudiant::draw_tour(const Transform &T, unsigned int tex)
{
    // Base de la tour (Triangle extrudé).
    gl.model(T * RotationY(90.0) * Scale(5.0, 3.0, 1.0) * Translation(1.5, .0, -.8));
    gl.texture(tex);
    gl.draw(m_triangle_ex);

    // Rectangle qui fait la forme de la tour.
    gl.model(T * RotationY(90.0) * Scale(1.0, .7, 2.5) * Translation(8.0, 5.7, .0)); // Refaire si j'ai le temps avec 2 rectangles et 4 triangles.
    gl.texture(tex);
    gl.draw(m_cube);
}
// Procédure de rendu de la tour où l'on a des triangles qui font le tour du rectangle de la tour de controle.
void ViewerEtudiant::draw_contour_tour(const Transform &T, unsigned int tex)
{
    // Dessine les triangles qui seront le contour du rectangle pour la tour radio.
    gl.model(T * Scale(2.5, .5, 1.3) * RotationZ(90.0) * Translation(9.4, .0, -6.9));
    gl.texture(tex);
    gl.draw(m_triangle_ex);

    // Dessine les triangles qui seront le contour du rectangle pour la tour radio.
    gl.model(T * Scale(2.5, .5, 1.3) * Translation(.0, 9.4, -6.9));
    gl.texture(tex);
    gl.draw(m_triangle_ex);
}
// Procédure de rendu des Sphères et Cylindres au dessus du rectangle de la tour.
void ViewerEtudiant::draw_radio(const Transform &T, unsigned int tex)
{
    // ====================== Tour radio 1 droite ===================================

    // Pilier le plus à droite devant (vue de l'avant).
    gl.model(T * Scale(0.1, 0.4, .1) * Translation(15.0, 13.5, -76.0));
    gl.texture(tex);
    gl.draw(m_cylindre);

    // Pilier le plus à droite arrière (vue avant).
    gl.model(T * Scale(0.1, 0.4, .1) * Translation(15.0, 13.5, -84.0));
    gl.texture(tex);
    gl.draw(m_cylindre);

    // Pilier gauche avant (vue avant).
    gl.model(T * Scale(0.1, 0.4, .1) * Translation(8.0, 13.5, -76.0));
    gl.texture(tex);
    gl.draw(m_cylindre);

    // Pilier gauche arrière (vue avant).
    gl.model(T * Scale(0.1, 0.4, .1) * Translation(8.0, 13.5, -84.0));
    gl.texture(tex);
    gl.draw(m_cylindre);

    // Sphère de contrôle
    gl.model(T * Scale(0.5, 0.5, 0.5) * Translation(2.3, 11.5, -16.0));
    gl.texture(tex);
    gl.draw(m_sphere);
}
// Procédure de rendu de la forme du vaisseau avec des triangles (très mal opti cf explication rapport).
void ViewerEtudiant::draw_all_triangle(const Transform &T, unsigned int tex)
{

    gl.model(T * Rotation(Vector(1, 0, 0), 270.0) * Scale(20.0, 20.0, 20.0));
    gl.texture(tex);
    gl.draw(m_triangle);

    gl.model(T * Rotation(Vector(1, 0, 0), 270.0) * Scale(20.0, 20.0, 20.0));
    gl.texture(tex);
    gl.draw(m_triangle_close);

    gl.model(T * Rotation(Vector(1, 0, 0), 270.0) * Scale(20.0, 20.0, 20.0));
    gl.texture(tex);
    gl.draw(m_triangle_left);

    gl.model(T * Rotation(Vector(1, 0, 0), 270.0) * Scale(20.0, 20.0, 20.0));
    gl.texture(tex);
    gl.draw(m_triangle_close_left);

    // Réacteur gauche (en regardant à partir de derrière)
    gl.model(T * Translation(23, 0., 2.5) * Rotation(Vector(0, 0, 1), 90.0) * Scale(.5, .5, .5));
    gl.texture(tex);
    gl.draw(m_cylindre);
    // Réacteur milieu =======================
    gl.model(T * Translation(24.5, 1.0, 0) * Rotation(Vector(0, 0, 1), 90.0) * Scale(.5, .5, .5));
    gl.texture(tex);
    gl.draw(m_cylindre);
    //Réacteur droit en (en regardant de l'arrière)
    gl.model(T * Translation(23, 0., -2.5) * Rotation(Vector(0, 0, 1), 90.0) * Scale(.5, .5, .5));
    gl.texture(tex);
    gl.draw(m_cylindre);
}
// Procédure de rendu de qui affiche la structure en escalier du vaisseau.
void ViewerEtudiant::draw_base_croiseur(const Transform &T, unsigned int tex)
{

    /// ================ Affichage de l'objet extrudé =====================
    draw_extrusion(T * Scale(1.0, 0.5, 1.0), tex);
    draw_extrusion(T * Scale(0.8, 0.5, 0.9) * Translation(.0, 1.2, .0), tex); 
    draw_extrusion(T * Scale(0.5, 0.5, 0.6) * Translation(.0, 2.0, .0), tex);
    draw_extrusion(T * Scale(0.3, 0.5, 0.6) * Translation(.0, 3.0, .0), tex);

    // Tour
    draw_tour(T, tex);
    //      Contour Tour
    draw_contour_tour(T, tex);

    draw_contour_tour(T * RotationZ(-180.0) * Translation(.0, -8.0, .0), tex);

    //                    Radio

    draw_radio(T * RotationZ(-10.0) * Translation(-.2, .0, .0), tex);
    draw_radio(T * RotationZ(10.0) * Translation(-2.0, .0, .0), tex);
}
// Procédure qui affiche l'image selon la valeur du compteur qui est déf en fonction du temps (cf update).
void ViewerEtudiant::draw_animation(const Transform &T, unsigned int nbimage)
{
    switch (compteur % nbimage)
    { // Je n'ai pas trouvé d'autre option que de mettre 1 cas par image (manque de temps).
        case 1:
            draw_quad(T, m_animation[0]);
            break;
        case 2:
            draw_quad(T, m_animation[1]);
            break;
        case 3:
            draw_quad(T, m_animation[2]);
            break;
        case 4:
            draw_quad(T, m_animation[3]);
            break;
        case 5:
            draw_quad(T, m_animation[4]);
            break;
        case 6:
            draw_quad(T, m_animation[5]);
            break;
        case 7:
            draw_quad(T, m_animation[6]);
            break;
        case 8:
            draw_quad(T, m_animation[7]);
            break;
        case 9:
            draw_quad(T, m_animation[8]);
            break;
        case 10:
            draw_quad(T, m_animation[9]);
            break;
        case 11:
            draw_quad(T, m_animation[10]);
            break;
        case 12:
            draw_quad(T, m_animation[11]);
            break;
        case 13:
            draw_quad(T, m_animation[12]);
            break;
        case 14:
            draw_quad(T, m_animation[13]);
            break;
        case 15:
            draw_quad(T, m_animation[14]);
            break;
        case 16:
            draw_quad(T, m_animation[15]);
            break;
        case 17:
            draw_quad(T, m_animation[16]);
            break;
        case 18:
            draw_quad(T, m_animation[17]);
            break;
        case 19:
            draw_quad(T, m_animation[18]);
            break;
        case 20:
            draw_quad(T, m_animation[19]);
            break;
        case 21:
            draw_quad(T, m_animation[20]);
            break;
        case 22:
            draw_quad(T, m_animation[21]);
            break;
        case 23:
            draw_quad(T, m_animation[22]);
            break;
        case 24:
            draw_quad(T, m_animation[23]);
            break;
        case 25:
            draw_quad(T, m_animation[24]);
            break;
        case 26:
            draw_quad(T, m_animation[25]);
            break;
        case 27:
            draw_quad(T, m_animation[26]);
            break;
        case 28:
            draw_quad(T, m_animation[27]);
            break;
        case 29:
            draw_quad(T, m_animation[28]);
            break;
        case 30:
            draw_quad(T, m_animation[29]);
            break;
        case 31:
            draw_quad(T, m_animation[30]);
            break;
        case 32:
            draw_quad(T, m_animation[31]);
            break;
        case 33:
            draw_quad(T, m_animation[32]);
            break;
        case 0:
            draw_quad(T, m_animation[33]);
            break;
    }
}
// Affiche un quad avec une texture passé en paramètre.
void ViewerEtudiant::draw_quad(const Transform &T, unsigned int tex)
{
    gl.model(T);
    gl.alpha(0.5f);
    gl.texture(tex);
    gl.draw(m_quad);
}

// ========================== Fonction dans laquelle on fait les appels aux DrawObjet ============================

int ViewerEtudiant::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    manageCameraLight();

    gl.camera(m_camera);

    /// Transformation géométrique appliquée au Mesh
    Transform T = Translation(2, 0, 0);

    /// Cas où pas de transformation géométrique
    Transform T_init = Identity(); // Matrice identité.

    // =========== Affichage du Cube ==================
    //draw_Cube(T_init);

    // =========== Affichage de la sphere ==============
    draw_sphere(m_planete * Translation(4, 100, 4) * Scale(20, 20, 20));

    // ============== Affichage de l'objet de type obj dans le dossier data =========
    draw_objet(T * Translation(0, 20, 0) * Rotation(Vector(0, 0, 1), -15), m_obj);

    draw_objet(T * Translation(50.0, 25, 10.0) * Scale(.5, .5, .5) * RotationY(90), m_fighter);

    // ========== Affichage du cylindre =================
    //draw_cylindre(T_init);

    /// =============== Affichage du cone ================
    //draw_cone(T_init*Translation(0,5,0));

    /// ================ Affichage du vase =====================
    //draw_vase(T*Translation(0,5,0));

    ///  =================== Affichage du terrain =================
    draw_terrain(T_init);

    // =================== Affichage de l'arbre ====================
    draw_arbre(T* Translation(-20.0, -135.0, .0) * Scale(10.0, 20.0, 10.0));

    ///  =================== Affichage du Cubemap =================
    draw_cubemap(T);

    // ================== Affichage de l'objet simple animé (croiseur interstellaire starwars) ===============
    Transform base_croiseur = T_init * RotationY(270.0) * Scale(1.3, 1.3, 1.3) * Translation(.0, 32.0, -58.0);

    draw_all_triangle(m_croiseur * Translation(50.0, 40.0, .0) * Scale(2.0, 2.0, 2.0), texture_croiseur);
    draw_base_croiseur(m_croiseur * base_croiseur, texture_croiseur);

    // ================== Affichage de quads qui vont changer toute les 24s d'image ====================================
    draw_animation(T* Scale(5.0, 5.0, 5.0) * Translation(14.0, 1.0, 13.0), 34);

    return 1;
}

// ================================== Fonction Update ====================================
int ViewerEtudiant::update(const float time, const float delta)
{
    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.
    // Animation d'une iamge 2D
    float t_s2 = time / 24.0;
    compteur = int(t_s2);
    
    float t_s = time / 1000.0;

    int t_e = int(t_s);
    int it_e = t_e % m_anim.nb_points();

    float poids = t_s - t_e;
    int it_e_suiv = (t_e + 1) % m_anim.nb_points();
    int it_e_suiv2 = (it_e_suiv + 1) % m_anim.nb_points();

    

    Point p0 = m_anim[it_e];
    Point p1 = m_anim[it_e_suiv];
    Point p2 = m_anim[it_e_suiv2];
    Vector pos = Vector(p0) + (Vector(p1) - Vector(p0)) * poids;
    Vector pos_suiv = Vector(p1) + (Vector(p2) - Vector(p1)) * poids;
    Vector dir = normalize(pos_suiv - pos);
    Vector up = Vector(0, 1, 0);
    Vector codir = cross(dir, up);
    m_planete = Transform(dir.x, up.x, codir.x, pos.x, dir.y, up.y, codir.y, pos.y, dir.z, up.z, codir.z, pos.z, 0, 0, 0, 1);

    return 0;
}

/*
 * Constructeur.
 */

ViewerEtudiant::ViewerEtudiant() : Viewer()
{
}

// ============================= Programme principal ================================

int main(int argc, char **argv)
{
    ViewerEtudiant v;
    v.run();
    return 0;
}
