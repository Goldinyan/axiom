#pragma once

#include "Vector3.hpp"
#include "raylib.h"
#include <cmath>
#include <vector>

namespace Axiom
{

class MeshBuilder
{
public:
        static Mesh CreateMeshFromPoints(const std::vector<Vector3> &points, int resolution)
        {
                Mesh mesh = {};
                int vCount = points.size();
                int numQuads = resolution * resolution;

                mesh.vertexCount = vCount;
                mesh.triangleCount = numQuads * 4; // 4 Dreiecke pro Quad (2 vorne + 2 hinten)

                // 1. Vertices kopieren
                mesh.vertices = (float *)MemAlloc(vCount * 3 * sizeof(float));
                for (int i = 0; i < vCount; i++)
                {
                        mesh.vertices[i * 3] = points[i].x;
                        mesh.vertices[i * 3 + 1] = points[i].y;
                        mesh.vertices[i * 3 + 2] = points[i].z;
                }

                // 2. Indices erstellen (Die "Verbindungs-Logik")
                // Wir erstellen DOPPELTE Dreiecke mit unterschiedlicher Winding Order
                // Das sorgt dafür, dass man das Mesh von beiden Seiten sieht
                int trianglesPerQuad = 4; // 2 Front + 2 Back
                int maxTriangles = numQuads * trianglesPerQuad;

                mesh.indices = (unsigned short *)MemAlloc(maxTriangles * 3 * sizeof(unsigned short));

                int k = 0;
                for (int y = 0; y < resolution; y++)
                {
                        for (int x = 0; x < resolution; x++)
                        {
                                int topLeft = y * (resolution + 1) + x;
                                int topRight = topLeft + 1;
                                int bottomLeft = (y + 1) * (resolution + 1) + x;
                                int bottomRight = bottomLeft + 1;

                                // Skip quad if any vertex is NaN
                                if (std::isnan(points[topLeft].z) || std::isnan(points[topRight].z) ||
                                    std::isnan(points[bottomLeft].z) || std::isnan(points[bottomRight].z))
                                        continue;

                                // Dreieck 1 (Vorderseite)
                                mesh.indices[k++] = topLeft;
                                mesh.indices[k++] = bottomLeft;
                                mesh.indices[k++] = topRight;

                                // Dreieck 2 (Vorderseite)
                                mesh.indices[k++] = topRight;
                                mesh.indices[k++] = bottomLeft;
                                mesh.indices[k++] = bottomRight;

                                // Dreieck 1 (Rückseite - umgekehrte Winding Order)
                                mesh.indices[k++] = topRight;
                                mesh.indices[k++] = bottomLeft;
                                mesh.indices[k++] = topLeft;

                                // Dreieck 2 (Rückseite - umgekehrte Winding Order)
                                mesh.indices[k++] = bottomRight;
                                mesh.indices[k++] = bottomLeft;
                                mesh.indices[k++] = topRight;
                        }
                }

                mesh.triangleCount = k / 3;

                UploadMesh(&mesh, false);
                return mesh;
        }
};

} // namespace Axiom
