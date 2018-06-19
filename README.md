# PHYSICS ENGINE
# physics_engine

## Use the Mesh class for generating VAO VBO and IBO
1. Create all the vertices.
2. Create all the indices.
3. Pass in the VertexAttribPointer information by calling Mesh::addVertexAttribPointer(int,GLenum,bool,int,const void*)
4. Initialize by calling Mesh::createMesh(GLfloat*,unsigned int*, unsigned int,unsigned int)
5. Place the renderMesh() inside the render loop

### Optional (Texture)
https://learnopengl.com/Getting-started/Textures
Each Mesh Class contains a texture object. To add textures into the Mesh Object do the following:
1. Pass in the image path and GLenum texture (Used to represent a texture unit) to the function Mesh::addTextureAttrib(std::string path, GLenum texture)

## Use the Program class to link and compile shader programs
ShaderTypes are : GL_VERTEX_SHADER GL_FRAGMENT_SHADER GL_GEOMETRY_SHADER
1. Create a Program Object by calling Program::Program()
2. Get the shader file path and the shader type and pass into Program::addShader(std::string filepath, GLenum shaderType)
3. Compile the program by calling Program::compileProgram()
4. Use the program by calling Program::use()
5. Add any uniform value by calling the Program's set function after calling Program::use()
