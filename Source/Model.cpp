// Biblioteca propria
#include "../Header/Model.h"
#include "../Header/drawings.h"

Model::Model(const char* fileName)
{
	Parser aux = Parser::parseModel(fileName);

    const char* path = aux.texture;

    this->texture.id = loadTexture(path);
	this->texture.path = path;
	this->modelo = aux.modelo;
	this->dependsOnLight = aux.dependsOnLight;
	this->size = aux.size;
	this->translationPeriod = aux.translationPeriod;
    this->rotationPeriod = aux.rotationPeriod;

	double translationSpeed, angularSpeed;

    if(translationPeriod != 0) translationSpeed = 306.0 / this->translationPeriod;
    else                       translationSpeed = 0;

    if(rotationPeriod != 0) angularSpeed = 30.0/ this->rotationPeriod;
    else                    angularSpeed = 0;

    this->translationAngularSpeed = translationSpeed;
    this->rotationAngularSpeed = angularSpeed;

	this->light = new Light(); 
	this->hasLight = 0;

	this->material = new Material();

    for(int i=0; i<4; i++)
    {
        this->material->matAmbient[i] = aux.matAmbient[i];
        this->material->matDifuse[i] = aux.matDifuse[i];
        this->material->matEspec[i] = aux.matEspec[i];
    }
    this->material->matShininess = aux.matShininess;

	this->vertices = loadObject(aux.modelo);

	GLuint auxList = glGenLists(1);

	glNewList(auxList, GL_COMPILE);
		drawVertex(this);
	glEndList();

    displayListId = auxList;
}

std::vector<Vertex> Model::loadObject(const char* fileName)
{
	//Vertex portions
	std::vector<glm::fvec3> positions;
	std::vector<glm::fvec2> textureCoords;
	std::vector<glm::fvec3> normals;

	//Face vectors
	std::vector<GLfloat> positionIndices;
	std::vector<GLfloat> textureCoordIndices;
	std::vector<GLfloat> normalIndices;

	//Vertex array
	std::vector<Vertex> vertices;

	std::stringstream ss;
	std::ifstream file(fileName);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;

	//File open error check
	if (!file.is_open())
		std::cout<< "Erro na loadObject: arquivo nao pode ser aberto." << std::endl;
	

	//Read one line at a time
	while (std::getline(file, line))
	{
		//Get the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#"){}

		else if (prefix == "o"){}
		else if (prefix == "s"){}
		else if (prefix == "use_mtl"){}

		else if (prefix == "v") //Vertex position
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			positions.push_back(temp_vec3);
		}

		else if (prefix == "vt")
		{
			ss >> temp_vec2.x >> temp_vec2.y;
			textureCoords.push_back(temp_vec2);
		}

		else if (prefix == "vn")
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			normals.push_back(temp_vec3);
		}

		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> temp_glint)
			{
				//Pushing indices into correct arrays
				if (counter == 0)
					positionIndices.push_back(temp_glint);
				else if (counter == 1)
					textureCoordIndices.push_back(temp_glint);
				else if (counter == 2)
					normalIndices.push_back(temp_glint);

				//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}

				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
					counter = 0;
			}	
		}
		else{}
	}

	//Build final vertex array (Model)
	vertices.resize(positionIndices.size(), Vertex());

	//Load in all indices
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i].position = positions[positionIndices[i]-1];
		vertices[i].texCoord = textureCoords[textureCoordIndices[i]-1];
		vertices[i].normal = normals[normalIndices[i]-1];
		vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
	}

	//DEBUG
	//std::cout << "Nr of vertices: " << vertices.size() << "\n";

	return vertices;
}