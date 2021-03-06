#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our {

    #define ATTRIB_LOC_POSITION 0
    #define ATTRIB_LOC_COLOR    1
    #define ATTRIB_LOC_TEXCOORD 2
    #define ATTRIB_LOC_NORMAL   3

    class Mesh {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // We need to remember the number of elements that will be draw by glDrawElements 
        GLsizei elementCount;
    public:

        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering 
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& elements)
        {
            //TODO: (Req 1) Write this function
            // remember to store the number of elements in "elementCount" since you will need it for drawing
            // For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc




            //storing number of elements
            elementCount = elements.size();


            //vertex array
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            //vertex buffer
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            //element buffer
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount*sizeof(unsigned int), &elements[0], GL_STATIC_DRAW);



            

            
            //we will use the constants defined
            GLint positionloc = ATTRIB_LOC_POSITION;
            GLint colorloc = ATTRIB_LOC_COLOR;
            GLint texloc = ATTRIB_LOC_TEXCOORD;
            GLint normalloc = ATTRIB_LOC_NORMAL;
            glEnableVertexAttribArray(positionloc);
            glEnableVertexAttribArray(colorloc);
            glEnableVertexAttribArray(texloc);
            glEnableVertexAttribArray(normalloc);
            //reading 3 vertices per time, sliding by sizeof(Vertex) per read, no offset as it is always the first 3 objects
            glVertexAttribPointer(positionloc, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
            // missing: rest of the attributes
            glVertexAttribPointer(colorloc, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void*)offsetof(Vertex, color));
            glVertexAttribPointer(texloc, 2, GL_FLOAT, true, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
            glVertexAttribPointer(normalloc, 3, GL_FLOAT, true, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        }

        // this function should render the mesh
        void draw() 
        {
            //TODO: (Req 1) Write this function


            // note : not sure where we bind the VAO// come here
            

            //missing : change from unsigned short to glint
            glBindVertexArray(VAO);

            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void*)0);
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh(){
            //TODO: (Req 1) Write this function



            //cleanup
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}