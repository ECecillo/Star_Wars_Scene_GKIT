# Rapport TP CECILLON Enzo 11805901

![src/readme/Untitled.png](src/readme/Untitled.png)

![src/readme/Untitled%201.png](src/readme/Untitled%201.png)

## 1. Manipulation des Formes de Bases.

### 🧊  Cube

---

- **Code**
    
    En-tête de la procédure dans le .h
    
    ![src/readme/Untitled%202.png](src/readme/Untitled%202.png)
    
    Corps Procédure Affichage :
    
    ![src/readme/Untitled%203.png](src/readme/Untitled%203.png)
    
- **Affichage**
    
    ![src/readme/Untitled%204.png](src/readme/Untitled%204.png)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%205.png](src/readme/Untitled%205.png)

### 🥫 Cylindre

---

- **Code**
    
    En-tête de la procédure dans le .h
    
    ![src/readme/Untitled%206.png](src/readme/Untitled%206.png)
    
    Corps Procédure Affichage :
    
    ![src/readme/Untitled%207.png](src/readme/Untitled%207.png)
    
- **Affichage**
    
    ![src/readme/Untitled%208.png](src/readme/Untitled%208.png)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%209.png](src/readme/Untitled%209.png)

### Cône

---

- **Code**
    
    En-tête de la procédure dans le .h
    
    ![src/readme/Untitled%2010.png](src/readme/Untitled%2010.png)
    
    Corps Procédure Affichage :
    
    ![src/readme/Untitled%2011.png](src/readme/Untitled%2011.png)
    
- **Affichage**
    
    ![src/readme/Untitled%2012.png](src/readme/Untitled%2012.png)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%2013.png](src/readme/Untitled%2013.png)

### ⭕ Sphere

---

- **Code**
    
    En-tête de la procédure dans le .h
    
    ![src/readme/Untitled%2014.png](src/readme/Untitled%2014.png)
    
    Corps Procédure Affichage :
    
    ![src/readme/Untitled%2015.png](src/readme/Untitled%2015.png)
    
- **Affichage**
    
    ![src/readme/Untitled%2016.png](src/readme/Untitled%2016.png)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%2017.png](src/readme/Untitled%2017.png)

## 2. Affichage à l'aide de Transformation géométriques

---

### Destroyeur Star Wars

---

- **Code**
    
    En-tête de la procédure dans le .h
    
    ![src/readme/Untitled%2018.png](src/readme/Untitled%2018.png)
    
    Corps Procédure Affichage :
    
    Affichage de la base du vaisseau (la forme qui fait comme un escalier)
    
    ![src/readme/Untitled%2019.png](src/readme/Untitled%2019.png)
    
    ![src/readme/Untitled%2020.png](src/readme/Untitled%2020.png)
    
    Procédure qui affiche la tour, radio, et le contour du rectangle de la tour.
    
    ![src/readme/Untitled%2021.png](src/readme/Untitled%2021.png)
    
    Procédure qui affiche les mesh que l'on a définit dans les init_triangles pour la forme du vaisseau et une grosse procédure qui appel tous les draws pour que cela soit moins chargé dans render()
    
    ![src/readme/Untitled%2022.png](src/readme/Untitled%2022.png)
    
- **Affichage**
    
    ![src/readme/Untitled%2023.png](src/readme/Untitled%2023.png)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%2024.png](src/readme/Untitled%2024.png)

![src/readme/Untitled%2025.png](src/readme/Untitled%2025.png)

<aside>
⚠️ **J'ai utilisé le code de l'extrusion pour le reste du vaisseau (base)**

</aside>

---

## 3. Terrain, texture, billboard (arbre) et Cubemap

---

### Terrain

---

- **Code**
    
    En-tête de la procédure dans le .h
    
    ![src/readme/Untitled%2026.png](src/readme/Untitled%2026.png)
    
    Corps Procédure Affichage :
    
    ![src/readme/Untitled%2027.png](src/readme/Untitled%2027.png)
    
- **Affichage**
    
    ![src/readme/Untitled%2028.png](src/readme/Untitled%2028.png)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%2029.png](src/readme/Untitled%2029.png)

### Arbre | Billboard

---

- Code
    
    En tête de la procédure dans le .h
    
    ![src/readme/Untitled%2030.png](src/readme/Untitled%2030.png)
    
    Corps Procédure Affichage :
    
    ![src/readme/Untitled%2031.png](src/readme/Untitled%2031.png)
    
- Affichage
    
    ![src/readme/Untitled%2032.png](src/readme/Untitled%2032.png)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%2033.png](src/readme/Untitled%2033.png)

<aside>
📌 **Je n'ai pas compris comment définir la position d'un arbre en fonction de la hauteur du terrain donc je n'ai pas mis de boucle for avec une position aléatoire.**

</aside>

### Cubemap

---

- Code
    
    En tête de la procédure dans le .h
    
    ![src/readme/Untitled%2034.png](src/readme/Untitled%2034.png)
    
    Corps Procédure Affichage :
    
    ![src/readme/Untitled%2035.png](src/readme/Untitled%2035.png)
    
- Affichage
    
    ![src/readme/Untitled%2036.png](src/readme/Untitled%2036.png)
    
    ![src/readme/Untitled%2037.png](src/readme/Untitled%2037.png)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%2038.png](src/readme/Untitled%2038.png)

## 4. Modélisation d'un objet par extrusion 3D

---

- **Code**
    
    En-tête de la procédure dans le .h
    
    ![src/readme/Untitled%2039.png](src/readme/Untitled%2039.png)
    
    Corps Procédure Affichage :
    
    <aside>
    ⚠️ **J'utilise ce code pour l'extrusion de mes objets pour mon vaisseau donc ce n'est pas vraiment une procédure indépendante.**
    
    </aside>
    
    ![src/readme/Untitled%2040.png](src/readme/Untitled%2040.png)
    
    ![src/readme/Untitled%2041.png](src/readme/Untitled%2041.png)
    
- **Affichage**
    
    Exemple avec l'extrusion du triangle
    
    ![src/readme/Untitled%2042.png](src/readme/Untitled%2042.png)
    
    <aside>
    ⚠️ **On a déclaré une fonction init pour avoir les faces avant et arrière de notre triangle extrudé (On doit faire cette fonction pour chaque forme que l'on veut extrudé.)**
    
    </aside>
    
    ![src/readme/Untitled%2043.png](src/readme/Untitled%2043.png)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%2044.png](src/readme/Untitled%2044.png)

![src/readme/Untitled%2045.png](src/readme/Untitled%2045.png)

![src/readme/Untitled%2046.png](src/readme/Untitled%2046.png)

## 5. Texture animée

---

- Code
    
    En tête de la procédure dans le .h
    
    ![src/readme/Untitled%2047.png](src/readme/Untitled%2047.png)
    
    Corps Procédure Affichage :
    
    <aside>
    📌 **Très mal optimisé mais je n'ai pas eu le temps de re réfléchir cette étape du draw.**
    
    </aside>
    
    ![src/readme/Untitled%2048.png](src/readme/Untitled%2048.png)
    
- Affichage
    
    ![src/readme/Peek_27-11-2020_13-04.gif](src/readme/Peek_27-11-2020_13-04.gif)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%2049.png](src/readme/Untitled%2049.png)

## 6. Animation

---

- Code
    
    En tête de la procédure dans le .h
    
    ![src/readme/Untitled%2050.png](src/readme/Untitled%2050.png)
    
    Corps Procédure Affichage :
    
    ![src/readme/Untitled%2051.png](src/readme/Untitled%2051.png)
    

Corps de la procédure dans le .cpp

![src/readme/Untitled%2052.png](src/readme/Untitled%2052.png)

- Affichage
    
    ![src/readme/Peek_27-11-2020_13-06.gif](src/readme/Peek_27-11-2020_13-06.gif)
    

![src/readme/Untitled%2053.png](src/readme/Untitled%2053.png)
