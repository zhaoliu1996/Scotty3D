#include <float.h>
#include <assert.h>
#include "meshEdit.h"
#include "mutablePriorityQueue.h"
#include "error_dialog.h"


namespace CMU462 {
    
VertexIter HalfedgeMesh::splitEdge(EdgeIter e0) {
    // for boundary line, only one triangle
    
    if (e0->isBoundary()){
        if (e0->halfedge()->face()->degree()==3){
            cout<<"hehehe"<<endl;
            VertexIter m = newVertex();
            vector<EdgeIter> ve;
            FaceIter nf = newFace();
            vector<HalfedgeIter> vh;
            ve.push_back(newEdge());
            ve.push_back(newEdge());
            vh.push_back(newHalfedge());
            vh.push_back(newHalfedge());
            vh.push_back(newHalfedge());
            vh.push_back(newHalfedge());
            
            
            // position for the new vertex
            m->position = e0->centroid();
            HalfedgeIter h0 = e0->halfedge()->twin();
            HalfedgeIter h1 = e0->halfedge()->next();
            HalfedgeIter h2 = h1->next();
            HalfedgeIter h3 = h0->next();
            
            FaceIter of = e0->halfedge()->face();
            
            of->halfedge() = h2;
            nf->halfedge() = h1;
            FaceIter face_boundary = h0->face();
            
            e0->halfedge()->next() = vh[2];
            e0->halfedge()->twin() = vh[1];
            e0->halfedge()->edge() = ve[0];
            //e0->halfedge()->setNeighbors(vh[2], vh[1], <#VertexIter vertex#>, ve[0], <#FaceIter face#>);
            
            h1->next() = vh[3];
            h1->face() = nf;
            //h1->setNeighbors(vh[3], <#HalfedgeIter twin#>, <#VertexIter vertex#>, <#EdgeIter edge#>, nf);
            
            h0->next() = vh[1];
            h0->twin() = vh[0];
            //h0->setNeighbors(vh[1], vh[0], <#VertexIter vertex#>, <#EdgeIter edge#>, <#FaceIter face#>);
            
            ve[0]->halfedge() = h0;
            ve[1]->halfedge() = vh[2];
            m->halfedge() = vh[0];
            
            vh[0]->setNeighbors(h1, h0, m, ve[0], nf);
            vh[1]->setNeighbors(h3, e0->halfedge(), m, e0, face_boundary);
            vh[2]->setNeighbors(h2, vh[3], m, ve[1], of);
            vh[3]->setNeighbors(vh[0], vh[2], h2->vertex(), ve[1], nf);
            
            return m;
        }
        
        return e0->halfedge()->vertex();
        
    }
    
    
    if (e0->halfedge()->face()->degree()!=3 || e0->halfedge()->twin()->face()->degree()!=3){
        return e0->halfedge()->vertex();
    }
    // allocate space for new things
    vector<EdgeIter> ve;
    vector<HalfedgeIter> vh;
    vector<FaceIter> vf;
    VertexIter m = newVertex();
    
    ve.push_back(newEdge());
    ve.push_back(newEdge());
    ve.push_back(newEdge());
    vf.push_back(newFace());
    vf.push_back(newFace());
    vh.push_back(newHalfedge());
    vh.push_back(newHalfedge());
    vh.push_back(newHalfedge());
    vh.push_back(newHalfedge());
    vh.push_back(newHalfedge());
    vh.push_back(newHalfedge());
    
    
    // position for the new vertex
    m->position = e0->centroid();
   
    // old halfedges
    HalfedgeIter h0 = e0->halfedge();
    HalfedgeIter h1 = h0->next();
    HalfedgeIter h2 = h1->next();
    HalfedgeIter h3 = h0->twin()->next();
    HalfedgeIter h4 = h3->next();
    
    //assign halfedges for the new vertex and old vertex
    m->halfedge() = h0;
    h0->vertex()->halfedge() = h3;
    
    // assign halfedges for new faces and old faces
    vf[0]->halfedge() = h3;
    vf[1]->halfedge() = h2;
    h0->face()->halfedge() = h0;
    h0->twin()->face()->halfedge() = h0->twin();
    h1->face() = h0->face();
    h2->face() = vf[1];
    h3->face() = vf[0];
    h4->face() = h0->twin()->face();
    
    // assign halfedges for new edges
    ve[0]->halfedge() = vh[0];
    ve[1]->halfedge() = vh[2];
    ve[2]->halfedge() = vh[4];

    //reassign halfedges
    h0->setNeighbors(h1, h0->twin(), m, e0, h0->face());
    h0->twin()->next() = vh[0];
    h1->next() = vh[5];
    h2->next() = vh[3];
    h4->next() = h0->twin();
    h3->next() = vh[1];
    vh[0]->setNeighbors(h4, vh[1], m, ve[0], h0->twin()->face());
    vh[1]->setNeighbors(vh[2], vh[0], h4->vertex(), ve[0], vf[0]);
    vh[2]->setNeighbors(h3, vh[3], m, ve[1], vf[0]);
    vh[3]->setNeighbors(vh[4], vh[2], h3->vertex(), ve[1], vf[1]);
    vh[4]->setNeighbors(h2, vh[5], m, ve[2], vf[1]);
    vh[5]->setNeighbors(h0, vh[4], h2->vertex(), ve[2], h0->face());
    
    return m;
    
    
  // TODO: (meshEdit)
  // This method should split the given edge and return an iterator to the
  // newly inserted vertex. The halfedge of this vertex should point along
  // the edge that was split, rather than the new edges.

  
}

VertexIter HalfedgeMesh::collapseEdge(EdgeIter e) {
  // TODO: (meshEdit)
  // This method should collapse the given edge and return an iterator to
  // the new vertex created by the collapse.

  showError("collapseEdge() not implemented.");
  return VertexIter();
}

VertexIter HalfedgeMesh::collapseFace(FaceIter f) {
  // TODO: (meshEdit)
  // This method should collapse the given face and return an iterator to
  // the new vertex created by the collapse.
  showError("collapseFace() not implemented.");
  return VertexIter();
}

FaceIter HalfedgeMesh::eraseVertex(VertexIter v) {
  // TODO: (meshEdit)
  // This method should replace the given vertex and all its neighboring
  // edges and faces with a single face, returning the new face.

  return FaceIter();
}

FaceIter HalfedgeMesh::eraseEdge(EdgeIter e) {
  // TODO: (meshEdit)
  // This method should erase the given edge and return an iterator to the
  // merged face.

  showError("eraseVertex() not implemented.");
  return FaceIter();
}

EdgeIter HalfedgeMesh::flipEdge(EdgeIter e0) {
    
    if (e0->isBoundary()){
        return e0;
    }
    
    HalfedgeIter h0 = e0->halfedge();
    HalfedgeIter h1 = h0->next();
    HalfedgeIter h2 = h1->next();
    HalfedgeIter h3 = h0->twin();
    HalfedgeIter h4 = h3->next();
    HalfedgeIter h5 = h4->next();
    HalfedgeIter h6 = h1->twin();
    //HalfedgeIter h7 = h2->twin();
    HalfedgeIter h8 = h4->twin();
    //HalfedgeIter h9 = h5->twin();
    HalfedgeIter h10 = h3;
    while (h10->next()!=h3){
        h10 = h10->next();
    }
    HalfedgeIter h11 = h0;
    while (h11->next()!=h0){
        h11 = h11->next();
    }
    
    VertexIter v0 = h0->vertex();
    VertexIter v1 = h3->vertex();
    VertexIter v2 = h6->vertex();
    VertexIter v3 = h8->vertex();
    

    
    FaceIter f0 = h0->face();
    FaceIter f1 = h3->face();
    
    
    v0->halfedge() = h4;
    v1->halfedge() = h1;
    v2->halfedge() = h2;
    v3->halfedge() = h5;
    f0->halfedge() = h2;
    f1->halfedge() = h5;
    
    h0->next() = h2;
    h0->twin() = h3;
    h0->vertex() = v3;
    h0->face() = f0;
    h1->next() = h3;
    //h1->twin() = h6;
    //h1->vertex() = v1;
    h1->face() = f1;
    if (h2->next()==h0){
        h2->next()=h4;
    }
    //h2->twin() = h7;
    //h2->vertex() = v2;
    //h2->face() = f0;
    h3->next() = h5;
    h3->twin() = h0;
    h3->vertex() = v2;
    h3->face() = f1;
    h4->next() = h0;
    //h4->twin() = h8;
    //h4->vertex() = v0;
    h4->face() = f0;
    h10->next() = h1;
    //h10->twin()
    //h10->vertex()
    //h10->face()
    h11->next() = h4;
    
  // TODO: (meshEdit)
  // This method should flip the given edge and return an iterator to the
  // flipped edge.

    
  return e0;
}

void HalfedgeMesh::subdivideQuad(bool useCatmullClark) {
  // Unlike the local mesh operations (like bevel or edge flip), we will perform
  // subdivision by splitting *all* faces into quads "simultaneously."  Rather
  // than operating directly on the halfedge data structure (which as you've
  // seen
  // is quite difficult to maintain!) we are going to do something a bit nicer:
  //
  //    1. Create a raw list of vertex positions and faces (rather than a full-
  //       blown halfedge mesh).
  //
  //    2. Build a new halfedge mesh from these lists, replacing the old one.
  //
  // Sometimes rebuilding a data structure from scratch is simpler (and even
  // more
  // efficient) than incrementally modifying the existing one.  These steps are
  // detailed below.

  // TODO Step I: Compute the vertex positions for the subdivided mesh.  Here
  // we're
  // going to do something a little bit strange: since we will have one vertex
  // in
  // the subdivided mesh for each vertex, edge, and face in the original mesh,
  // we
  // can nicely store the new vertex *positions* as attributes on vertices,
  // edges,
  // and faces of the original mesh.  These positions can then be conveniently
  // copied into the new, subdivided mesh.
  // [See subroutines for actual "TODO"s]
  if (useCatmullClark) {
    computeCatmullClarkPositions();
  } else {
    computeLinearSubdivisionPositions();
  }

  // TODO Step II: Assign a unique index (starting at 0) to each vertex, edge,
  // and
  // face in the original mesh.  These indices will be the indices of the
  // vertices
  // in the new (subdivided mesh).  They do not have to be assigned in any
  // particular
  // order, so long as no index is shared by more than one mesh element, and the
  // total number of indices is equal to V+E+F, i.e., the total number of
  // vertices
  // plus edges plus faces in the original mesh.  Basically we just need a
  // one-to-one
  // mapping between original mesh elements and subdivided mesh vertices.
  // [See subroutine for actual "TODO"s]
  assignSubdivisionIndices();

  // TODO Step III: Build a list of quads in the new (subdivided) mesh, as
  // tuples of
  // the element indices defined above.  In other words, each new quad should be
  // of
  // the form (i,j,k,l), where i,j,k and l are four of the indices stored on our
  // original mesh elements.  Note that it is essential to get the orientation
  // right
  // here: (i,j,k,l) is not the same as (l,k,j,i).  Indices of new faces should
  // circulate in the same direction as old faces (think about the right-hand
  // rule).
  // [See subroutines for actual "TODO"s]
  vector<vector<Index> > subDFaces;
  vector<Vector3D> subDVertices;
  buildSubdivisionFaceList(subDFaces);
  buildSubdivisionVertexList(subDVertices);

  // TODO Step IV: Pass the list of vertices and quads to a routine that clears
  // the
  // internal data for this halfedge mesh, and builds new halfedge data from
  // scratch,
  // using the two lists.
  rebuild(subDFaces, subDVertices);
}

/**
 * Compute new vertex positions for a mesh that splits each polygon
 * into quads (by inserting a vertex at the face midpoint and each
 * of the edge midpoints).  The new vertex positions will be stored
 * in the members Vertex::newPosition, Edge::newPosition, and
 * Face::newPosition.  The values of the positions are based on
 * simple linear interpolation, e.g., the edge midpoints and face
 * centroids.
 */
void HalfedgeMesh::computeLinearSubdivisionPositions() {
  // TODO For each vertex, assign Vertex::newPosition to
  // its original position, Vertex::position.

  // TODO For each edge, assign the midpoint of the two original
  // positions to Edge::newPosition.

  // TODO For each face, assign the centroid (i.e., arithmetic mean)
  // of the original vertex positions to Face::newPosition.  Note
  // that in general, NOT all faces will be triangles!
    
    for (VertexIter v = verticesBegin(); v != verticesEnd(); ++v){
        v->newPosition = v->position;
    }
    
    for (EdgeIter e = edgesBegin(); e != edgesEnd(); ++e){
        e->newPosition = e->centroid();
    }
    
    for (FaceIter f = facesBegin(); f != facesEnd(); ++f){
        f->newPosition = f->centroid();
    }
}

/**
 * Compute new vertex positions for a mesh that splits each polygon
 * into quads (by inserting a vertex at the face midpoint and each
 * of the edge midpoints).  The new vertex positions will be stored
 * in the members Vertex::newPosition, Edge::newPosition, and
 * Face::newPosition.  The values of the positions are based on
 * the Catmull-Clark rules for subdivision.
 */
void HalfedgeMesh::computeCatmullClarkPositions() {
  // TODO The implementation for this routine should be
  // a lot like HalfedgeMesh::computeLinearSubdivisionPositions(),
  // except that the calculation of the positions themsevles is
  // slightly more involved, using the Catmull-Clark subdivision
  // rules. (These rules are outlined in the Developer Manual.)

    
  // TODO face
    for (FaceIter f = facesBegin(); f != facesEnd(); ++f)
    {
        f->newPosition = f->centroid();
    }
    
  // TODO edges
    for (EdgeIter e = edgesBegin(); e != edgesEnd(); ++e)
    {
        e->newPosition = (e->centroid() * 2 + e->halfedge()->face()->newPosition + e->halfedge()->twin()->face()->newPosition)*0.25;
    }
    
  // TODO vertices
    for (VertexIter v = verticesBegin(); v != verticesEnd(); ++v)
    {
        int n = v->degree();
        Vector3D sum_faces_center;
        Vector3D sum_edges_center;
        HalfedgeIter h = v->halfedge();
        
        do {
            h = h->twin()->next();
            sum_faces_center += h->face()->newPosition;
            sum_edges_center += h->edge()->newPosition;
        } while (h != v->halfedge());
        
        sum_faces_center = sum_faces_center / n;
        sum_edges_center = sum_edges_center / n;
        
        v->newPosition = (sum_faces_center + 2 * sum_edges_center + v->position*(n - 3)) / n;
    }
}

/**
 * Assign a unique integer index to each vertex, edge, and face in
 * the mesh, starting at 0 and incrementing by 1 for each element.
 * These indices will be used as the vertex indices for a mesh
 * subdivided using Catmull-Clark (or linear) subdivision.
 */
void HalfedgeMesh::assignSubdivisionIndices() {
  // TODO Start a counter at zero; if you like, you can use the
  // "Index" type (defined in halfedgeMesh.h)

  // TODO Iterate over vertices, assigning values to Vertex::index

  // TODO Iterate over edges, assigning values to Edge::index

  // TODO Iterate over faces, assigning values to Face::index
    Index i = 0;
    for (VertexIter v = verticesBegin(); v != verticesEnd(); ++v){
        v->index = i;
        i++;
    }
    
    for (EdgeIter e = edgesBegin(); e != edgesEnd(); ++e){
        e->index = i;
        i++;
    }
    
    for (FaceIter f = facesBegin(); f != facesEnd(); ++f){
        f->index = i;
        i++;
    }
}

/**
 * Build a flat list containing all the vertex positions for a
 * Catmull-Clark (or linear) subdivison of this mesh.  The order of
 * vertex positions in this list must be identical to the order
 * of indices assigned to Vertex::newPosition, Edge::newPosition,
 * and Face::newPosition.
 */
void HalfedgeMesh::buildSubdivisionVertexList(vector<Vector3D>& subDVertices) {
  // TODO Resize the vertex list so that it can hold all the vertices.

  // TODO Iterate over vertices, assigning Vertex::newPosition to the
  // appropriate location in the new vertex list.

  // TODO Iterate over edges, assigning Edge::newPosition to the appropriate
  // location in the new vertex list.

  // TODO Iterate over faces, assigning Face::newPosition to the appropriate
  // location in the new vertex list.
    for (VertexIter v = verticesBegin(); v != verticesEnd(); ++v){
        subDVertices.push_back(v->newPosition);
    }
    
    for (EdgeIter e = edgesBegin(); e != edgesEnd(); ++e){
        subDVertices.push_back(e->newPosition);
    }
    
    for (FaceIter f = facesBegin(); f != facesEnd(); ++f){
        subDVertices.push_back(f->newPosition);
    }
}

/**
 * Build a flat list containing all the quads in a Catmull-Clark
 * (or linear) subdivision of this mesh.  Each quad is specified
 * by a vector of four indices (i,j,k,l), which come from the
 * members Vertex::index, Edge::index, and Face::index.  Note that
 * the ordering of these indices is important because it determines
 * the orientation of the new quads; it is also important to avoid
 * "bowties."  For instance, (l,k,j,i) has the opposite orientation
 * of (i,j,k,l), and if (i,j,k,l) is a proper quad, then (i,k,j,l)
 * will look like a bowtie.
 */
void HalfedgeMesh::buildSubdivisionFaceList(vector<vector<Index> >& subDFaces) {
  // TODO This routine is perhaps the most tricky step in the construction of
  // a subdivision mesh (second, perhaps, to computing the actual Catmull-Clark
  // vertex positions).  Basically what you want to do is iterate over faces,
  // then for each for each face, append N quads to the list (where N is the
  // degree of the face).  For this routine, it may be more convenient to simply
  // append quads to the end of the list (rather than allocating it ahead of
  // time), though YMMV.  You can of course iterate around a face by starting
  // with its first halfedge and following the "next" pointer until you get
  // back to the beginning.  The tricky part is making sure you grab the right
  // indices in the right order---remember that there are indices on vertices,
  // edges, AND faces of the original mesh.  All of these should get used.  Also
  // remember that you must have FOUR indices per face, since you are making a
  // QUAD mesh!

  // TODO iterate over faces
  // TODO loop around face
  // TODO build lists of four indices for each sub-quad
  // TODO append each list of four indices to face list
    vector<Index> quad(4);
    int n; //number of sides
    HalfedgeIter h, h_prev;
    
    for (FaceIter f = facesBegin(); f != facesEnd(); ++f)
    {
        
        n = f->degree();
        h = f->halfedge();
        h_prev = h;
        
        while (h_prev->next() != h){
            h_prev = h_prev->next();
        }
        
        for (int i = 0; i<n; i++)
        {
            quad[0] = h->vertex()->index;
            quad[1] = h->edge()->index;
            quad[2] = h->face()->index;
            quad[3] = h_prev->edge()->index;
            
            subDFaces.push_back(quad);
            h_prev = h;
            h = h->next();
        }
    }
}

FaceIter HalfedgeMesh::bevelVertex(VertexIter v) {
  // TODO This method should replace the vertex v with a face, corresponding to
  // a bevel operation. It should return the new face.  NOTE: This method is
  // responsible for updating the *connectivity* of the mesh only---it does not
  // need to update the vertex positions.  These positions will be updated in
  // HalfedgeMesh::bevelVertexComputeNewPositions (which you also have to
  // implement!)

  showError("bevelVertex() not implemented.");
  return facesBegin();
}

FaceIter HalfedgeMesh::bevelEdge(EdgeIter e) {
  // TODO This method should replace the edge e with a face, corresponding to a
  // bevel operation. It should return the new face.  NOTE: This method is
  // responsible for updating the *connectivity* of the mesh only---it does not
  // need to update the vertex positions.  These positions will be updated in
  // HalfedgeMesh::bevelEdgeComputeNewPositions (which you also have to
  // implement!)

  showError("bevelEdge() not implemented.");
  return facesBegin();
}

FaceIter HalfedgeMesh::bevelFace(FaceIter f) {
    
    //check if f is boundary then dont do anything
    if (f->isBoundary()) return f;
    
    // the degree of the face to bevel
    int n = f->degree();
    
    // h is the face's haleedge
    HalfedgeIter h = f->halfedge();
    HalfedgeIter t = h;
    
    //adding new elements to corresponding vectors
    vector<VertexIter> vv;
    vector<EdgeIter> ve;
    vector<FaceIter> vf;
    vector<HalfedgeIter> vh;
    
    for (int i = 0; i<n; i++){
        vv.push_back(newVertex());
        ve.push_back(newEdge());
        ve.push_back(newEdge());
        vf.push_back(newFace());
        vh.push_back(newHalfedge());
        vh.push_back(newHalfedge());
        vh.push_back(newHalfedge());
        vh.push_back(newHalfedge());
     
    }
    
    // assign pointers to those value
    for (int i = 0; i<n; i++){
        h = t;
        
        //for h: new face and new next
        h->face() = vf[i];
        vv[i]->halfedge() = vh[4*i+1];
        vv[i]->position = h->next()->vertex()->position;
        ve[2*i]->halfedge() = vh[4*i];
       
        ve[2*i+1]->halfedge() = vh[4*i+1];
        vf[i]->halfedge() = vh[4*i+1];
        cout<<"still working3"<<endl;
        vh[4*i]->setNeighbors(vh[4*i+1], vh[(4*i+7)%(4*n)], h->next()->vertex(), ve[2*i], vf[i]);
        cout<<4*i+1<<" "<<(4*i+7)%(4*n)<<endl;
        vh[4*i+1]->setNeighbors(vh[4*i+3], vh[4*i+2], vv[i], ve[2*i+1], vf[i]);
        
        vh[4*i+2]->setNeighbors(vh[(4*i+6)%(4*n)], vh[4*i+1], vv[(n+i-1)%n], ve[2*i+1], f);
        
        vh[4*i+3]->setNeighbors(h, vh[(4*n+4*i-4)%(4*n)], vv[(n+i-1)%n], ve[(2*n+2*i-2)%(2*n)], vf[i]);
        cout<<(i-1)%n<<" "<<(4*i-4)%(4*n)<<endl;
        t = t->next();
        cout<<"still working4"<<endl;
        h->next() = vh[4*i];
        cout<<"still working5"<<endl;
    }
    
    f->halfedge() = vh[2];
    
    
    
  // TODO This method should replace the face f with an additional, inset face
  // (and ring of faces around it), corresponding to a bevel operation. It
  // should return the new face.  NOTE: This method is responsible for updating
  // the *connectivity* of the mesh only---it does not need to update the vertex
  // positions.  These positions will be updated in
  // HalfedgeMesh::bevelFaceComputeNewPositions (which you also have to
  // implement!)

  return f;
}


void HalfedgeMesh::bevelFaceComputeNewPositions(
    vector<Vector3D>& originalVertexPositions,
    vector<HalfedgeIter>& newHalfedges, double normalShift,
    double tangentialInset) {
  // TODO Compute new vertex positions for the vertices of the beveled face.
  //
  // These vertices can be accessed via newHalfedges[i]->vertex()->position for
  // i = 1, ..., newHalfedges.size()-1.
  //
  // The basic strategy here is to loop over the list of outgoing halfedges,
  // and use the preceding and next vertex position from the original mesh
  // (in the originalVertexPositions array) to compute an offset vertex
  // position.
  //
  // Note that there is a 1-to-1 correspondence between halfedges in
  // newHalfedges and vertex positions
  // in orig.  So, you can write loops of the form
  //
  // for( int i = 0; i < newHalfedges.size(); hs++ )
  // {
  //    Vector3D pi = originalVertexPositions[i]; // get the original vertex
  //    position correponding to vertex i
  // }
  //
    FaceIter f = newHalfedges[0]->twin()->next()->twin()->face();
    Vector3D norm = f->normal();
    Vector3D cent = f->centroid();
    for( int i = 0; i < newHalfedges.size(); i++ )
    {
        Vector3D pi = originalVertexPositions[i]; // get the original vertex
        
        newHalfedges[i]->vertex()->position = newHalfedges[i]->vertex()->position + norm*normalShift+(cent-pi)*tangentialInset;
    }
}

void HalfedgeMesh::bevelVertexComputeNewPositions(
    Vector3D originalVertexPosition, vector<HalfedgeIter>& newHalfedges,
    double tangentialInset) {
  // TODO Compute new vertex positions for the vertices of the beveled vertex.
  //
  // These vertices can be accessed via newHalfedges[i]->vertex()->position for
  // i = 1, ..., hs.size()-1.
  //
  // The basic strategy here is to loop over the list of outgoing halfedges,
  // and use the preceding and next vertex position from the original mesh
  // (in the orig array) to compute an offset vertex position.

}

void HalfedgeMesh::bevelEdgeComputeNewPositions(
    vector<Vector3D>& originalVertexPositions,
    vector<HalfedgeIter>& newHalfedges, double tangentialInset) {
  // TODO Compute new vertex positions for the vertices of the beveled edge.
  //
  // These vertices can be accessed via newHalfedges[i]->vertex()->position for
  // i = 1, ..., newHalfedges.size()-1.
  //
  // The basic strategy here is to loop over the list of outgoing halfedges,
  // and use the preceding and next vertex position from the original mesh
  // (in the orig array) to compute an offset vertex position.
  //
  // Note that there is a 1-to-1 correspondence between halfedges in
  // newHalfedges and vertex positions
  // in orig.  So, you can write loops of the form
  //
  // for( int i = 0; i < newHalfedges.size(); i++ )
  // {
  //    Vector3D pi = originalVertexPositions[i]; // get the original vertex
  //    position correponding to vertex i
  // }
  //

}

void HalfedgeMesh::splitPolygons(vector<FaceIter>& fcs) {
  for (auto f : fcs) splitPolygon(f);
}

void HalfedgeMesh::splitPolygon(FaceIter f) {
    
    int n = f->degree();
    
    HalfedgeIter h0 = f->halfedge();
    VertexIter v0 = h0->vertex();
    HalfedgeIter t = h0;
    HalfedgeIter temp = h0;
    if (n == 3){return;}
    
    
    
    vector<HalfedgeIter> vh;
    vector<FaceIter> vf;
    vector<EdgeIter> ve;
    
    for (int i = 0; i<(n-3); i++){
        //allocate space for new edges, faces and halfedges
        vh.push_back(newHalfedge());
        vh.push_back(newHalfedge());
        vf.push_back(newFace());
        ve.push_back(newEdge());
    }
    //set the initial face's halfedges to h0
    f->halfedge() = h0;
    
    //the last h in polygon
    while (t->next()!=h0) {
        t = t->next();
    }
    
    temp = h0->next()->next();
    //for i==0
    
    vf[0]->halfedge() = vh[0];
    ve[0]->halfedge() = vh[0];
    vh[0]->setNeighbors(h0->next()->next(), vh[1], v0, ve[0], vf[0]);
    vh[1]->setNeighbors(h0, vh[0], h0->next()->next()->vertex(), ve[0], f);
    h0->next()->next()=vh[1];
    t->next() = vh[0];
    t->face() = vf[0];
    h0->next()->next()->face() = vf[0];
    
    
    for (int i = 1; i<(n-3); i++){
        //allocate space for new edges, faces and halfedges
        h0=temp;
        vf[i]->halfedge() = vh[2*i];
        ve[i]->halfedge() = vh[2*i];
        vh[2*i]->setNeighbors(h0->next(), vh[2*i+1], v0, ve[i], vf[i]);
        vh[2*i+1]->setNeighbors(vh[2*i-2], vh[2*i], h0->next()->vertex(), ve[i], vf[i-1]);
        h0->next()->face() = vf[i];
        t->face() = vf[i];
        t->next() = vh[2*i];
        temp = h0->next();
        h0->next() = vh[2*i+1];
    }
    
    
  // TODO: (meshedit) 
  // Triangulate a polygonal face
  
}
    

EdgeRecord::EdgeRecord(EdgeIter& _edge) : edge(_edge) {
  // TODO: (meshEdit)
  // Compute the combined quadric from the edge endpoints.
  // -> Build the 3x3 linear system whose solution minimizes the quadric error
  //    associated with these two endpoints.
  // -> Use this system to solve for the optimal position, and store it in
  //    EdgeRecord::optimalPoint.
  // -> Also store the cost associated with collapsing this edg in
  //    EdgeRecord::Cost.
}

void MeshResampler::upsample(HalfedgeMesh& mesh)
// This routine should increase the number of triangles in the mesh using Loop
// subdivision.
{
  // TODO: (meshEdit)
  // Compute new positions for all the vertices in the input mesh, using
  // the Loop subdivision rule, and store them in Vertex::newPosition.
  // -> At this point, we also want to mark each vertex as being a vertex of the
  //    original mesh.
  // -> Next, compute the updated vertex positions associated with edges, and
  //    store it in Edge::newPosition.
  // -> Next, we're going to split every edge in the mesh, in any order.  For
  //    future reference, we're also going to store some information about which
  //    subdivided edges come from splitting an edge in the original mesh, and
  //    which edges are new, by setting the flat Edge::isNew. Note that in this
  //    loop, we only want to iterate over edges of the original mesh.
  //    Otherwise, we'll end up splitting edges that we just split (and the
  //    loop will never end!)
  // -> Now flip any new edge that connects an old and new vertex.
  // -> Finally, copy the new vertex positions into final Vertex::position.

  // Each vertex and edge of the original surface can be associated with a
  // vertex in the new (subdivided) surface.
  // Therefore, our strategy for computing the subdivided vertex locations is to
  // *first* compute the new positions
  // using the connectity of the original (coarse) mesh; navigating this mesh
  // will be much easier than navigating
  // the new subdivided (fine) mesh, which has more elements to traverse.  We
  // will then assign vertex positions in
  // the new mesh based on the values we computed for the original mesh.
    
    
    
    
    
    
    //Mark all vertices as belonging to the original mesh by setting Vertex::isNew to false for all vertices in the mesh.
    
    //Compute updated positions for all vertices in the original mesh using the vertex subdivision rule, and store them in Vertex::newPosition.
    
    for (VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++){
        double u;
        double n = (double)(v->degree());
        
        if (v->degree() == 3){
            u = 3. / 16.;
        }
        else{
            u = 3. / (8.*n);
        }

        v->newPosition = (1. - n*u)*v->position + (u*n)*v->neighborhoodCentroid();
        v->isNew = false;
    }
    
    //Compute new positions associated with the vertices that will be inserted at edge midpoints, and store them in Edge::newPosition.
    for (EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); ++e){
        Vector3D A = e->halfedge()->vertex()->position;
        Vector3D B = e->halfedge()->twin()->vertex()->position;
        Vector3D C = e->halfedge()->next()->next()->vertex()->position;
        Vector3D D;
        if (e->isBoundary()){
            D = C;
        }
        else{
            D = e->halfedge()->twin()->next()->next()->vertex()->position;
        }
        e->newPosition = (3. / 8.)*(A+B) + (1. / 8.)* (C+D);
        e->isNew = false;
    }
    
    //Split every edge in the mesh, being careful about how the loop is written. In particular, you should make sure to iterate only over edges of the original mesh. Otherwise, the loop will keep splitting edges that you just created!
    
    
    VertexIter v_temp;
    
    HalfedgeIter he_temp;
    Vector3D e_new_pos_hold;
    vector<EdgeIter> original_edges;
    
    int n = mesh.nEdges();
    EdgeIter e = mesh.edgesBegin();
    for (int i = 0; i<n; i++){
        EdgeIter e_next = e;
        e_next++;
        if (e->isNew == false && e->isBoundary()==false){
            e_new_pos_hold = e->newPosition;
            v_temp = mesh.splitEdge(e);
            v_temp->newPosition = e->newPosition;
            v_temp->isNew = true;
            
            he_temp = v_temp->halfedge();
            
            do {
                he_temp->edge()->isNew = true;
                he_temp = he_temp->twin()->next();
                
            } while (he_temp != v_temp->halfedge());
            original_edges.push_back(v_temp->halfedge()->edge());
            original_edges.push_back(v_temp->halfedge()->twin()->next()->twin()->next()->edge());
        }
        e = e_next;
    }
    
    for (int i = 0; i<original_edges.size(); i++){
        original_edges[i]->isNew = false;
    }

    //Flip any new edge that connects an old and new vertex.
    
    n = mesh.nEdges();
    e = mesh.edgesBegin();
    for (int i = 0; i<n; i++){
        EdgeIter e_next = e;
        e_next++;
        if ((e->isNew == true) && ((e->halfedge()->vertex()->isNew == true && e->halfedge()->twin()->vertex()->isNew == false) || (e->halfedge()->vertex()->isNew == false && e->halfedge()->twin()->vertex()->isNew == true))){
            e_next = mesh.flipEdge(e);
            
        }
        e = e_next;
    }
    
    //copy the new vertex positions (Vertex::newPosition)into the usual vertex positions (Vertex::position).
    for (VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); ++v){
        v->position = v->newPosition;
    }
    
}

void MeshResampler::downsample(HalfedgeMesh& mesh) {
  // TODO: (meshEdit)
  // Compute initial quadrics for each face by simply writing the plane equation
  // for the face in homogeneous coordinates. These quadrics should be stored
  // in Face::quadric
  // -> Compute an initial quadric for each vertex as the sum of the quadrics
  //    associated with the incident faces, storing it in Vertex::quadric
  // -> Build a priority queue of edges according to their quadric error cost,
  //    i.e., by building an EdgeRecord for each edge and sticking it in the
  //    queue.
  // -> Until we reach the target edge budget, collapse the best edge. Remember
  //    to remove from the queue any edge that touches the collapsing edge
  //    BEFORE it gets collapsed, and add back into the queue any edge touching
  //    the collapsed vertex AFTER it's been collapsed. Also remember to assign
  //    a quadric to the collapsed vertex, and to pop the collapsed edge off the
  //    top of the queue.
  showError("downsample() not implemented.");
}

void MeshResampler::resample(HalfedgeMesh& mesh) {
  // TODO: (meshEdit)
  // Compute the mean edge length.
  // Repeat the four main steps for 5 or 6 iterations
  // -> Split edges much longer than the target length (being careful about
  //    how the loop is written!)
  // -> Collapse edges much shorter than the target length.  Here we need to
  //    be EXTRA careful about advancing the loop, because many edges may have
  //    been destroyed by a collapse (which ones?)
  // -> Now flip each edge if it improves vertex degree
  // -> Finally, apply some tangential smoothing to the vertex positions
  showError("resample() not implemented.");
}

}  // namespace CMU462
