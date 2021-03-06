// #include "Mesh.hpp"

// Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
// {
// 	this->vertices = vertices;
// 	this->indices = indices;
// 	this->textures = textures;

// 	// now that we have all the required data, set the vertex buffers and its attribute pointers.
// 	SetupMesh();
// }

// Mesh::Mesh()
// {
// 	//Test mesh
// 	std::vector<Vertex> vertices;
// 	Vertex vertex;
// 	vertex.Position = glm::vec3(-0.5f, -0.5f, 0.0f);
// 	vertex.Normal = glm::vec3(1, 1, 1);
// 	vertex.TexCoords = glm::vec3(1, 1, 1);
// 	vertex.Bitangent = glm::vec3(1, 1, 1);
// 	vertex.Tangent = glm::vec3(1, 1, 1);
// 	vertices.push_back(vertex);
// 	vertex.Position = glm::vec3(0.5f, -0.5f, 0.0f);
// 	vertex.Normal = glm::vec3(1, 1, 1);
// 	vertex.TexCoords = glm::vec3(1, 1, 1);
// 	vertex.Bitangent = glm::vec3(1, 1, 1);
// 	vertex.Tangent = glm::vec3(1, 1, 1);
// 	vertices.push_back(vertex);
// 	vertex.Position = glm::vec3(0.0f, 0.5f, 0.0f);
// 	vertex.Normal = glm::vec3(1, 1, 1);
// 	vertex.TexCoords = glm::vec3(1, 1, 1);
// 	vertex.Bitangent = glm::vec3(1, 1, 1);
// 	vertex.Tangent = glm::vec3(1, 1, 1);
// 	vertices.push_back(vertex);
// 	std::vector<unsigned int> indices;
// 	indices.push_back(0);
// 	indices.push_back(1);
// 	indices.push_back(2);
// 	this->vertices = vertices;
// 	this->indices = indices;

// 	SetupMesh();
// }

// Mesh::~Mesh()
// {
// }

// void Mesh::Draw(unsigned int shaderID)
// {
// 	// bind appropriate textures
// 	unsigned int diffuseNr = 1;
// 	unsigned int specularNr = 1;
// 	unsigned int normalNr = 1;
// 	unsigned int heightNr = 1;
// 	for (unsigned int i = 0; i < textures.size(); i++)
// 	{
// 		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
// 		// retrieve texture number (the N in diffuse_textureN)
// 		std::string number;
// 		std::string name = textures[i].type;
// 		if (name == "texture_diffuse")
// 			number = std::to_string(diffuseNr++);
// 		else if (name == "texture_specular")
// 			number = std::to_string(specularNr++); // transfer unsigned int to stream
// 		else if (name == "texture_normal")
// 			number = std::to_string(normalNr++); // transfer unsigned int to stream
// 		else if (name == "texture_height")
// 			number = std::to_string(heightNr++); // transfer unsigned int to stream

// 												 // now set the sampler to the correct texture unit
// 		glUniform1i(glGetUniformLocation(shaderID, (name + number).c_str()), i);
// 		// and finally bind the texture
// 		glBindTexture(GL_TEXTURE_2D, textures[i].id);
// 	}

// 	// draw mesh
// 	glBindVertexArray(VAO);
// 	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
// 	glBindVertexArray(0);

// 	// always good practice to set everything back to defaults once configured.
// 	glActiveTexture(GL_TEXTURE0);
// }

// void Mesh::SetupMesh()
// {
// 	// create buffers/arrays
// 	glGenVertexArrays(1, &VAO);
// 	glGenBuffers(1, &VBO);
// 	glGenBuffers(1, &EBO);

// 	glBindVertexArray(VAO);
// 	// load data into vertex buffers
// 	glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 	// A great thing about structs is that their memory layout is sequential for all its items.
// 	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
// 	// again translates to 3/2 floats which translates to a byte array.
// 	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

// 	// set the vertex attribute pointers
// 	// vertex Positions
// 	glEnableVertexAttribArray(0);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
// 	// vertex normals
// 	glEnableVertexAttribArray(1);
// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
// 	// vertex texture coords
// 	glEnableVertexAttribArray(2);
// 	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
// 	// vertex tangent
// 	glEnableVertexAttribArray(3);
// 	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
// 	// vertex bitangent
// 	glEnableVertexAttribArray(4);
// 	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

// 	glBindVertexArray(0);
// }
