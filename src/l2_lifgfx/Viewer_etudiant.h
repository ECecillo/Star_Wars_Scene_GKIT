
#ifndef VIEWER_ETUDIANT_H
#define VIEWER_ETUDIANT_H

#include "Viewer.h"

class ViewerEtudiant : public Viewer
{
public:
    ViewerEtudiant();

    int init();
    int render();
    int update(const float time, const float delta);

protected:
    // =================== Déclaration des Structures de donnée ============================
    struct Vase
    {
        int vase_NBPT;            // Nombre de point pour la silhouette 2D.
        int vase_NBROT;           // Nombre de point que l'on veut pour faire la rotation du vase (plus il y aura de point plus on aura un vase lisse).
        Point vase_p[10];         // Tableau de point qui seront la référence à notre base.
        Point vase_v[100][100];   // Tableau de tout mes sommets pour le vase
        Vector vase_vn[100][100]; // Tableau pour les normales de mes sommets dans vase_v
    };
    struct extruded_obj
    {
        int extrud_NBPT; // Nombre de point de l'objet 2D.
        int extrud_NBA;  // Nombre de fois que l'on applique la fonction sur les points.

        Point extrusion_p[100];           // Tableau de point pour l'objet 2D avant extrusion.
        Vector extrusion_vec[100][2];     // Tableau de point pour l'objet après l'application du vecteur.
        Vector extrusion_vecNorm[2][100]; // Tableau de normale pour les points de extrusion_vec.
    };

    // ================================== Déclaration des structures de données qui seront utilisés =============================
    Vase va;             // Pour l'utilisation de la structure vase.
    extruded_obj rec;    // Déclaration d'une variable de type extruded_obj pour faire un rectangle.
    extruded_obj tr;     // Déclaration d'une variable de type extruded_obj pour faire un triangle.
    extruded_obj equerre;// Déclaration d'une variable de type extruded_obj pour faire une équerre.

    /// =========================== Declaration des Mesh =============================================
    Mesh m_disque;                  // Objet de maillage pour le disque.
    Mesh m_Cube;                    // Objet de maillage pour le cube.
    Mesh m_cylindre;                // Objet de maillage pour le cylindre.
    Mesh m_cone;                    // Objet de maillage pour le cône.
    Mesh m_sphere;                  // Objet de maillage pour la sphère.
    Mesh m_vase;                    // Objet de maillage pour le vase.
    Mesh m_terrain;                 // Objet de maillage pour la génération du terrain.
    Mesh m_arbre;                   // Objet de maillage pour la génération d'abre.
    Mesh m_cubemap;                 // Objet de maillage pour le cubemap.


    Mesh m_obj;                     // Mesh pour essayer d'afficher un fichier obj.
    Mesh m_fighter;                 // Mesh pour importer le fichier tie fighter.obj.
    
    
    Mesh m_rectangle_ex;            // Objet que l'on utilisera pour l'extrusion d'un rectangle.
    Mesh m_triangle_ex;             // Objet de maillage que l'on utilisera pour faire l'extrusion d'un triangle.
    
    Mesh m_triangle;                // Triangle qui fait la forme du Croiseur Interstellaire.
    Mesh m_triangle_left;           // Triangle à gauche (vue de l'avant) qui fait également la forme du Croiseur.
    Mesh m_triangle_close;          // Triangle qui ferme l'arrière du croiseur.
    Mesh m_triangle_close_left;     // Triangle qui ferme le côté gauche à l'arrière du croiseur.

    Mesh m_quad;                    // Objet de maillage d'un quad.

    // ========================= Déclaration objet Transform pour animation =============================================
    Transform m_croiseur;           // Objet que l'on utilise pour le maillage et l'anim. (dans notre cas on ne l'utilisera pas).

    Transform m_planete;            // Objet que l'on utilisera pour faire tourner notre sphère sur elle même pour avoir un mouvement d'orbite.
    Transform R;

    // ========================= Variable nécessaire pour faire un compteur (image 2D animé) ====================================
    unsigned int compteur;   // Compteur qui nous donnera le temps pour l'animation.
    GLuint m_animation[100]; // On met le tableau à 100 car c'est un tableau statique (on aurait put utiliser les TD avec les vectors).

    /// ======================== Declaration des Textures ============================
    GLint obj;               // Texture de l'objet importé.
    GLuint terrain_texture;  // Texture du Terrain
    GLuint vase_text;        // Texture du Vase
    GLuint cone_texture;     // Texture du Cone.
    GLuint cylindre_texture; // Texture du Cylindre.
    GLuint disque_texture;   // Texture du Disque.
    GLuint sphere_texture;   // Texture de la Sphere.
    GLuint arbre_texture;    // Texture de l'arbre.
    GLuint cubemap;          // Texture du Cubemap.
    GLuint triangle_texture; // Texture du Triangle.
    GLuint texture_croiseur; // Texture du croiseur.


    /// ================ Declaration des fonction de creation de Mesh du type init_votreObjet() ==========================
    void init_quad();                 // Procédure qui initialise un quad avec des triangles Strip.
    void init_disque();               // Procédure d'initialisation du Mesh du Disque.
    void init_Cube();                 // Procédure d'initialisation du Mesh du Cube.
    void init_cylindre();             // Procédure d'initialisation du Mesh du Cylindre.
    void init_cone();                 // Procédure d'initialisation du Mesh du Cône.
    void init_sphere();               // Procédure d'initialisation du Mesh de la Sphere.
    void create_vertex_normal_vase(); // Procédure d'initialisation de la silhouette 2D du vase (Points, Normales ...).
    void init_vase();                 // Procédure d'initialisation du Mesh du Vase.
    void init_terrain();              // Procédure d'initialisation du Mesh du Terrain qui fera appel à la fonction de type vector NormalTerrain.
    void init_arbre();                // Procédure d'initialisation du Mesh arbre qui 
    void init_cubemap();              // Procédure d'initialisation du Mesh pour le Cubemap.

    void init_triangle();             // Les procédures d'initialisations pour l'initialisation du vaisseau (cf les mesh correspondants aux proc).
    void init_triangle_close();       // Les procédures d'initialisations pour l'initialisation du vaisseau (cf les mesh correspondants aux proc).
    void init_triangle_left();        // Les procédures d'initialisations pour l'initialisation du vaisseau (cf les mesh correspondants aux proc).
    void init_triangle_close_left();  // Les procédures d'initialisations pour l'initialisation du vaisseau (cf les mesh correspondants aux proc).

    void generate_extrusion(extruded_obj &obj, int nbPoint, Point tab[100]);     // Calcul les points pour l'extrusion d'un objet 2D que l'on aura passé en paramètre.
/*     
    obj : structure dans laquelle on a définit les champs nécessaires pour faire l'extrusion.
    nbPoint : Le nombre de point de la forme 2D.
    tab : Tableau de point qui comprendra les coordo de la figure 2D.
*/

    void init_face_triangle(Mesh &m_extr, extruded_obj &obj); // Initialise les faces avant et arrière du triangle pour pouvoir le fermer.
/*
    m_extr : Objet de type maillage que l'on passe en paramètre si l'on veut faire plusieurs extrusions.
    obj : Structure de donnée que l'on passe en paramètre qui contient les champs nécessaires à la fonction.
*/

    void init_extrusion(Mesh& mesh_object, extruded_obj &obj, int nbPoint, Point tab[100]);  // Initialisation du Mesh pour l'extrusion (normales, text ...)
/*     
     mesh_object : Mesh que l'on veut passer en paramètre si on veut plusieurs objets.
     obj : Structure de l'objet sur lequel on a fait les calculs précédement dans generate_extrusion.
     nbPoint : Le nombre de point de la forme 2D.
     tab : Tableau de point qui comprendra les coordo de la figure 2D.
*/

    void init_2D_table(const unsigned int nombre_image);


    /// ================== Declaration des fonctions draw_votreObjet(const Transform& T) ========================

    void draw_disque(const Transform &T);                                     // Procédure de rendu et d'affichage d'un Disque.
    void draw_Cube(const Transform &T);                                       // Procédure d'affichage du Cube avec T la variable que l'on passera en paramètre pour appliquer des Transformations sur Objet.
    void draw_sphere(const Transform &T);                                     // Procédure d'affichage de la Sphère avec T la variable que l'on passera en paramètre pour appliquer des Transformations sur Objet.
    void draw_cylindre(const Transform &T);                                   // Procédure de rendu et d'affichage d'un Cylindre. 
    void draw_cone(const Transform &T);                                       // Procédure d'affichage du Cône avec T la variable que l'on passera en paramètre pour appliquer des Transformations sur Objet.
    void draw_vase(const Transform &T);                                       // Procédure de rendu et d'affichage d'un Vase.
    void draw_terrain(const Transform &T);                                    // Procédure de rendu et d'affichage d'un Terrain.
    void draw_objet(const Transform &T, Mesh &obj);                           // Procédure de rendu et d'affichage d'un Objet que l'on a importé.
    void draw_cubemap(const Transform &T);                                    // Procédure de rendu et d'affichage d'un Cubemap.

    void draw_extrusion(const Transform &T, unsigned int tex);                // Procédure de rendu et d'affichage d'un Objet extrué.
    void draw_quad(const Transform &T, unsigned int tex);                     // Procédure de rendu et d'affichage d'un Quad.
    
    // Tous les draws que l'on utilisera pour faire la forme.
    void draw_all_triangle(const Transform &T, unsigned int tex);             // Procédure de rendu de la forme du vaisseau avec des triangles (très mal opti cf explication rapport).
    void draw_tour(const Transform& T, unsigned int tex);                     // Procédure de rendu de la tour de controle (Rectangle et Triangle pour la base).
    void draw_contour_tour(const Transform& T, unsigned int tex);             // Procédure de rendu de la tour où l'on a des triangles qui font le tour du rectangle de la tour de controle.
    void draw_radio(const Transform& T, unsigned int tex);                    // Procédure de rendu des Sphères et Cylindres au dessus du rectangle de la tour.
    void draw_base_croiseur(const Transform& T, unsigned int tex);            // Procédure de rendu de qui affiche la structure en escalier du vaisseau.
    void draw_animation(const Transform& T, unsigned int nbimage);            // Procédure qui affiche l'image selon la valeur du compteur qui est déf en fonction du temps (cf update).
    void draw_arbre(const Transform& T);
};

#endif


    Transform m_planete;            // Objet que l'on utilisera pour faire tourner notre sphère sur elle même pour avoir un mouvement d'orbite.
    GLuint sphere_texture;   // Texture de la Sphere.
