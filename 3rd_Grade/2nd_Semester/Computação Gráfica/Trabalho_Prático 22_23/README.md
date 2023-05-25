# Computação Gráfica

## Authors:

    Grupo34
    
    Paulo Filipe Cruz a80949
    Daniel Barbosa Faria a93191
    João Augusto Macedo Moreira a93326
    

# Overview:
This project is a 3D graphics engine that aims to provide the user with the ability to create and display 3D models with various features. The project is divided into four phases, each focusing on specific functionalities.

# Phase 1 – Graphical Primitives
This phase involves creating two applications: a model generator and an engine. The model generator generates files with model information by defining vertices, and the engine reads an XML configuration file to display the models.

# Phase 2 – Geometric Transforms
In this phase, the engine is updated to create hierarchical scenes using geometric transforms, such as translate, rotate, and scale. A scene is defined as a tree where each node contains a set of geometric transforms and models, with children nodes.

# Phase 3 – Curves, Cubic Surfaces and VBOs
The model generator application is updated to create a new type of model based on Bezier patches. The engine is extended to include the ability to perform animations based on Catmull-Rom cubic curves. Models may have time-dependent or static transforms. The rotation node is updated to perform a full 360 degrees rotation around the specified axis in a specified number of seconds.

# Phase 4 – Normals and Texture Coordinates
The model generator application is updated to generate texture coordinates and normals for each vertex. The engine is updated to activate lighting and texturing functionalities and apply the normals and texture coordinates from the model files.
