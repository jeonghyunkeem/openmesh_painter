// iostream
#include <iostream>
// OpenMesh
#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/IO/writer/OBJWriter.hh>
// Eigen
#include <Eigen/Core>

using namespace OpenMesh;
using namespace Eigen;
using namespace std;

/* -------------------------------------------------------------------------------------
 * Mesh painter
 * 
 *  Args:
 *      _mesh, _mesh_name: mesh file(.obj) and its name(path)
 *      _vectors: function matrix to be visualized
 *      _c: column to be draw
 * ------------------------------------------------------------------------------------- */
void paint_mesh(Mesh& _mesh, const string _mesh_name, MatrixXd& _vectors, const int _c){
    // set color attribute
    _mesh.request_face_colors();
    IO::Options opt;
    opt += IO::Options::FaceColor;

    // normalize function value to color range
    const double col_range = 255.0;
    const VectorXd vc = _vectors.col(_c);
    const double min_coeff = vc.minCoeff();
    const VectorXd vc_shift = vc.array() + abs(min_coeff);
    
    const double max_coeff = vc_shift.maxCoeff();
    const double cs = col_range/max_coeff;
    const VectorXd palette = vc_shift * cs;
    
    // set face color
    for (Mesh::ConstFaceIter f_it = _mesh.faces_begin(); f_it != _mesh.faces_end(); ++f_it)
    {
        Mesh::Color color = {255, 255, 255};  // inital color
        for (Mesh::ConstFaceVertexIter fv_it = _mesh.cfv_iter(*f_it); fv_it.is_valid(); ++fv_it)
        {
            const Mesh::VertexHandle v_i = (*fv_it);
            const int idx = v_i.idx();

            color.data()[0] -= palette.coeff(idx)/3.0;
            color.data()[1] -= palette.coeff(idx)/3.0;
        }
        _mesh.set_color(*f_it, color);
    }

    // wrtie results
    string out_file = _mesh_name + "/eig_" + to_string(_c) + ".obj";
    cout << "Writing to file '" << out_file << "'... ";
    if (!IO::write_mesh(_mesh, out_file, opt)) {
        cout << "\tFailed!" << endl;
    }
    cout << "\tDone." << endl;
    _mesh.release_face_colors();
}
