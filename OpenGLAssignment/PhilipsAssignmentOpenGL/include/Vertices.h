#include <GL/glew.h>

const GLfloat floor_vertex_buffer_data[] = {
	-1.0f, -1.0f, -1.0f, //left bottom front
	1.0f, -1.0f, -1.0f,  //right bottom front
	1.0f, -1.0f, 1.0f,   // right back
	-1.0f, -1.0f, 1.0f //left back
};

const GLfloat floor_tex_buffer_data[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
};

const GLuint floor_index_buffer_data[] = {
	0,1,3,2
};


const GLfloat cube_vertex_buffer_data[] = {
	//front
	 -0.2f, -0.5f, 0.0f, // top left // 0
	 -0.2f, -0.9f, 0.0f, // bottom left //1
	 0.2f,  -0.9f, 0.0f, // bottom right //2
	 0.2f,  -0.5f, 0.0f , // top right //3
	 // back
	 -0.2f, -0.5f, 0.4f , //4
	 -0.2f, -0.9f, 0.4f, // 5
	 0.2f,  -0.9f, 0.4f , //6
	 0.2f,  -0.5f, 0.4f //7

};

const GLuint cube_index_buffer_data[] = {
	//front
 0, 1, 2, 0, 2, 3,
 // right
 3, 2, 6, 3, 6, 7,
 // back
 4, 5, 6, 4, 6, 7,
 // left
 4, 5, 1, 4 , 1, 0,
 //top
 4, 0, 3, 4, 3, 7,
 //bottom
 5, 1, 2, 5, 2, 6
};


//this has both vertices and texture coords
const GLfloat cube_vertex_texture_buffer_data[] = {
    // positions          // texture Coords
		
		//front
		0.2f, -0.9f,  0.0f,  0.25f, 0.33f,  // left bottom
		0.4f, -0.9f,  0.0f,  0.5f, 0.33f,   //right bottom
		0.4f, -0.5f,  0.0f,  0.5f, 0.66f,    // top right
		0.4f, -0.5f,  0.0f,  0.5f, 0.66f,
		0.2f, -0.5f,  0.0f,  0.25f, 0.66f,    //top left 
		0.2f, -0.9f,  0.0f,  0.25f, 0.33f,

		//back
		0.2f, -0.9f,  0.4f,  0.75f, 0.33f,
		0.4f, -0.9f,  0.4f,  1.0f,  0.33f,
		0.4f, -0.5f,  0.4f,  1.0f,  0.66f,
		0.4f, -0.5f,  0.4f,  1.0f,  0.66f,
		0.2f, -0.5f,  0.4f,  0.75f,  0.66f,
		0.2f, -0.9f,  0.4f,  0.75f,  0.33f,

		//left
		0.2f, -0.5f,  0.4f,  0.0f, 0.66f,
		0.2f, -0.5f,  0.0f,  0.25f, 0.66f,
		0.2f, -0.9f,  0.0f,  0.25f, 0.33f,
		0.2f, -0.9f,  0.0f,  0.25f, 0.33f,
		0.2f, -0.9f,  0.4f,  0.0f, 0.33f,
		0.2f, -0.5f,  0.4f,  0.0f, 0.66f,

		//right
		0.4f, -0.5f,  0.4f,  0.75f, 0.66f,
		0.4f, -0.5f,  0.0f,  0.5f, 0.66f,
		0.4f, -0.9f,  0.0f,  0.5f, 0.33f,
		0.4f, -0.9f,  0.0f,  0.5f, 0.33f,
		0.4f, -0.9f,  0.4f,  0.75f, 0.33f,
		0.4f, -0.5f,  0.4f,  0.75f, 0.66f,

		//bottom
		
		0.2f, -0.9f,  0.0f,  0.25f, 0.33f,
		0.4f, -0.9f,  0.0f,  0.5f, 0.33f,
		0.4f, -0.9f,  0.4f,  0.5f, 0.0f,
		0.4f, -0.9f,  0.4f,  0.5f, 0.0f,
		0.2f, -0.9f,  0.4f,  0.25f, 0.0f,
		0.2f, -0.9f,  0.0f,  0.25f, 0.33f,


		//top
		0.2f, -0.5f,  0.0f,  0.25f, 0.33f,
		0.4f, -0.5f,  0.0f,  0.5f, 0.33f,
		0.4f, -0.5f,  0.4f,  0.5f, 0.0f,
		0.4f, -0.5f,  0.4f,  0.5f, 0.0f,
		0.2f, -0.5f,  0.4f,  0.25f, 0.0f,
		0.2f, -0.5f,  0.0f,  0.25f, 0.33f
};