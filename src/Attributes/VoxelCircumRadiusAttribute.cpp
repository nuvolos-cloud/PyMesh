/* This file is part of PyMesh. Copyright (c) 2017 by Qingnan Zhou */
#include "VoxelCircumRadiusAttribute.h"

#include <Mesh.h>
#include <Core/Exception.h>

using namespace PyMesh;

void VoxelCircumRadiusAttribute::compute_from_mesh(Mesh& mesh) {
    const size_t dim = mesh.get_dim();
    const size_t num_voxels = mesh.get_num_voxels();
    const size_t vertex_per_voxel = mesh.get_vertex_per_voxel();

    if (vertex_per_voxel != 4) {
        throw NotImplementedError(
                "Voxel incenter is defined for 3D tet mesh only.");
    }
    if (dim != 3) {
        throw RuntimeError("Voxel incenter is defined for 3D tet mesh only.");
    }

    if (!mesh.has_attribute("voxel_circum_center")) {
        mesh.add_attribute("voxel_circum_center");
    }
    const auto& circumcenter = mesh.get_attribute("voxel_circum_center");

    VectorF& circumradius = m_values;
    circumradius.resize(num_voxels);
    const auto& voxels = mesh.get_voxels();
    const auto& vertices = mesh.get_vertices();

    for (size_t i=0; i<num_voxels; i++) {
        Vector4I voxel = voxels.segment<4>(i*4);
        Vector3F v0 = vertices.segment<3>(voxel[0]*3);
        Vector3F center = circumcenter.segment<3>(i*3);
        circumradius[i] = (v0 - center).norm();
    }
}

