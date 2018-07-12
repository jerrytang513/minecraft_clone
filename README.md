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

=========================================================================
HeightChunk

Feed in a

TODO List :

Each Chunk Contains an ID number.
After a height chunk is deleted. Set its pointer in the grid to nullptr.
 Initial width and initial length value can be stored inside the height chunk.
Have a 2D world space grid of constant width and length
All grids have needUpdate = false
Each grid will contain a height chunk
A height chunk will have the following functionalities
- Generate initial Height
  - Dynamically add heights and build up chunks.
  - When a chunk is built or modified set it to need update
  - If at least one chunk inside the height chunk need update, then the whole height chunk is set to need update.
- Generate chunk mesh.
When player moved, row of height chunks are created and rows of height chunks behind the user are destroyed.


Once a chunk gets updated, call generateChunkMesh for surrounding 6 chunks and the current chunk.
Each chunk contains an ID, generateChunkMesh will store this ID inside a hashmap, the generate and update mesh process will be :

A chunk is updated.
Check the status of surrounding 6 chunks. (Will be deleted, notActive, normal)
If they are in normal stat, delete its mesh in the display list and generate their chunk mesh concurrently.

1. Generate all heights concurrently, maintain a counter, if counter != 0 then some height has not been generated yet. Hold, until all heights are valid. 
