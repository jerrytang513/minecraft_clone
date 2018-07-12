=========================================================================
ChunkRenderer's render requirements:
1. Chunk Mesh
2. Draw Function to render the mesh

Functions:

void draw(ChunkMesh mesh);
void getChunkMesh(ChunkMesh mesh);
void generateChunkMesh(int chunkX, int chunkY, int chunkZ, const std::vector<std::vector<std::vector<BlockChunk>>>& m_chunks);
// Generate the ChunkMesh for the specific Chunk


pass in the ChunkMesh to render the whole thing

=========================================================================

ChunkMesh requirements:
1. Chunk Mesh should contain everything for chunkRender.
The following are Chunk Mesh's data :
2. Chunk location
3. Number of triangles inside a chunk
4. VAO
5. Shader Program
6. Indices
7. Textures
8. Vertices

Functions:

void setShader(Shader shader);
unsigned int getShaderID();
Vec3D getChunkCoordinate();

std::map<unsigned int, unsigned int>  getTextureIndexes();
This is used to define the index of the texture image. It contains 2 different data information
1. The index number of the picture.
2. The number of occurance.

std::vector<unsigned int> getTextureId();
This will be used in combine with the getTextureIndexes.
1. Get the texture index number
2. Set the texture ID corresponds to the texture index number
3. Use this texture for the number of times

unsigned int getVAO();

int getNumTriangles();

std::vector<unsigned int>& const getIndices();

setupMesh();
This will be called internally by the constructor to set up all the information and generate the VBO, EBO and VAO data.

ChunkMesh(std::vector<Vec3D> vertices, std::vector<unsigned int> indices,  std::map<unsigned int, unsigned int> textureIndexes, std::vector<Vec2D> textureCoords, int chunkX, int chunkY, int chunkZ, unsigned int shaderID);
This is the constructor, need to define all information to set up the Chunk Mesh.


=========================================================================
TextureManager

Intro: This is a central texture manager, it controls all textures, and can generate the texture coordinates for a specific texture index.

Functions:

Texture getTexture(int index)
std::vector<Vec2D> getCoordinates(int index, Vec2D cooridnate)

=========================================================================
BlockChunk

Data needed for initialization
1. Seed
2. Starting Location 
