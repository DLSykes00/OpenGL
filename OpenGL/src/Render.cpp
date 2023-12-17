#include "Render.h"

#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <cmath>

const double _PI = 3.14159265358979323846;
const double _2PI = (2 * _PI);

Render::Render() 
{
    glGenBuffers(1, &vertexBufferID);
   
    glGenBuffers(1, &indexBufferID);
    
    glGenBuffers(1, &textureBufferID);

    glGenBuffers(1, &instanceOffsetBufferID);
}

unsigned int Render::drawTriangle()
{
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    float vertexPositions[] =
    {
        -0.5f, -0.5f, //0
        0.5f, -0.5f, //1
        0.5f, 0.5f, //2
        -0.5f, 0.5f, //3
    };

    unsigned int vertexIndices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    unsigned int numOfVertElements = sizeof(vertexPositions) / sizeof(float);
    unsigned int numOfVertIndices = sizeof(vertexIndices) / sizeof(unsigned int);
    std::cout << numOfVertIndices << std::endl;

    glBufferData(GL_ARRAY_BUFFER, numOfVertElements * sizeof(float), vertexPositions, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfVertIndices * sizeof(unsigned int), vertexIndices, GL_STATIC_DRAW);

    return numOfVertIndices;
}

unsigned int Render::drawCircle(float s)
{
    float size = s;
    float y;
    float x;
    unsigned int numOfTris = 64;

    /*Get verts  (parametric equation of circle)*/
    float tIncrement = float((_2PI / numOfTris) + 0.00001f);
    const int arraySizeVertexPositions = (int)(2.0f * (std::ceil(_2PI / tIncrement) + 1.0f));
    float* vertexPositions = (float*)malloc(arraySizeVertexPositions * sizeof(float));

    vertexPositions[0] = 0;
    vertexPositions[1] = 0;
    int arrayIndex = 2;

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    for ( float t = 0; t < _2PI; t += tIncrement )
    {
        x = size * std::cos(t);
        vertexPositions[arrayIndex] = x; arrayIndex++;

        y = size * std::sin(t); 
        vertexPositions[arrayIndex] = y; arrayIndex++;
    }

    const unsigned int numOfVertPoints = arraySizeVertexPositions/2;
    std::cout << "\nNumber of vert points: " << numOfVertPoints << std::endl;

    /*Vert Indicies*/
    const unsigned int numOfVertIndices = 3 * (numOfVertPoints - 1);
    unsigned int* vertexIndices = (unsigned int*)malloc(numOfVertIndices * sizeof(unsigned int));

    arrayIndex = 0;
    for (unsigned int i = 1; i < (numOfVertPoints-1); i++)
    {
        vertexIndices[arrayIndex] = 0; arrayIndex++;
        vertexIndices[arrayIndex] = i; arrayIndex++;
        vertexIndices[arrayIndex] = i + 1; arrayIndex++;   
    }
    //Connect center, last and first vertex to close circle
    vertexIndices[numOfVertIndices - 3] = 0; vertexIndices[numOfVertIndices - 2] = numOfVertPoints - 1; vertexIndices[numOfVertIndices - 1] = 1;

    std::cout << "\nNum of verts: " << numOfVertIndices << std::endl;
    std::cout << "Num of tris: " << numOfVertIndices/3 << std::endl;

    glBufferData(GL_ARRAY_BUFFER, arraySizeVertexPositions * sizeof(float), vertexPositions, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfVertIndices * sizeof(unsigned int), vertexIndices, GL_STATIC_DRAW);
    
    free(vertexIndices);
    free(vertexPositions);

    return numOfVertIndices;
}

void Render::drawCube()
{
    float vertexPositions[] =
    {
        //Front
        -1.0f, -1.0f,  1.0f,  //0
        1.0f, -1.0f,  1.0f,  //1   
        1.0f,  1.0f,  1.0f,  //2
        -1.0f,  1.0f,  1.0f,  //3
        //right
        1.0f, -1.0f,  1.0f,  //4 
        1.0f, -1.0f, -1.0f,  //5
        1.0f,  1.0f, -1.0f,  //6
        1.0f,  1.0f,  1.0f,  //7
        //left
        -1.0f, -1.0f, -1.0f,  //8 
        -1.0f, -1.0f,  1.0f,  //9
        -1.0f,  1.0f,  1.0f,  //10
        -1.0f,  1.0f, -1.0f,  //11
        //back
        1.0f, -1.0f, -1.0f,  //12
        -1.0f, -1.0f, -1.0f,  //13 
        -1.0f,  1.0f, -1.0f,  //14
        1.0f,  1.0f, -1.0f,  //15
        //bottom
        -1.0f, -1.0f, -1.0f,  //16
        1.0f, -1.0f, -1.0f,  //17
        1.0f, -1.0f,  1.0f,  //18
        -1.0f, -1.0f,  1.0f,  //19
        //top
        -1.0f,  1.0f,  1.0f,  //20
        1.0f,  1.0f,  1.0f,  //21
        1.0f,  1.0f, -1.0f,  //22
        -1.0f,  1.0f, -1.0f   //23

    };

    float textureBuffer[] =
    {
        //front
        0.0f, 0.0f,  
        1.0f, 0.0f, 
        1.0f, 1.0f, 
        0.0f, 1.0f,
        //right
        0.0f, 0.0f, 
        1.0f, 0.0f,  
        1.0f, 1.0f, 
        0.0f, 1.0f,
        //left
        0.0f, 0.0f, 
        1.0f, 0.0f, 
        1.0f, 1.0f, 
        0.0f, 1.0f,
        //back
        0.0f, 0.0f,  
        1.0f, 0.0f,  
        1.0f, 1.0f, 
        0.0f, 1.0f,
        //bottom
        0.0f, 0.0f,  
        1.0f, 0.0f, 
        1.0f, 1.0f,
        0.0f, 1.0f,
        //top
        0.0f, 0.0f,  
        1.0f, 0.0f,  
        1.0f, 1.0f, 
        0.0f, 1.0f
    };

    unsigned int vertexIndices[] =
    {
        // front
        0, 1, 2,
        2, 3, 0,
        // right
        4, 5, 6,
        6, 7, 4,
        // left
        8, 9, 10,
        10, 11, 8,
        // back
        12, 13, 14,
        14, 15, 12,
        // bottom
        16, 17, 18,
        18, 19, 16,
        // top
        20, 21, 22,
        22, 23, 20
    };

    
    float instaceOffsetBuffer[] = 
    {
        -2.0f, 0.0f, 0.0f,
        2.0f, 0.0f, 0.0f
    };
    

    int numOfVertElements = sizeof(vertexPositions) / sizeof(float);
    int numOfVertIndices = sizeof(vertexIndices) / sizeof(unsigned int);

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0 );
    glBufferData(GL_ARRAY_BUFFER, numOfVertElements * sizeof(float), vertexPositions, GL_STATIC_DRAW);

    //Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(unsigned int), 0);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfVertIndices * sizeof(unsigned int), vertexIndices, GL_STATIC_DRAW);
    
    //Texture
    glBindBuffer(GL_ARRAY_BUFFER, textureBufferID);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureBuffer), textureBuffer, GL_STATIC_DRAW);
   
    //Instance
    glBindBuffer(GL_ARRAY_BUFFER, instanceOffsetBufferID);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(instaceOffsetBuffer), instaceOffsetBuffer, GL_STATIC_DRAW);
    glVertexAttribDivisor(2, 1);

    vertCount = numOfVertIndices;
    instanceCount = sizeof(instaceOffsetBuffer) / (3 * sizeof(float));
}

unsigned int Render::drawSquare3D()
{
    float vertexPositions[] =
    {
        //Face
        -1.0f, -1.0f,  1.0f,  //0
        1.0f, -1.0f,  1.0f,  //1   
        1.0f,  1.0f,  1.0f,  //2
        -1.0f,  1.0f,  1.0f,  //3
    };

    float textureBuffer[] =
    {
        //Face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };

    unsigned int vertexIndices[] =
    {
        //Face
        0, 1, 2,
        2, 3, 0,
    };


    float instaceOffsetBuffer[] =
    {
        0.0f, 0.0f, 0.0f
    };

    int numOfVertElements = sizeof(vertexPositions) / sizeof(float);
    int numOfVertIndices = sizeof(vertexIndices) / sizeof(unsigned int);

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glBufferData(GL_ARRAY_BUFFER, numOfVertElements * sizeof(float), vertexPositions, GL_STATIC_DRAW);

    //Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(unsigned int), 0);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfVertIndices * sizeof(unsigned int), vertexIndices, GL_STATIC_DRAW);

    //Texture
    glBindBuffer(GL_ARRAY_BUFFER, textureBufferID);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureBuffer), textureBuffer, GL_STATIC_DRAW);

    //Instance
    glBindBuffer(GL_ARRAY_BUFFER, instanceOffsetBufferID);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(instaceOffsetBuffer), instaceOffsetBuffer, GL_STATIC_DRAW);
    glVertexAttribDivisor(2, 1);

    return numOfVertIndices;
}

unsigned int Render::getVertCount()
{
    return vertCount;
}

unsigned int Render::getInstanceCount()
{
    return instanceCount;
}
