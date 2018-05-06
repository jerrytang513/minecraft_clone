#include "cube.h"

using namespace std;

	void valueAssign(Vec3D* vertices,GLdouble* data){
		
		data[0] =  vertices[0].x;
		data[1] =  vertices[0].y;
		data[2] =  vertices[0].z;
		data[3] =  vertices[1].x;
		data[4] =  vertices[1].y;
		data[5] =  vertices[1].z;
		data[6] =  vertices[2].x;
		data[7] =  vertices[2].y;
		data[8] =  vertices[2].z;
		data[9] =  vertices[3].x;
		data[10] =  vertices[3].y;
		data[11] =  vertices[3].z;
		data[12] =  vertices[4].x;
		data[13] =  vertices[4].y;
		data[14] =  vertices[4].z;
		data[15] =  vertices[5].x;
		data[16] =  vertices[5].y;
		data[17] =  vertices[5].z;

		data[18] =  vertices[6].x;
		data[19] =  vertices[6].y;
		data[20] =  vertices[6].z;
		data[21] =  vertices[7].x;
		data[22] =  vertices[7].y;
		data[23] =  vertices[7].z;
		data[24] =  vertices[8].x;
		data[25] =  vertices[8].y;
		data[26] =  vertices[8].z;
		data[27] =  vertices[9].x;
		data[28] =  vertices[9].y;
		data[29] =  vertices[9].z;
		data[30] =  vertices[10].x;
		data[31] =  vertices[10].y;
		data[32] =  vertices[10].z;
		data[33] =  vertices[11].x;
		data[34] =  vertices[11].y;
		data[35] =  vertices[11].z;
		
		data[36] =  vertices[12].x;
		data[37] =  vertices[12].y;
		data[38] =  vertices[12].z;
		data[39] =  vertices[13].x;
		data[40] =  vertices[13].y;
		data[41] =  vertices[13].z;
		data[42] =  vertices[14].x;
		data[43] =  vertices[14].y;
		data[44] =  vertices[14].z;
		data[45] =  vertices[15].x;
		data[46] =  vertices[15].y;
		data[47] =  vertices[15].z;
		data[48] =  vertices[16].x;
		data[49] =  vertices[16].y;
		data[50] =  vertices[16].z;
		data[51] =  vertices[17].x;
		data[52] =  vertices[17].y;
		data[53] =  vertices[17].z;

		data[54] =  vertices[18].x;
		data[55] =  vertices[18].y;
		data[56] =  vertices[18].z;
		data[57] =  vertices[19].x;
		data[58] =  vertices[19].y;
		data[59] =  vertices[19].z;
		data[60] =  vertices[20].x;
		data[61] =  vertices[20].y;
		data[62] =  vertices[20].z;
		data[63] =  vertices[21].x;
		data[64] =  vertices[21].y;
		data[65] =  vertices[21].z;
		data[66] =  vertices[22].x;
		data[67] =  vertices[22].y;
		data[68] =  vertices[22].z;
		data[69] =  vertices[23].x;
		data[70] =  vertices[23].y;
		data[71] =  vertices[23].z;
	}

	Cube::Cube(GLdouble centerPosX, GLdouble centerPosY, GLdouble centerPosZ, GLdouble edgeLength):Shape3D(Vec3D(centerPosX,centerPosY,centerPosZ)){
		halfSideLength = edgeLength * 0.5;
		frontTopLeft = Vec3D(centerPosX - halfSideLength,centerPosY + halfSideLength, centerPosZ + halfSideLength);
		frontTopRight = Vec3D(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength);
		frontBottomRight = Vec3D(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength);
		frontBottomLeft = Vec3D(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength);


		backTopLeft = Vec3D(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength); // top left
		backTopRight = Vec3D(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength); // top right
		backBottomRight = Vec3D(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength);// bottom right
		backBottomLeft = Vec3D(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength); // bottom left

		// left face
		leftTopLeft = Vec3D(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength); // top left
		leftTopRight = Vec3D(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength); // top right
		leftBottomRight = Vec3D(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength); // bottom right
		leftBottomLeft = Vec3D(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength); // bottom left

		// right face
		rightTopLeft = Vec3D(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength); // top left
		rightTopRight = Vec3D(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength); // top right
		rightBottomRight = Vec3D(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength); // bottom right
		rightBottomLeft = Vec3D(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength); // bottom left

		// top face
		topTopLeft = Vec3D(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength); // top left
		topTopRight = Vec3D(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength); // top right
		topBottomRight = Vec3D(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength); // bottom right
		topBottomLeft = Vec3D(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength); // bottom left

		// top face
		bottomTopLeft = Vec3D(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength); // top left
		bottomTopRight = Vec3D(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength); // top right
		bottomBottomRight = Vec3D(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength); // bottom right
		bottomBottomLeft = Vec3D(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength); // bottom left
		
		vertices[0] = Vec3D(frontTopLeft.x,frontTopLeft.y,frontTopLeft.z);
		vertices[1] = Vec3D(frontTopRight.x,frontTopRight.y,frontTopRight.z);
		vertices[2] = Vec3D(frontBottomRight.x,frontBottomRight.y,frontBottomRight.z);
		vertices[3] = Vec3D(frontBottomLeft.x,frontBottomLeft.y,frontBottomLeft.z);

		vertices[4] = Vec3D(backTopLeft.x,backTopLeft.y,backTopLeft.z);
		vertices[5] = Vec3D(backTopRight.x,backTopRight.y,backTopRight.z);
		vertices[6] = Vec3D(backBottomRight.x,backBottomRight.y,backBottomRight.z);
		vertices[7] = Vec3D(backBottomLeft.z,backBottomLeft.y,backBottomLeft.z);

		vertices[8] = Vec3D(leftTopLeft.x,leftTopLeft.y,leftTopLeft.z);
		vertices[9] = Vec3D(leftTopRight.x,leftTopRight.y,leftTopRight.z);
		vertices[10] = Vec3D(leftBottomRight.x,leftBottomRight.y,leftBottomRight.z);
		vertices[11] = Vec3D(leftBottomLeft.x,leftBottomLeft.y,leftBottomLeft.z);

		vertices[12] = Vec3D(rightTopLeft.x,rightTopLeft.y,rightTopLeft.z);
		vertices[13] = Vec3D(rightTopRight.x,rightTopRight.y,rightTopRight.z);
		vertices[14] = Vec3D(rightBottomRight.x,rightBottomRight.y,rightBottomRight.z);
		vertices[15] = Vec3D(rightBottomLeft.x,rightBottomLeft.y,rightBottomLeft.z);

		vertices[16] = Vec3D(topTopLeft.x,topTopLeft.y,topTopLeft.z);
		vertices[17] = Vec3D(topTopRight.x,topTopRight.y,topTopRight.z);
		vertices[18] = Vec3D(topBottomRight.x,topBottomRight.y,topBottomRight.z);
		vertices[19] = Vec3D(topBottomLeft.x,topBottomLeft.y,topBottomLeft.z);

		vertices[20] = Vec3D(bottomTopLeft.x,bottomTopLeft.y,bottomTopLeft.z);
		vertices[21] = Vec3D(bottomTopRight.x,bottomTopRight.y,bottomTopRight.z);
		vertices[22] = Vec3D(bottomBottomRight.x,bottomBottomRight.y,bottomBottomRight.z);
		vertices[23] = Vec3D(bottomBottomLeft.x,bottomBottomLeft.y,bottomBottomLeft.z);

		valueAssign(vertices,data);
	}

        void Cube::draw(){
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer( 3, GL_DOUBLE, 0, data);

		glDrawArrays( GL_QUADS, 0, 24);
		glDisableClientState( GL_VERTEX_ARRAY);
	}

        void Cube::rotate(GLdouble angle, Vec3D axis){

		for(int i = 0; i < 24; i++){
			Quaternion q(0,vertices[i].x,vertices[i].y,vertices[i].z);
			Vec3D rotationVec = q.rotation(angle,axis);
			vertices[i].x = rotationVec.x;
			vertices[i].y = rotationVec.y;
			vertices[i].z = rotationVec.z;
			
		}
		std::cout << vertices[0].x << std::endl;

		valueAssign(vertices,data);

	}


