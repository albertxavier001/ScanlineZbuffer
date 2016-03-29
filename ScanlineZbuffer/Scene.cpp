#include "Scene.h"


Scene::Scene() :/*light(fvec("1.0; 1.0; 1.0")),*/ cam(Camera())
{
	mesh.f.resize(0,0,3);
	light.at(0) = 1.f;
	light.at(1) = 1.f;
	light.at(2) = 1.f;
	light.at(3) = 1.f;
}


Scene::~Scene()
{
}

void Scene::loadScene(string fileName)
{
	fstream fin(fileName);
	if (!fin.is_open()) {
		cout << "Error: Cannot open file" << endl;
		getchar();
		exit(1);
	}

	string oneline;
	string type;
	while (getline(fin, oneline)) {
		parseLine(oneline);
	}
	mesh.f -= 1.0;
	assignNormal();

	///xxx
	cam.w = cam.image.at(0);
	cam.h = cam.image.at(1);
	cam.wcs2ccsMatrix = hp.getLookatMatrix(cam.eye, cam.look, cam.up);
	cam.ccs2viewMatrix = hp.perspectiveMatrix(cam.fov, 0.001f, 300.f);

	mesh.v = join_vert(mesh.v, ones<fmat>(1, mesh.v.n_cols));
	mesh.n = join_vert(mesh.n, ones<fmat>(1, mesh.n.n_cols));
}

void Scene::assignNormal()
{
	mesh.n.resize(3, mesh.f.n_cols);
	for (int i = 0; i < mesh.f.n_cols ; i++) 
	{
		int ind0 = mesh.f.at(0, i, 0);
		int ind1 = mesh.f.at(1, i, 0);
		int ind2 = mesh.f.at(2, i, 0);
		fvec3 v0 = mesh.v.col(ind0);
		fvec3 v1 = mesh.v.col(ind1);
		fvec3 v2 = mesh.v.col(ind2);
		fvec3 v  = normalise(cross(v0 - v1, v0 - v2));
		mesh.n.col(i) = v;
	}
}

void Scene::parseLine(const string &oneline){
	fmat  &v = mesh.v;
	fmat  &n = mesh.n;
	icube &f = mesh.f;
	
	stringstream ss(oneline);
	string key, val;
	ss >> key;
	
	/// camera
	if (key == "eye")
	{
		ss >> cam.eye.at(0) >> cam.eye.at(1) >> cam.eye.at(2);
		cam.eye.print("eye");
	}
	
	if (key == "look")
		ss >> cam.look.at(0) >> cam.look.at(1) >> cam.look.at(2);
	
	if (key == "up") 
		ss >> cam.up.at(0) >> cam.up.at(1) >> cam.up.at(2);
	
	if (key == "image") {
		ss >> cam.image.at(0) >> cam.image.at(1);
		
	}
	if (key == "fov")
		ss >> cam.fov;
	
	/// light
	if (key == "light")
		ss >> light.at(0) >> light.at(1) >> light.at(2);

	/// mesh
	/// vertex
	if (key == "v") {
		v.resize(3, v.n_cols + 1);
		ss 
			>> v.at(0, v.n_cols - 1)
			>> v.at(1, v.n_cols - 1)
			>> v.at(2, v.n_cols - 1);
	}
	/// normal
	if (key == "vn") {
		n.resize(3, n.n_cols + 1);
		ss
			>> n.at(0, n.n_cols - 1)
			>> n.at(1, n.n_cols - 1)
			>> n.at(2, n.n_cols - 1);
	}
	/// face(temp)
	if (key == "f") {
		///add one more column
		f.resize(3, f.n_cols + 1, 3);
		string str = ss.str();
		int cntSlash = count(str.begin(), str.end(), '/');
		switch (cntSlash) {
		case 0: {
			/// vertex only
			/// vertex index+1
			ss
				>> f.at(0, f.n_cols - 1, 0)
				>> f.at(1, f.n_cols - 1, 0)
				>> f.at(2, f.n_cols - 1, 0);
			f.slice(1).col(f.n_cols - 1).fill(0);
			f.slice(2).col(f.n_cols - 1).fill(0);
			break;
		}
		case 3: {
			replace(ss.str().begin(), ss.str().begin(), '/', ' ');
			/// vertex index+1
			/// normal index+1
			ss
				>> f.at(0, f.n_cols - 1, 0)
				>> f.at(0, f.n_cols - 1, 1)
				>> f.at(1, f.n_cols - 1, 0)
				>> f.at(1, f.n_cols - 1, 1)
				>> f.at(2, f.n_cols - 1, 0)
				>> f.at(2, f.n_cols - 1, 1);
			f.slice(2).col(f.n_cols - 1).fill(0);
			break;
		}
		case 6: {
			replace(ss.str().begin(), ss.str().begin(), '/', ' ');
			/// vertex index+1
			/// normal index+1
			/// textur index+1
			ss
				>> f.at(0, f.n_cols - 1, 0)
				>> f.at(0, f.n_cols - 1, 1)
				>> f.at(0, f.n_cols - 1, 2)
				>> f.at(1, f.n_cols - 1, 0)
				>> f.at(1, f.n_cols - 1, 1)
				>> f.at(1, f.n_cols - 1, 2)
				>> f.at(2, f.n_cols - 1, 0)
				>> f.at(2, f.n_cols - 1, 1)
				>> f.at(2, f.n_cols - 1, 2);
			break;
		}
		default: break;
		}
	}
}
