#OpenGL and C++ activity.
The assignment is developed in Windows and demonstrates the concepts of modern OpenGL programming.


#Deliverable description
The deliverable includes the following :

## 1. executable 
This directory contains the executable, required resources and DLLs to run.

Note : This requires Microsoft Visual C++ Redistributable for Visual Studio 2015.
	   If its not installed in the system, the redistributable is also attached as vc_redist.x64.zip
	   
Executable supports the following Mouse and keyboard controls to navigate through the scene:

- Mouse controls to move the camera.
- Mouse scroll to zoom in/zoom out.
- Keyboard keys : Left, Right, Top, Bottom to move camera right, left, forward and backward respectively.
- Escape key : to close the window.

## 2. video

The video is attached for demonstrating the functionality.
	   
## 3. OpenGLAssignment 

This contains the required dependencies, assignment code and Microsoft visual studio solution and project.

### Libraries used :
1. GLEW for loading OpenGL Extensions. (version 2.1.0)
2. GLFW for creating and managing window as well as opengl context. (version 3.2.2)
3. glm for mathematics (version 0.9.9.8)
4. assimp for importing/loading wavefront object model. (version 3.3.1)

### PhilipsAssignmentOpenGL :

This contains Microsoft visual studio solution and project along-with the source code.

Source code:

1. PhilipsAssignmentOpenGL : starting point of application which contains main function. 
   GLFW is used here to create and manage window along with opengl context.
   Callback handlers are implemented here to control mouse and keyboard inputs.
   
2. Scene : Scene has 3D objects/Models like floor, cube and robot.
   Maintains floor and cube model and respective VAO and shader handles.
   
3. Camera : This class is  handling the point of view set up for the scene, maintains view and projections matrices.
   Also handles mouse and keyboard inputs received from application.
   
4. Model : It contains vertex buffer objects(VBO) for Model type of objects like floor and Cube.

5. ComplexModel : It contains vector of meshes and textures to be used for complex models like robot. 
   This class is also responsible for loading wavefront object model using the assimp library.
   
6. Mesh : Mesh contains the vertex, indices, textures and other details from the object loader. 
   It is also responsible for maintaining VAO, VBOs and rendering of mesh.
   
7. Shader : Shader class is responsible for loading the vertex and fragment shaders.

8. Texture : This class is responsible for loading textures.

9. Vertices.h : This contains the vertex , index and texture data for floor and model.

	
 


