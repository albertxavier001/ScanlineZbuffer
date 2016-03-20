#include "Scene.h"


Scene::Scene() :light(fvec("1.0; 1.0; 1.0")), cam(Camera())
{
	mesh.f.resize(0,0,3);
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
		ss >> cam.eye.at(0) >> cam.eye.at(1) >> cam.eye.at(2);
	
	if (key == "look")
		ss >> cam.look.at(0) >> cam.look.at(1) >> cam.look.at(2);
	
	if (key == "up") 
		ss >> cam.up.at(0) >> cam.up.at(1) >> cam.up.at(2);
	
	if (key == "image") 
		ss >> cam.image.at(0) >> cam.image.at(1);

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
		f.resize(3, f.n_cols + 1, f.n_slices);
		int cntSlash = count(ss.str().begin(), ss.str().end(), '/');
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
	/// 

}
