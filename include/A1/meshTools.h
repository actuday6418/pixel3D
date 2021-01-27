#ifndef MESHTOOLS_H
#define MESHTOOLS_H

#include<cmath>
struct vector3 {
        float x, y, z;

        vector3(float x=0, float y=0, float z=0): x(x), y(y), z(z){}

        vector3 operator - (const vector3 &v){
                vector3 ret(x-v.x, y-v.y, z-v.z);
                return ret;
        }

        vector3 operator + (const vector3 &v){
                vector3 ret(x+v.x, y+v.y, z+v.z);
                return ret;
        }
};

struct triangle {
        vector3 vertices[3];

        triangle(vector3 a=vector3(), vector3 b=vector3(), vector3 c=vector3()): vertices{a,b,c}{}

};

struct mesh {
        vector3 origin;
        std::vector < triangle > tris;

        void calcOrigin(){
                origin.x = 0;
                origin.y = 0;
                origin.z = 0;
                int nop = 0;//No of points in mesh
                for(auto const &tri : tris){
                        for(auto const &vert : tri.vertices){
                                nop++;
                                origin.x += vert.x;
                                origin.y += vert.y;
                                origin.z += vert.z;
                        }
                }
                origin.x /= (float)nop;
                origin.y /= (float)nop;
                origin.z /= (float)nop;
        }

        //Zero axis is X, 1 Y, and 2 is Z.
        void rotateMesh(int axis, float dTheta){

                /*
                 * ============ Equations derived from rotation transform ======
                 *
                 * ============ Y axis rotation ===========
                 *  posX = posX*cosdY + posZ*sindY
                 *  posY = posY
                 *  posZ = posz*cosdY - posX*sindY
                 *  =======================================
                 *
                 * ============ X axis rotation ===========
                 *  posX = posX
                 *  posY = posY*cosdX - posZ*sindX
                 *  posZ = posY*sindX + posZ*cosdX
                 *  =======================================
                 *
                 * ============ Z axis rotation ===========
                 *  posX = posX*cosdZ - posY*sindZ
                 *  posY = posX*sindZ + posY*cosdZ
                 *  posZ = posZ
                 *  =======================================
                 * ============================================================
                 */

                float cosTheta = std::cos(dTheta);
                float sinTheta = std::sin(dTheta);
                calcOrigin();

                switch(axis){
                        case 0: //case: X axis
                                for(auto &tri : tris){
                                        for(auto &vert : tri.vertices){
                                                vert = vert - origin;
                                                vector3 v = vert;
                                                //vert.x unchanged
                                                v.y = vert.y*cosTheta - vert.z*sinTheta;
                                                v.z = vert.y*sinTheta + vert.z*cosTheta;
                                                vert = v + origin;
                                        }
                                }
                                break;
                        case 1: //case: Y axis
                                for(auto &tri : tris){
                                        for(auto &vert : tri.vertices){
                                                vert = vert - origin;
                                                vector3 v = vert;
                                                v.x = vert.z*sinTheta + vert.x*cosTheta;
                                                //v.y unchanged
                                                v.z = vert.z*cosTheta - vert.x*sinTheta;
                                                vert = v;
                                                vert = v + origin;
                                        }
                                }
                                break;
                        case 2: //case: Z axis
                                for(auto &tri : tris){
                                        for(auto &vert : tri.vertices){
                                                vert = vert - origin;
                                                vector3 v = vert;
                                                v.x = vert.x*cosTheta - vert.y*sinTheta;
                                                v.y = vert.x*sinTheta + vert.y*cosTheta;
                                                //vert.z unchanged
                                                vert = v + origin;
                                        }
                                }
                                break;
                }
        }
        //Zero axis is X, 1 Y, 2 Z, 3 is all
        void scale(int axis, float scale){
                calcOrigin();
                scale += 1;
                switch (axis){
                        case 0:
                                for(auto &tri : tris){
                                        for(auto &vert : tri.vertices){
                                                vert.x -= origin.x;
                                                vert.x *= scale;
                                                vert.x += origin.x;
                                        }
                                }
                                break;
                        case 1:
                                for(auto &tri : tris){
                                        for(auto &vert : tri.vertices){
                                                vert.y -= origin.y;
                                                vert.y *= scale;
                                                vert.y += origin.y;
                                        }
                                }
                                break;
                        case 2:
                                for(auto &tri : tris){
                                        for(auto &vert : tri.vertices){
                                                vert.z -= origin.z;
                                                vert.z *= scale;
                                                vert.z += origin.z;
                                        }
                                }
                                break;
                        case 3:
                                for(auto &tri : tris){
                                        for(auto &vert : tri.vertices){
                                                vert = vert - origin;
                                                vert.x *= scale;
                                                vert.y *= scale;
                                                vert.z *= scale;
                                                vert = vert + origin;
                                        }
                                }
                                break;
                }
        }
};
#endif
